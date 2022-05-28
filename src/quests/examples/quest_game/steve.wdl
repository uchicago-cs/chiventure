{ 
    "GAME": {
        "start": "Starting City",
        "intro": "Welcome to 'THE LEGEND OF STEVE'\n \n(HINT: type 'look' to start, and 'talk to <NPC>' to interact with NPCs)",
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
                    "Task Name": "Talk to Land Scout",
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
                }
            ],
            "Task List": [
                {
                    "Task Name": "Talk to Land Scout",
                    "Mission": {
                        "Target Name": "Land Scout",
                        "Type": "Meet NPC"
                    },
                    "Prerequisites": {
                        "Health": 10,
                        "Level": 2
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
                        "Health": 12,
                        "Level": 3,
                        "Tasks": ["Talk to Land Scout"]
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
                        "Health": 10,
                        "Level": 2,
                        "Tasks": ["Talk to Land Scout"]
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
                    "Prerequisites": {
                        "Health": 15,
                        "Level": 4
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
                        "Health": 15,
                        "Level": 4,
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
                        "Health": 15,
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
                        "Health": 20,
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
                "Health": 20,
                "Level": 7,
                "Quests": ["Find Steve"]
            },
            "Task Tree": [
                {
                    "Task Name": "Kill Steve"
                },
                {
                    "Task Name": "Show Steve his Embarassing Baby Photos"
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
                        "Health": 30,
                        "Level": 12,
                        "Quests": ["Find Steve"],
                        "Tasks": ["Obtain Knife"]
                    },
                    "Rewards": {
                        "XP": 500
                    }
                },
                {
                    "Task Name": "Show Steve his Embarassing Baby Photos",
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
    "ROOMS": [
        {
            "id": "Starting City",
            "short_desc": "A city.",
            "long_desc": "A bustling city, whose denizens have pleaded for you to find and vanquish the villainous Steve. Talk to the mayor to get started.",
            "items": [],
            "connections":[
                {"direction": "west", "to": "Pirate Cove"},
                {"direction": "south", "to": "Steve's Lair"}
            ]
        },
        {
            "id": "Steve's Lair",
            "short_desc": "Steve's Lair",
            "long_desc": "A dank cave, smelling of odd mosses and other gross substances, inhabited by Steve.",
            "items": [],
            "connections":[
                {"direction": "north", "to": "Starting City"},
                {"direction": "east", "to": "Steve's Sanctum"}
            ]
        },
        {
            "id": "Pirate Cove",
            "short_desc": "A cove of pirates",
            "long_desc": "The cove is inhabited by all sorts of pirates, lying about drunk. In the back, you can see what appears to be their captain. Near your feet is a scrap of parchment that appears to be some sort of map.",
            "items": [],
            "connections":[
                {"direction": "east", "to": "Starting City"}
            ]
        },
        {
            "id": "Steve's Sanctum",
            "short_desc": "Steve's hidden sanctum",
            "long_desc": "A richly decorated room containing all of Steve's Treasures.",
            "items": [],
            "connections":[
                {"direction": "west", "to": "Steve's Lair"}
            ]
        }
    ],
    "ITEMS": {
        "Search Warrant": {
            "short_desc": "A search warrant.",
            "long_desc": "An official document that grants one the ability to call upon law enforcement",
            "in": "npc",
            "actions": [
                {
                    "action": "FLAUNT",
                    "text_success": "You proudly wave the search warrant, already abusing your authority.",
                    "text_fail": "You realize this is a bad idea."
                }
            ]
        },
        "Pirate Map": {
            "short_desc": "A map", 
            "long_desc": "A map owned by the pirates that details the surrounding area. Steve's hideout is marked.",
            "in": "Pirate Cove",
            "actions": [{
                    "action": "FLAUNT",
                    "text_success": "You proudly wave the pirate map, for some reason.",
                    "text_fail": "You realize this is a bad idea."
                },
                {
                    "action": "READ",
                    "text_success": "You see that Steve's Lair is east of the city",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Sailing Handbook": {
            "short_desc": "A blue handbook.",
            "long_desc": "A somewhat worn handbook that details the basics of sailing.",
            "actions": [{
                    "action": "READ",
                    "text_success": "You learn about sailing.",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Interrogation Handbook": {
            "short_desc": "A purple handbook.",
            "long_desc": "A pristine handbook that details the basics of interrogation.",
            "actions": [{
                    "action": "READ",
                    "text_success": "You learn about interrogation.",
                    "text_fail": "You remembered that you are illiterate. Oops!"
                }
            ]
        },
        "Legendary Sword of Steve": {
            "short_desc": "A gleaming sword",
            "long_desc": "A shining, elegant sword imbued with magic power. Vague runes can be seen on the side, remnants of a lost age.",
            "actions": [{
                "action": "SWING",
                "text_success": "You swing the blade through the air and feel the power of the sword slice the microbes in its path.",
                "text_fail": "You remember that you don't know how to swing a sword. Oops!"
            }
        ]
        },
        "Steve's Embarassing Baby Photos": {
            "short_desc": "A photo book.",
            "long_desc": "A photo book containing pictures from Steve's infancy. The shame is sure to wound him more than any blade.",
            "actions": []
        },
        "Knife": {
            "short_desc": "A knife.",
            "long_desc": "The knife is worn, but of good quality and free of rust.",
            "in": "Steve's Lair"
        }

    },

    "NPCS": {
        "Mayor": {
            "short_desc": "This is the mayor",
            "long_desc": "He really wants to talk to you.",
            "in": "Starting City",
            "inventory": [
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "We're counting on you!"
                    }
                ]
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
                }
            ]
            
        },
        "Land Scout": {
            "short_desc": "This is a Land Scout",
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
                ]
            },
            "Tasks": [
                {
                    "Task Name": "Talk to Land Scout",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, adventurer! I see you have come to help us fight the dastardly STEVE! His lair is to the South of the city, though maybe you might want to speak to his mother first."
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
                                "quip": "South I go!",
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
                ]
            },
            "Tasks": [
                {
                    "Task Name": "Talk to Sea Scout",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, adventurer! I see you have come to help us fight the dastardly STEVE! Information regarding his location might be known to the pirates inhabiting the Pirate Cove to the west."
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
                                "quip": "West I go!",
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
                ]
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
                    "item_id": "Steve's Embarrasing Baby Photos"
                }
            ],
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "It ain't ready yet, dearie!"
                    }
                ]
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
                ]
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
                                "npc_dialogue": "Aaaaaaaahhhhhhhhhhh! Not my embarrasing baby photos!!! Nooooo!"
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
                    "Task Name": "Show Steve his Embarassing Baby Photos",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Let us begin our battle!"
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Aaaaaaaahhhhhhhhhhh! Not my embarrasing baby photos!!! Nooooo!"
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
    },

    "NPCs To be deleted": {
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
                        "npc_dialogue": "Sounds fun! Make sure to be safe on your trip over."
                    },
                    {
                        "id": "2b",
                        "npc_dialogue": "Be safe!"
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
            },
            "Quests": [
                {
                    "Quest Name": "Talk to Oak",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello dearest child, what are you up to?"
                            },
                            {
                                "id": "2",
                                "npc_dialogue": "Oh, are you heading to see Professor Oak? I need you to give him this book.",
                                "actions": [
                                    {
                                        "action": "GIVE_ITEM",
                                        "action_id": "ENCYCLOPEDIA"
                                    }
                                ]
                            },
                            {
                                "id": "3a",
                                "npc_dialogue": "Great! Thanks sweetie."
                            },
                            {
                                "id": "3b",
                                "npc_dialogue": "Why did I get stuck with a beast like you as a son? Go run and do your mother's errands!"
                            }
                        ],
                        "edges": [
                            {
                                "quip": "The spirits compel me to go see Professor Oak",
                                "from_id": "1",
                                "to_id": "2"
                            },
                            {
                                "quip": "Ok",
                                "from_id": "2",
                                "to_id": "3a"
                            },
                            {
                                "quip": "No, don't force your burdens on me, mother!",
                                "from_id": "2",
                                "to_id": "3b"
                            }
                        ]
                    }
                }
            ]
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
            },
            "Tasks": [
                {
                    "Task Name": "Talk to Oak",
                    "Dialogue": {
                        "nodes": [
                            {
                                "id": "1",
                                "npc_dialogue": "Hello, lad, what seems to be the problem?"
                            },
                            {
                                "id": "2a",
                                "npc_dialogue": "Alright, thanks for the book! Talk to me again and I'll actually take it from you"
                            },
                            {
                                "id": "2b",
                                "npc_dialogue": "Oh?! I'll head over right away! Also, I see you have my book! Talk to me again and I'll take that from you."
                            }
                        ],
                        "edges": [
                            {
                                "quip": "My mom finished with your book",
                                "from_id": "1",
                                "to_id": "2a"
                            },
                            {
                                "quip": "My mom wants to see you ;)",
                                "from_id": "1",
                                "to_id": "2b"
                            }
                        ]
                    }
                }
            ]
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
                                "item_id": "POKEBALL"
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