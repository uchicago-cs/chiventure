Playerclass

Key Features

    - Provide basic classes for game developers to utilize
    - Provide framework for game developers to create their own classes in place of or in addition to our provided classes
    - Work with rpg-battle team to implement specific combat statistics / effects for different classes
    - Work with other teams to implement additional game functionality based on class, such as custom dialogue, custom NPC names, custom item usage, etc.

Data Structures

    class_t struct
        - char* Name
        - int num_parent_class;
        - char** parent_class_names;
        - char* Short Description
        - char* Long Description
        - obj_t* Array of attributes
        - stats_hash_t* Base Stats
        - effects_hash_t* Stat Effects
        - skilltree_t* Skilltree
        - skill_inventory_t* Combat Actions
        - skill_inventory_t* Non-combat Actions

    *** Currently the skilltree_t part of the class_t struct is stubbed out and do NOT function with other modules ***

Modules

class

    Create a new playerclass
        class_t* = class_new(char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);
    Initialize values inside the playerclass
        class_t* = class_init(class_t* class, char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);
    Combine two playerclasses (multiclass)
        class_t* = multiclass(class_t* base_class, class_t* second_class, char* name);
    Free a playerclass
        void class_free(class_t* c);
