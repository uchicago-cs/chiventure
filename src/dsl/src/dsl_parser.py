import sys
from lark import Lark, Transformer
from lark.lexer import Token
import json
from pathlib import Path

base_path = Path(__file__).parent
grammar_f = open(base_path / "dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

class TreeToDict(Transformer):
    # we have several objects of the form ('type', <value>) and
    # we want to group all objects with type "ROOM" into their own list
    def game(self, s):
        # first place all non-room objects into a dict
        d = dict((k,v) for k,v in s if k != "ROOM")
        
        # now place all rooms into their own dictionary
        d["rooms"] = dict([v for k,v in s if k == "ROOM"])
        return d

    # we have several objects of the form ('type', <value>) and
    # we want to group all objects with type "ITEM" into their own list
    def room(self, s: list) -> tuple[str, tuple[str, dict]]:
        room_id = s.pop(0)[1]

        # first place all non-item objects into a dict
        d = dict((k,v) for k,v in s if k != "ITEM")

        # create a list of items and place in its own entry of the dict
        d["items"] = list([v for k,v in s if k == "ITEM"])
        return ('ROOM', (room_id, d))

    def connections(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        return ("connections", dict(s))

    def item(self, s: list[tuple[str,str]]) -> tuple[str, dict]:
        return ('ITEM', dict(s))

    def action(self, s: list) -> tuple[str, tuple[str, dict]]:
        action_id = s.pop(0)[1]
        return ('action', (action_id, dict(s)))

    # the functions below do simple transformations

    def ESCAPED_STRING(self, s: Token) -> str:
        # replace escaped characters with unicode characters
        decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
        return decoded
    def start_g(self, s: list[str]) -> tuple[str, str]:
        return ("start", s[0])

    def end_g(self, s: list[str]) -> tuple[str, str]:
        return ("end", s[0])

    def id(self, s: list[str]) -> tuple[str, str]:
        return ("id", s[0])

    def location(self, s):
        return ("location", s[0])
    def phrase(self, s: list[Token]) -> str:
        return ' '.join(s)

    connection = tuple
    property = tuple


parser = Lark(dsl_grammar, parser='earley')

def main():
    with open(sys.argv[1]) as f:
        file_str = f.read()
        
        tree = parser.parse(file_str)
        print(json.dumps(TreeToDict().transform(tree), indent=2))

        

if __name__ == '__main__':
    main()
