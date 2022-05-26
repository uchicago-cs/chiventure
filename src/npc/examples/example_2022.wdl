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
            "long_desc": "This is the library. The Quad is to the South and Mansuetto is upstairs.",
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
            "long_desc": "This is Mansuetto. Downstairs is the way back to The Reg.",
            "connections": [
                {
                    "to": "The Reg",
                    "direction": "DOWN"
                }
            ]
        }
        "The Quad": {
            "short_desc": "The center of campus",
            "long_desc": "This is the quad. The Reg is to the North and Crear is to the West.",
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
            "long_desc": "This is Crear. The Quad is to the East.",
            "connections": [
                {
                    "to": "The Quad",
                    "direction": "East"
                }
            ]
        }
    }
}