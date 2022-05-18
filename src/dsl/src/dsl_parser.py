"""This module parses a dsl file and outputs an intermediate stage"""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

from lark import Lark, Transformer
from lark.lexer import Token
from pathlib import Path
from warnings import warn
import json


grammar_path = Path(__file__).parent.parent / "grammars"
grammar_f = open(grammar_path / "dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(dsl_grammar, parser='earley', import_paths=[grammar_path])


# main outward-facing function
def export_dict(file_str, debug=False, debug_modes=[]):
    """Parses the language and returns an intermediate stage consisting
    of python dictionaries"""
    tree = parser.parse(file_str)
    if debug and "dsl-tree" in debug_modes:
        print(tree.pretty())
    intermediate = TreeToDict().transform(tree)
    if debug and "intermediate" in debug_modes:
        print(json.dumps(intermediate, indent=2))
    return intermediate


class TreeToDict(Transformer):
    def game(self, s: list) -> dict:
        """
        S contains several objects of the form ('type', <value>), where
        value is dependent upon the type. This function creates a dictionary
        based on the type, and also places all rooms into their own 
        dictionary for convenience.
        """

        # first place all non-room objects into a dict
        # k (a string) and v represent key-value pairs of any kind such as property-value or
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
        # k (a string) and v represent key-value pairs of any kind such as property-value pairs or
        # action and action attributes, etc.
        d = dict((k, v) for k, v in s if k != "ITEM")

        # create a list of items and place it in its own entry of the dict
        # the values placed into this entry will correspond to item attributes
        # since the key is guaranteed to be the string "ITEM"
        d["items"] = [v for k, v in s if k == "ITEM"]
        
        return ('ROOM', (room_id, d))
    
    # s contains several objects of the form ('type', <value>) and
    # we want to group all objects with type "attributes" and "base_stats" into their own list
    def player_class(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """
        S contains several objects of the form ('type', <value>), where
        value is dependent upon the type. This function creates a dictionary
        based on the key or type, and also places all items into their own list
        for convenience.
        """
        
        # gets the player class id.
        class_id = s.pop(0)[1]

        # first place all non-item objects into a dict
        # k (a string) and v represent key-value pairs of any kind such as property-value pairs or
        # action and action attributes, etc.
        d = dict((k, v) for k, v in s if k != "attributes" and k != "base_stats")

        # create a list of attributes and place it in its own entry of the dict
        # the values placed into this entry will correspond to item attributes
        # since the key is guaranteed to be the string "attributes"
        d["attributes"] = [v for k, v in s if k == "attributes"]

        # create a list of base_stats and place it in its own entry of the dict
        # the values placed into this entry will correspond to item attributes
        # since the key is guaranteed to be the string "base_stats"
        d["base_stats"] = [v for k, v in s if k == "base_stats"]
        
        return ('player_class', (class_id, d))

    # s contains several objects of the form ('type', <value>) and
    # we want to group all objects with type "attributes" and "base_stats" into their own list
    def npc(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """
        S contains several objects of the form ('type', <value>), where
        value is dependent upon the type. This function creates a dictionary
        based on the key or type, and also places all items into their own list
        for convenience.
        """
        
        # gets the player class id.
        name = s.pop(0)[1]

        # first place all non-item objects into a dict
        # k (a string) and v represent key-value pairs of any kind such as property-value pairs or
        # action and action attributes, etc.
        d = dict((k, v) for k, v in s if k != "inventory")

        # create a list of attributes and place it in its own entry of the dict
        # the values placed into this entry will correspond to item attributes
        # since the key is guaranteed to be the string "attributes"
        d["inventory"] = [v for k, v in s if k == "inventory"]
        
        return ('NPCS', (name, d))

    def inventory(self, s:list[tuple[str, str]]) -> tuple[str, dict]:
        """Takes a list of key-value pairs which belong to an attributes and places them
        into a dictionary which is labeled "attributes" """
        return ('inventory', dict(s))

    def attributes(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """Takes a list of key-value pairs which belong to an attributes and places them
        into a dictionary which is labeled "attributes" """
        return ('attributes', dict(s))

    def base_stats(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
        """Takes a list of key-value pairs which belong to an base_stats and places them
        into a dictionary which is labeled "base_stats" """
        return ('base_stats', dict(s))

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
        action_properties = s
        
        actions_dictionary = {}
        
        for action in action_ids:
            actions_dictionary[action] = {}
        for action_property in action_properties:
            name, value = action_property

            matched = False
            # match name to the action name
            for action in action_ids:
                if action == name[:len(action)]:
                    matched = True
                    # extract the "success" from "OPEN success"
                    property_name = name[len(action):]
                    
                    # remove whitespace
                    property_name = property_name.strip()
                    
                    actions_dictionary[action][property_name] = value
            if matched == False:
                warn(f"Unexpected object under actions will be ignored: {action_property}")
        return ("actions", actions_dictionary)
    
    def misplaced_property(self, s: list[Token]) -> str:
        raise Exception('"property FOR object" syntax is not yet supported')
    

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

