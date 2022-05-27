# This file contains the function parsed_dict_to_json
# Convert the intermediate data structure that is given by the LARK parser into a working WDL or JSON format.
import json
from warnings import warn
from collections import ChainMap

from to_wdl.wdl_room import Room
from to_wdl.wdl_item import Item
from to_wdl.wdl_game import Game
from to_wdl.wdl_player import Player_Class


def parsed_dict_to_json(intermediate: dict, debug=False, debug_modes=[], default="") -> str:
    """
        Main outward-facing function. Transforms the intermediate data 
        structure outputted by the parser into valid WDL/JSON format.
    """

    rooms = []
    items = []
    player_class = []

    if "rooms" not in intermediate:
        warn("This game has no rooms.")
    else:
        rooms_dict = intermediate.pop("rooms")
        for room_name, contents in rooms_dict.items():
            room_items = contents["items"]
            room_items_objs = []
            for item in room_items:
                location = room_name
                if "location" in item:
                    location = item.pop("location")
                item_obj = Item(location, item, default)
                items.append(item_obj)
                room_items_objs.append(item_obj)
            contents["items"] = room_items_objs
            rooms.append(Room(room_name, contents, default))
    
    if "player_class" not in intermediate:
        warn("This game has no players.")
    else:
        player_class_dict = intermediate.pop("player_class")
        for p_class, contents in player_class_dict.items():
            # player_class_ATTRIBUTES = content["attributes"]
            # player_class_BASESTATS = content["base_stats"]
            contents["attributes"] = []
            contents["base_stats"] = []
        
            # print("content: ", contents)
            player_class.append(Player_Class(p_class, contents, default))
    
    game = Game(intermediate, default)
    
    # acts as a "union" operation on multiple dictionaries
    rooms_wdl = dict(ChainMap(*[r.to_wdl_structure() for r in rooms]))
    items_wdl = dict(ChainMap(*[i.to_wdl_structure() for i in items]))
    players_wdl = dict(ChainMap(*[p.to_wdl_structure() for p in player_class]))

    out = json.dumps({
        **game.to_wdl_structure(), 
        "ROOMS": rooms_wdl,
        "ITEMS": items_wdl,
        "PLAYER_CLASS": players_wdl
        }, indent=2)

    if debug and "end" in debug_modes:
        print(out)

    return out