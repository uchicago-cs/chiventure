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
        - battle_t* Combat Actions
        - action_t* Non-combat Actions

Modules

class

    Create a new playerclass
        class_t* = class_new(char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_t* stat, battle_t* battle, action_t* action);
    Initialize values inside the playerclass
        class_t* = class_init(class_t* class, char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_t* stat, battle_t* battle, action_t* action);
    Free a playerclass
        void class_free(class_t* c);
