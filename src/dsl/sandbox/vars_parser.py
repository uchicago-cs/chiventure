from lark.lexer import Token
from lark import Lark, Transformer

grammar_f = open("vars.lark")
vars_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(vars_grammar, parser='earley')

def evalVars(file: str) -> str:
    tree = parser.parse(file)
    print(tree)
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
  return "\n".join(out)

class SimplifyTree(Transformer):
  def start(self, s: list[Token]):
    vars = dict(v for k,v in s if k == "assignment")
    return evalParsedVars(s, vars)

  def assignment(self, s: list[Token]) -> tuple[str, str]:
    return ("assignment", tuple(s))

  def reference(self,s):
    return ("reference", s[0])
    
  def assignment_inner(self, s: list[Token]) -> str:
    return str(s[0])

  def other(self, s: list[Token]) -> tuple[str, str]:
    return ("string", str(s[0]))
  
  def CNAME(self, s: list[Token]) -> str:
    return str(s)

  def ESCAPED_STRING(self, s: list[Token]) -> str:
      # replace escaped characters with unicode characters
      decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
      return decoded