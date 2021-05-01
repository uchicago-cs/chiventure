# Documentation of Non-Playable Characters in chiventure

## Index

### Wiki Pages
- https://github.com/uchicago-cs/chiventure/wiki/NPC-Design-and-Planning
- https://github.com/uchicago-cs/chiventure/wiki/NPC-Player-Interaction-Design-and-Planning
### Modules
- NPC + next steps
- Dialogue + next steps
### Directories
- include/npc
- src/npc
- tests/ncc
### Subdirectories
- src/npc/examples
- src/npc/sandbox

## Modules

### NPC Module
- Contains code relating to the creation, use, and deletion of non-playable characters in chiventure.
- See chiventure/include/npc.h for in-code documentation on the nitty-gritty technical details of NPCs.
- NPCs in chiventure were designed to be a mix of players and items. They have inventories like players, and descriptions like items.
- NPCs are unique in that they can participate in dialogue with the player.
- NPCs also possess a class struct, which contains a stats struct and skill tree, much like a player.

### Next Steps for the NPC Module
- Integrate with chiventure by adding NPCs to the game struct.
- Complete npc-action module currently contained in the branch npc/action so that NPCs can be spoken and traded with in chiventure.
- Integrate with battle module by making it possible to battle NPCs in a chiventure game.
- Integrate with WDL so that NPCs can be specified in that format.

### Dialogue Module
- Contains code relating to the creation, use, and deletion of dialogue in chiventure/an NPC in chiventure.
- See chiventure/include/dialogue.h for in-code documentation on the nitty-gritty technical details of dialogue.
- Dialogue in chiventure was designed to follow the concept of branching-dialogue, where the player's input determines the course of the conversation.
- This was accomplished with structs relating to a directed graph structure, such as nodes and edges.
- A "node" is one possible section of a conversation, including dialogue to be spoken by the NPC and a collection of edges to be accessed by user input.
- An "edge" is a connection between nodes, to be accessed when the player indicates the edge's "keyword". This keyword functions as the edge's identification, therefore, no two edges in a conversation may have the same keyword.
        - Note: currently, in the dialogue_example, the player is able to state the exact keyword, and this is read and parsed by the NPC-CLI in the example. This is not compatible with chiventure's UI/CLI.
        - This "keyword" functionality will soon be replaced with numeric options (see Next Steps for the Dialogue Module).

- A "convo" is a conversation that the NPC can carry out, feature a collection of nodes.

### Next Steps for the Dialogue Module
- Integrate with chiventure's UI/CLI.
        - When keywords were implemented one main issue encountered was the inability to register keywords as non-action-inducing commands. The goal was to have the player type in the keyword (which is a string, and currently can contain more than one word as long as it is smaller than 50 characters. This becomes an issue with CLI's parsing and tokenizing strategy), then advance to the next node.
        - All these issues will be taken care of with the CLI mode feature currently in development. It will allow the CLI to switch from a normal "game mode" to a "conversation mode" in which the program only checks for dialogue options.
- Instead of offering dialogue options based on keywords, numeric options will be given where the player will simply input an integer to indicate which dialogue option they would like to choose. This will not be a significant structural change to how the dialogue functions, but it adheres to dialogue styles present in many other games.

## Directories

### chiventure/include/npc
- Interface of NPC and dialogue modules.

### chiventure/src/npc
- Besides this README, chiventure/src/npc includes an examples directory, a sandbox directory, a src directory, and a CMakeLists.txt file.

### chiventure/tests/npc
- NPC and dialogue testing functions.

## Subdirectories

### chiventure/src/npc/examples
- Contains an npc_example.c, a dialogue_example.c, and a CMakeLists.txt configured to create both executables on `make examples`.
- After making chiventure and making examples, run `src/npc/examples/npc_example` or `src/npc/examples/dialogue_example`.

Notable files:

npc_example.c
- A monkeypatched chiventure executable to display how dialogue *can* (but probably shouldn't) currently look in chiventure, using the backend of the dialogue module. 
- The team did not have time to fully integrate dialogue into chiventure's UI/CLI.
- Our hope is that dialogue in chiventure will someday look more like our dialogue_example.
- Additionally, we hope that built-in commands like `look <item>` will be configured to include looking at NPCs, and that actions such as battling and trading with NPCs will be implemented.

dialogue_example.c
- Uses the backend of the dialogue module and a frontend that is unfortunately incompatible with chiventure as it stands.
- Prints possible player responses in a different color.

### chiventure/src/npc/sandbox
- Contains pre-`make examples` artifact code of what is currently dialogue_example.c.
