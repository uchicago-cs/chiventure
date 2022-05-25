{
  "GAME": {
    "start": "room B",
    "end": {
      "in_room": "room C"
    },
    "intro": "Welcome \"adventurer\"! You have made your way to the dungeons of the Lavender Palace. Don't be fooled by the cute name! This is one of Throxar the Terrible's most fearsome strongholds... and also his best scented one. Queen Vanadia has tasked you with recovering the Distaff of Knowledge, which her spies assure you is somewhere in these dungeons."
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
      "long_desc": "The walls are damp and moldy and, yet, the scent of freshly\n   cut lavender flowers pervades the air.",
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
      "extra property": "value",
      "items": [
        "sconce"
      ]
    }
  },
  "ITEMS": {
    "DISTAFF": {
      "short_desc": "The Distaff of Knowledge",
      "long_desc": "The Distaff of Knowledge is an ancient magical artifact that can be used to weave knowledge itself. It will come in very handy at dinner parties.",
      "in": "room C",
      "actions": []
    },
    "DOOR": {
      "short_desc": "A large wooden door",
      "long_desc": "It looks very heavy, and it doesn't have a keyhole.",
      "in": "room B",
      "actions": []
    },
    "SCONCE": {
      "short_desc": "A sconce holding a candle",
      "long_desc": "It looks a bit loose.",
      "in": "room A",
      "actions": []
    }
  }
}