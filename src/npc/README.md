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
- An "edge" is a connection between nodes, to be accessed when the player indicates the edge's "keyword". This keyword functions as the edge's identification, therefore, **no two edges in a conversation may have the same keyword.**
    - Note: currently, in the dialogue_example, the player is able to state the exact keyword, and this is read and parsed by the NPC-CLI in the example. This is **not** compatible with chiventure's UI/CLI, and it is certainly possible that the format of this may have to change to become compatible, perhaps more like the "choose a number" concept showcased in the Feature Wishlist Wiki page under NPCs.
- A "convo" is a conversation that the NPC can carry out, feature a collection of nodes.

### Next Steps for the Dialogue Module
- Integrate with chiventure's UI/CLI. Will involve:
    - review of the ncurses library
    - review of existing print functions
    - review of existing CLI/Action Management code
        - One main issue we encountered was the inability to register keywords as non-action-inducing commands. The goal is to have the player type in the keyword (which is a string, and currently can contain more than one word as long as it is smaller than 50 characters. This becomes an issue with CLI's parsing and tokenizing strategy), then advance to the next node. 

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
- The team did not have time to fully integrate dialogue into chiventure's UI/CLI, so this example was the best we could do at the end of the quarter.
- Our hope is that dialogue in chiventure will someday look more like our dialogue_example.
- Additionally, we hope that built-in commands like `look <item>` will be configured to include looking at NPCs, and that actions such as battling and trading with NPCs will be implemented.

dialogue_example.c
- Uses the backend of the dialogue module and a frontend that is unfortunately incompatible with chiventure as it stands.
- Prints possible player responses in a different color.

### chiventure/src/npc/sandbox
- Contains pre-`make examples` artifact code of what is currently dialogue_example.c.
