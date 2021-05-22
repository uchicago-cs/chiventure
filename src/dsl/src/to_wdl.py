import json

class Room:
    def __init__(self,id,contents):
        self.id = id
        self.contents = contents

    ## to do: figure out how to get other attributes of the room into the output
    def to_json(self):
        self.generate_defaults()
        return json.dumps({self.id: {
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc'],
            "connections": self.connections_list(),
            "items": self.items_list()
        }})

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return

    # takes a dict of direction/destination pairs, converts to json
    def connections_list(self):
        return list(map(lambda i: {
                'direction': i.lower(),
                'to' : self.contents['connections'][i]    
            },self.contents['connections']))

    # takes a list of item dicts within a room, converts to json
    def items_list(self):
        return list(map(lambda i: i['id'], self.contents['items']))

class Item:
    def __init__(self,location,contents):
        self.location = location
        self.contents = contents

    ## to do: figure out how to get other attributes of the item into the output
    ## to do: figure out actions
    def to_json(self):
        self.generate_defaults()
        return json.dumps({self.contents['id']: {
            'in' : self.location,
            "short_desc": self.contents['short desc'],
            "long_desc": self.contents['long desc']
        }})

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return

class Game:
    def __init__(self,contents):
        self.contents = contents

    def to_json(self):
        self.generate_defaults()
        return json.dumps({'GAME': {
            'start' : self.contents['start'],
            "intro": self.contents['intro'],
            "end": {
                'in_room' : self.contents['end']
            }, # ideally this transformation would be done in Game.generate_defaults 
        },
        'ROOMS': 'placeholder',
        'ITEMS': 'placeholder'}) #figure out how to feed and process lists into here

    # dummy function
    # fixes/fills any parameters (long/short descriptions, etc, that are nonstandard)
    def generate_defaults(self):
        return


# test json output

room = Room('room a',{
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

item = Item('room a',{
          "id": "sconce",
          "short desc": "A sconce holding a candle",
          "long desc": "It looks a bit loose."
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

print(room.to_json())
print(item.to_json())
print(game.to_json())