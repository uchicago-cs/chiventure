{
    "GAME": {
        "start": "The Reg",
        "intro": "Welcome to the Reg! Your name is JASON. Your journey is just beginning. !\n \n(HINT: type 'look' to start, and 'talk to <NPC>' to interact with NPCs, use 'HELP' for more information)",
        "end": {
            "in_room": "Mansuetto"
        }
    },
    "ROOMS": {
        "The Reg": {
            "short_desc": "The library",
            "long_desc": "This is the library. The Quad is to the South and Mansuetto is upstairs.",
            "connections": [
                {
                    "to": "Mansuetto",
                    "direction": "UP"
                }
                {
                    "to": "The Quad",
                    "direction": "South"
                }
            ]
        },
        "Mansuetto": {
            "short_desc": "The bubble library",
            "long_desc": "This is Mansuetto. Downstairs is the way back to The Reg.",
            "connections": [
                {
                    "to": "The Reg",
                    "direction": "DOWN"
                }
            ]
        }
        "The Quad": {
            "short_desc": "The center of campus",
            "long_desc": "This is the quad. The Reg is to the North and Crear is to the West.",
            "connections": [
                {
                    "to": "The Reg",
                    "direction": "North"
                }
                {
                    "to": "Crear"
                    "direction": "West"
                }
            ]
        }
        "Crear": {
            "short_desc": "CS Library",
            "long_desc": "This is Crear. The Quad is to the East.",
            "connections": [
                {
                    "to": "The Quad",
                    "direction": "East"
                }
            ]
        }
    },
    "ITEMS": {
        "RARE BOW": {
            "short_desc": "A rare bow", 
            "long_desc": "A rare bow you found while exploring",
            "in": "Merchant's Shop",
            "actions": []
        },
        "HEALTH POTION": {
            "short_desc": "A simple potion", 
            "long_desc": "A simple potion that restores 10 HP",
            "in": "npc",
            "actions": []
        },
        "GOLDEN SWORD": {
            "short_desc": "A golden sword", 
            "long_desc": "Unused and shining. Looks very sharp",
            "in": "npc",
            "actions": []
        },
        "IRON PICKAXE": {
            "short_desc": "An iron pickaxe", 
            "long_desc": "A little worn. Might not last long",
            "in": "npc",
            "actions": []
        },
        "IRON HELMET": {
            "short_desc": "An iron helmet", 
            "long_desc": "Seems durable. Would protect you in a fight",
            "in": "npc",
            "actions": []
        },
        "MERCHANT'S NECKLACE": {
            "short_desc": "The merchant's necklace", 
            "long_desc": "Kept within a box on his desk. He would get very angry if you took it",
            "in": "npc",
            "actions": []
        }
    },
    "NPCS": {
        "MERCHANT": {
            "short_desc": "A merchant",
            "long_desc": "Can trade items with him",
            "in": "Merchant's Shop",
            "inventory": [
                {
                    "item_id": "HEALTH POTION"
                },
                {
                    "item_id": "GOLDEN SWORD"
                },
                {
                    "item_id": "IRON PICKAXE"
                },
                {
                    "item_id": "IRON HELMET"
                },
                {
                    "item_id": "MERCHANT'S NECKLACE"
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
                        ,
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