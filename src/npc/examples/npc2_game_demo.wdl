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
        "LUNCH BOX": {
            "short_desc": "ASH's lunch box",
            "long_desc": "Made with love from Mom",
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
                    "item_id": "LUNCH BOX"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Good morning sweetie. Here, take your lunch box."
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "You're welcome.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "LUNCH BOX"
                            }
                        ]
                    }
                ],
                "edges": [
                    {
                        "quip": "Thanks, Mom",
                        "from_id": "1",
                        "to_id": "2"
                    }
                ]
            }
        }
    }
}