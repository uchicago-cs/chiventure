{
  "GAME": {
    "start": "room A",
    "end": {
      "in_room": "room C"
    },
    "intro": "Welcome! You're in a room A"
  },
  "ROOMS": {
    "room C": {
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        }
      ],
      "items": [],
      "long_desc": "This is a room C. ",
      "short_desc": "room C"
    },
    "room B": {
      "connections": [
        {
          "direction": "SOUTH",
          "to": "room A"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": [
        "item_B"
      ],
      "long_desc": "This is a room B. ",
      "short_desc": "room B"
    },
    "room A": {
      "connections": [
        {
          "direction": "SOUTH",
          "to": "room B"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": [
        "item_A",
        "item_B"
      ],
      "long_desc": "This is a room A. ",
      "short_desc": "room A"
    }
  },
  "ITEMS": {
    "ITEM_B": {
      "actions": [
        {
          "action": "OPEN",
          "text_success": "You open the item_B.",
          "text_fail": "You cannot open the item_B."
        },
        {
          "action": "CLOSE",
          "text_success": "You close the item_B.",
          "text_fail": "You cannot close the item_B."
        }
      ],
      "in": "room A",
      "long_desc": "This is a item_B. ",
      "short_desc": "item_B"
    },
    "ITEM_A": {
      "in": "room A",
      "actions": [],
      "long_desc": "This is a item_A. ",
      "short_desc": "item_A"
    }
  }
}