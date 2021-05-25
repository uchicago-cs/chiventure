{
  "GAME": {
    "start": "room B",
    "intro": "Welcome!",
    "end": {
      "in_room": "room C"
    }
  },
  "ROOMS": {
    "room C": {
      "short_desc": "room C",
      "long_desc": "This is a room C. ",
      "connections": [],
      "items": []
    },
    "room B": {
      "short_desc": "A dungeon room.",
      "long_desc": "This is a room B. A dungeon room.",
      "connections": [],
      "items": [
        "Door"
      ]
    }
  },
  "ITEMS": {
    "Door": {
      "in": "room B",
      "short_desc": "A large wooden door",
      "long_desc": "This is a Door. A large wooden door",
      "actions": [
        {
          "action": "OPEN",
          "text_success": "You open the door.",
          "text_fail": "You can't open the door."
        },
        {
          "action": "BREAK",
          "text_success": "You break the door.",
          "text_fail": "You can't break the door."
        }
      ]
    }
  }
}