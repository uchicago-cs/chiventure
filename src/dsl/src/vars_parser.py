"""This module evaluates references to variables in a dsl file."""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

from lark.lexer import Token
from lark import Lark, Transformer
from pathlib import Path
from functools import partial

grammar_path = Path(__file__).parent.parent / "grammars"
grammar_f = open(grammar_path / "vars.lark")
vars_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(vars_grammar, parser='earley', import_paths=[grammar_path])

# main outward-facing function
def evalVars(file: str, debug=False, debug_modes=[]) -> str:
    """Replaces the references to variables in a file with their assigned values"""
    tree = parser.parse(file)
    if debug and "vars-tree" in debug_modes:
        print(tree.pretty())
    out = SimplifyTree().transform(tree)
    assert(type(out) == str)
    if debug and "vars" in debug_modes:
        print(out)
    return out


def evalParsedVars(parsed: list[tuple[str, str]], vars: dict[str, str]) -> str:
    """
      Takes a list of tuples of form (type: str, value). For all variables, it 
      replaces the variable with its value according to the vars dict
    """
    out = []
    for token_type, val in parsed:
        if token_type == "reference":
            name, replacements = val
            # vars[name] is a function which outputs a string when given
            # the replacements dict as an input
            out.append(vars[name](replacements))
        elif token_type == "string":
            out.append(val)
    return "".join(out)


def evalStringTemplates(components: list[tuple[str, str]], values: dict) -> str:
    """
      Evaluates string templates. Takes in list of type-value tuples, and replaces
      items of type var with their values stored in the values dict. 
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
        
        # key_type will always be a string, while v is dependent on key_type
        vars = dict(v for key_type, v in s if key_type == "assignment")
        return evalParsedVars(s, vars)

    def assignment(self, s: list[str, str]) -> tuple:
        """
          Takes the name of the variable and a string template contained in the
          input s. Labels the output as assignment, and associates the variable
          name with a function which returns a string when given the unassigned
          inner variables as inputs.
        """

        name, components = s
        
        # template_func is a function which maps a variable assignment
        # dictionary to a string
        template_func = partial(evalStringTemplates, components)
        return ("assignment", (name, template_func))

    def reference(self, s: list) -> tuple[str, str]:
        """
          labels the reference to a variable, and creates a dictionary 
          associating each in-text variable name with its replacement
        """

        # the name of the entire variable (a string) is always the first 
        # element in s
        var_name = s.pop(0)
        
        # the remaining elements in s are key-value pairs denoting what each of
        # the variables should be replaced with (e.g. ("name", "John"))
        replacements = dict(s)
        return ("reference", (var_name, replacements))

    def var(self, s: list[str]) -> tuple[str, str]:
        """labels the variable name as a variable"""
        return ("var", s[0])

    def assignment_inner(self, s: list[Token]) -> str:
        """Concatenates the strings in all tokens and labels it"""
        return ("string", ''.join([str(t) for t in s]))

    def escaped_char(self, s: list[Token]) -> tuple[str, str]:
        """Extracts the escaped character from a singleton token list and labels
        it as a string"""
        return ("string", "\\" + str(s[0]))

    def other(self, s: list[Token]) -> tuple[str, str]:
        """Extracts the string from a singleton list of tokens, and labels it as
        a string"""
        return ("string", str(s[0]))

    # this functions return its input
    def triple_quotes(_, x): return x

    def escaped_string_with_vars(self, s: list[tuple[str, str]]) -> list[tuple[str, str]]:
        """S is a template for a string, meaning it contains (key, value) pairs
        where the key is either "string" or "var" and the value is a string. 
        This functions adds quotes around the template for an escaped string 
        with variables."""
        quote_tuple = [("string", "\"")]
        return quote_tuple + s + quote_tuple

    def CNAME(self, s: Token) -> str:
        """Extracts the string from a token"""
        return str(s)

    def keyval(self, s: list[str, str]) -> tuple[str, str]:
        """The first element of s is the key, while the second element is the
        value. This function transforms s into a tuple."""
        return tuple([s[0], s[1]])

    def phrase(self, s: list[Token]) -> str:
        """Concatenates the strings contained within a list of tokens"""
        return ' '.join(s)

    def ESCAPED_STRING(self, s: Token) -> str:
        """Extracts the a string from a token and removes the quotes, but leaves
        the escaped characters unaltered so that the dsl parser can handle them."""
        return str(s[1:-1])
