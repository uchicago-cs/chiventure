# Battle Library

## Modules

## Examples
This directory contains scripts for running a sample battle.
In order to run a script, type `make examples` followed by `cd examples`. Then run one of the following:

`./battle_command_example.c`
`./battle_flow_example.c`

These are the current scripts: 
* `battle_command_example.c`: Simulates the ability for player input during a battle.
    * Viable commands take the form: 
        * MOVE: when the player decides to perform an action regarding moves
            * USE move_name ON enemy_name: this leads the player to using a move on a specific enemy
            * LIST: lists the possible moves the player can perform
        * HELP: displays possible commands (i.e. MOVE USE... and MOVE LIST)
    * We are also hoping to have these actions in the future
        * ITEM: allows the player to consume an item
            * USE item_name: Player consumes an item
* `battle_flow_example.c`: Runs a sample battle using hard-coded moves for the player and enemy. This demonstrates how to set up a battle correctly.
