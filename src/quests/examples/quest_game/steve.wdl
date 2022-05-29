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
                            "Task Name": "Obtain the Pirates' Map"
                        },
                        {
                            "Task Name": "Interrogate the Pirate Captain"
                        }
                    ]
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
                    "Task Name": "Get Photos From Mom",
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
                    "Task Name": "Get Photos From Mom",
                    "Mission": {
                        "Target Name": "Steve's Mom",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Quests": ["Find Steve"],
                        "Tasks": ["Talk to Steve's Mom"]
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
        },
        {
            "Quest Name": "Become a Wizard",
            "Rewards": {
                "XP": 999999
            },
            "Task Tree": [
                {
                    "Task Name": "Get Into College"
                }
            ],
            "Task List": [
                {
                    "Task Name": "Get Into College",
                    "Mission": {
                        "Target Name": "Admissions Ally",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Level": 10000
                    }
                }
            ]
        }
    ],
    "ROOMS": {
        "Starting City": {
            "short_desc": "A city.",
            "long_desc": "A bustling city, whose denizens have pleaded for you to find and vanquish the villainous Steve. Talk to the Mayor to get started. \nAround the city, you see the Mayor, a Ground Scout, a Sea Scout, and Admissions Ally",
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
            "long_desc": "A dank cave, smelling of odd mosses and other gross substances, inhabited by Steve. You can see the red glow of a KNIFE in the corner of the room.",
            "connections":[
                {"direction": "NORTH", "to": "Starting City"},
                {"direction": "EAST", "to": "Steve's Sanctum"}
            ]
        },
        "Pirate Cove": {
            "short_desc": "A cove of pirates",
            "long_desc": "The cove is inhabited by all sorts of pirates, lying about drunk. In the back, you can see what appears to be the Pirate Captain Captain. Near your feet is a scrap of parchment that appears to be some sort of PIRATE MAP.",
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
                    "action": "TAKE",
                    "text_success": "You pick up the map and see that Steve's Lair is EAST of the city",
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
        "Baby Photos": {
            "short_desc": "A photo book.",
            "long_desc": "A photo book containing pictures from Steve's infancy. The shame is sure to wound him more than any blade.",
            "in": "npc",
            "actions": [
                {
                    "action": "TAKE",
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
                    "action": "TAKE",
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
                                "npc_dialogue": "Hello, adventurer! I'm sure you are aware of the problem that has been plaguing this land."
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "You don't know? The powerful wizard 'Steve: Destroyer of Worlds, Archmage of Chaos' has been terrorizing the people. If I don't do something about it, it will KILL my reelection campaign!"
                            },
                            {
                                "id": "3",
                                "npc_dialogue": "I need you to track him down and vanquish him from the land by any means necessary! Report back to me once you find his location."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "What problem",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "How can I help?",
                                "from_id": "2",
                                "to_id": "3"
                            }
                        ]
                    }
                },
                {
                    "Quest Name":"Vanquish Steve",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Well done. Now vanquish that heathen!"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "What are you standing there for? Hurry along! I need to go back to embezzeling mon-I mean helping the people!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "** stare blankly **",
                                "from_id": "1",
                                "to_id": "2"
                            }
                        ]
                    }
                }
            ]  
        },
        "Admissions Ally": {
            "short_desc": "The admissions representative for Wizard University, the number 1 university for aspiring Wizards",
            "long_desc": "She wants to talk to you.",
            "in": "Starting City",
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Come back when you're the right level!"
                    }
                ],
                "edges": []
            },
            "Quests": [
                {
                    "Quest Name":"Become a Wizard",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "So, you want to join Wizard University and become a Wizard, huh?"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "Well it ain't gonna be easy. Before you can hop into the wonderful world of functional spellcraft and learn to prevent the infamous SEGFAULT curses, you need to get the right qualifications."
                            },
                            {
                                "id": "3",
                                "npc_dialogue": "Come back to me once you are level 10000. Then you can get started!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "You bet!",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "Oh, what do I need to do?",
                                "from_id": "2",
                                "to_id": "3"
                            }
                        ]
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
                                "npc_dialogue": "You scare me, nut not as much as that Steve guy from that cave SOUTH of the city..."
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "You really scare me. Much more than that Steve guy from that cave SOUTH of the city..."
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
                    "item_id": "Baby Photos"
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
                                "npc_dialogue": "How lovely! I'm glad he's finally starting to meet new people. I was worried he would never meet anyone after staying locked up in that cave down SOUTH all day!"
                            },
                            {
                                "id": "3",
                                "npc_dialogue": "Oh, while you're here, would you like to see some of little Stevie Weevie's baby photos? He was so cute back then!"
                            },
                            {
                                "id": "4",
                                "npc_dialogue": "Shoot, I can't find them right now! Why don't you stop by later to pick them up?"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "I'm a friend of your son, Steve",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "Yes, he's a great friend that I've totally met before! I'm not lying to you at all!",
                                "from_id": "2",
                                "to_id": "3"
                            },
                            {
                                "quip": "I'd love to!",
                                "from_id": "3",
                                "to_id": "4"
                            }
                        ]
                    }
                },
                {
                    "Task Name": "Get Photos From Mom",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Oh, you're back!"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "You're so charming! By the way, I found the baby photos you asked for before."
                            },
                            {
                                "id": "3",
                                "npc_dialogue": "Of course! Here you go, make sure not to lose them!",
                                "actions": [
                                    {
                                        "action": "GIVE_ITEM",
                                        "action_id": "Baby Photos"
                                    }
                                ]
                            }
                        ],
                        "edges": [
                            {
                                "quip": "Yes, love",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "Awesome, can I see them?",
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