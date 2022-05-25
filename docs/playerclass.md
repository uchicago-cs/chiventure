# Playerclass Documentation

## Wiki Pages

- [Player Class Dependencies](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Dependencies)
- [Player Class Requirements and User Stories](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Requirements,-User-Stories,-Dependencies)
- [Player Class Design](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Design)
- [Loading Player Classes from WDL](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Loading-Classes-from-WDL)
- [Player Class: Multiclassing Design](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Multiclassing:-Design)
- [Prefabricated Classes](https://github.com/uchicago-cs/chiventure/wiki/Player-Class-~-Prefabricated-Classes)

## Directories
- [include/playerclass](https://github.com/uchicago-cs/chiventure/tree/playerclass/documentation-update/include/playerclass) - Provides function header files and documentation
- [src/playerclass](https://github.com/uchicago-cs/chiventure/tree/dev/src/playerclass) - Contains the implementation of all player class functions
- [tests/playerclass](https://github.com/uchicago-cs/chiventure/tree/dev/tests/playerclass) - Includes tests for all functions in the player class module

## Key Features

- Provide basic prefabricated classes for game developers to utilize
- Provide framework for game developers to create their own classes in place of or in addition to our prefabricated classes
- Allow for multiclassing (a single player using more than one class)
- Allow certain player classes to use items more or less effectively
- Work with rpg-battle team to implement specific combat statistics / effects for different classes (in progress)
- Work with other teams to implement additional game functionality based on class, such as custom dialogue, custom NPC names, usage, etc. (in progress)

## Modules

### Class
_The Class module provides basic functions for working with classes._

#### Player Class Struct
```
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
    - skill_inventory_t* Starting_skills
    - UT_hash_handle Field Used by UTHASH Macros
```

Create a new playerclass:
- `class_t* class_new(char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);`

Initialize values inside the playerclass:
- `class_t* class_init(class_t* class, char* name, char* shortdesc, char* longdesc, obj_t* attr, stats_hash_t* stat, effects_hash_t* effect);`

Combine two playerclasses (multiclass)
- `class_t* = multiclass(class_t* base_class, class_t* second_class, char* name);`

Free a playerclass:
- `void class_free(class_t* c);`

Add skill fields to playerclass:
- `int class_add_skills(class_t* class, skill_inventory_t* skills, skill_tree_t* skilltree);`

### Class Prefabs
_The Class Prefabs module provides access to prefabricated classes, for the developer to use._

Generate the class struct for a prefab class:
- `class_t* class_prefab_new(chiventure_ctx_t* ctx, char *class_name);`

Add the skill fields to a prefab class:
- `int class_prefab_add_skills(class_t* class);`

### Class Items
_The Class Items module handles interactions between items and classes._

Interactions between items and classes currently utilize a framework based on **multipliers**. Multipliers allow certain classes to be more or less proficient at using a certain item (whether this be in a combat situation, or elsewhere), and are currently denoted by numerical values. Class multipliers are stored internally within an item.

Add a multiplier to an item for a given class:
- `int add_item_multiplier(item_t* item, class_t* class, double multiplier);`

Lookup the multiplier for a class-item pair:
- `double get_class_item_multiplier(item_t* item, class_t* class);`

Remove the multiplier for a class-item pair:
- `int remove_item_multiplier(item_t* item, class_t* class);`

Internally, class restrictions are signalled by a multiplier of 0.

Add a restricted class to an item:
- `int add_item_restriction(item_t* item, class_t* class);`

Lookup if an class is restricted from a certain item:
- `bool is_restricted(item_t* item, class_t* class);`

Remove a class item restriction:
- `int remove_item_restriction(item_t* item, class_t* class);`
