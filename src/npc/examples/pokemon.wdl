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
            "inventory": [],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Do you have the ENCYCLOPEDIA?"
                    },
                    {
                        "id": "2a",
                        "npc_dialogue": "Thanks",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "id": "2b",
                        "npc_dialogue": "Talk to your Mom"
                    }
                ],
                "edges": [
                    {
                        "quip": "Yes",
                        "from_id": "1",
                        "to_id": "2a",
                        conditions: [
                            {
                                "type": "INVENTORY",
                                "item_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "quip": "No",
                        "from_id": "1",
                        "to_id": "2b"
                    }
                ]
            }
        }
    }
}
