#include <stdio.h>


enum actions {
	OPEN, // world
	CLOSE, // world
	PUSH, // world
	PULL, // world
	EXAMINE, // synonymous to look at // world
	TURN_ON, // world
	TURN_OFF, // world
	TALK_TO, // NPC
	GIVE, // requires 2 arguments // NPC
	GO, // synonymous with "go", "walk to", "move to" // world
	TAKE, // synonymous with "pick up" // inventory
	DROP, // inventory
	CONSUME, // synonymous with "use", "drink", "eat" // inventory
	USE_ON, // WORLD NPC
	MEDLY // NPC
};

enum action_type {
	ACT_NPC, // give, talk to
	ACT_WORLD, // look at, examine, open, close, push, pull
// turn on, turn off
	ACT_INVENTORY
}

struct action_struct {
	enum actions act;
	enum action_type type;
	char *success; //string
	char *failure;
};

typedef struct action_struct action_t;


//
action_t *action_new(enum actions act, enum action_type type, char *success, char *failure);
int action_init();
void action_free();

/*
 * Use, Pick up/Take, Drop
*/
void act_inventory(action_struct, object_struct, inventory_struct, room_struct);

void act_NPC(action_struct, object_struct, inventory_struct, NPC_struct);

void act_world(action_struct, object_struct, room_struct);

//inventory
