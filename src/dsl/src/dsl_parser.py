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
    def game(self, s):
        """
        S contains several objects of the form ('type', <value>), where
        value is dependent upon the type. This function creates a dictionary
        based on the type, and also places all rooms into their own 
        dictionary for convenience.
        """

        # first place all non-room objects into a dict
        # k and v represent key-value pairs of any kind such as property-value or
        # item and item attributes, etc.
        game_dictionary = dict((k, v) for k, v in s if k != "ROOM")

        # now place all rooms into their own dictionary
        # the values placed into this entry will correspond to room attributes
        game_dictionary["rooms"] = dict([value for key_type, value in s if key_type == "ROOM"])
        return game_dictionary

    # s contains several objects of the form ('type', <value>) and
    # we want to group all objects with type "ITEM" into their own list
    def room(self, s: list) -> tuple[str, tuple[str, dict]]:
        """
        S contains several objects of the form ('type', <value>), where
        value is dependent upon the type. This function creates a dictionary
        based on the key or type, and also places all items into their own list
        for convenience.
        """
        room_id = s.pop(0)[1]

        # first place all non-item objects into a dict
        # k and v represent key-value pairs of any kind such as property-value pairs or
        # action and action attributes, etc.
        d = dict((k, v) for k, v in s if k != "ITEM")

        # create a list of items and place it in its own entry of the dict
        # the values placed into this entry will correspond to item attributes
        d["items"] = list([v for k, v in s if k == "ITEM"])
        return ('ROOM', (room_id, d))

    def connections(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """Takes a list of room-direction string pairs and outputs a dictionary
        labeled as "connections"""
        return ("connections", dict(s))

    def item(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """Takes a list of key-value pairs which belong to an item and places them
        into a dictionary which is labeled "ITEM" """
        return ('ITEM', dict(s))

    def action(self, s: list) -> tuple[str, tuple[str, dict]]:
        """S contains a list of key-value pairs. The first element will be a list of action ids, while the
        rest will be properties that correspond to specific actions. This function associates properties
        with the appropriate action in the form of a dictionary"""
        
        # action_ids is a list of strings
        action_ids = s.pop(0)[1]
        
        # actions_properties is a list with items of the form ("OPEN SUCCESS", "you opened the door")
        action_properties = s[1:]
        
        actions_dictionary = {}
        
        # match action properties to the action name
        for action in action_ids:
            action_dict = {}
            for action_property in action_properties:
                name, value = action_property
                # an example name would be "OPEN success"
                
                # match name to the action name
                if action == name[:len(action)]:
                    # extract the "success" from "OPEN success"
                    property_name = name[len(action):]
                    
                    # remove whitespace
                    property_name = property_name.strip()
                    
                    action_dict[property_name] = value
            actions_dictionary[action] = action_dict
        return ("actions", actions_dictionary)

    # the functions below do simple transformations

    def ESCAPED_STRING(self, s: Token) -> str:
        """replace escaped characters with unicode equivalents"""
        decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
        return decoded

    def start_g(self, s: list[str]) -> tuple[str, str]:
        """Labels the start location as "start" """
        return ("start", s[0])

    def end_g(self, s: list[str]) -> tuple[str, str]:
        """labels the end location as "end" """
        return ("end", s[0])

    def id(self, s: list[str]) -> tuple[str, str]:
        """labels the id as an id"""
        return ("id", s[0])

    def action_ids(self, s: list[tuple[str, str]]):
        """Takes a list of ("id", <str>) pairs corresponding to action ids, and
        extracts the action ids into a list. This list is then labelled as
        "action_ids" """
        action_names = [name for _, name in s]
        return ("action_ids", action_names)

    def location(self, s: list[str]) -> tuple[str, str]:
        """Labels the location as a location"""
        return ("location", s[0])

    def phrase(self, s: list[Token]) -> str:
        """Joins a list of strings contained within token objects"""
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
