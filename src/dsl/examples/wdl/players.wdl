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
      "short_desc": "library room.",
      "connections": [
        {
          "direction": "EAST",
          "to": "room B"
        }
      ],
      "items": [],
      "long_desc": "This is a room C. "
    },
    "room B": {
      "short_desc": "A dungeon room.",
      "connections": [
        {
          "direction": "WEST",
          "to": "room C"
        }
      ],
      "items": [
        "DOOR"
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
      "long_desc": "This is a DOOR. A large wooden door"
    }
  },
  "CLASSES": {
    "Knight": {
      "short_desc": "Knight's short description",
      "long_desc": "Knight's long description",
      "attributes": {
        "noble": true,
        "hotheaded": true
      },
      "base_stats": {
        "health": {
          "current": 100,
          "max": 200
        },
        "mana": {
          "current": 20,
          "max": 100
        }
      }
    }
  }
}