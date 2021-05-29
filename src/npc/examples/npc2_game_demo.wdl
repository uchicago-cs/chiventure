{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!",
        "end": {
            "in_room": "Outside"
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
            "long_desc": "Your MOM is here. There is an exit to the South.",
            "connections": [
                {
                    "to": "Bedroom",
                    "direction": "UP"
                },
                {
                    "to": "Outside",
                    "direction": "SOUTH"
                }
            ]
        },
        "Outside": {
            "short_desc": "Outside",
            "long_desc": "This is outside, the final room in the game",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "NORTH"
                }
            ]
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
        }
    }
}