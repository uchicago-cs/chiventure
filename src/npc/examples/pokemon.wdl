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
            "long_desc": "Your MOM is here. There is an exit to the East, and stairs leading upstairs.",
            "connections": [
                {
                    "to": "Bedroom",
                    "direction": "UP"
                },
                {
                    "to": "Pallet Town",
                    "direction": "EAST"
                }
            ]
        },
        "Pallet Town": {
            "short_desc": "A small town in southwestern Kanto",
            "long_desc": "Your house is to the West, Prof. OAK's lab is to the South, and Route 1 is to the North.",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "WEST"
                },
                {
                    "to": "Lab",
                    "direction": "SOUTH"
                },
                {
                    "to": "Route 1",
                    "direction": "NORTH"
                }
            ]
        },
        "Lab": {
            "short_desc": "Prof. OAK's lab",
            "long_desc": "Prof. OAK is here. There is an exit to the North.",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "NORTH"
                },
                {
                    "to": "End Room",
                    "direction": "END"
                }
            ]
        },
        "Route 1": {
            "short_desc": "Route 1",
            "long_desc": "You walk into the tall grass. A wild PIDGEY appears! Try talking to it!",
            "connections": [
                {
                    "to": "Pallet Town",
                    "direction": "SOUTH"
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
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You pushed the bed. \nIt looks good here.",
                    "text_fail": "You cannot push the bed."
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the bed. \nIt looks better here.",
                    "text_fail": "You cannot pull this bed"
                }
            ]
        },
        "TV": {
            "short_desc": "A TV", 
            "long_desc": "It's a 20 inch CRT TV with an SNES connected to it.",
            "in": "Bedroom",
            "actions": [{
                    "action": "PUSH",
                    "text_success": "The TV is too heavy for you to push.",
                    "text_fail": "You cannot push the TV."
                },
                {
                    "action": "PULL",
                    "text_success": "The TV is too heavy for you to pull.",
                    "text_fail": "You cannot pull the TV"
                },
                {
                    "action": "TURNON",
                    "text_success": "The TV is on, there is static on the screen.",
                    "text_fail": "You cannot turn on the TV"
                },
                {
                    "action": "TURNOFF",
                    "text_success": "The TV is off, the screen is black.",
                    "text_fail": "You cannot turn off the TV"
                }
            ]
        },
        "SNES": {
            "short_desc": "A SNES", 
            "long_desc": "Just a SNES, the controller is missing.",
            "in": "Bedroom",
            "actions": [{
                    "action": "PUSH",
                    "text_success": "You pushed the SNES. \nIt said thank you.",
                    "text_fail": "You cannot push the SNES."
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the SNES.",
                    "text_fail": "You cannot pull the SNES"
                },
                {
                    "action": "TURNON",
                    "text_success": "The SNES is on, but there is no game.",
                    "text_fail": "You cannot turn on the SNES"
                },
                {
                    "action": "TURNOFF",
                    "text_success": "The SNES is off.",
                    "text_fail": "You cannot turn off the SNES"
                }
            ]
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
        },
        "PIDGEY": {
            "short_desc": "The tiny bird pokemon",
            "long_desc": "A common sight in forests and woods. It flaps its wings at ground level to kick up blinding sand.",
            "in": "Route 1",
            "inventory": [
                {
                    "item_id": "PIDGEY"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "The wild Pidgey attacks!"
                    },
                    {
                        "id": "4",
                        "npc_dialogue": "Got away safely!"
                    },
                    {
                        "id": "2a",
                        "npc_dialogue": "Pidgey broke free! Pidgey used sand attack!"
                    },
                    {
                        "id": "2b",
                        "npc_dialogue": "Pidgey looks hurt! Pidgey used gust!"
                    },
                    {
                        "id": "3",
                        "npc_dialogue": "The wild Pidgey was caught!",
                        "actions": [
                            {
                                "action": "TAKE_ITEM",
                                "action_id": "POKEBALL"
                            },
                            {
                                "action": "GIVE_ITEM",
                                "action_id": "PIDGEY"
                            }
                        ]
                    }
                ],
                "edges": [
                    {
                        "quip": "Run Away!",
                        "from_id": "1",
                        "to_id": "4"
                    },
                    {
                        "quip": "Run Away!",
                        "from_id": "2b",
                        "to_id": "4"
                    },
                    {
                        "quip": "Run Away!",
                        "from_id": "2a",
                        "to_id": "4"
                    },
                    {
                        "quip": "Squirtle, use water gun!",
                        "from_id": "1",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "SQUIRTLE"
                            }
                        ]
                    },
                    {
                        "quip": "Bulbasaur, use vine whip!",
                        "from_id": "1",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "BULBASAUR"
                            }
                        ]
                    },
                    {
                        "quip": "Charmander, use ember!",
                        "from_id": "1",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "CHARMANDER"
                            }
                        ]
                    },
                    {
                        "quip": "Squirtle, use water gun!",
                        "from_id": "2b",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "SQUIRTLE"
                            }
                        ]
                    },
                    {
                        "quip": "Bulbasaur, use vine whip!",
                        "from_id": "2b",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "BULBASAUR"
                            }
                        ]
                    },
                    {
                        "quip": "Charmander, use ember!",
                        "from_id": "2b",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "CHARMANDER"
                            }
                        ]
                    },
                    {
                        "quip": "Squirtle, use water gun!",
                        "from_id": "2a",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "SQUIRTLE"
                            }
                        ]
                    },
                    {
                        "quip": "Bulbasaur, use vine whip!",
                        "from_id": "2a",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "BULBASAUR"
                            }
                        ]
                    },
                    {
                        "quip": "Charmander, use ember!",
                        "from_id": "2a",
                        "to_id": "2b",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "CHARMANDER"
                            }
                        ]
                    },
                    {
                        "quip": "I'll throw a Pokeball!",
                        "from_id": "1",
                        "to_id": "2a",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "POKEBALL",
                            }
                        ]
                    },
                    {
                        "quip": "I'll throw a Pokeball!",
                        "from_id": "2a",
                        "to_id": "2a",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "POKEBALL"
                            }
                        ]
                    },
                    {
                        "quip": "I'll throw a Pokeball!",
                        "from_id": "2b",
                        "to_id": "3",
                        "conditions": [
                            {
                                "type": "INVENTORY",
                                "item_id": "POKEBALL"
                            }
                        ]
                    }
                ]
            }
        }
    }
}
