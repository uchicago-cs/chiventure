import json
from warnings import warn
from collections import ChainMap

# to do: figure out how to get other properties of the item/game/room to output
# to do: improve default generation

PROPERTY_ALIASES = {
    "short desc": "short_desc",
    "short": "short_desc",
    "long desc": "long_desc",
    "long": "long_desc",
    "introduction": "intro"
}

class Room:
    def __init__(self, id: str, contents: dict):
        """
            Defines a Room class for conversion to WDL, with an id and a list of
            contents and/or properties.
        """
        self.id = id
        self.contents = contents
        
        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}

    def to_json(self) -> str: 
        """ For internal testing only: converts a room to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)
    
    def to_wdl_structure(self) -> dict:
        """
            Converts a Room item to WDL structure using its contents. Generates 
            default values where they are missing, and assembles a list of 
            connections and items for WDL compatibility.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "connections":
                self.wdl_contents["connections"] = self.connections_list()
            elif k == "items":
                self.wdl_contents["items"] = self.items_list()
            else:
                self.wdl_contents[k] = v

        self.generate_defaults()
        return {self.id: self.wdl_contents}
        
    def generate_defaults(self):
        """
            Ensures thats a Room item can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with default values.
        """

        # generate default for long description
        if 'long_desc' not in self.wdl_contents:
            id = self.id or "room"
            short = self.wdl_contents.get('short desc', '')
            default = f"This is a {id}. {short}"
            self.wdl_contents['long_desc'] = f"{default}"
            warn(f'''
                missing: long description for {id}, 
                generated default: {self.wdl_contents['long_desc']}''')

        # generate default for short description     
        if 'short_desc' not in self.wdl_contents:
            default_id = self.id or "a room"
            self.wdl_contents['short_desc'] = f"{default_id}"
            warn(f'''
                missing: short description for {default_id}, 
                generated default: {self.wdl_contents['short_desc']}''')
            
    def connections_list(self) -> list:
        """
            Assembles a list of a room's conections, with their directions and 
            desinations included.
        """
        if 'connections' not in self.contents:
            warn(f'''room {self.id} has no connections''')
            return []
        else:
            return list(map(lambda i: {
                'direction': i.upper(),
                'to': self.contents['connections'][i]
            }, self.contents['connections']))

    def items_list(self) -> list:
        """
            Assembles a list of a room's items.
        """
        return list(map(lambda i: i['id'], self.contents.get('items',[])))

class Item:
    def __init__(self, location: str, contents: dict):
        """
            Defines an Item class for conversion to WDL, with an id, a location, 
            and a list of actions and/or properties.
        """
        self.location = location
        self.contents = contents
        assert 'id' in self.contents, "Item is missing an id"
        self.id = self.contents['id']

        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}

    def to_json(self) -> str: 
        """ For internal testing only: converts an item to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)

    def to_wdl_structure(self) -> dict:
        """
            Converts an Item to WDL structure using its properties. Generates 
            default values where they are missing, and assembles a list of 
            actions for WDL compatibility.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "actions":
                self.wdl_contents["connections"] = self.actions_list()
            elif k not in ['id']:
                self.wdl_contents[k] = v

        self.wdl_contents['in'] = self.location
        self.generate_defaults()
        return {self.id: self.wdl_contents}

    def generate_defaults(self):
        """
            Ensures that an Item can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with its default values.
        """

        # generate default for long description
        if 'long_desc' not in self.wdl_contents:
            short_desc = self.wdl_contents.get('short_desc', '')
            default = f"This is a {self.id}. {short_desc}"
            self.wdl_contents['long_desc'] = f"{default}"
            warn(f'''
                missing: long description for {self.id}, 
                generated default: {self.wdl_contents['long_desc']}''')
                
        # generate default for short description
        if 'short_desc' not in self.wdl_contents:
            self.wdl_contents['short_desc'] = f"{self.id}"
            warn(f'''
                missing: short description for {self.id}, 
                generated default: {self.wdl_contents['short_desc']}''')

        # generate default interaction text for actions
        for i in self.wdl_contents.get('actions', []):
            id = self.wdl_contents.get('id', "item")
            if 'success' not in self.wdl_contents['actions'][i]:
                self.wdl_contents['actions'][i]['success'] = f"You {i.lower()} the {id}."
                warn(f'''
                    missing: success text for action {i} for item {id}, 
                    generated default: {self.wdl_contents['actions'][i]['success']}''')
            if 'fail' not in self.wdl_contents['actions'][i]:
                self.wdl_contents['actions'][i]['fail'] = f"You cannot {i.lower()} the {id}."
                warn(f'''
                    missing: failure text for action {i} for item {id}, 
                    generated default: {self.wdl_contents['actions'][i]['fail']}''')

    # to do: action conditions -- how?
    def actions_list(self) -> list:
        """
            Assembles a list of an item's actions, with their success and 
            failure text included.
        """
        return list(map(lambda i: {
            'action': i,
            'text_success': self.contents['actions'][i]['success'],
            'text_fail': self.contents['actions'][i]['fail']
        }, self.contents.get('actions',[])))


class Game:
    def __init__(self, contents: dict):
        """
            Defines a Game class for conversion to WDL, with an id and a list of
            contents and/or properties.
        """
        self.contents = contents

        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}

    def to_json(self) -> str: 
        """ For internal testing only: converts a game to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)
    
    def to_wdl_structure(self) -> dict:
        """
            Converts a Game to WDL structure using its properties. Generates 
            default values where they are missing.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            if k == "end":
                self.wdl_contents["end"] = {"in_room": v}
            else:
                self.wdl_contents[k] = v
        self.generate_defaults()
        return {'GAME': self.wdl_contents}
        return {'GAME': {
            'start': self.contents['start'],
            "intro": self.contents['intro'],
            "end": {
                'in_room': self.contents['end']
            }
        }}

    def generate_defaults(self):
        """
            Ensures that a Game can be converted to WDL by filling in 
            neccesary information (like an introduction) that is not 
            included with its default values.
        """

        # generate default for introduction
        if 'intro' not in self.wdl_contents:
            default = self.wdl_contents.get('start') or "room"
            self.wdl_contents['intro'] = f"Welcome! You're in a {default}"
            warn(f'''
                missing: introduction for game, 
                generated default: {self.wdl_contents['intro']}''')


def parsed_dict_to_json(intermediate: dict) -> str:
    """
        Transforms the intermediate data structure outputted by the parser into
        valid WDL/JSON format.
    """

    rooms = []
    items = []

    if "rooms" not in intermediate:
        warn("This game has no rooms.")
    else:
        rooms_dict = intermediate.pop("rooms")
        for room_name, contents in rooms_dict.items():
            room_items = contents["items"]
            rooms.append(Room(room_name, contents))
            for item in room_items:
                location = room_name
                if "location" in item:
                    location = item.pop("location")
                items.append(Item(location, item))
    
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
    print(parsed_dict_to_json(game.contents))