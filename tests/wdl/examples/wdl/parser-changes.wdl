{
    "GAME": {
        "start": "The Mystical Realm",
        "intro": "This is the intro",
        "end": {
            "in_room": "Dungeon of Death"
        }
    },
    "ROOMS": {
        "The Mystical Realm": {
            "short_desc": "This is The Mystical Realm",
            "long_desc": "This is The Mystical Realm. There's a an enchanted table and an exit to the south.",
            "connections": [
                {
                    "to": "Home_base",
                    "direction": "SOUTH"
                }
            ]
        },
        "Home_base": {
            "short_desc": "This is Home Base",
            "long_desc": "This is Home Base. It's empty, but there is an escape to the north.",
            "connections": [
                {
                    "to": "The_Tavern",
                    "direction": "WEST"
                }
            ]
        },
        "The_Tavern": {
            "short_desc": "This is The Tavern",
            "long_desc": "This is The Tavern. There's a chair and an exit to the west. Some even call it the Dungeon of Death...",
            "connections": [
                {
                    "to": "Dungeon of Death",
                    "direction": "DUNGEON OF DEATH"
                }
            ]
        },
        "Dungeon of Death": {
            "short_desc": "This is the Dungeon of Death",
            "long_desc": "This is the Dungeon of Death, the final room in the game",
            "connections": [
                {
                    "to": "The Mystical Realm",
                    "direction": "NORTH"
                }
            ]
        }
    },
    "ITEMS": {
        },
        "ENCHANTED TABLE": {
            "short_desc": "This is a an enchanted table",
            "long_desc": "This is a an enchanted table long",
            "in": "The Mystical Realm",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the an enchanted table",
                    "text_fail": "You cannot push this an enchanted table"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the an enchanted table",
                    "text_fail": "You cannot pull this an enchanted table"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the an enchanted table",
                    "text_fail": "You cannot take this an enchanted table"
                }
            ]
        },
        "TABLE": {
            "short_desc": "This is a table",
            "long_desc": "This is a table long",
            "in": "Home_base",
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