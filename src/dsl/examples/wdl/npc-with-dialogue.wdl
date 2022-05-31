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
  },
  "NPCS": {
    "OAK": {
      "in": "room B",
      "short_desc": "Kanto's premier Pokemon expert",
      "long_desc": "Enjoys exploring human-Pokemon relationships",
      "inventory": [
        {
          "item_id": "DOOR"
        }
      ],
      "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Hello ASH. How are you?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Have a nice day!"
                    },
                    {
                        "id": "3",
                        "npc_dialogue": "Oh! Thank you. By the way, your mother tells me you're going off to explore more of the Kanto region soon.\nShe has asked me to help prepare you to go off on your own. Outside of pallet town, pokemon lurk around every corner.\nIt's dangerous to go alone, please take one of these pokemon. Would you like a Bulbasaur, Squirtle, or Charmander?"
                    },
                    {
                        "id": "4",
                        "npc_dialogue": "Wonderful, you're on your way to becoming a great Pokemon trainer! Type GO END to complete your journey."
                    },
                    {
                        "id": "6a",
                        "npc_dialogue": "Here is your Bulbasaur! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!."
                    },
                    {
                        "id": "6b",
                        "npc_dialogue": "Here is your Squirtle! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!."
                    },
                    {
                        "id": "6c",
                        "npc_dialogue": "Here is your Charmander! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!."
                    }
                ],                    
                "edges": [
                    {
                        "quip": "Good.",
                        "from_id": "1",
                        "to_id": "2"
                    },
                    {
                        "quip": "I have an ENCYCLOPEDIA that belongs to you.",
                        "from_id": "1",
                        "to_id": "3"
                    },
                    {
                        "quip": "I've caught the PIDGEY you asked for!",
                        "from_id": "1",
                        "to_id": "4"
                    },
                    {
                        "quip": "I'll take Bulbasaur.",
                        "from_id": "3",
                        "to_id": "6a"
                    },
                    {
                        "quip": "I'll take Squirtle.",
                        "from_id": "3",
                        "to_id": "6b"
                    },
                    {
                        "quip": "I'll take Charmander.",
                        "from_id": "3",
                        "to_id": "6c"
                    }
                ]
            }
        }
    }
  }
}