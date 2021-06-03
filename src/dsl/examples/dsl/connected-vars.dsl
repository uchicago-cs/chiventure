$rm = """ROOM room {letter}
    short: "This is room {letter}"
    long: "This is room {letter}. There's a {contents} and an exit to the {exitdir}."
    connections: {exitdir}   TO room {nextletter}
        ITEM {contents}"""

GAME START room A END room C

$rm {letter: A, contents: chair, exitdir: SOUTH, nextletter: B}
$rm {letter: B, contents: table, exitdir: WEST, nextletter: C}
$rm {letter: C, contents: trophy, exitdir: NORTH, nextletter: A}