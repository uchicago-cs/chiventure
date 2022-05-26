{
  "GAME": {
    "start": "room A",
    "end": {
      "in_room": "room C"
    },
    "intro": "This is the intro"
  },
  "ROOMS": {
    "room C": {
      "short_desc": "This is room C",
      "long_desc": "This is room C, the final room in the game",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        }
      ],
      "items": [
        "DOOR"
      ]
    },
    "room B": {
      "short_desc": "This is room B",
      "long_desc": "This is room B. There's a table and an exit to the west.",
      "connections": [
        {
          "direction": "WEST",
          "to": "room C"
        }
      ],
      "items": []
    },
    "room A": {
      "short_desc": "This is room A",
      "long_desc": "This is room A. There's a chair and an exit to the south.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "room B"
        }
      ],
      "items": []
    }
  },
  "ITEMS": {
    "DOOR": {
      "short_desc": "A large wooden door",
      "long_desc": "It looks very heavy, and it doesn't have a keyhole",
      "actions": [
        {
          "action": "OPEN",
          "text_success": "You open the door.",
          "text_fail": "You can't open the door. It seems to be locked."
        },
        {
          "action": "GO",
          "text_success": "You walk through the door",
          "text_fail": "You can't do that, the door is closed"
        }
      ],
      "in": "room A"
    }
  }
}