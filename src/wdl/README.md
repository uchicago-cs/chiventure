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
This directory contains scripts for validating code from the validation and parse modules and sample yaml files located in `examples/sample_yaml`. 
In order to run a script, type `make examples` followed by `cd examples`. Then run the following based on the script and yaml file from the directory 
`sample_yaml` you would like to run: 

`[script.c] sample_yaml/[yaml file]`

These are the current scripts: 
* `typecheck_demo.c`: First official test of our type-checking and printing functions. It takes in a YAML file, does basic type-checking and prints all content that is printable.

These are the current YAML files:
* `connected_rooms.wdl`: simple YAML file that contains rooms and connections
