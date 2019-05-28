#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.pb-c.h"
#include "load.h"
#define MAX_BUF_SIZE 1000000


// see load.h
size_t read_file(char *filename, unsigned max_length, uint8_t *out)
{
    size_t cur_len = 0;
    size_t nread;
    FILE *fp = fopen(filename, "r");
    while((nread = fread(out + cur_len, 1, max_length - cur_len, fp)) != 0) {
        cur_len += nread;
        if (cur_len == max_length) {
            fprintf(stderr, "max message length exceed\n");
            return max_length;
        }
    }
    fclose(fp);
    return cur_len;
}


// see load.h
int load_attribute_value(Attribute_value *av, attribute_value_t *av_t)
{
    
    if (av_t == NULL) {
        fprintf(stderr, "given null attribute_value_t struct\n");
        return -1;
    }

    if (av->double_value != NULL) {
        av_t->double_value = av->double_value;
    } else {
        av_t->double_value = NULL;
    }

    if (av->char_val != NULL) {
        av_t->char_val = av->char_val;
    } else {
        av_t->char_val = NULL;
    }

    if (av->bool_val != NULL) {
        av_t->bool_val = av->bool_val;
    } else {
        av_t->bool_val = NULL;
    }

    if (av->str_val != NULL) {
        av_t->str_val = av->str_val;
    } else {
        av_t->str_val = NULL;
    }

    if (av->int_val != NULL) {
        av_t->int_val = av->int_val;
    } else {
        av_t->int_val = NULL;
    }

    return 0;
}


// see load.h
int load_attribute(Attribute *a, attribute_t *a_t)
{
    if (a_t == NULL) {
        fprintf(stderr, "given null attribute_t struct\n");
        return -1;
    }

    a_t->attribute_key = a->attribute_key;

    if (strcmp(a->attribute_tag, "DOUBLE") == 0) {
        a_t->attribute_tag = DOUBLE;
    } else if (strcmp(a->attribute_tag, "BOOLE") == 0) {
        a_t->attribute_tag = BOOLE;
    } else if (strcmp(a->attribute_tag, "CHARACTER") == 0) {
        a_t->attribute_tag = CHARACTER;
    } else if (strcmp(a->attribute_tag, "STRING") == 0) {
        a_t->attribute_tag = STRING;
    } else {
        a_t->attribute_tag = INTEGER;
    } 

    load_attribute_value(a->attribute_value, a_t->attribute_value);

    return 0;
}


// see load.h
int load_item(Item *i, item_t *i_t);
{
    if(i_t == NULL) {
        fprintf(stderr, "given null item_t struct\n");
        return -1;
    }

    i_t->item_id = i->item_id;

    if (i->short_desc != NULL) {
        i_t->short_desc = i->short_desc;
    } else {
        i_t->short_desc = NULL;
    }

    if (i->long_desc != NULL) {
        i_t->long_desc = i->long_desc;
    } else {
        i_t->long_desc = NULL;
    }

    // Fill in the new attribute (assuming that the number and id's of the attributes don't change)
    int iter;
    for (iter = 0; iter < i->attributes_len; iter++) {
        switch (i->attributes[iter]->attribute_tag) {
            case STRING:
                int set_str_success = set_str_attr(i_t, i->attributes[iter]->attribute_key, i->attributes[iter]->attribute_value);
                if (set_str_success != SUCCESS){
                    fprintf(stderr, "Could not set string attribute for item \n");
                    return -1;
                }
                break;
      
            case INTEGER:
                int set_int_success = set_int_attr(i_t, i->attributes[iter]->attribute_key, i->attributes[iter]->attribute_value);
                if (set_int_success != SUCCESS){
                    fprintf(stderr, "Could not set integer attribute for item \n");
                    return -1;
                }
                break;
      
            case DOUBLE:
                int set_double_success = set_double_attr(i_t, i->attributes[iter]->attribute_key, i->attributes[iter]->attribute_value);
                if (set_double_success != SUCCESS){
                    fprintf(stderr, "Could not set double attribute for item \n");
                    return -1;
                }
                break;
        
            case CHARACTER:
                int set_char_success = set_char_attr(i_t, i->attributes[iter]->attribute_key, i->attributes[iter]->attribute_value);
                if (set_char_success != SUCCESS){
                    fprintf(stderr, "Could not set character attribute for item \n");
                    return -1;
                }
                break;
      
            case BOOLE:
                int set_bool_success = set_bool_attr(i_t, i->attributes[iter]->attribute_key, i->attributes[iter]->attribute_value);
                if (set_bool_success != SUCCESS){
                    fprintf(stderr, "Could not set boole attribute for item \n");
                    return -1;
                }
                break;
        
            default:
                fprintf(stderr, "Could not set any attribute \n");
                return -1;
        }
  
    }
    return 0;
}


// Completed code for condition, will delete in master
int load_condition(Condition *c, condition_t *c_t)
{
    if (c_t == NULL) {
        fprintf(stderr, "given null condition_t struct\n");
        return -1;
    }

    if (c->item_id != NULL) {
        c_t->item->item_id = c->item_id;
    } else {
        c_t->item->item_id = NULL;
    }

    // something here? idk depends on game state

    // optional Attribute here but might change
    if (i_t->expected_attribute != NULL){
        i_t->expected_attribute = malloc(sizeof(Attribute));
    }
    int load_attribute_success = load_attribute(i->expected_attribute, i_t->expected_attribute) 
    if (load_attribute_success != 0) {
        fprintf(stderr, "Could not load expected attribute for condition \n");
    }
    return 0;
}


// see load.h
int load_path(Path *p, path_t *p_t, game_t *g_t)
{
    if (p_t == NULL) {
        fprintf(stderr, "given null path_t struct\n");
        return -1;
    }

    if (p->direction != NULL) {
        p_t->direction = p->direction;
    } else {
        p_t->direction = NULL;
    }

  
    // if game state changes dest to a pointer to something, this will need to change!!
    if (p->dest != NULL) {   // dest cannot be NULL at the moment
        p_t->dest = p->dest;
        // Write commented code here to loop through the list of rooms and assign a pointer instead of room ID (either Ellyn or Jonah)
    } else {
        p_t->dest = NULL;
    }

    return 0;
}


// see load.h
int load_room(Room *r, room_t *r_t, item_t **all_items, int all_items_len, game_t *g_t)
{
    if (r_t == NULL) {
        fprintf(stderr, "given null room_t struct\n");
        return -1;
    }

    r_t->room_id = r->room_id;

    if (r->short_desc != NULL) {
        r_t->short_desc = r->short_desc;
    } else {
        r_t->short_desc = NULL;
    }

    if (r->long_desc != NULL) {
        r_t->long_desc = r->long_desc;
    } else {
        r_t->short_desc = NULL;
    }
  
    // Free all items in the room
    ITER_ALL_ITEMS_IN_ROOM(r_t, curr_item){
        int item_free_success = item_free(curr_item);
        if (item_free_success != 0){
            fprintf(stderr, "Failed to remove/ free item from room \n");
        }
    }
  
    // Fill room with items (we assume that no item get destroyed/created during the game)
    int iter;
    int j;
    for (iter = 0; iter < r->items_len; iter++){
        for (j = 0; j < all_items_len; j++){
            if (r->items[iter]->item_id == all_items[j]->item_id){
                int load_item_success = load_item(r->items[iter], all_items[j]);
                if (load_item_success != 0){
                    fprintf(stderr, "Failed to load item in room \n");
                }
                int add_item_success = add_item_to_room(r_t, all_items[j]);
                if (add_item_success != 0){
                    fprintf(stderr, "Failed to add item to room \n");
                }
            }
        }
    }
    
  // path stuff here (Jonah would you be able to write this?)

  return 0;
}


// see load.h
int load_player(Player *p, player_t *p_t, item_t **all_items, int all_items_len, game_t *g_t)
{
    if (p_t == NULL) {
        fprintf(stderr, "given null player_t struct\n");
        return -1;
    }

    p_t->player_id = p->player_id;

    if (p->level != NULL) {
        p_t->level = p->level;
    } else {
        p_t->level = NULL;
    }

    if (p->health != NULL) {
        p_t->health = p->health;
    } else {
        p_t->health = NULL;
    }

    if (p->xp != NULL) {
        p_t->xp = p->xp;
    } else {
        p_t->xp = NULL;
    }

    // Free all items in the inventory
    ITER_ALL_ITEMS_IN_INVENTORY(p_t, curr_item){
        int item_free_success = item_free(curr_item);
        if (item_free_success != 0){
            fprintf(stderr, "Failed to remove/ free item from inventory \n");
        }
    }
  
    // Fill inventory with items (we assume that no item get destroyed/created during the game)
    int iter;
    int j;
    for (iter = 0; iter < p->inventory_len; iter++){
        for (j = 0; j < all_items_len; j++){
            if (strcmp(p->inventory[iter]->item_id, all_items[j]->item_id) == 0){
                int load_item_success = load_item(p->inventory[iter], all_items[j]);
                if (load_item_success != 0){
                    fprintf(stderr, "Failed to load item in inventory \n");
                }
                int add_item_success = add_item_to_player(p_t, all_items[j]);
                if (add_item_success != 0){
                    fprintf(stderr, "Failed to add item to inventory \n");
                }
            }
        }
    }
    return 0;
}    


// see load.h
int load_game(Game *g, game_t *g_t)
{
    if (g_t == NULL) {
        fprintf(stderr, "given null game_t struct\n");
        return -1;
    }
  
    // Malloc an array of all items in the game
    int item_len = 0;
    room_t *curr_r;
    ITER_ALL_ROOMS(g_t, curr_r){
        item_len += COUNT_ITEMS_IN_ROOM(curr_r);
    }
    player_t *curr_p;
    ITER_ALL_PLAYERS(g_t, curr_p){
        item_len += COUNT_ITEMS_IN_INVENTORY(curr_p);
    }
    item_t **all_items = malloc(sizeof(item_t*) * item_len);
  
    // Create a deep copy of all items in the game
    int iter = 0;
    ITER_ALL_ROOMS(g_t, curr_r){
        ITER_ALL_ITEMS_IN_ROOM(curr_r, curr_item){
            all_items[iter] = item_new(curr_item->item_id, curr_item->short_desc, curr_item->long_desc);
            iter++;
        }
    }
    
    iter = 0;
    ITER_ALL_PLAYERS(g_t, curr_p){
        ITER_ALL_ITEMS_IN_INVENTORY(curr_r, curr_item){
            all_items[iter] = item_new(curr_item->item_id, curr_item->short_desc, curr_item->long_desc);
            iter+=1;
        }
    }
  
  
    // Malloc an array of all paths in the game
    int path_len = 0;
    ITER_ALL_ROOMS(g_t, curr_r){
        path_len += COUNT_PATHS_IN_ROOM(curr_r);
    }
    path_t **all_paths = malloc(sizeof(path_t*) * path_len);
  
    // Create a deep copy of all paths in the game
    iter = 0;
    ITER_ALL_ROOMS(g_t, curr_r){
        ITER_ALL_PATHS(curr_r, curr_path){
            // This may change in the future depends on how dest changes, should also include direction, should talk to game state
            all_paths[iter] = path_new(curr_path->dest);  
            ITER_ALL_CONDITIONS(curr_path, curr_condi){
                int add_condition_success = add_condition_to_path(all_paths[iter], curr_condi);
                if (add_condition_success != SUCCESS){
                    fprintf(stderr, "Condition cannot be loaded into path deep copy. Will proceed \n");
                }
            }
            iter+=1;
        }
    }
  
    // Load room into game
    int i;
    for (i = 0; i < g->room_len; i++){
        ITER_ALL_ROOMS(g_t, curr_r){
            if (strcmp(g->all_rooms[i]->room_id, curr_r->room_id) == 0){
                int load_room_success = load_room(g->all_rooms[i], curr_r);
                if (load_room_success != 0){
                    fprintf(stderr, "Failed to load room into game. Abort! \n");
                    return -1;
                }
            }
        }
    }
    
    // Load player into game
    for (i = 0; i < g->player_len; i++){
        ITER_ALL_PLAYERS(g_t, curr_p){
            if (strcmp(g->all_players[i]->player_id, curr_p->player_id) == 0){
                int load_player_success = load_player(g->all_players[i], curr_p);
                if (load_player_success != 0){
                    fprintf(stderr, "Failed to load player into game. Abort! \n");
                    return -1;
                }
            }
        }
    } 
  
    // Note: in game state structs, curr_room is a room struct that contains a room_id
    // In the proto struct, curr_room is simply the room_id as a string
    if(g->curr_room != -1) {
        room_t *curr_r;
        ITER_ALL_ROOMS(g_t, curr_r) {
            if (strcmp(curr_r->room_id, g->curr_room) == 0){
                move_room(g_t, curr_r)
            }
        }
    }

    if (g->curr_player != -1) {
        player_t *curr_p;
        ITER_ALL_PLAYERS(g_t, curr_p) {
            if (strcmp(curr_p->player_id, g->curr_player) == 0){
                set_curr_player(g_t, curr_p);
            }
        }
    } 

    return 0;
}


// see load.h
int load(char *filename, Game *g, game_t *g_t)
{
    uint8_t buffer[MAX_BUF_SIZE];
    size_t game_len = read_file(filename, MAX_BUF_SIZE, buffer);
    printf("game_len: %ld\n", game_len);

    g = game__unpack(NULL, game_len, buffer);

    if (g == NULL) {
        fprintf(stderr, "error unpacking incoming game\n");
        exit(1);
    }

    load_game(g, g_t);

    game__free_unpacked(g, NULL);

    return 0;
}

