from lark.lexer import Token
from lark import Lark, Transformer
from pathlib import Path
from functools import partial

base_path = Path(__file__).parent
grammar_f = open(base_path / "vars.lark")
vars_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(vars_grammar, parser='earley')

# main outward-facing function
def evalVars(file: str, debug=False) -> str:
    """Replaces the references to variables in a file with their assigned values"""
    tree = parser.parse(file)
    if debug: 
      print(tree.pretty())
    out = SimplifyTree().transform(tree)
    assert(type(out) == str)
    return out



def evalParsedVars(parsed: list[tuple[str, str]], vars: dict[str, str]) -> str:
  """
    Takes a list of tuples of form (type, value). For all variables, it 
    replaces the variable with its value according to the vars dict
  """
  out = []
  for token_type, val in parsed:
    if token_type == "reference":
      name, replacements = val
      out.append(vars[name](replacements))
    elif token_type == "string":
      out.append(val)
  return "".join(out)

def evalStringTemplates(components: list[tuple[str, str]], values: dict[str, str]) -> str:
  """
    Evaluates template strings. Takes in list of type-value tuples, and replaces
    items of type var with their values. 
  """
  out = ""
  for val_type, value in components:
    if val_type == "string":
      out += value
    elif val_type == "var":
      assert value in values, f"Expected {value} to be in values dict"
      out += values[value]
  return out
  


class SimplifyTree(Transformer):
  def start(self, s: list) -> str:
    """
      Takes in a list with type-value tuples, and appropriately evaluates them
    """
    vars = dict(v for k,v in s if k == "assignment")
    return evalParsedVars(s, vars)

  def assignment(self, s: list[str, str]) -> tuple[str, str]:
    """
      Takes the name of the variable and a template string. Outputs a function
      which returns a string when given the unassigned variables as inputs.
    """
    name, components = s
    template_func = partial(evalStringTemplates, components)
    return ("assignment", [name, template_func])

  def reference(self,s: list[str]) -> tuple[str, str]:
    """
      labels the reference, and associates the variable name with a dictionary 
      for the text replacements
    """
    var_name = s[0]
    replacements = dict(s[1:])
    return ("reference", (var_name, replacements))
  
  def var(self, s: list[str]) -> tuple[str, str]:
    """labels the variable name as a variable"""
    return ("var", s[0])
    
  def assignment_inner(self, s: list[Token]) -> str:
    """Extracts the string from a singleton list of tokens"""
    return ("string", str(s[0]))
  
  def escaped_char(self, s: list[Token]) -> tuple[str, str]:
    """Extracts the escaped character from a token and labels it as a string"""
    return ("string", "\\" + str(s[0]))
  
  def other(self, s: list[Token]) -> tuple[str, str]:
    """Extracts the string from a singleton list of tokens, and labels it as a string"""
    return ("string", str(s[0]))
  
  # these functions return their input
  escaped_string_with_vars = lambda _, x: x
  triple_quotes = lambda _, x: x

  
  def CNAME(self, s: Token) -> str:
    """Extracts the string from a token"""
    return str(s)
    
  def keyval(self, s: list[str, str]) -> tuple[str, str]:
    # remove the quotes from the string, but don't evaluate escape characters
    return tuple([s[0], s[1][1:-1]])
    

  def phrase(self, s: list[Token]) -> str:
      """Concatenates the strings contained within a list of tokens"""
      return ' '.join(s)

  def ESCAPED_STRING(self, s: Token) -> str:
      # we want to leave characters unaltered so that the dsl parser can handle them
      return str(s)