{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!",
        "end": {
            "in_room": "Lab"
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
        }
    },
    "NPCS": {
        "MOM": {
            "short_desc": "ASH's mom",
            "long_desc": "Makes sure you are well fed",
            "in": "Living Room",
            "inventory": [],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Good morning sweetie. Can you help me take this book to Prof. Oak?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Thanks sweetie.",
                        "actions": []
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
