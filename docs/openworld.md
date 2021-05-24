# Openworld Documentation

The goal of the openworld module is to implement a feature that allows automatic map/world generation in chiventure.

## Wiki Pages
- [Source Document](https://github.com/uchicago-cs/chiventure/wiki/Open-World-~-Source-Document) - Implementation details about the openworld module
- [User Stories](https://github.com/uchicago-cs/chiventure/wiki/Open-World-~-User-Stories) - Product documentation for end-users on using openworld
- [Feature Wishlist](https://github.com/uchicago-cs/chiventure/wiki/Open-World-~-Feature-Wishlist) - Summary of recent changes made to the openworld module and a list of potential new features to be implemented

## Directories

### chiventure/include/openworld
Interface of openworld module
- [autogenerate.h](https://github.com/uchicago-cs/chiventure/blob/dev/include/openworld/autogenerate.h) - Gathers room specifications from the defaults and generates the room
- [default_items.h](https://github.com/uchicago-cs/chiventure/blob/dev/include/openworld/default_items.h) - Contains a list of default items to be placed into the rooms during room generation
- [default_rooms.h](https://github.com/uchicago-cs/chiventure/blob/dev/include/openworld/default_rooms.h) - Contains a list of default rooms from which autogenerate pulls the room info from during room generation
- [gen_structs.h](https://github.com/uchicago-cs/chiventure/blob/dev/include/openworld/gen_structs.h) - Provides the structs that make generation work smoothly:
    - roomspec_t struct - Carries the necessary info for creating a room
    - speclist_t struct - Functions as a list of all the roomspec_t's
    - gencontext_t struct - Carries the info for the generation algorithm
    - roomlevel_t struct - Encode maps between difficulty/rooms needed for level-oriented generation
    - levelspec_t struct - Carries all the info needed for level-oriented generation

### chiventure/src/openworld
Openworld source code
- src/
    - [autogenerate.c](https://github.com/uchicago-cs/chiventure/blob/dev/src/openworld/src/autogenerate.c) - Implementation of autogenerate.h
    - [default_items.c](https://github.com/uchicago-cs/chiventure/blob/dev/src/openworld/src/default_items.c) - Implementation of default_items.h
    - [default_rooms.c](https://github.com/uchicago-cs/chiventure/blob/dev/src/openworld/src/default_rooms.c) - Implementation of default_rooms.h
    - [gen_structs.c](https://github.com/uchicago-cs/chiventure/blob/dev/src/openworld/src/gen_structs.c) - Implementation of gen_structs.h
- [CMakeLists.txt](https://github.com/uchicago-cs/chiventure/blob/dev/src/openworld/CMakeLists.txt) - CMake file for openworld

### chiventure/tests/openworld
Openworld testing functions
- [CMakeLists.txt](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/CMakeLists.txt)
- [main.c](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/main.c)
- [test_autogenerate.c](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/test_autogenerate.c)
- [test_items.c](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/test_items.c)
- [test_rooms.c](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/test_rooms.c)
- [test_structs.c](https://github.com/uchicago-cs/chiventure/blob/dev/tests/openworld/test_structs.c)