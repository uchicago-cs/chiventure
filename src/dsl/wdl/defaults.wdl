{
  "GAME": {
    "start": "point a",
    "intro": "Welcome! You're in a point a",
    "end": {
      "in_room": "point c"
    }
  },
  "ROOMS": {
    "point c": {
      "short_desc": "point c",
      "long_desc": "This is a point c. ",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "point b"
        }
      ],
      "items": [
        "trophy"
      ]
    },
    "point b": {
      "short_desc": "point b",
      "long_desc": "This is a point b. ",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "point a"
        },
        {
          "direction": "NORTH",
          "to": "point c"
        }
      ],
      "items": []
    },
    "point a": {
      "short_desc": "point a",
      "long_desc": "This is a point a. ",
      "connections": [
        {
          "direction": "NORTH",
          "to": "point b"
        }
      ],
      "items": [
        "fork"
      ]
    }
  },
  "ITEMS": {
    "trophy": {
      "in": "point c",
      "short_desc": "trophy",
      "long_desc": "This is a trophy. ",
      "actions": [
        {
          "action": "ADMIRE",
          "text_success": "You admire the trophy.",
          "text_fail": "You cannot admire the trophy."
        },
        {
          "action": "HOIST",
          "text_success": "You hoist the trophy.",
          "text_fail": "You cannot hoist the trophy."
        },
        {
          "action": "CELEBRATE WITH",
          "text_success": "You celebrate with the trophy.",
          "text_fail": "You cannot celebrate with the trophy."
        }
      ]
    },
    "fork": {
      "in": "point a",
      "short_desc": "fork",
      "long_desc": "This is a fork. ",
      "actions": [
        {
          "action": "EAT WITH",
          "text_success": "You eat with the fork.",
          "text_fail": "You cannot eat with the fork."
        },
        {
          "action": "SING ABOUT",
          "text_success": "You sing about the fork.",
          "text_fail": "You cannot sing about the fork."
        }
      ]
    }
  }
}