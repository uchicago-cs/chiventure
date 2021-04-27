
#include "playerclass/class_prefabs.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* Testing out how this might work */
class_t* class_prefab_warrior() {
    char *name = "Warrior"; 
    char *short_desc = "Guy with sword."; 
    char *long_desc = "Guy with sword. Guy hit thing in head with sword. Guy use " 
    "few words, sword is better than words.";
    
    obj_t *attr = NULL;
    stats_hash_t *stats = NULL;
    effects_hash_t *effects = NULL;
    return class_new(name, short_desc, long_desc, attr, stats, effects);
}
