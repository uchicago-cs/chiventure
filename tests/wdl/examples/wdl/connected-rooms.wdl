{
    "GAME": {
        "start": "room_A",
        "intro": "This is the intro",
        "end": {
            "in_room": "room_D"
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
            "long_desc": "This is room B. It's empty, but there is an escape to the north.",
            "connections": [
                {
                    "to": "room_C",
                    "direction": "NORTH"
                }
            ]
        },
        "room_C": {
            "short_desc": "This is room C",
            "long_desc": "This is room C. There's a table and an exit to the west. Some even call it the Dungeon of Death...",
            "connections": [
                {
                    "to": "room_D",
                    "direction": "DUNGEON OF DEATH"
                }
            ]
        },
        "room_D": {
            "short_desc": "This is the Dungeon of Death",
            "long_desc": "This is the Dungeon of Death, the final room in the game",
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