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
      "short_desc": "This is room C",
      "long_desc": "This is room C. There's a trophy and an exit to the NORTH.",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        }
      ],
      "items": [
        "trophy"
      ]
    },
    "room B": {
      "short_desc": "This is room B",
      "long_desc": "This is room B. There's a table and an exit to the WEST.",
      "connections": [
        {
          "direction": "WEST",
          "to": "room C"
        }
      ],
      "items": [
        "table"
      ]
    },
    "room A": {
      "short_desc": "This is room A",
      "long_desc": "This is room A. There's a chair and an exit to the SOUTH.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "room B"
        }
      ],
      "items": [
        "chair"
      ]
    }
  },
  "ITEMS": {
    "TROPHY": {
      "in": "room C",
      "actions": [],
      "long_desc": "This is a trophy. ",
      "short_desc": "trophy"
    },
    "TABLE": {
      "in": "room B",
      "actions": [],
      "long_desc": "This is a table. ",
      "short_desc": "table"
    },
    "CHAIR": {
      "in": "room A",
      "actions": [],
      "long_desc": "This is a chair. ",
      "short_desc": "chair"
    }
  }
}