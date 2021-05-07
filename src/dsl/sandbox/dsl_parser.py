# https://github.com/uchicago-cs/chiventure/wiki/DSL:-User-Stories

import sys
from lark import Lark, Transformer
import json

grammar_f = open("dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

class TreeToDict(Transformer):
    """Transform the parsing tree into a dictionary"""
    def string(self, s):
        (s,) = s
        return str(s)

    def util__escaped_string(self, s):
        (s,) = s
        return s[1:-1]

    def phrase(self, s):
        return ' '.join(s)

    def start_g(self, s):
        (s,) = s
        return ("start", s)

    def end_g(self, s):
        (s,) = s
        return ("end", s)

    def id(self, s):
        (s,) = s
        return ("id", s)

    def location(self, s):
        (s,) = s
        return ("location", s)

    def DIRECTION(self, s):
        print(s)
        return str(s)

    def connections(self, s):
        print(s)
        return ("connections", dict(s))
    def connection(self, s):
        print(tuple(s))
        return tuple(s)
    room = dict

    def properties(self, s):
        return ("properties", dict(s))

    def items(self, s):
        return ("items", list(s))

    def rooms(self, s):
        return ("rooms", list(s))
    property = tuple

    item = dict

    game = dict


parser = Lark(dsl_grammar, parser='lalr')

def main():
    with open(sys.argv[1]) as f:
        tree = parser.parse(f.read())
        print(tree.pretty())
        # print(TreeToDict().transform(tree))
        print(json.dumps(TreeToDict().transform(tree), indent=2))

        

if __name__ == '__main__':
    main()
