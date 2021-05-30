{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!",
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
            "short_desc": "sd",
            "long_desc": "ld",
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
            "short_desc": "sd",
            "long_desc": "ld",
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
            "short_desc": "sd",
            "long_desc": "ld",
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
            "short_desc": "sd",
            "long_desc": "ld",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "EAST"
                }
            ]
        },
        "End Room": {
            "short_desc": "sd",
            "long_desc": "ld",
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
            "short_desc": "Pidgey",
            "long_desc": "The bird pokemon",
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
            "short_desc": "sd",
            "long_desc": "ld",
            "in": "Lab",
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Hello ASH. How are you?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Have a good day."
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
