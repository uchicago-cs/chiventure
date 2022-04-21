/*
 * Defines a player class struct to store base class information.
 *
 * For more information see class.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "playerclass/class_prefabs.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/inventory.h"
#include "common/utlist.h"



/* See class.h */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_hash_t* stat, effects_hash_t* effect) {
    int rc;
    class_t* c;

    c = (class_t*) calloc(1, sizeof(class_t));

    if(c == NULL) {
        fprintf(stderr, "Could not allocate space for class_new.\n");
        return NULL;
    }

    rc = class_init(c, name, shortdesc, longdesc, attr, stat, effect);

    if (rc == EXIT_FAILURE) {
        fprintf(stderr, "Could not initalize values for class_new.\n");
    }

    return c;
}

/* See class.h */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_hash_t* stat, effects_hash_t* effect) {
    if (class == NULL) {
        fprintf(stderr, "Class to initialize in class_init is NULL.\n");
        return EXIT_FAILURE;
    }

    class->name = (char*) calloc(MAX_NAME_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for name in class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->name, name, MAX_NAME_LEN);

    class->num_parent_class = 0;
    class->parent_class_names = NULL;

    class->shortdesc = (char*) calloc(MAX_SHORT_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for short description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->shortdesc, shortdesc, MAX_SHORT_DESC_LEN);

    class->longdesc = (char*) calloc(MAX_LONG_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for long description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->longdesc, longdesc, MAX_LONG_DESC_LEN);

    class->attributes = attr;
    class->base_stats = stat;
    class->effects = effect;

    /* These are initialized by class_init_skills() */
    class->skilltree = NULL;
    class->starting_skills = NULL;

    return EXIT_SUCCESS;
}

/*
 * Creates a shortdesc for a multiclass by simply listing the component classes.
 *
 * Paramaters:
 *  - base_class: the character's base class (their current class).
 *  - second_class: the class being added to the original class.
 *
 * Returns:
 *  - a pointer to a string with the new shortdesc.
 */
char* multiclass_shortdesc(class_t* base_class, class_t* second_class) {

    int num_multiclass = 2 + base_class->num_parent_class + second_class->num_parent_class;

    char* new_shortdesc = (char*) malloc(MAX_SHORT_DESC_LEN + 1);
    strncat(new_shortdesc, "Multiclass of ", 15);
    strncat(new_shortdesc, base_class->name, strlen(base_class->name));
    if (num_multiclass == 2){
        strncat(new_shortdesc, ", ", 3);
    } else{
        strncat(new_shortdesc, " and ", 6);
    }
    strncat(new_shortdesc, second_class->name, strlen(second_class->name));
    for (int i = 0; i < base_class->num_parent_class; i++) {
        if(i == base_class->num_parent_class - 1 && second_class->num_parent_class == 0){
            strncat(new_shortdesc, " and ", 6);
        } else{
            strncat(new_shortdesc, ", ", 3);  
        }
        strncat(new_shortdesc, base_class->parent_class_names[i], strlen(base_class->parent_class_names[i]));
    }
    for (int i = 0; i < second_class->num_parent_class - 1; i++) {
        if(i == second_class->num_parent_class - 1){
            strncat(new_shortdesc, " and ", 6);
        } else{
            strncat(new_shortdesc, ", ", 3);    
        }
        strncat(new_shortdesc, second_class->parent_class_names[i], strlen(second_class->parent_class_names[i]));
    }

    strncat(new_shortdesc, ".", 2);
    return new_shortdesc;
}

/*
 * Creates a longdesc for a multiclass by concatenating the shortdescs
 * of all the component classes.
 *
 * Paramaters:
 *  - base_class: the character's base class (their current class).
 *  - second_class: the class being added to the original class.
 *
 * Returns:
 *  - a pointer to a string with the new longdesc.
 */
char* multiclass_longdesc(class_t* base_class, class_t* second_class) {
    char* new_longdesc = (char*) calloc(MAX_LONG_DESC_LEN + 1, sizeof(char));
    strncat(new_longdesc, base_class->shortdesc, strlen(base_class->shortdesc));
    strncat(new_longdesc, "\n\n", 3);
    strncat(new_longdesc, second_class->shortdesc, strlen(second_class->shortdesc));
    return new_longdesc;
}

/*
 * Creates an effects hash for a multiclass
 * by adding together the effects of both classes.
 *
 * Paramaters:
 *  - base_effects: the character's base class's effect hash.
 *  - second_effects: the effect hash of the class being added to the base.
 *
 * Returns:
 *  - a pointer to the combined effect hash.
 *  - note that the effects in the combined inventory are deepcopied, but the stat mods are not.
 */
effects_hash_t* multiclass_effects(effects_hash_t* base_effects, effects_hash_t* second_effects) {
    effects_global_t* global;
    if (base_effects != NULL) {
        global = base_effects->global;
    }
    else if (second_effects != NULL) {
        global = second_effects->global;
    }
    else {
        return NULL;
    }

    effects_hash_t *new_effects = stat_effect_new(global);
    if (base_effects != NULL) {
        new_effects->key = base_effects->key;
        new_effects->stat_list = base_effects->stat_list;
        base_effects = base_effects->hh.next;
    }
    else {
        new_effects->key = second_effects->key;
        new_effects->stat_list = second_effects->stat_list;
        second_effects = second_effects->hh.next;
    }
    effects_hash_t *cur = new_effects;

    while (base_effects != NULL) {
        effects_hash_t *effect_copy = stat_effect_new(global);
        effect_copy->key = base_effects->key;
        effect_copy->stat_list = base_effects->stat_list;
        cur->hh.next = effect_copy;
        cur = cur->hh.next;
        base_effects = base_effects->hh.next;
    }
    while (second_effects != NULL) {
        effects_hash_t *effect_copy = stat_effect_new(global);
        effect_copy->key = second_effects->key;
        effect_copy->stat_list = second_effects->stat_list;
        cur->hh.next = effect_copy;
        cur = cur->hh.next;
        second_effects = second_effects->hh.next;
    }
}

/*
 * Creates a skill tree for a multiclass
 * by adding together the nodes of both classes in a new tree.
 *
 * Paramaters:
 *  - name: the name of the tree (same as the name of the multiclass)
 *  - base_tree: the character's base class's tree.
 *  - second_tree: the tree of the class being added to the base.
 *
 * Returns:
 *  - a pointer to the combined tree.
 *  - note that the nodes in the combined trees are not deepcopied.
 */
skill_tree_t* multiclass_tree(char* name, skill_tree_t* base_tree, skill_tree_t* second_tree) {
    if (base_tree == NULL && second_tree == NULL) {
        return NULL;
    }
    unsigned int num_nodes;
    if (base_tree == NULL) {
        int num_nodes = second_tree->num_nodes;
    }
    else if (second_tree == NULL) {
        int num_nodes = base_tree->num_nodes;
    }
    tid_t tid = 1000; // TID is placeholder
    skill_tree_t* new_tree = skill_tree_new(tid, name, num_nodes);
    if (base_tree != NULL) {
        for (int i = 0; i < base_tree->num_nodes; i++) {
            skill_tree_node_add(new_tree, base_tree->nodes[i]);
        }
    }
    if (second_tree != NULL) {
        for (int i = 0; i < second_tree->num_nodes; i ++) {
            skill_tree_node_add(new_tree, second_tree->nodes[i]);
        }
    }
    return new_tree;
}

/*
 * Creates a skill inventory for a multiclass
 * by adding together the skills of both classes.
 *
 * The max active and passive will be the larger of the two classes.
 *
 * Paramaters:
 *  - base_inventory: the character's base class's skill inventory.
 *  - second_inventory: the skill inventory of the class being added to the base.
 *
 * Returns:
 *  - a pointer to the combined inventory.
 *  - note that the skills in the combined inventory are not deepcopied.
 */
skill_inventory_t* multiclass_inventory(skill_inventory_t* base_inventory, skill_inventory_t* second_inventory) {
    /* Safely unpack inventory sizes (Handling NULL) */
    unsigned int base_max_active = base_inventory == NULL ? 0 : base_inventory->max_active;
    unsigned int base_max_passive = base_inventory == NULL ? 0 : base_inventory->max_passive;
    unsigned int second_max_active = second_inventory == NULL ? 0 : second_inventory->max_active;
    unsigned int second_max_passive = second_inventory == NULL ? 0 : second_inventory->max_passive;

    unsigned int base_curr_active = base_inventory == NULL ? 0 : base_inventory->num_active;
    unsigned int base_curr_passive = base_inventory == NULL ? 0 : base_inventory->num_passive;
    unsigned int second_curr_active = second_inventory == NULL ? 0 : second_inventory->num_active;
    unsigned int second_curr_passive = second_inventory == NULL ? 0 : second_inventory->num_passive;

    /* Calculate new inventory sizes */
    unsigned int max_active;
    unsigned int max_passive;
    if (base_max_active >= second_max_active) {
        max_active = base_max_active;
    }
    else {
        max_active = second_max_active;
    }
    if (base_max_passive >= second_max_passive) {
        max_passive = base_max_passive;
    }
    else {
        max_passive = second_max_passive;
    }

    /* Generate new inventory */
    skill_inventory_t* new_inventory = inventory_new(max_active, max_passive);
    for (int i = 0; i < base_curr_active; i++) {
        inventory_skill_add(new_inventory, base_inventory->active[i]);
    }
    for (int i = 0; i < second_curr_active; i++) {
        inventory_skill_add(new_inventory, second_inventory->active[i]);
    }
    for (int i = 0; i < base_curr_passive; i++) {
        inventory_skill_add(new_inventory, base_inventory->passive[i]);
    }
    for (int i = 0; i < second_curr_passive; i++) {
        inventory_skill_add(new_inventory, second_inventory->passive[i]);
    }
    
    return new_inventory;
}

/*
 * Creates an attribute object for a multiclass
 * by adding the objects of both classes to a new object.
 *
 *
 * Paramaters:
 *  - base_attributes: the attributes of the base class.
 *  - second_attributes: the attributes of the second class.
 *  - multiclass_name: the name of the multiclass
 *
 * Returns:
 *  - a pointer to the combined attributes.
 *  - note that the attributes in the combined object are not deepcopied.
 */
obj_t* multiclass_attributes(obj_t* base_attributes, obj_t* second_attributes, char* multiclass_name) {
    char* obj_name = (char*) malloc(sizeof(char) * strlen(multiclass_name) + 6);
    strcpy(obj_name, multiclass_name);
    strncat(obj_name, "_attr", 6);
    obj_t* new_attributes = obj_new(obj_name);
    obj_add_attr(new_attributes, base_attributes->id, base_attributes);
    obj_add_attr(new_attributes, second_attributes->id, second_attributes);
    return new_attributes;
}

/* See class.h */
class_t* multiclass(class_t* base_class, class_t* second_class, char* name) {
    char* new_shortdesc = multiclass_shortdesc(base_class, second_class);
    char* new_longdesc = multiclass_longdesc(base_class, second_class);
    obj_t* combined_attr = multiclass_attributes(base_class->attributes, second_class->attributes, name);
    effects_hash_t* combined_effects = multiclass_effects(base_class->effects, second_class->effects);
    
    class_t* new_class = class_new(name, new_shortdesc, new_longdesc, combined_attr, base_class->base_stats, combined_effects);
    if (new_class == NULL) {
        return NULL;
    }
    
    new_class->num_parent_class = 2 + base_class->num_parent_class + second_class->num_parent_class;
    new_class->parent_class_names = (char**) malloc(new_class->num_parent_class * sizeof(char*));
    for (int i = 0; i < new_class->num_parent_class; i++) {
        new_class->parent_class_names[i] = (char*) calloc(MAX_NAME_LEN + 1, sizeof(char));
        if (new_class->parent_class_names[i] == NULL) return NULL;
    }
    memcpy(new_class->parent_class_names[0], base_class->name, MAX_NAME_LEN + 1);
    memcpy(new_class->parent_class_names[1], second_class->name, MAX_NAME_LEN + 1);
    int i = 0;
    while (i < base_class->num_parent_class) {
        memcpy(new_class->parent_class_names[i + 2], base_class->parent_class_names[i], MAX_NAME_LEN + 1);
    }
    while (i < second_class->num_parent_class - base_class->num_parent_class) {
        memcpy(new_class->parent_class_names[i + 2], second_class->parent_class_names[i], MAX_NAME_LEN + 1);
    }

    new_class->skilltree = multiclass_tree(name, base_class->skilltree, second_class->skilltree);
    new_class->starting_skills = multiclass_inventory(base_class->starting_skills, second_class->starting_skills);

    return new_class;
}

/* See class.h */
int class_add_skills(class_t* class, skill_inventory_t* starting_skills, 
                     skill_tree_t* skilltree) {
    class->starting_skills = starting_skills;
    class->skilltree = skilltree;
    return EXIT_SUCCESS;
}

/* see class.h */
int has_component_class(class_t* class, char* name) {
    if (!(strncmp(class->name, name, strlen(name)))) {
        return 1;
    }
    for (int i = 0; i < class->num_parent_class; i++) {
        if (!(strncmp(class->parent_class_names[i], name, strlen(name)))) {
            return 1;
        }
    }
    return 0;
}

/* See class.h */
int class_free(class_t* class) {
    if (class == NULL) {
        return EXIT_SUCCESS;
    }

    if (class->name != NULL) {
        free(class->name);
    }
    if (class->parent_class_names != NULL) {
        for (int i = 0; i < class->num_parent_class; i++) {
            free(class->parent_class_names[i]);
            i++;
        }
        free(class->parent_class_names);
    }
    if (class->shortdesc != NULL) {
        free(class->shortdesc);
    }
    if (class->longdesc != NULL) {
        free(class->longdesc);
    }
    if (class->skilltree != NULL) {
        skill_tree_free(class->skilltree);
    }
    if (class->starting_skills != NULL) {
        inventory_free(class->starting_skills);
    }

    free(class);

    return EXIT_SUCCESS;
}

/* Class Hashtable functions */

/* See class.h */
int add_class(class_hash_t** hashtable, class_t* class) {
    if (class == NULL || class->name == NULL)
        return FAILURE;

    if (find_class(hashtable, class->name) != NULL)
        return FAILURE;

    HASH_ADD_STR(*hashtable, name, class); 
    return SUCCESS;
}

/* See class.h */
int set_class(class_hash_t** hashtable, class_t* class) {
    if (class == NULL || class->name == NULL)
        return FAILURE;
    
    class_t* replaced_class = NULL;
    HASH_REPLACE_STR(*hashtable, name, class, replaced_class);

    if (replaced_class != NULL)
        class_free(replaced_class);
    
    return SUCCESS;
}

/* See class.h */
class_t* find_class(class_hash_t** hashtable, char* name) {
    if (hashtable == NULL || name == NULL)
        return NULL;
    class_t* output_ptr = NULL;
    HASH_FIND_STR(*hashtable, name, output_ptr);
    return output_ptr;
}

/* See class.h */
int delete_class(class_hash_t** hashtable, char* name) {
    if (hashtable == NULL || name == NULL)
        return FAILURE; 
    
    class_t* class = find_class(hashtable, name);
    if (class == NULL)
        return FAILURE;

    /* Removes class from hashtable */
    HASH_DEL(*hashtable, class);

    /* Class must still be freed after removal */
    class_free(class);

    return SUCCESS;
}

/* See class.h */
int count_classes(class_hash_t** hashtable) {
    return HASH_COUNT(*hashtable);
}
