{ 
    "GAME": {
        "start": "Starting City",
        "intro": "Welcome to 'THE LEGEND OF STEVE'\n \n(HINT: type 'look' to start, and 'talk to npc <NPC>' to interact with NPCs)",
        "end": {
            "in_room": "Steve's Sanctum"
        }
    },
    "QUESTS": [
        {
            "Quest Name": "Find Steve",
            "Rewards": {
                "XP": 500
            },
            "Task Tree": [
                {
                    "Task Name": "Talk to Ground Scout",
                    "Task Tree": [
                        {
                            "Task Name": "Enter Steve's Lair"
                        },
                        {
                            "Task Name": "Talk to Steve's Mom"
                        }
                    ]
                },
                {
                    "Task Name": "Talk to Sea Scout",
                    "Task Tree": [
                        {
                            "Task Name": "Find the Pirate Cove",
                            "Task Tree": [
                                {
                                    "Task Name": "Obtain the Pirates' Map"
                                },
                                {
                                    "Task Name": "Interrogate the Pirate Captain"
                                }
                            ]
                        }
                    ]
                },
                {
                    "Task Name": "Impossible Task"
                }
            ],
            "Task List": [
                {
                    "Task Name": "Talk to Ground Scout",
                    "Mission": {
                        "Target Name": "Ground Scout",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 0
                    },
                    "Rewards": {
                        "XP": 100,
                        "Item": "Search Warrant"
                    }
                },
                {
                    "Task Name": "Enter Steve's Lair",
                    "Mission": {
                        "Target Name": "Steve's Lair",
                        "Type": "Visit Room"
                    },
                    "Prerequisites": {
                        "Level": 0,
                        "Tasks": ["Talk to Ground Scout"]
                    },
                    "Rewards": {
                        "XP": 100
                    }
                },
                {
                    "Task Name": "Talk to Steve's Mom",
                    "Mission": {
                        "Target Name": "Steve's Mom",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 0,
                        "Tasks": ["Talk to Ground Scout"]
                    },
                    "Rewards": {
                        "XP": 50
                    }
                },
                {
                    "Task Name": "Talk to Sea Scout",
                    "Mission": {
                        "Target Name": "Sea Scout",
                        "Type": "Meet NPC"
                    },
                    "Rewards": {
                        "XP": 100,
                        "Item": "Search Warrant"
                    }
                },
                {
                    "Task Name": "Find the Pirate Cove",
                    "Mission": {
                        "Target Name": "Pirate Cove",
                        "Type": "Visit Room"
                    },
                    "Prerequisites": {
                        "Level": 2,
                        "Tasks": ["Talk to Sea Scout"]
                    },
                    "Rewards": {
                        "XP": 100
                    }
                },
                {
                    "Task Name": "Obtain the Pirates' Map",
                    "Mission": {
                        "Target Name": "Pirate Map",
                        "Type": "Collect Item"
                    },
                    "Prerequisites": {
                        "Level": 4,
                        "Tasks": ["Talk to Sea Scout", "Find the Pirate Cove"]
                    },
                    "Rewards": {
                        "XP": 200,
                        "Item": "Sailing Handbook"
                    }
                },
                {
                    "Task Name": "Interrogate the Pirate Captain",
                    "Mission": {
                        "Target Name": "Pirate Captain",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 5,
                        "Tasks": ["Talk to Sea Scout", "Find the Pirate Cove"]
                    },
                    "Rewards": {
                        "XP": 250,
                        "Item": "Interrogation Handbook"
                    }
                },
                {
                    "Task Name": "Impossible Task",
                    "Mission": {
                        "Target Name": "Mayor",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 100000
                    }
                }
            ]
        },
        {
            "Quest Name": "Vanquish Steve",
            "Rewards": {
                "XP": 1000,
                "Item": "Legendary Sword of Steve"
            },
            "Prerequisites": {
                "Level": 7,
                "Quests": ["Find Steve"]
            },
            "Task Tree": [
                {
                    "Task Name": "Kill Steve"
                },
                {
                    "Task Name": "Talk to Mayor",
                    "Task Tree": [
                        {
                            "Task Name": "Show Steve his Embarrassing Baby Photos"
                        }
                    ]
                }
            ],
            "Task List": [
                {
                    "Task Name": "Kill Steve",
                    "Mission": {
                        "Target Name": "Steve",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 8,
                        "Quests": ["Find Steve"],
                        "Tasks": ["Obtain Knife"]
                    },
                    "Rewards": {
                        "XP": 500
                    }
                },
                {
                    "Task Name": "Talk to Mayor",
                    "Mission": {
                        "Target Name": "Mayor",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Quests": ["Find Steve"]
                    }
                },
                {
                    "Task Name": "Show Steve his Embarrassing Baby Photos",
                    "Mission": {
                        "Target Name": "Steve",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Quests": ["Find Steve"],
                        "Tasks": ["Talk to Steve's Mom"]
                    },
                    "Rewards": {
                        "XP": 100
                    }
                },
                {
                    "Task Name": "Obtain Knife",
                    "Mission": {
                        "Target Name": "Knife",
                        "Type": "Collect Item"
                    }
                }
            ]
        }
    ],
    "ROOMS": {
        "Starting City": {
            "short_desc": "A city.",
            "long_desc": "A bustling city, whose denizens have pleaded for you to find and vanquish the villainous Steve. Talk to the mayor to get started.",
            "connections":[
                {
                    "to": "Pirate Cove",
                    "direction": "WEST"
                },
                {"direction": "SOUTH", "to": "Steve's Lair"}
            ]
        },
        "Steve's Lair": {
            "short_desc": "Steve's Lair",
            "long_desc": "A dank cave, smelling of odd mosses and other gross substances, inhabited by Steve.",
            "connections":[
                {"direction": "NORTH", "to": "Starting City"},
                {"direction": "EAST", "to": "Steve's Sanctum"}
            ]
        },
        "Pirate Cove": {
            "short_desc": "A cove of pirates",
            "long_desc": "The cove is inhabited by all sorts of pirates, lying about drunk. In the back, you can see what appears to be their captain. Near your feet is a scrap of parchment that appears to be some sort of map.",
            "connections":[
                {"direction": "EAST", "to": "Starting City"}
            ]
        },
        "Steve's Sanctum": {
            "short_desc": "Steve's hidden sanctum",
            "long_desc": "A richly decorated room containing all of Steve's Treasures.",
            "connections":[
                {"direction": "WEST", "to": "Steve's Lair"}
            ]
        }
    },
    "ITEMS": {
        "Search Warrant": {
            "short_desc": "A search warrant.",
            "long_desc": "An official document that grants one the ability to call upon law enforcement",
            "in": "npc",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "You pull out and proudly wave the search warrant, already abusing your authority.",
                    "text_fail": "You realize this is a bad idea."
                }
            ]
        },
        "Pirate Map": {
            "short_desc": "A map", 
            "long_desc": "A map owned by the pirates that details the surrounding area. Steve's hideout is marked.",
            "in": "Pirate Cove",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "You pull out the map and see that Steve's Lair is EAST of the city",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Sailing Handbook": {
            "short_desc": "A blue handbook.",
            "long_desc": "A somewhat worn handbook that details the basics of sailing.",
            "in": "npc",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "You pull out the book and learn about sailing.",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Interrogation Handbook": {
            "short_desc": "A purple handbook.",
            "long_desc": "A pristine handbook that details the basics of interrogation.",
            "in": "npc",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "You pull out the book and learn about interrogation.",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Legendary Sword of Steve": {
            "short_desc": "A gleaming sword",
            "long_desc": "A shining, elegant sword imbued with magic power. Vague runes can be seen on the side, remnants of a lost age.",
            "in": "npc",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the blade through the air and feel the power of the sword slice the microbes in its path.",
                    "text_fail": "You remember that you don't know how to swing a sword. Oops!"
                }
            ]
        },
        "Steve's Embarrassing Baby Photos": {
            "short_desc": "A photo book.",
            "long_desc": "A photo book containing pictures from Steve's infancy. The shame is sure to wound him more than any blade.",
            "in": "npc",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "You pull our the photos and see the most absurd photos known to man. Photos like these would bring great shame to the elite",
                    "text_fail": "You forgot your glasses at home, but you're sure something interesting is in the photos"
                }
            ]
        },
        "Knife": {
            "short_desc": "A knife.",
            "long_desc": "The knife is worn, but of good quality and free of rust.",
            "in": "Steve's Lair",
            "actions": [
                {
                    "action": "PULL",
                    "text_success": "About time.",
                    "text_fail": "LV is too low!"
                }
            ]
        }
    },
    "NPCS": {
        "Mayor": {
            "short_desc": "This is the mayor",
            "long_desc": "He really wants to talk to you.",
            "in": "Starting City",
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "We're counting on you!"
                    }
                ],
                "edges": []
            },
            "Quests": [
                {
                    "Quest Name": "Find Steve",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, adventurer! Please help us fight Steve!"
                            }
                        ],
                        "edges": []
                    }
                },
                {
                    "Quest Name":"Vanquish Steve",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Well done. Now vanquish that heathen!"
                            }
                        ],
                        "edges": []
                    }
                }
            ],
            "Tasks": [
                {
                    "Task Name": "Talk to Mayor",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Woah, are those Steve's baby photos?"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "Look at little Stevie Weevie, he's so cute! Wow, if he saw these, it would be a fate worse than death!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "Yup",
                                "from_id": "1",
                                "to_id": "2"
                            }
                        ]
                    }
                },
                {
                    "Task Name": "Impossible Task",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "How are you seeing this, wretched hacker? Get out of the game's files and get a life!"
                            }
                        ],
                        "edges": []
                    }
                }
            ]
            
        },
        "Ground Scout": {
            "short_desc": "This is a Ground Scout",
            "long_desc": "She wants to talk to you.",
            "in": "Starting City",
            "inventory": [
                {
                    "item_id": "Search Warrant"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Well, go on. You have a task to do."
                    }
                ],
                "edges": []
            },
            "Tasks": [
                {
                    "Task Name": "Talk to Ground Scout",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, adventurer! I see you have come to help us fight the dastardly STEVE! His lair is to the SOUTH of the city, though maybe you might want to speak to his mother first."
                            },
                            {
                                "id": "2a",
                                "npc_dialogue": "Good Luck! Here, take this Search Warrant."
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Very well. Here, take this Search Warrant."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "SOUTH I go!",
                                "from_id": "1",
                                "to_id": "2a"
                            },
                            {
                                "quip": "Um, ok...",
                                "from_id": "1",
                                "to_id": "2b"
                            }
                        ]
                    }
                }
            ]
            
        },
        "Sea Scout": {
            "short_desc": "This is a Sea Scout",
            "long_desc": "He wants to talk to you.",
            "in": "Starting City",
            "inventory": [
                {
                    "item_id": "Search Warrant"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Well, go on. You have a task to do."
                    }
                ],
                "edges": []
            },
            "Tasks": [
                {
                    "Task Name": "Talk to Sea Scout",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, adventurer! I see you have come to help us fight the dastardly STEVE! Information regarding his location might be known to the pirates inhabiting the Pirate Cove to the WEST."
                            },
                            {
                                "id": "2a",
                                "npc_dialogue": "Good Luck! Here, take this Search Warrant."
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Show a little more enthusiasm, will you? Here, take this Search Warrant."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "WEST I go!",
                                "from_id": "1",
                                "to_id": "2a"
                            },
                            {
                                "quip": "Um, ok...",
                                "from_id": "1",
                                "to_id": "2b"
                            }
                        ]
                    }
                }
            ]
        },
        "Pirate Captain": {
            "short_desc": "This is a Pirate Captain",
            "long_desc": "He does not want to talk to you.",
            "in": "Pirate Cove",
            "inventory": [],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Arrghh!"
                    }
                ],
                "edges": []
            },
            "Tasks": [
                {
                    "Task Name": "Interrogate the Pirate Captain",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Who dares disturb me!"
                            },
                            {
                                "id": "2a",
                                "npc_dialogue": "You scare me."
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "You really scare me."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "Someone who is stronger than you",
                                "from_id": "1",
                                "to_id": "2a"
                            },
                            {
                                "quip": "Me",
                                "from_id": "1",
                                "to_id": "2b"
                            }
                        ]
                    }
                }
            ]
        },
        "Steve's Mom": {
            "short_desc": "This is Steve's Mom",
            "long_desc": "She is slightly reluctant to talk to you.",
            "in": "Starting City",
            "inventory": [
                {
                    "item_id": "Steve's Embarrassing Baby Photos"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "It ain't ready yet, dearie!"
                    }
                ],
                "edges": []
            },            
            "Tasks": [
                {
                    "Task Name": "Talk to Steve's Mom",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Who are you?"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "*Gasp* Please don't! Steve's such a precious boy! Look, I have all these photos from when he was a baby!"
                            },
                            {
                                "id": "3",
                                "npc_dialogue": "Yes! Oh dear, I seem to have lost them. I'll look around, come back later if you need to see them."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "I need to kill Steve",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "Baby Photos?",
                                "from_id": "2",
                                "to_id": "3"
                            }
                        ]
                    }
                }
            ]
        },
        "Steve": {
            "short_desc": "This is Steve",
            "long_desc": "The vanquisher of the heavens, Steve is a legendary warrior with an equally renowned blade.",
            "in": "Steve's Lair",
            "inventory": [
                {
                    "item_id": "Legendary Sword of Steve"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "*Sniffle*"
                    }
                ],
                "edges": []
            },
            "Tasks": [
                {
                    "Task Name": "Kill Steve",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Let us begin our battle!"
                            },
                            {
                                "id": "2a",
                                "npc_dialogue": "Aaaaahhhhh! I surrender! I surrender!"
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Aaaaaaaahhhhhhhhhhh! Not my embarrassing baby photos!!! Nooooo!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "En Garde!",
                                "from_id": "1",
                                "to_id": "2a"
                            }
                        ]
                    }
                },
                {
                    "Task Name": "Show Steve his Embarrassing Baby Photos",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Let us begin our battle!"
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Aaaaaaaahhhhhhhhhhh! Not my embarrassing baby photos!!! Nooooo!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "I have something much more interesting to show you",
                                "from_id": "1",
                                "to_id": "2b"
                            }
                        ]
                    }
                }
            ]
        }
    }
}