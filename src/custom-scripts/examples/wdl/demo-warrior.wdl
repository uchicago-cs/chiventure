{
    "GAME": {
        "start": "room_A",
        "intro": "This is a test game for the Warrior Class. It is based off connected-rooms.wdl",
        "end": {
            "in_room": "room_C"
        }
    },
    "ROOMS": {
        "room_A": {
            "short_desc": "This is room A",
            "long_desc": "This is room A. There's a chair and an exit to the north.",
            "connections": [
                {
                    "to": "room_B",
                    "direction": "NORTH"
                }
            ]
        },
        "room_B": {
            "short_desc": "This is room B",
            "long_desc": "This is room B. There's a table, an exit to the south, and an exit to the east.",
            "connections": [
                {
                    "to": "room_A",
                    "direction": "SOUTH"
                },
                {
                    "to": "room_C",
                    "direction": "EAST"
                }
            ]
        },
        "room_C": {
            "short_desc": "This is room C",
            "long_desc": "This is room C, the final room in the game",
            "connections": [
                {
                    "to": "room_A",
                    "direction": "SOUTH"
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
        }
        "BORJA": {
            "short_desc": "This is the evil king",
            "long_desc": "This is the evil king Borja",
            "in": "room_B",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the evil king",
                    "text_fail": "You cannot push this evil king"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the evil king",
                    "text_fail": "You cannot pull this evil king"
                },
                {
                    "action": "SLASH",
                    "text_success": "You defeated the evil king BORJA",
                    "text_fail": "You cannot slash without a sword",
                    "conditions": [
                        {
                            "type": "INVENTORY",
                            "item_id": "SWORD"
                        }
                    ]
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
                    "text_fail": "You cannot push this table. Maybe if you had a chair...",
                    "conditions": [
                        {
                            "type": "INVENTORY",
                            "item_id": "CHAIR"
                        }
                    ]
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the table",
                    "text_fail": "You cannot pull this table"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the table",
                    "text_fail": "You cannot take this table. Maybe if you had a chair...",
                    "conditions": [
                        {
                            "type": "INVENTORY",
                            "item_id": "CHAIR"
                        }
                    ]
                }
            ]
        }
    }
}