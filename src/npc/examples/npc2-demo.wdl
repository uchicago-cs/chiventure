{
    "GAME": {
        "start": "Bedroom",
        "intro": "Welcome to Pokemon Red! Your name is ASH. A world of dreams and adventures with Pokemon awaits!",
        "end": {
            "in_room": "Outside"
        }
    },
    "ROOMS": {
        "Bedroom": {
            "short_desc": "ASH's bedroom",
            "long_desc": "This is your bedroom. There's a bed and stairs leading downstairs.",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "DOWN"
                }
            ]
        },
        "Living Room": {
            "short_desc": "ASH's living room",
            "long_desc": "Your Mom is here. There is an exit to the South.",
            "connections": [
                {
                    "to": "Bedroom",
                    "direction": "UP"
                },
                {
                    "to": "Outside",
                    "direction": "SOUTH"
                }
            ]
        },
        "Outside": {
            "short_desc": "Outside",
            "long_desc": "This is outside, the final room in the game",
            "connections": [
                {
                    "to": "Living Room",
                    "direction": "NORTH"
                }
            ]
        }
    },
    "ITEMS": {
        "BED": {
            "short_desc": "ASH's bed",
            "long_desc": "Looks comfortable",
            "in": "Bedroom",
            "actions": []
        }
    }
}
