# CLI Documentation
## The documentation for the CLI module of chiventure
##### Spring 2021 Team: Marta Beramendi-Conde, Beza Desta, Marcus Goodman, David Chen, Sam Donio

The cli (command-line interface) is the way in which the player interacts with the chiventure program. By typing things into the command line the user is able to perform a multitude of actions inside of chiventure. At a high level the cli takes in a string that is inputted by the user, parses it using the cli parser, and then, depending on what the user has inputted, performs different actions. 

## cli Module
The cli module consists of several parts

The shell

    shell.c and shell.h
+ The shell file contains mostly system internal functions that do things like print a list of supported commands, print a greeting when the game starts, prints a history of commands that have been used so far, or prints a message.

The parser

    parser.c and parser.h
+ The parser files work to parse the input from the user. The way this is currently implemented is by turning the users input into a linked list of 'tokens' and then passing this linked list along so that the user's inputs can be performed (if valid).

The operations

    operations.c and operations.h
+ The operations files contain all of the operations that can be used in chiventure, everything from picking up an item to loading a new wdl file.

The command list

    cmdlist.c and cmdlist.h
+ The cmdlist files serve the purpose of allowing the user to be able to list the commands that they have inputted during any game.

The commands

    cmd.c and cmd.h
+ The cmd files defines the command datatype, the lookup entry for a hastable, and many functions that realte to interacting with these datatypes.

## Things added in 2021
As of the creation of this document, things that have been implemented by the cli team in 2021:
- The use of linked lists as the datatype that the parser uses so that the user can input multiple commands at once using the connecting word 'and'
- Suggestions for when the user incorrectly spells an input, previously the cli would just say that this feature was not supported but now, for example, if the user inputs 'tak' the cli will recommend that the user meant 'take'
- The load_wdl commmand has been fixed, previously this function was completely broken and would cause seg faults, but now the user can load wdl files and an error will be printed if the path is incorrect
- The history command was added, so now the user can see what commands they have previously typed
- The indentation on the cli would be off-center until the user typed something, now the indentation is correct
- The user can type 'items' and a list of items that are in the room a player currently is in will be printed
- The user can now type 'credits' to see credits of a list of users who have previously worked on chiventure
- The number of objects in a command is now validated
- The user can now type 'QUIT' in order to quit chiventure along with pressing CTRL+D