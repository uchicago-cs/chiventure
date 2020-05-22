Playerclass

Key Features

    - Provide basic classes for game developers to utilize
    - Provide framework for game developers to create their own classes in place of or in addition to our provided classes
    - Work with rpg-battle team to implement specific combat statistics / effects for different classes
    - Work with other teams to implement additional game functionality based on class, such as custom dialogue, custom NPC names, custom item usage, etc.

Data Structures

    class_t struct
        - char* Name
        - char* Short Description
        - char* Long Description
        - obj_t* Array of attributes
        - stats_t* Base Stats
        - skilltree_t* Skilltree
        - skill_t* Combat Actions
        - skill_t* Non-combat Actions

    *** Currently the stats_t, skilltree_t, and skill_t parts of the class_t struct are stubbed out and do NOT function with other modules ***

Modules

class

    Create a new playerclass
        class_t* = class_new(char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_t* stat, skilltree_t* skilltree, skill_t* combat, skill_t* noncombat);
    Initialize values inside the playerclass
        class_t* = class_init(class_t* class, char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_t* stat, skilltree_t* skilltree, skill_t* combat, skill_t* noncombat);
    Free a playerclass
        void class_free(class_t* c);
