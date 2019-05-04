
struct room_struct {
	list_t NPCs;
	list_t objects;
}
struct object_struct {
	int allowed_actions[]; // we want allowed actions to be an array reflective of enum actions
	int num_allowed_actions;
	int size; // how much inventory space is needed
}

struct player_struct {
	bool alive_or_dead;
}

function(player_struct) {
	playerstrcut =dead; 
}


init_object(*)

{OPEN, CLOSE, PULL, PUSH}