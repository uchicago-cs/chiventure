{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!\n \n(HINT: type 'look' to start, and 'talk to <NPC>' to interact with NPCs, use 'HELP' for more information)",
        "end": {
            "in_room": "Pallet Town"
        }
    },
    "ROOMS": {
        "Bedroom": {
            "short_desc": "ASH's bedroom",
            "long_desc": "This is your bedroom. There are stairs leading downstairs.",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "DOWN"
                }
            ]
        },
        "Living Room": {
            "short_desc": "ASH's living room",
            "long_desc": "Your MOM is here. There is an exit to the North, and stairs leading upstairs.",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "NORTH"
                }
            ]
        },
        "Pallet Town": {
            "short_desc": "A small town in southwestern Kanto",
            "long_desc": "Your house is to the South, Prof. OAK's lab is to the North, and Route 1 is to the West.",
            "connections": []
        }
    },
    "ITEMS": {
        "ENCYCLOPEDIA": {
            "short_desc": "A big book",
            "long_desc": "Contains information about the world and the Pokemon that inhabit it",
            "in": "npc",
            "actions": []
        }
    },
    "NPCS": {
        "MOM": {
            "short_desc": "ASH's mom",
            "long_desc": "Makes sure you are well fed",
            "in": "Living Room",
            "inventory": [
                {
                    "item_id": "ENCYCLOPEDIA"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Good morning sweetie. What will you be doing today?"
                    },
                    {
                        "id": "2a",
                        "npc_dialogue": "Oh, since you're heading there, can you help me return this book to Prof. OAK? I borrowed it some time ago. Thanks sweetie.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "id": "2b",
                        "npc_dialogue": "Be safe!",
                    }
                ],
                "edges": [
                    {
                        "quip": "I'm heading to Prof. OAK's lab. He says he has something for me.",
                        "from_id": "1",
                        "to_id": "2a"
                    },
                    {
                        "quip": "Finding wild pokemon!",
                        "from_id": "1",
                        "to_id": "2b"
                    }
                ]
            }
        }
    }
}
