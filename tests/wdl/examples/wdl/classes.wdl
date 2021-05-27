{
    "GAME": {
        "start": "room_A",
        "intro": "This is the intro for a test game, which is exactly like that in connected-rooms.wdl execpt it also has classes.",
        "end": {
            "in_room": "room_C"
        }
    },
    "CLASSES": {
        "Knight": {
            "short_desc": "Knight's short description",
            "long_desc": "Knight's long description",
            "attributes": {
                "noble": true,
                "hot-headed": true
            },
            "base_stats": {
                "health": {
                    "current": 100,
                    "max": 200
                },
                "mana": {
                    "current": 20,
                    "max": 100
                }
            },
            "effects": null,
            "skill_tree": null,
            "starting_skills": null
        },
        "Lich": {
            "short_desc": "Lich's short description",
            "long_desc": "Lich's long description",
            "attributes": {
                "evil": true,
                "brittle": true
            },
            "base_stats": {
                "health": {
                    "current": 40,
                    "max": 200
                },
                "mana": {
                    "current": 80,
                    "max": 100
                },
                "spookiness": {
                    "current": 8,
                    "max": 10
                }
            },
            "effects": null,
            "skill_tree": null,
            "starting_skills": null
        },
        "Rogue": {
            "long_desc": "Rogue's long description"
        },
        "Monk": {
            "prefab": true
        },
        "Warrior": {
            "prefab": true,
            "long_desc": "Warrior's overwritten long description",
            "base_stats": {
                "health": {
                    "max": 200,
                    "current": 120
                },
                "mana": {
                    "max": 100,
                    "current": 5
                }
            }
        }
    },
    "ROOMS": {
        "room_A": {
            "short_desc": "This is room A",
            "long_desc": "This is room A. There's a chair and an exit to the south.",
            "connections": [
                {
                    "to": "room_B",
                    "direction": "SOUTH"
                }
            ]
        },
        "room_B": {
            "short_desc": "This is room B",
            "long_desc": "This is room B. There's a table and an exit to the west.",
            "connections": [
                {
                    "to": "room_C",
                    "direction": "WEST"
                }
            ]
        },
        "room_C": {
            "short_desc": "This is room C",
            "long_desc": "This is room C, the final room in the game",
            "connections": [
                {
                    "to": "room_A",
                    "direction": "NORTH"
                }
            ]
        }
    },
    "ITEMS": {
        "CHAIR": {
            "short_desc": "This is a chair",
            "long_desc": "This is a chair long",
            "in": "room_A",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the chair",
                    "text_fail": "You cannot push this chair"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the chair",
                    "text_fail": "You cannot pull this chair"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the chair",
                    "text_fail": "You cannot take this chair"
                }
            ]
        },
        "TABLE": {
            "short_desc": "This is a table",
            "long_desc": "This is a table long",
            "in": "room_B",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the table",
                    "text_fail": "You cannot push this table"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the table",
                    "text_fail": "You cannot pull this table"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the table",
                    "text_fail": "You cannot take this table"
                }
            ]
        }
    }
}