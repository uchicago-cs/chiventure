# libobj library

This library includes:

1. A basic structure for objects providing:
    - flexible data storage in simple objects
    - simple object getters
    - simple object setters
2. A parser to turn a YAML file into simple objects
3. An example file for using objects (`examples/obj.c`)
    - to make: `make examples/obj`
    - ro run: `examples/obj`
4. An example file for parsing YAML into objects
    - to make: `make examples/parse`
    - to run: `examples/parse $YAML_FILE`

### Dependencies

To use the parsing library, you'll need to have libyaml installed

Follow the instructions here: https://pyyaml.org/wiki/LibYAML

# Using Objects

Once created, an object works as a flexible data storage tool. It can have properties, which each are able to hold their own value.

It is capable of storing:
    - Booleans
    - Characters
    - Integers
    - Strings
    - Other objects

- Setting properties is done with dot notation

    `obj_set_str(room, "location.talisman", "a real slick talisman");`

- Intermediate properties can also have a value

    `obj_set_str(room, "location", "a pedestal");`

- An object can also have multiple properties at a time. Each property can have whatever type you want

    `obj_set_int(room, "size", 64);`

See the provided `obj_example.c` file for more information on using objects. See `include/obj.h` for documentation on all provided functions

## Parsing YAML into Objects
To turn a YAML file into an object:
1. Get the filename (NOTE: it must have a .yaml extension)
2. Create an object with `obj_new()` to make the destination object

    Note: as per normal YAML usage, the outermost structure is expected to be a list. (For more on that, keep reading)

Details on parsing:
- In YAML, there are two main types that we model as objects:
    1. Lists
    2. Dictionaries

    See https://learn.getgrav.org/15/advanced/yaml for more information on YAML types

- The way this parser works together with the object structures, any information is stored under (1) the header, and then (2) in the case of a list, the list index as a string, and in the case of a dictionary, the key.
- This parser stores information in lists or dictionaries in the following way:
    - To access an item from a list, use the item's index as a string
        - `items[0]` becomes `obj_get_str(items, "0")`
        - `things[2]` becomes `obj_get_int(things, "2")`
    - To access an item from a dictionary, use the item's key
        - `items["key"]` becomes `obj_get_bool(items, "key")`
        - `things["keyname"]` becomes `obj_char(things, "keyname")`
            
