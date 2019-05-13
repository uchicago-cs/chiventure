# Game-State Documentation

## Intro

Hello and welcome to game-state and the lit times that will follow! We’re responsible for changing, (as the name perhaps hinted) at changing the state of the game and modifying the structs.

The workflow that we’re in charge of looks a bit like this:

WDL -> Game-state (which is then used by Action Management/Checkpointing/UI)

Action Management -> Game-state (once an action is legal, we provide the functionality that modifies the game state. Eg move room, add object to inventory, etc)

Game-stat -> Checkpointing (serializing and de-serializing the game-state)

##
Updates:

Sprint 1 - Designed initial structs/designs

Sprint 2 - Expanded designs/functionality to include directionality, began functions to modify and construct game states.
