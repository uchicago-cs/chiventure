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
            "connections": [
                {
                    "to": "Lab",
                    "direction": "NORTH"
                }
            ]
        },
        "Lab": {
            "short_desc": "Lab",
            "long_desc": "Lab long",
            "connections": []
        },
        "End Room": {
            "short_desc": "Lab",
            "long_desc": "Lab long",
            "connections": []
        }
    },
    "ITEMS": {
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
        },
        "CHARMANDER": {
            "short_desc": "A fire pokemon",
            "long_desc": "Prefers hot places. When it rains, steam is said to spout from the tip of its tail.",
            "in": "npc",
            "actions": []
        },
        "SQUIRTLE": {
            "short_desc": "A water pokemon",
            "long_desc": "After birth, its back swells and hardens into a shell. Powerfully sprays foam from its mouth.",
            "in": "npc",
            "actions": []
        },
        "BULBASAUR": {
            "short_desc": "A grass Pokemon",
            "long_desc": "It can go for days without eating a single morsel. In the bulb on its back, it stores energy.",
            "in": "npc",
            "actions": []
        },
        "POKEBALL": {
            "short_desc": "A pokeball",
            "long_desc": "A pokeball used to capture pokemon",
            "in": "npc",
            "actions": [
                {
                    "action": "TAKE",
                    "text_success": "You take the pokeball",
                    "text_fail": "You cannot take the pokeball"
                }
            ]
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
        },
        "OAK": {
            "short_desc": "Kanto's premier Pokemon expert",
            "long_desc": "Enjoys exploring human-Pokemon relationships",
            "in": "Lab",
            "inventory": [
                {
                    "item_id": "CHARMANDER"
                },
                {
                    "item_id": "SQUIRTLE"
                },
                {
                    "item_id": "BULBASAUR"
                },
                {
                    "item_id": "POKEBALL"
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
                        "npc_dialogue": "Oh! Thank you. By the way, your mother tells me you're going off to explore more of the Kanto region soon.\nShe has asked me to help prepare you to go off on your own. Outside of pallet town, pokemon lurk around every corner.\nIt's dangerous to go alone, please take one of these pokemon. Would you like a Bulbasaur, Squirtle, or Charmander?",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "ENCYCLOPEDIA"
                            }
                        ]
                    },
                    {
                        "id": "4",
                        "npc_dialogue": "Wonderful, you're on your way to becoming a great Pokemon trainer! Type GO END to complete your journey.",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "PIDGEY"
                            }
                        ]
                    },
                    {
                        "id": "6a",
                        "npc_dialogue": "Here is your Bulbasaur! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "BULBASAUR"
                            },
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "POKEBALL"
                            }
                        ]
                    },
                    {
                        "id": "6b",
                        "npc_dialogue": "Here is your Squirtle! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "SQUIRTLE"
                            },
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "POKEBALL"
                            }
                        ]
                    },
                    {
                        "id": "6c",
                        "npc_dialogue": "Here is your Charmander! You should also learn what to do when confronting pokemon in the wild.\nGo catch a Pidgey on Route 1 and bring it back to me. You will need these pokeballs too!.",
                        "actions": [
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "CHARMANDER"
                            },
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "POKEBALL"
                            }
                        ]
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
