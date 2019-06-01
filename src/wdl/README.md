# WDL Library

## Dependencies
This library is dependent on `libobj`.  Before building the code, ensure that a copy of `libobj.a` is present and properly referenced in the `Makefile`.

`libobj` is dependent on `libyaml`.  For more information consult the `libobj` read-me.

## Modules

### Parse
This module is responsible for getting `room`, `item`, and `player` objects from
a YAML file.

### Validate
This module is responsible for checking objects have all the required fields and checking that those fields are of the right type.

## Examples
* `typecheck_demo`: First official test of our type-checking and printing functions.  It takes in a YAML file, does basic type-checking and prints out whatever content it can.