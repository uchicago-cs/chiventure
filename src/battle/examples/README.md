# Battle Library

## Examples
This directory contains scripts for running a sample battle.
In order to run a script:
1. Make sure you have built Chiventure (see the main Chiventure README for instructions)
2. Enter the `chiventure\build` directory
3. Run `make examples` to build the example files
4. Use `cd src/battle/examples` to enter the battle examples directory
5. Run `./battle_command_example`, `./battle_flow_example`, or `./battle_cli_example` to run a sample battle

These are the current scripts: 
* `battle_command_example.c`: Simulates the ability for player input during a battle.
    * Viable commands take the form: 
        * MOVE: when the player decides to perform an action regarding moves
            * USE move_name ON enemy_name: this leads the player to using a move on a specific enemy
            * LIST: lists the possible moves the player can perform
        * HELP: displays possible commands and available items (i.e. MOVE USE..., MOVE LIST, USE.... )
        * USE item_id: Player consumes an item
        * ITEM LIST : lists the available items
        * the user story has more about commands and an example of a battle
            * https://github.com/uchicago-cs/chiventure/wiki/RPG-Battle-Systems-%7C-User-Stories
* `battle_flow_example.c`: Runs a sample battle using hard-coded moves for the player and enemy. This demonstrates how to set up a battle correctly.
* `battle_cli_example.c`: Demonstrates integration with the Chiventure CLI. This is the most recent example file (added May 2021)
