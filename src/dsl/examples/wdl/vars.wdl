{
  "GAME": {
    "start": "Room A",
    "end": {
      "in_room": "room C"
    },
    "intro": "hello John Smith"
  },
  "ROOMS": {
    "room A": {
      "items": [
        "Fork",
        "fork2",
        "Fork"
      ],
      "long_desc": "This is a room A. ",
      "short_desc": "room A"
    }
  },
  "ITEMS": {
    "FORK": {
      "long_desc": "a fork. theres \"nothing\" remarkably special about it.",
      "actions": [
        {
          "action": "TAKE",
          "text_success": "success",
          "text_fail": "failure"
        }
      ],
      "in": "room A",
      "short_desc": "Fork"
    },
    "FORK2": {
      "property1": "value",
      "in": "room B",
      "actions": [],
      "long_desc": "This is a fork2. ",
      "short_desc": "fork2"
    }
  }
}