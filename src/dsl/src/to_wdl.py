import json
from warnings import warn
from collections import ChainMap


class Room:
    def __init__(self, id, contents):
        self.id = id
        self.contents = contents

    # to do: figure out how to get other attributes of the room into the output
    def to_json(self):
        self.generate_defaults()
        return json.dumps({self.id: {
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc'],
            "connections": self.connections_list(),
            "items": self.items_list()
        }}, indent=2)
    
    def to_wdl_structure(self):
        self.generate_defaults()
        return {self.id: {
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc'],
            "connections": self.connections_list(),
            "items": self.items_list()
        }}
        

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return

    # takes a dict of direction/destination pairs, converts to json
    def connections_list(self):
        return list(map(lambda i: {
            'direction': i.upper(),
            'to': self.contents['connections'][i]
        }, self.contents['connections']))

    # is the list necessary?
    # takes a list of item dicts within a room, converts to json
    def items_list(self):
        return list(map(lambda i: i['id'], self.contents['items']))


class Item:
    def __init__(self, location, contents):
        self.location = location
        self.contents = contents

    # to do: figure out how to get other attributes of the item into the output
    # to do: figure out actions
    def to_json(self):
        self.generate_defaults()
        return json.dumps({self.contents['id']: {
            'in': self.location,
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc'],
            "actions": self.actions_list()
        }}, indent=2)

    def to_wdl_structure(self):
        self.generate_defaults()
        return {self.contents['id']: {
            'in': self.location,
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc'],
            "actions": self.actions_list()
        }}

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return

    # to do: action conditions -- how?
    def actions_list(self):
        if "actions" in self.contents:
            return list(map(lambda i: {
                'action': i,
                'text_success': self.contents['actions'][i]['success'],
                'text_fail': self.contents['actions'][i]['fail']
            }, self.contents['actions']))
        else:
            return []


class Game:
    def __init__(self, contents):
        self.contents = contents

    def to_json(self):
        self.generate_defaults()
        return json.dumps({'GAME': {
            'start': self.contents['start'],
            "intro": self.contents['intro'],
            "end": {
                'in_room': self.contents['end']
            },  # ideally this transformation would be done in Game.generate_defaults
        },
            'ROOMS': 'placeholder',
            'ITEMS': 'placeholder'}, indent=2)  # figure out how to feed and process lists into here
    
    def to_wdl_structure(self):
        self.generate_defaults()
        return {'GAME': {
            'start': self.contents['start'],
            "intro": self.contents['intro'],
            "end": {
                'in_room': self.contents['end']
            },  # ideally this transformation would be done in Game.generate_defaults
        }}

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return


def parsed_dict_to_json(intermediate: dict) -> str:
    """Transforms the intermediate data structure outputted by the parser into
    valid wdl json format"""

    #TODO: add support for ITEM IN ROOM and property FOR object
    rooms = []
    items = []

    if "rooms" not in intermediate:
        warn("This game has no rooms.")
    else:
        rooms_dict = intermediate.pop("rooms")
        for room_name, contents in rooms_dict.items():
            # can use pop if list of items is not needed
            # room_items = contents.pop("items")
            room_items = contents["items"]
            rooms.append(Room(room_name, contents))
            for i in room_items:
                items.append(Item(room_name, i))
    
    game = Game(intermediate)
    
    # acts as a "union" operation on multiple dictionaries
    rooms_wdl = dict(ChainMap(*[r.to_wdl_structure() for r in rooms]))
    items_wdl = dict(ChainMap(*[i.to_wdl_structure() for i in items]))

    return json.dumps({
        **game.to_wdl_structure(), 
        "ROOMS": rooms_wdl,
        "ITEMS": items_wdl
        }, indent=2)
    
    



# test json output
room = Room('room a', {
    "short desc": "A dungeon room.",
    "long desc": "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are.",
    "connections": {
        "SOUTH": "room B"
    },
    "items": [
        {
            "id": "sconce",
            "short desc": "A sconce holding a candle",
            "long desc": "It looks a bit loose."
        }
    ]
})

item = Item('room a', {
    "id": "sconce",
          "short desc": "A sconce holding a candle",
          "long desc": "It looks a bit loose.",
          "actions": {
            "OPEN": {
                "success": "You open the door.",
                "fail": "You can't open the door."
            },
            "BREAK": {
                "condition": "Door is in front of you.",
                "success": "You break the door.",
                "fail": "You can't break the door."
            }
            }
})

game = Game({
    "start": "room B",
    "end": "room C",
    "intro": "Welcome \"adventurer\"! You have made your way to the dungeons of the Lavender Palace. Don't be fooled by the cute name! This is one of Throxar the Terrible's most fearsome strongholds... and also his best scented one. Queen Vanadia has tasked you with recovering the Distaff of Knowledge, which her spies assure you is somewhere in these dungeons.",
    "rooms": {
        "room A": {
            "short desc": "A dungeon room.",
            "long desc": "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are.",
            "connections": {
                "SOUTH": "room B"
            },
            "items": [
                {
                    "id": "sconce",
                    "short desc": "A sconce holding a candle",
                    "long desc": "It looks a bit loose."
                }
            ]
        },
        "room B": {
            "short desc": "A dungeon room.",
            "long desc": "The walls are damp and moldy and, yet, the scent of freshly\n   # intentional line break\n   \n   cut lavender flowers pervades the air.",
            "connections": {
                "NORTH": "room A",
                "EAST": "room C"
            },
            "items": [
                {
                    "id": "Door",
                    "location": "room B",
                    "short desc": "A large wooden door",
                    "long desc": "It looks very heavy, and it doesn't have a keyhole."
                }
            ]
        },
        "room C": {
            "short desc": "A dungeon room.",
            "long desc": "The walls are neither damp nor moldy. It looks like they do get around to cleaning them once in a while.",
            "connections": {
                "WEST": "room B"
            },
            "items": [
                {
                    "id": "Distaff",
                    "short desc": "The Distaff of Knowledge",
                    "long desc": "The Distaff of Knowledge is an ancient magical artifact that can be used to weave knowledge itself. It will come in very handy at dinner parties."
                }
            ]
        }
    }
})


if __name__ == "__main__":
    # print(room.to_json())
    # print(item.to_json())
    # print(game.to_json())
    
    print(parsed_dict_to_json(game))