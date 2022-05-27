#Skilltrees Demo 2022 Script
This file is to give the order of the functions needed to run the Skilltrees Demo, and build instructions. 

Lore:
You are a young adventurer, going to skills academy in order to get strong. 
Your mentor teaches you about complex skills, classes, and how to read, when he turns out to be vampire, and you kill him. 

## Running the Demo Game
1. Clone the chiventure repo into your folder of choice.
    ```
    $ git clone https://github.com/uchicago-cs/chiventure.git
    ```
2. Change directories.
    ```
    $ cd chiventure
    ```
3. Build chiventure.
    ```
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    ```
4. Compile the executable (from within the top-level `build` directory).
    ```
    $ cd src/skilltrees/examples
    $ make
    ```
5. Run the demo game!
    ```
    $ ./skilltrees_demo_2022
    ```

## CLI Operations And Script Order
`GO NORTH`
`TALK_TO_MENTOR`
`LEARN_COMBINED`
`USE_COMBINED_BOOST`
`GO NORTH`
`LEARN_SEQUENTIAL`
`USE_SEQUENTIAL_MOVE`
`GO NORTH`
`LEARN_CONDITIONAL`
`SMASH_DUMMY!`
`TURN_INTO_ORC`
`SMASH_DUMMY!`
`GO NORTH`
`LISTEN_TO_LECTURE`
`READ_TOME`
`RANDOM_SKILLS`
`GO NORTH`
`READ_WEAKNESS`
`SMASH_WINDOW!`
`TURN_INTO_ORC_AGAIN`
`SMASH_WINDOW!`