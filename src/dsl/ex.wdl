{
  "GAME": {
    "start": "lab",
    "end": {
      "in_room": "room other"
    },
    "intro": "Welcome!",
    "NPC": [
      "BOT",
      {
        "location": "other",
        "short desc": "Kanto's premier Pokemon expert",
        "long desc": "Enjoys exploring human-Pokemon relationships",
        "age": "25",
        "gender": "Male",
        "INVENTORY": {
          "item_id1": "CHARMANDER",
          "item_id2": "SQUIRTLE",
          "item_id3": "BULBASAUR",
          "item_id4": "POKEBALL"
        }
      }
    ],
    "npc": {
      "OAK": {
        "location": "lab",
        "short desc": "Kanto's premier Pokemon expert",
        "long desc": "Enjoys exploring human-Pokemon relationships",
        "age": "25",
        "gender": "Male",
        "INVENTORY": {
          "item_id1": "CHARMANDER",
          "item_id2": "SQUIRTLE",
          "item_id3": "BULBASAUR",
          "item_id4": "POKEBALL"
        }
      },
      "ASH": {
        "location": "other",
        "short desc": "Kanto's premier Pokemon expert",
        "long desc": "Enjoys exploring human-Pokemon relationships",
        "age": "25",
        "gender": "Male",
        "INVENTORY": {
          "item_id1": "CHARMANDER",
          "item_id2": "SQUIRTLE",
          "item_id3": "BULBASAUR",
          "item_id4": "POKEBALL"
        }
      },
      "BOT": {
        "location": "other",
        "short desc": "Kanto's premier Pokemon expert",
        "long desc": "Enjoys exploring human-Pokemon relationships",
        "age": "25",
        "gender": "Male",
        "INVENTORY": {
          "item_id1": "CHARMANDER",
          "item_id2": "SQUIRTLE",
          "item_id3": "BULBASAUR",
          "item_id4": "POKEBALL"
        }
      }
    }
  },
  "ROOMS": {
    "house": {
      "short_desc": "Oak's house.",
      "long_desc": "Professor Oak's lab in Pallet Town",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": [
        "CHARMANDER",
        "SQUIRTLE",
        "BULBASAUR",
        "POKEBALL"
      ]
    },
    "other": {
      "short_desc": "Oak's other.",
      "long_desc": "Professor Oak's lab in Pallet Town",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": []
    },
    "lab": {
      "short_desc": "Oak's lab.",
      "long_desc": "Professor Oak's lab in Pallet Town",
      "connections": [
        {
          "direction": "NORTH",
          "to": "room A"
        },
        {
          "direction": "EAST",
          "to": "room C"
        }
      ],
      "items": [
        "COMPUTER"
      ]
    }
  },
  "ITEMS": {
    "POKEBALL": {
      "short_desc": "A pokeball",
      "long_desc": "A pokeball used to capture pokemon",
      "actions": [
        {
          "action": "TAKE",
          "text_success": "You take the pokeball",
          "text_fail": "You cannot take the pokeball"
        }
      ],
      "in": "OAK"
    },
    "BULBASAUR": {
      "short_desc": "A grass Pokemon",
      "long_desc": "It can go for days without eating a single morsel. In the bulb on its back, it stores energy.",
      "in": "OAK",
      "actions": []
    },
    "SQUIRTLE": {
      "short_desc": "A water pokemon",
      "long_desc": "After birth, its back swells and hardens into a shell. Powerfully sprays foam from its mouth.",
      "in": "OAK",
      "actions": []
    },
    "CHARMANDER": {
      "short_desc": "A fire pokemon",
      "long_desc": "Prefers hot places. When it rains, steam is said to spout from the tip of its tail.",
      "in": "OAK",
      "actions": []
    },
    "COMPUTER": {
      "short_desc": "A computer.",
      "long_desc": "A computer in Oak's lab",
      "in": "lab",
      "actions": []
    }
  },
  "NPCS": {}
}