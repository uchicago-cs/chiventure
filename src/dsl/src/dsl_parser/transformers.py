"""
This module contains definitions for transformers that convert 
DSL grammars to an intermediate stage

"""

from lark.lexer import Token
from warnings import warn
import warnings

def transform_game(self, s: list) -> dict:
    """
    S contains several objects of the form ('type', <value>), where
    value is dependent upon the type. This function creates a dictionary
    based on the type, and also places all rooms into their own 
    dictionary for convenience.
    """

    # first place all non-room objects (excluding playerclasses) into a dict
    # k (a string) and v represent key-value pairs of any kind such as property-value or
    # item and item attributes, etc.
    game_dictionary = dict((k, v) for k, v in s if k != "ROOM" and k != "PLAYER_CLASS")

    # now place all rooms into their own dictionary
    # the values placed into this entry will correspond to room attributes
    game_dictionary["rooms"] = dict([value for key_type, value in s if key_type == "ROOM"])
    # return game_dictionary

    # now place all player_class into their own dictionary
    # the values placed into this entry will correspond to player_class attributes
    game_dictionary["players"] = dict([value for key_type, value in s if key_type == "PLAYER_CLASS"])
    return game_dictionary


# s contains several objects of the form ('type', <value>) and
# we want to group all objects with type "attributes" and "base_stats" into their own list
def transform_player_class(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """
    S contains several objects of the form ('type', <value>), where
    value is dependent upon the type. This function creates a dictionary
    based on the key or type, and also places all items into their own list
    for convenience.
    """
    class_name = s.pop(0)[1]

    # first place all non-item objects into a dict
    # k (a string) and v represent key-value pairs of any kind such as property-value pairs or
    # action and action attributes, etc.
    d = dict((k, v) for k, v in s if k != "attributes" and k != 'base_stats')

    # create a list of items and place it in its own entry of the dict
    # the values placed into this entry will correspond to player class attributes
    # since the key is guaranteed to be the string "attributes"
    d["attributes"] = [v for k, v in s if k == "attributes"][0]

    # create a list of items and place it in its own entry of the dict
    # the values placed into this entry will correspond to player class base stats
    # since the key is guaranteed to be the string "base_stats"
    d["base_stats"] = [v for k, v in s if k == "base_stats"][0]
    
    return ('PLAYER_CLASS', (class_name, d))

# s contains several objects of the form ('type', <value>) and
# we want to group all objects with type "ITEM" into their own list
def transform_room(self, s: list) -> tuple[str, tuple[str, dict]]:
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


def transform_connections(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """Takes a list of room-direction string pairs and outputs a dictionary
    labeled as "connections"""
    return ("connections", dict(s))

def transform_item(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """Takes a list of key-value pairs which belong to an item and places them
    into a dictionary which is labeled "ITEM" """
    return ('ITEM', dict(s))


def transform_action(self, s: list) -> tuple[str, tuple[str, dict]]:
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

def transform_attributes(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """Takes a list of key-value pairs which belong to an attributes and places them
    into a dictionary which is labeled "attributes" """
    new_dict = {}
    for val in s:
        dic = val[1]
        name = list(dic.keys())[0]
        new_dict[name] = dic[name]
    return ('attributes', new_dict)

def transform_attribute_state(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """Takes a list of key-value pairs which belong to an attributes and places them
    into a dictionary which is labeled "attributes" """
    new_dict = {}
    new_dict[s[0]] = s[1]
    return ('attributes', new_dict)

def transform_base_stats(self, s: list[tuple[str, str]]) -> tuple[str, dict]:
    """Takes a list of key-value pairs which belong to an base_stats and places them
    into a dictionary which is labeled "base_stats" """
    return ('base_stats', dict(s))

def transform_stat_setting(self, s: list[tuple[str, Token]]) -> tuple[str, dict]:
    return('stat_setting', dict(s))

def transform_state(self, s: list[tuple[Token]]) -> tuple[str, dict]:
    count = 1
    d = {}
    for t in s:
        if count == 1:
            d["CURRENT"] = t[0]+t[1]
        elif count == 2:
            d["MAX"] = t[0]+t[1]
        count += 1
    return('state', d)

def transform_misplaced(self, s: list[Token]) -> str:
    raise Exception('"property FOR object" syntax is not yet supported')

