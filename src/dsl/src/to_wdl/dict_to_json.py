# This file contains the function parsed_dict_to_json
# Convert the intermediate data structure that is given by the LARK parser into a working WDL or JSON format.
import json
from warnings import warn
from collections import ChainMap

from to_wdl.wdl_room import Room
from to_wdl.wdl_item import Item
from to_wdl.wdl_game import Game
from to_wdl.wdl_npc import Npc


def parsed_dict_to_json(intermediate: dict, debug=False, debug_modes=[], default="") -> str:
    """
        Main outward-facing function. Transforms the intermediate data 
        structure outputted by the parser into valid WDL/JSON format.
    """
    print('hi')
    print(intermediate)
    rooms = []
    items = []
    npcs = []
    npc_dict = {}
    # print(intermediate)
    # print()
    # print(intermediate)
    if "rooms" not in intermediate:
        warn("This game has no rooms.")
    else:
        rooms_dict = intermediate.pop("rooms")
        # print(rooms_dict)
        # print(rooms_dict['lab'])
        # print(rooms_dict)
        for rm in rooms_dict:
            npc_data = rooms_dict[rm].pop("npcs")
            full_npc = {}
            if len(npc_data) > 0:
                full_npc = npc_data

            # print(npc_data)

            # print("dafasdf")
            # print()
            # print(rooms_dict)
        
            # print(rm)
            print()
            # print(rooms_dict[rm])
            print()
        print("end-----")
            # curr_npc = rooms_dict[rm]['NPCS']
            # info = curr_npc[1]
            # name = curr_npc[0]
            
            # npc_dict[name] = info
            # print(npc_dict)
        # print(rooms_dict)
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


            # room_npcs = contents["npcs"]
            # room_npcs_objs = []
            # for npc in room_npcs:
            #     print("printing npc")
            #     print(npc)
            #     npc_id = npc[0]
            #     npc_contents = npc[1]
            #     location = room_name
            #     if "location" in npc_contents:
            #         location = npc_contents.pop("location")
                # npc_obj = Npc(npc_id, location, npc_contents, default)
                # npcs.append(npc_obj)
                # room_npcs_objs.append(npc_obj)
            # contents["npcs"] = room_npcs_objs

            # rooms.append(Room(room_name, contents, default))
            # print("room npcs")
            # print(room_npcs)


    
    if "npcs" in intermediate:
        npcs_dict = intermediate.pop("npcs")
        for curr in npcs_dict:
            for npcs, val in curr.items():
                npcs.append(Npcs(npcs, val, default))
    
    
    game = Game(intermediate, default)
    
    # acts as a "union" operation on multiple dictionaries
    rooms_wdl = dict(ChainMap(*[r.to_wdl_structure() for r in rooms]))
    items_wdl = dict(ChainMap(*[i.to_wdl_structure() for i in items]))
    npcs_wdl = dict(ChainMap(*[n.to_wdl_structure() for n in npcs]))

    out = json.dumps({
        **game.to_wdl_structure(), 
        "ROOMS": rooms_wdl,
        "ITEMS": items_wdl,
        "NPCS": npc_dict
        }, indent=2)

    if debug and "end" in debug_modes:
        print(out)

    return out