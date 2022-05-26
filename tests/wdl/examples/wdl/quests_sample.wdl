{   
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
                    "Task Name": "Steal Steve's Embarassing Baby Photos"
                }
            ],
            "Task List": [
                {
                    "Task Name": "Kill Steve",
                    "Mission": {
                        "Target Name": "Steve",
                        "Type": "Kill NPC"
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
                    "Task Name": "Steal Steve's Embarassing Baby Photos",
                    "Mission": {
                        "Target Name": "Steve's Embarassing Baby Photos",
                        "Type": "Collect Item"
                    },
                    "Prerequisites": {
                        "Quests": ["Find Steve"],
                        "Tasks": ["Interrogate the Pirate Captain"]
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
    ]
}