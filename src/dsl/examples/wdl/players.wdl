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
  "PLAYERS": {
    "KNIGHT": {
      "short_desc": "Knight",
      "long_desc": "This a Knight",
      "attributes": {
        "noble": "TRUE",
        "strong": "TRUE"
      },
      "base_stats": {
        "stat_setting": {
          "id": "health",
          "state": {
            "CURRENT": "20",
            "MAX": "10"
          }
        }
      }
    }
  }
}