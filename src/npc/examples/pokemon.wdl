{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!\n \n(HINT: type 'look' to start, and 'talk to <NPC>' to interact with NPCs, use 'HELP' for more information)",
        "end": {
            "in_room": "End Room"
        }
    },
    "ROOMS": {
        "Bedroom": {
            "short_desc": "ASH's bedroom",
            "long_desc": "This is your bedroom. There's a bed and stairs leading downstairs.",
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
                    "to": "Bedroom",
                    "direction": "UP"
                },
                {
                    "to": "Pallet Town",
                    "direction": "NORTH"
                }
            ]
        },
        "Pallet Town": {
            "short_desc": "A small town in southwestern Kanto",
            "long_desc": "Your house is located to the South, Prof. OAK's lab is to the North, and Route 1 is to the West.",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "SOUTH"
                },
                {
                    "to": "Lab",
                    "direction": "NORTH"
                },
                {
                    "to": "Route 1",
                    "direction": "WEST"
                }
            ]
        },
        "Lab": {
            "short_desc": "Prof. OAK's lab",
            "long_desc": "Prof. OAK is here. There is an exit to the South.",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "SOUTH"
                },
                {
                    "to": "End Room",
                    "direction": "END"
                }
            ]
        },
        "Route 1": {
            "short_desc": "Route 1",
            "long_desc": "The route is filled with grass, which seem to rustle with Pokemon. Pallet Town is to the East.",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "EAST"
                }
            ]
        },
        "End Room": {
            "short_desc": "end",
            "long_desc": "end",
            "connections": []
        }
    },
    "ITEMS": {
        "BED": {
            "short_desc": "ASH's bed", 
            "long_desc": "Looks comfortable",
            "in": "Bedroom",
            "actions": []
        },
        "ENCYCLOPEDIA": {
            "short_desc": "A big book",
            "long_desc": "Contains information about the world and the Pokemon that inhabit it",
            "in": "npc",
            "actions": []
        },
        "PIDGEY": {
            "short_desc": "The tiny bird pokemon",
            "long_desc": "A common sight in forests and woods. It flaps its wings at ground level to kick up blinding sand.",
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
                        "npc_dialogue": "Good morning sweetie. Can you help me take this book to Prof. Oak?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Thanks sweetie.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "ENCYCLOPEDIA"
                            }
                        ]
                    }
                ],
                "edges": [
                    {
                        "quip": "Okay",
                        "from_id": "1",
                        "to_id": "2"
                    }
                ]
            }
        },
        "OAK": {
            "short_desc": "Kanto's premier Pokemon expert",
            "long_desc": "Enjoys exploring human-Pokemon relationships",
            "in": "Lab",
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Hello ASH. How are you?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Have a nice day."
                    },
                    {
                        "id": "3",
                        "npc_dialogue": "Oh! Thank you. ... <Starter pokemon>",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "id": "4",
                        "npc_dialogue": "Wonderful! ... <Directs player to end the game>",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "PIDGEY"
                            }
                        ]
                    }
                ],
                "edges": [
                    {
                        "quip": "Good",
                        "from_id": "1",
                        "to_id": "2"
                    },
                    {
                        "quip": "I have an ENCYCLOPEDIA that belongs to you.",
                        "from_id": "1",
                        "to_id": "3",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "quip": "I've caught the PIDGEY you asked for!",
                        "from_id": "1",
                        "to_id": "4",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "PIDGEY"
                            }
                        ]
                    }
                ]
            }
        }
    }
}
