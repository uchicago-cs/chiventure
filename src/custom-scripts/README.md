# Custom Scripts

This is the file in which all sandbox/testing files for custom-scripts will be located going forward. 
This README file can serve as a way to help future teams with understanding how LUA works 
for the purposes of custom-scripts.

## What is Lua? 

Lua is basically an embedded language that can be used for scripting to modify structs and variables within C.
In this sandbox directory, you will see 3 files which have been created to serve as a 
guideline to understanding how Lua and C interact with one another. 

In this case, we have created an example "chest" struct which will be modified by a lua file.

Here is the list of the three files: 

1. `gold.h`: This is the header file which contains the chest struct which has only one variable of type "int" 
	     which represents the number of coins inside a chest

2. `gold.c`: This contains the C file in which the main() function works to create
	     the Lua State and also push variables from C into the virtual stack 
	     so that the Lua script can handle it. In this case, we assign a value of "0" to the coins
	     initially within the chest struct. We then push the coins variable to Lua where it is modified. 

3. `sample.lua`: This is the Lua script that will modify the value of the coins by changing it to 10. 

## Running the Code

To run the code on one's own computer, one must download the lua package on their own computer. 
Here is the link to the website: http://www.lua.org/start.html

Follow the instructions on how to build from source.

If you do so correctly and then compile it using:
```shell
gcc gold.c -o gold -llua
```

## Desired Output
```shell
value of chest coins is initially is 0
Result of chest coins after lua is now = 10
```
