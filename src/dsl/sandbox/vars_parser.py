from lark.lexer import Token
from lark import Lark, Transformer

grammar_f = open("vars.lark")
vars_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(vars_grammar, parser='earley')

def evalVars(file: str) -> str:
    tree = parser.parse(file)
    out = SimplifyTree().transform(tree)
    assert(type(out) == str)
    return out


def evalParsedVars(parsed: list[tuple[str, str]], vars: dict[str, str]) -> str:
  out = []
  for token_type, val in parsed:
    if token_type == "reference":
      out.append(vars[val])
    elif token_type == "string":
      out.append(val)
  return "".join(out)

class SimplifyTree(Transformer):
  def start(self, s: list) -> str:
    vars = dict(v for k,v in s if k == "assignment")
    return evalParsedVars(s, vars)

  def assignment(self, s: list) -> tuple[str, str]:
    return ("assignment", tuple(s))

  def reference(self,s: list) -> tuple[str, str]:
    return ("reference", s[0])
    
  def assignment_inner(self, s: list) -> str:
    return str(s[0])
  
  def other(self, s: list) -> tuple[str, str]:
    return ("string", str(s[0]))
  
  def CNAME(self, s: list) -> str:
    return str(s)

  def ESCAPED_STRING(self, s: list) -> str:
      # we want to leave characters unaltered so that the dsl parser can handle them
      return str(s)