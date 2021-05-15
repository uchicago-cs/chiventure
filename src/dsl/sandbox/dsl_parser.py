import sys
from lark import Lark, Transformer
import json
from vars_parser import evalVars

grammar_f = open("dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

class TreeToDict(Transformer):
    def start_g(self, s):
        return ("start", s[0])
    def end_g(self, s):
        return ("end", s[0])
    def id(self, s):
        (s,) = s
        return ("id", s)
    def location(self, s):
        return ("location", s)

    connection = tuple
    property = tuple

    def phrase(self, s):
        return ' '.join(s)

    def ESCAPED_STRING(self, s):
      # replace escaped characters with unicode characters
      decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
      return decoded

    def connections(self, s):
        return ("connections", dict(s))

    def item(self, s):
        return ('ITEM', dict(s))

    # input is of the form [('id':value),<properties>]
    # output is of the form ("action", ("<action id>", <properties>))
    def action(self, s):
        action_id = s.pop(0)[1]
        return ('action', (action_id, dict(s)))

    # we have several objects of the form ('ITEM', <item dict>) and
    # we want to group all items into their own list
    def room(self, s):
        room_id = s.pop(0)[1]

        # first place all non-item objects into a dict
        d = dict((k,v) for k,v in s if k != "ITEM")

        d["items"] = list([v for k,v in s if k == "ITEM"])
        return ('ROOM', (room_id, d))
    
    # we have several objects of the form ('ROOM', (<room id>, <room properties>)) and
    # we want to group all rooms into their own dict of the form {<room id>: <room properties>}
    def game(self, s):
        d = {}
        for k,v in s:
            if k != "ROOM":
                d[k] = v
        d["rooms"] = dict([v for k,v in s if k == "ROOM"])
        return d

    

parser = Lark(dsl_grammar, parser='earley')

def main():
    with open(sys.argv[1]) as f:
        file_str = f.read()
        vars_evaluated = evalVars(file_str)
        
        tree = parser.parse(vars_evaluated)
        print(json.dumps(TreeToDict().transform(tree), indent=2))

        

if __name__ == '__main__':
    main()
