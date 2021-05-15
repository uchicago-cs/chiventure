
import sys
from lark import Lark, Visitor
import json

grammar_f = open("dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

d = {}
d["ROOMS"] = []
d["ITEMS"] = []

def id(c, dict):
    dict["id"] = ' '.join(c.children[0].children)
    return dict["id"]

def property(c, dict):
    desc = ' '.join(c.children[0].children)
    dict[desc] = c.children[1][1:-1]

def room_connection(c, room):
    connections = []
    for conn in c.children:
        connections.append(dict(to = ' '.join(conn.children[1].children), 
                                direction = conn.children[0].children[0]))
    room["connections"] = connections

def room_item(c, room_id):
    item = {}
    for c in c.children:
        if c.data == 'id':
            id(c, item)
        elif c.data == 'property':
            property(c, item)
    item["in"] = room_id
    d["ITEMS"].append(item)


class TreeToDict(Visitor):
    def game(self, s):
        game = {}
        game["start"] = ' '.join(s.children[0].children[0].children)
        game["intro"] = s.children[2].children[1][1:-1]
        game["end"] = ' '.join(s.children[1].children[0].children)
        d["GAME"] = game
    
    def room(self, s):
        room = {}
        for c in s.children:
            if c.data == 'id':
                room_id = id(c, room)
            elif c.data == 'property':
                property(c, room)
            elif c.data == 'connections':
                room_connection(c, room)
            elif c.data == 'item':
                room_item(c, room_id)
        d["ROOMS"].append(room)
    


parser = Lark(dsl_grammar, parser='lalr')
 
def main():
    with open(sys.argv[1]) as f:
        tree = parser.parse(f.read())
        print(tree.pretty())
        TreeToDict().visit(tree)
        print(json.dumps(d, indent=2))

if __name__ == '__main__':
    main()