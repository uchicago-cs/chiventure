# This file contains the function parsed_dict_to_json
# Convert the intermediate data structure that is given by the LARK parser into a working WDL or JSON format.
import json
from warnings import warn
from collections import ChainMap

from to_wdl.wdl_room import Room
from to_wdl.wdl_item import Item
from to_wdl.wdl_game import Game
from to_wdl.wdl_player import Player_Class
from to_wdl.wdl_npc import Npc


def parsed_dict_to_json(intermediate: dict, debug=False, debug_modes=[], default="") -> str:
    """
        Main outward-facing function. Transforms the intermediate data 
        structure outputted by the parser into valid WDL/JSON format.
    """
    rooms = []
    items = []
    players = []
    npcs = []

    # Rooms and Items processing
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

    # Players processing
    if "players" not in intermediate:
        warn("This game has no players.")
    else:
        players_dict = intermediate.pop("players")
        for player_name, contents in players_dict.items():
            players.append(Player_Class(player_name, contents, default))
        
    # NPCs processing
    if "npc" not in intermediate:
        warn("This game has no NPCs.")
    else:
        npc_dict = intermediate.pop("npc")
        for npc_name, val in npc_dict.items():
            npcs.append(Npc(npc_name, val, default))
    
    game = Game(intermediate, default)
    
    # acts as a "union" operation on multiple dictionaries
    rooms_wdl = dict(ChainMap(*[r.to_wdl_structure() for r in rooms]))
    items_wdl = dict(ChainMap(*[i.to_wdl_structure() for i in items]))
    players_wdl = dict(ChainMap(*[p.to_wdl_structure() for p in players]))
    npcs_wdl = dict(ChainMap(*[n.to_wdl_structure() for n in npcs]))

    out = json.dumps({
        **game.to_wdl_structure(), 
        "CLASSES": players_wdl,
        "ROOMS": rooms_wdl,
        "ITEMS": items_wdl,
        "NPCS": npcs_wdl
        }, indent=2)

    if debug and "end" in debug_modes:
        print(out)

    return out