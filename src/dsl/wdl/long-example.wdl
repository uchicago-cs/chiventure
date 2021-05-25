{
  "GAME": {
    "start": "alcatraz cell",
    "intro": "It's dusk in San Francisco, but not the cool part of the city. You're on an island with views of the Bay, which would be dope if the island didn't have a prison on top of it that you lived in. For what seems like the millionth time, you stare out into the distance, the faint light of the neon sign from the world-famous Ghirardelli factory \u00e2\u0080\u0094 yet another place you can't go \u00e2\u0080\u0094 shining through your tiny barred window. You resolve to get yourself out of here, as soon as possible.",
    "end": {
      "in_room": "san francisco"
    }
  },
  "ROOMS": {
    "prison hallway": {
      "short_desc": "prison hallway",
      "long_desc": "This is a prison hallway. ",
      "connections": [],
      "items": [
        "guard badge"
      ]
    },
    "alcatraz cell": {
      "short_desc": "You're in a prison cell.",
      "long_desc": "This is a alcatraz cell. You're in a prison cell.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "secret tunnel"
        },
        {
          "direction": "NORTH",
          "to": "prison hallway"
        }
      ],
      "items": [
        "deck of cards",
        "toilet"
      ]
    }
  },
  "ITEMS": {
    "guard badge": {
      "in": "prison hallway",
      "short_desc": "guard badge",
      "long_desc": "This is a guard badge. ",
      "actions": [
        {
          "action": "THROW LIKE FRISBEE",
          "text_success": "You throw the guard badge across the room like a Frisbee.",
          "text_fail": "You try to throw the guard badge across the room like a Frisbee, but you realize you can't. You've never seen a Frisbee in your life; you've only read about them. You think they were invented after you got locked up here, but you don't know that for sure."
        }
      ]
    },
    "toilet": {
      "in": "alcatraz cell",
      "short_desc": "toilet",
      "long_desc": "Your cell's got a toilet. It's the first thing you see when you wake up every day and the last thing you see each night. Nobody inside likes you all that much, so you figue the toilet's gotta be your best friend in all this world. A few years ago, you decided to name it Barbara, and you've grown attatched to the name.",
      "actions": [
        {
          "action": "LIFT",
          "text_success": "You lift the toilet.",
          "text_fail": "The toilet is too heavy for you to lift!"
        },
        {
          "action": "FLUSH",
          "text_success": "You flush the toilet.",
          "text_fail": "You can't flush the toilet! It's quiet hour, idiot."
        },
        {
          "action": "SING ABOUT",
          "text_success": " You {} the toilet.",
          "text_fail": " You cannot {} the toilet."
        }
      ]
    },
    "deck of cards": {
      "in": "alcatraz cell",
      "short_desc": "deck of cards",
      "long_desc": "You have a deck of cards. It's a full deck, if you're willing to forget the fact that it was missing the 7\u00e2\u0099\u00a3 when you got it and also that your former cellmate tore the J\u00e2\u0099\u00a6 in half as part of a 'magic trick' that didn't work at all.",
      "actions": [
        {
          "action": "SHUFFLE",
          "text_success": "You shuffle the cards.",
          "text_fail": " You cannot {'success': 'You shuffle the cards.', 'failure': \"You fail to shuffle the cards! They spectacularly spray all over your cell, and what's worse, the K\u00e2\\x99\\xa0 landed in your neighbor's cell. You are no longer able to maintain the lie you've told yourself that your deck of cards is perfectly good. It's not \u00e2\\x80\\x94 it's ruined. You can't have good things, it seems.\"} the deck of cards."
        }
      ]
    }
  }
}