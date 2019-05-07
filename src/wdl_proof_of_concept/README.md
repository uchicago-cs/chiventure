# WDL Proof of Concept

## Purpose
The purpose of this code was to figure out how to parse a given YAML using `libobj`.  Using `libobj` and `libyaml`, we wrote code to take in a YAML file and create a `document` object from its contents.  We wrote functions to validate and print out `game`, `room`, and `item` sub-objects.  For now, validation is limited to verifying object fields are of the correct type.

## Usage
To run the code, first compile it using the provided `Makefile` and then run the command:
```bash
$ ./main <YAML file directory>
```

Note that for the moment being, our code can only work with YAML files with three rooms and three items where each has an id, a short description, and a long description.  The behavior of the code is undefined for any other format.