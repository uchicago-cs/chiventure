# Design Document for Skill Trees
## Version 2.1

<details>
<summary> Updates from last version</summary>

 * `skill_t` struct, fields changed

```C
typedef struct skill {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The skill type
    skill_type_t type;

    // The name of the skill
    char* name;

    // The description of the skill
    char* desc;

    // The player's current level of the skill
    unsigned int level;

    // The player's current experience points associated with the skill
    unsigned int xp;

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The minimum number of experience points needed to level up
    unsigned int min_xp;

    // The pointer to the function that will execute the skill effect
    skill_effect_t effect;

} skill_t;
```

 * `inventory_t` struct renamed to `skill_inventory_t`, fields changed

```C
typedef struct skill_inventory {
    // An array of active skills belonging to a player
    skill_t** active;

    // The number of active skills belonging to a player
    unsigned int num_active;

    // The maximum number of active skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_active;

    // An array of passive skills belonging to a player
    skill_t** passive;

    // The number of passive skills belonging to a player
    unsigned int num_passive;

    // The maximum number of passive skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_passive;

} skill_inventory_t;
```

 * `branch_t` renamed to `skill_node_t`, fields changed

```C
typedef struct skill_node skill_node_t;

struct skill_node {
    // The skill represented by the skill node
    skill_t* skill;

    // Points to a list of prerequisites immediately preceeding the level in the
    // tree, in which the skill node presides
    skill_node_t** prereqs;

    // The number of prerequisite skill nodes
    unsigned int num_prereq_skills;

    // The size of the skill node, for the graphics team
    unsigned int size;

};
```

 * `tree_t` renamed to `skill_tree_t`, fields changed

```C
typedef struct skill_tree {
    // The tree ID that uniquely identifies the skill tree
    tid_t tid;

    // The name of the skill tree
    char* name;

    // The list of tree nodes
    skill_node_t** nodes;

    // The number of tree nodes
    unsigned int num_nodes;

} skill_tree_t;
```

 * Function header changes

```C
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   unsigned int max_level, unsigned int min_xp,
                   skill_effect_t effect);
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               unsigned int max_level, unsigned int min_xp,
               skill_effect_t effect);

```

 * Function renamed

```C
skill_node_t* skill_node_new(skill_t* skill, unsigned int num_prereq_skills,
                              unsigned int size);
int skill_node_free(skill_node_t* node);
int node_prereq_add(skill_node_t* node, skill_node_t* prereq);
int node_prereq_remove(skill_node_t* node, skill_node_t* prereq);
skill_tree_t* skill_tree_new(tid_t tid, char* name, unsigned int num_nodes);
int skill_tree_free(skill_tree_t* tree);
int skill_tree_node_add(skill_tree_t* tree, skill_node_t* node);
int skill_tree_has_node(skill_tree_t* tree, sid_t sid);
int skill_tree_node_remove(skill_tree_t* tree, skill_node_t* node);
skill_t** get_all_skill_prereqs(skill_tree_t* tree, sid_t sid,
                                int* num_prereq_skills);
skill_t** get_acquired_skill_prereqs(skill_tree_t* tree,
                                     skill_inventory_t* inventory, sid_t sid,
                                     int* num_acquired_prereqs);
skill_t** skill_prereqs_missing(skill_tree_t* tree,
                                skill_inventory_t* inventory, sid_t sid,
                                int* nmissing);
int inventory_skill_acquire(skill_tree_t* tree, skill_inventory_t* inventory,
                            skill_t* skill);
```

</details>

## Version 2.0

Much of the high-level design philosophy remains the same as from the previous version, which can be seen below. However, there have been a few structural changes, as well as some function-renamings, that justify incrementing the version number, as well as updating documentation regarding the design of this module. 

This documentation is accurate and reflective of the ```skilltrees/skill_tree``` developmental branch, which will hold all updates in code. Headers are found in ```include/skilltrees```, and include the following files:

* ```stdst.h```
* ```skill.h```
* ```inventory.h```
* ```skilltree.h```

The implementations will be found in the corresponding source files ```*.c``` located in ```src/```. 

<details>
<summary>Individual Skill Tree</summary>

The following structs will be used to store skils associated with individual players:
 
```C
typedef char* (*skill_effect_t)(char*);

typedef struct skill {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The skill type
    skill_type_t type;

    // The name of the skill
    char* name;

    // The description of the skill
    char* desc;

    // The player's current level of the skill
    unsigned int level;

    // The player's current experience points associated with the skill
    unsigned int xp;

    // The pointer to the function that will execute the skill effect
    skill_effect_t effect;

} skill_t;

typedef struct inventory {
    // An array of active skills belonging to a player
    skill_t** active;

    // The number of active skills belonging to a player
    unsigned int nactive;

    // The maximum number of active skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_active;

    // An array of passive skills belonging to a player
    skill_t** passive;

    // The number of passive skills belonging to a player
    unsigned int npassive;

    // The maximum number of passive skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_passive;

} inventory_t;
```

Each skill will have a corresponding ```skill_t``` struct corresponding to it which holds all of the critical information,
and all of these skills will be held in a ```inventory_t``` struct, of which, each player will have exactly one of. 

```sid_t sid``` and ```skill_type_t type``` are enum-types that will be defined when the global skill tree is created. ```skill_effect_t effect``` is a function pointer that points to a corresponding function, which could have additional parameters, that reflects the effects of using the skill. 

To interact with the basic skill structs, the following functions are used:
```C
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   skill_effect_t effect);
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               skill_effect_t effect);
int skill_free(skill_t* skill);
char* skill_execute(skill_t* skill, char* args);
```
More details on these functions can be found in ```include/skill.h```. 

To interact with the inventory structs, the following functions are used:
```C
inventory_t* inventory_new(unsigned int max_active, unsigned int max_passive);
int inventory_free(inventory_t* inventory);
int inventory_skill_add(inventory_t* inventory, skill_t* skill);
int inventory_has_skill(inventory_t* inventory, sid_t sid, skill_type_t type);
int inventory_skill_remove(inventory_t* inventory, skill_t* skill);
```
More details on these functions can be found in ```include/inventory.h```. 
</details>

<details>

<summary>Global Skill Tree</summary>

The global skill tree will be stored in the following structs:

```C
typedef enum sid {
    // Example 1
    UNLOCK_DOOR,

    // Example 2
    DEFUSE_BOMB,

    // Example 3
    CHOP_TREE,

    // Example 4
    INNER_PEACE,

} sid_t;

typedef enum skill_type {
    // Denotes active skill
    ACTIVE,

    // Denotes passive skill
    PASSIVE,

} skill_type_t;

typedef struct branch {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The list of prerequisite skills to acquire skill `sid`
    skill_t** prereqs;

    // The number of prerequisite skills
    unsigned int nprereqs;

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The number of experience points needed to level up
    unsigned int min_xp;

} branch_t;

typedef enum tid {
    // Example 1
    HEALTH,

    // Example 2
    COMBAT,

    // Example 3
    CHARMS,

    // Example 4
    POTIONS,

} tid_t;

typedef struct tree {
    // The tree ID that uniquely identifies the tree
    tid_t tid;

    // The list of tree branches
    branch_t** branches;

    // The number of tree branches
    unsigned int nbranches;

} tree_t;
```
Each skill will have one ```branch_t``` struct associated with it to hold the critical information. These branches will be stored in a ```tree_t```, each of which has a unique ```tid_t```, which is an enum-type corresponding to a different distinct skill-tree that the player has access to. In each game, there is a potential to have multiple ```tree_t```'s, all of which are mapped in the ```tid_t``` enum-type. 

To interact with theses structs, use the following functions:

```C
branch_t* branch_new(sid_t sid, unsigned int nprereqs, unsigned int max_level,
                      unsigned int min_xp);
int branch_free(branch_t* branch);
int branch_prereq_add(branch_t* branch, skill_t* prereq);
int branch_prereq_remove(branch_t* branch, skill_t* prereq);
tree_t* tree_new(tid_t tid, unsigned int nbranches);
int tree_free(tree_t* tree);
int tree_branch_add(tree_t* tree, branch_t* branch);
int tree_has_branch(tree_t* tree, sid_t sid);
int tree_branch_remove(tree_t* tree, branch_t* branch);
```
More details on these functions can be found in the ```include/skilltree.h``` file. 
</details>
<details>
<summary>Interactions between Both</summary>
Here are a few higher level functions that interact at the intersection of the individual player skill tree and the global skill tree:

```C
skill_t** prereqs_all(tree_t* tree, sid_t sid, unsigned int* nprereqs);
skill_t** prereqs_acquired(tree_t* tree, inventory_t* inventory, sid_t sid,
                           unsigned int* nacquired);
skill_t** prereqs_missing(tree_t* tree, inventory_t* inventory, sid_t sid,
                          unsigned int* nmissing);
void levels_update(tree_t* tree, inventory_t* inventory);
int inventory_skill_acquire(tree_t* tree, inventory_t* inventory, sid_t sid);
```
More details on these functions can be found in the ```include/skilltree.h``` file. 

On a general note, this section is where most additional features will be added to support higher level interactions and interfacing with the module. 
</details>

## Version 1.0

Our design is based around two main objects:

* A static, global skill tree
* Dynamic, individual skill trees for each character

The goal of this dual-object approach is to front-load most of 
the heavy work at the launch of the game to minimize the work 
required to interact with skills later on. This approach will 
also provide a very clear interface for potential integration 
with other features. 

Below we will describe further how these two objects will be 
structured, as well as provide documentation for interfacing. 

<details>
<summary>Global Skill Tree Implementation</summary>

The global skill tree will serve as a master-list of all of 
the skills available to the player. It will be loaded into 
memory at the launch of every play-through, and will not be 
changed much later on through the play-through. 

The implementation will look something like as follows
```C
    typedef struct g_skill_node{
        const char *name;
        const char *description;
        int id;
        int *dependencies;
        int max_level;
        void *effect; 
        # potential future fields
    } g_skill_node_t;

    typedef struct g_skill_tree{
        int size;
        g_skill_node_t* skills[];
    } g_skill_tree_t;
```
Each skill will have a node that stores all of the relevant information,
and the tree will hold all of these nodes together. One key feature of 
this design is that each skill will have an integer ID attached to it. 
This will greatly reduce the friction with interactions between multiple
skill nodes in the future. Another key feature here is that the tree is 
not actually a tree, nor a graph, but rather just a table, mapping ID 
values to the nodes associated with them. This will greatly simplify the 
individual skill trees for the players later on. 

One benefit of this implementation is that in the future, should there 
be a need to add more data fields to skills, it can be done by just 
adding fields to the node struct, without having to change much 
preexisting code. 

One detail that is still unclear is how we will store the effects of the
skills. This part will be updated later on when the interactions with 
other features becomes more clear. 
</details>

<details>
<summary>Global Skill Tree Interface</summary>

At startup, the game will initialize the global skill tree. This will
be done via an init function. 
```C
    g_skill_tree_t *init_g_skill_tree(int size, const char *names, 
        const char *descriptions, int **dependencies, int *max_levels,
        void **effects);
```
This function will take in some parsed parameters from WDL to 
initialize a skill tree containing all of the skills. 

This function will use some internal helper functions to initialize
each individual node. These include
```C
    g_skill_node_t *init_g_skill_node(const char *name, const char *description
        int id, int *dependencies, int max_level, void *effect);
```
To free the tree when the game is closed, there will be some free function:
```C
    int free_g_skill_tree(g_skill_tree_t *tree);
```
which will call the corresponding internal helper function:
```C
    int free_g_skill_node(g_skill_node_t *node);
```
Interactions with the global skill tree will be (mostly) read-only. 
Therefore, interfacing will be done with the following functions:
```C
    const char *get_skill_name(g_skill_tree_t *tree, int id);
    const char *get_skill_description(g_skill_tree_t *tree, int id);
    int **get_skill_dependencies(g_skill_tree_t *tree, int id);
    int *get_skill_max_level(g_skill_tree_t *tree, int id);
    void *get_skill_effect(g_skill_tree_t *tree, int id);
```
All of these accessing functions will be reliant on the ID values
associated with the skill. Alternatively, there will also be a set 
of functions that can take in the skill name instead of the ID:
```C
    int get_skill_id_n(g_skill_tree_t  *tree, const char *name);
    const char *get_skill_description_n(g_skill_tree_t *tree, const char *name);
    int **get_skill_dependencies_n(g_skill_tree_t *tree, const char *name);
    int *get_skill_max_level_n(g_skill_tree_t *tree, const char *name);
    void *get_skill_effect_n(g_skill_tree_t *tree, const char *name);
```
These functions should be the only way that other features or the
user interacts with the global skill tree. 
</details>

<details>
<summary>Individual Skill Tree Implementation</summary>

Because this design front-loads the work of setting up the skill tree,
each individual skill tree will have a much simpler implementation.
```C
    typedef struct i_skill_tree{
        int size;
        int *skills;
    } i_skill_tree_t;
```
Each player instance will contain one of these structs, which contains
only a table that maps each skill ID to its level. The benefit of having 
this implementation is that it saves space in storing player data, and 
avoids cluttering with having too many skill struct nodes. 
</details>

<details>
<summary>Individual Skill Tree Interface</summary>
Individual skill trees will be initialized and freed with the 
following functions:

```C
    i_skill_tree_t *init_i_skill_tree(int size, int *skills);
    int free_i_skill_tree(i_skill_tree_t *tree);
```
The initialization will involve passing in starting values for the 
skill level of all of the skills. 

Interactions with individual skill trees will be done through 
the following functions:

```C
    int get_skill_level(i_skill_tree_t *tree, int id);
    int get_skill_level_n(i_skill_tree_t *tree, const char *name);
    bool can_level_skill(i_skill_tree_t *tree, int id, int level);
    bool can_level_skill_n(i_skill_tree_t *tree, const char *name, int level);
    int level_skill(i_skill_tree_t *tree, int id, int level);
    int level_skill_n(i_skill_tree_t *tree, const char *name, int level);
```
Because the individual skill tree is very minimal, interactions will
involve more with interfacing with the global skill tree. 
</details>
