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
      "short_desc": "room C",
      "long_desc": "This is a room C. "
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
      "items": [],
      "short_desc": "room B",
      "long_desc": "This is a room B. "
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
      "items": [],
      "short_desc": "room A",
      "long_desc": "This is a room A. "
    }
  },
  "ITEMS": {}
}