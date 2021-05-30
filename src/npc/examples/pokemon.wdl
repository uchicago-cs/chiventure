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
            "long_desc": "This is your bedroom.
    There's a bed in the SE corner with a TV in front of it.
    There's also a plant in the NW corner of the room.
    There are stairs leading downstairs.",
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
            "long_desc": "Your house is to the South, Prof. OAK's lab is to the North, and Route 1 is to the West.",
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
            "long_desc": "You walk into the tall grass. A wild Pidgey appears! Try talking to it!",
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
        "COOKIE": {
            "short_desc": "A Cookie", 
            "long_desc": "There's a cookie on the floor. It looks dusty.",
            "in": "Bedroom",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "The cookie slides across the floor and gets dirtier.",
                    "text_fail": "You cannot push the cookie."
                },
                {
                    "action": "PULL",
                    "text_success": "You weirdly pull the cookie towards you. \n It looks extra dusty.",
                    "text_fail": "You cannot pull the cookie."
                },
                {
                    "action": "EAT",
                    "text_success": "You stuff that disgusting cookie into your mouth and instantly spit it out.",
                    "text_fail": "You cannot eat the cookie."
                },
                {
                    "action": "CONSUME",
                    "text_success": "You stuff that disgusting cookie into your mouth and instantly spit it out.",
                    "text_fail": "You cannot consume the cookie."
                }
            ]
        },
        "PLANT": {
            "short_desc": "A house plant", 
            "long_desc": "Looks like it needs some water.",
            "in": "Bedroom",
            "actions": [{
                    "action": "PUSH",
                    "text_success": "You pushed the plant. \nIt didn't like that.",
                    "text_fail": "You cannot push the plant."
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the plant. \nIt liked that.",
                    "text_fail": "You cannot pull the plant"
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
            "in": "Lab",
            "actions": [
                {
                    "action": "TAKE",
                    "text_success": "You take Charmander",
                    "text_fail": "You cannot take Charmander"
                }
            ]
        },
        "BULBASAUR": {
            "short_desc": "A Grass Pokemon",
            "long_desc": "It can go for days without eating a single morsel. In the bulb on its back, it stores energy.",
            "in": "Lab",
            "actions": [
                {
                    "action": "TAKE",
                    "text_success": "You take Bulbasaur",
                    "text_fail": "You cannot take Bulbasaur"
                }
            ]
        },
        "SQUIRTLE": {
            "short_desc": "A water pokemon",
            "long_desc": "After birth, its back swells and hardens into a shell. Powerfully sprays foam from its mouth.",
            "in": "Lab",
            "actions": [
                {
                    "action": "TAKE",
                    "text_success": "You take Squirtle",
                    "text_fail": "You cannot take Squirtle"
                }
            ]
        },
        "POKEBALL": {
            "short_desc": "A pokeball",
            "long_desc": "A pokeball used to capture pokemon",
            "in": "Lab",
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
                        "npc_dialogue": "Good morning sweetie."
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Oh, since you're heading out, can you help me take this book to Prof. OAK? Thanks sweetie.",
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
                        "quip": "Morning Mom.",
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
            "inventory": [],
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
                        "npc_dialogue": "Wonderful, you're on your way to becoming a great Pokemon trainer! Type GO END to complete your journey.",
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
