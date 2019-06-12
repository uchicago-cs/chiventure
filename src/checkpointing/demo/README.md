How to run the Demonstration of saving and loading

Running `make` will create a binary file called `demo-checkpointing`.

To save the dummy game we have, we run `./demo-checkpointing` without
any command line arguments. This will print to stdout our demo game that we
created and the things which chad does that changes the game state. Then it
saves it to a file named `save.txt`. Then if we run `./demo-checkpointing save.txt`
it will load the save.txt file and print out the loaded game struct information.
Then it resaves it into a file named `resave.txt` which we can load the file if
we want to make sure that it saves everything without changing the structs by
running `./demo-checkpointing resave.txt`.
