# Battle State README.md

## The src directory and ../include/battle contain the following files:

- **battle_ai.c / battle_ai.h:** Deal with functions specific to only the AI player. Focus on determining the AI’s moves systematically or randomly, depending on the difficulty level of the game.

- **battle_flow_structs.c / battle_flow_structs.h:** Contain player, game, battle, and enemy structs and create functions to control the battles. 

- **battle_flow.c / battle_flow.h:** Control what happens in the battle during runtime. Functions make use of more specific functions in the lower modules to carry out each step of the battle.

- **battle_logic.c / battle_logic.h:** Read and update the battle state during battle by managing those functions accordingly. Some functions help keep the battle flow in place by checking if the battle is over or determining what player gets the first move, while other functions use battle logic to manipulate the battle state directly.

- **battle_moves.c / battle_moves.h:** Contain functions for creating and freeing moves that can used during a battle.

- **battle_print.c / battle_print.h:** Keep track of the battle flow by returning messages relevant to the current battle.

- **battle_state.c / battle_state.h:** Contain functions that deal with creating a new battle and opponents, including the battle_t, move_t and combatant_t structs.

- **battle_default_objects.c / battle_default_objects.h:** Contain functions that return a random battle_item_t, stat_t, and move_t with default values. 

- **battle_common.h:** Contains general structs for environment, battles, and combatants.

- **battle_structs.h:** Contains item, move, and stat structs.
