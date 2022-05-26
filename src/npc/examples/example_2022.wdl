{
    "GAME": {
        "start": "The Reg",
        "intro": "Welcome to the Reg! Your name is SAM. Your journey is just beginning. !\n \n(HINT: type 'look' to start, and 'talk to <NPC>' to interact with NPCs, use 'HELP' for more information)",
        "end": {
            "in_room": "Mansuetto"
        }
    },
    "ROOMS": {
        "The Reg": {
            "short_desc": "The library",
            "long_desc": "A place to get work done",
            "connections": [
                {
                    "to": "Mansuetto",
                    "direction": "UP"
                }
                {
                    "to": "The Quad",
                    "direction": "South"
                }
            ]
        },
        "Mansuetto": {
            "short_desc": "The bubble library",
            "long_desc": "That place from divergent",
            "connections": [
                {
                    "to": "The Reg",
                    "direction": "DOWN"
                }
            ]
        }
        "The Quad": {
            "short_desc": "The center of campus",
            "long_desc": "A big grassy area with old buildings",
            "connections": [
                {
                    "to": "The Reg",
                    "direction": "North"
                }
                {
                    "to": "Crear"
                    "direction": "West"
                }
            ]
        }
        "Crear": {
            "short_desc": "CS Library",
            "long_desc": "Looks old on the outside, looks new on the inside",
            "connections": [
                {
                    "to": "The Quad",
                    "direction": "East"
                }
            ]
        }
    }
}