{
  "GAME": {
    "start": "room B",
    "end": {
      "in_room": "room C"
    },
    "intro": "Welcome!"
  },
  "ROOMS": {
    "room C": {
      "items": [],
      "long_desc": "This is a room C. ",
      "short_desc": "room C"
    },
    "room B": {
      "short_desc": "A dungeon room.",
      "items": [
        "Door"
      ],
      "long_desc": "This is a room B. "
    }
  },
  "ITEMS": {
    "DOOR": {
      "short_desc": "A large wooden door",
      "actions": [
        {
          "action": "OPEN",
          "condition": "Door is in front of you.",
          "text_success": "You open the door.",
          "text_fail": "You can't open the door."
        },
        {
          "action": "BREAK",
          "condition": "Door is in front of you.",
          "text_success": "You break the door.",
          "text_fail": "You can't break the door."
        }
      ],
      "in": "room B",
      "long_desc": "This is a Door. A large wooden door"
    }
  },
  "PLAYERS": {
    "PLAYER": {
      "attributes": [
        "noble",
        "hot-headed"
      ],
      "stats": {
        "health": {
          "current": 20,
          "max": 100
        },
        "mana": {
          "current": 20,
          "max": 100
        }
      },
      "long_desc": "This is a Knight. ",
      "short_desc": "Knight"
    }
  }
}