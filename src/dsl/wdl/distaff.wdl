{
  "GAME": {
    "start": "room B",
    "intro": "Welcome \"adventurer\"! You have made your way to the dungeons of the Lavender Palace. Don't be fooled by the cute name! This is one of Throxar the Terrible's most fearsome strongholds... and also his best scented one. Queen Vanadia has tasked you with recovering the Distaff of Knowledge, which her spies assure you is somewhere in these dungeons.",
    "end": {
      "in_room": "room C"
    }
  },
  "ROOMS": {
    "room C": {
      "short_desc": "A dungeon room.",
      "long_desc": "The walls are neither damp nor moldy. It looks like they do get around to cleaning them once in a while.",
      "connections": [
        {
          "direction": "WEST",
          "to": "room B"
        }
      ],
      "items": [
        "Distaff"
      ]
    },
    "room B": {
      "short_desc": "A dungeon room.",
      "long_desc": "The walls are damp and moldy and, yet, the scent of freshly\n   # intentional line break\n   \n   cut lavender flowers pervades the air.",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": [
        "Door"
      ]
    },
    "room A": {
      "short_desc": "A dungeon room.",
      "long_desc": "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "room B"
        }
      ],
      "items": [
        "sconce"
      ]
    }
  },
  "ITEMS": {
    "Distaff": {
      "in": "room C",
      "short_desc": "The Distaff of Knowledge",
      "long_desc": "The Distaff of Knowledge is an ancient magical artifact that can be used to weave knowledge itself. It will come in very handy at dinner parties.",
      "actions": []
    },
    "Door": {
      "in": "room B",
      "short_desc": "A large wooden door",
      "long_desc": "It looks very heavy, and it doesn't have a keyhole.",
      "actions": []
    },
    "sconce": {
      "in": "room A",
      "short_desc": "A sconce holding a candle",
      "long_desc": "It looks a bit loose.",
      "actions": []
    }
  }
}