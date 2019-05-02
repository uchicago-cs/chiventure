**QUESTIONS:**

**1. Do we have a set list of actions that the user can write in the WDL file?** 

**2. Should we keep actions separate from objects?**

# WDL Specification
May 2, 2019

###### A WDL file is a YAML file that has at least the three file objects: Game, Room, Objects.

## Game
A Game must contain the following fields:
- start: used to specify which room the game will start in
	- ex. A, B, etc
		- Where each input is associated with an accessible room within the game
- intro: Introduction statement
	- Description for player to read at the beginning of the game
- end: a specification for how the game ends
	- ex. inventory contains: emerald gem, number of points: 100, etc
## Room
Each room has to have the following fields:
- id : An identification name that is unique to the room
	- Ex. A
- short_desc : The text that is displayed when the player first enters the room
	- Ex. “A dungeon room”
- long_desc : The text that is displayed once player enters “look at room”
	- Ex. “The walls are neither damp nor moldy. It looks well tended to. There is a coin on the ground.”
- connections
	- To : Lists a valid place the player can reach in one action from this room by ID - Ex. B
	- Direction: States the direction that connection is in
		- Ex. north
	- Through: If applicable, the object that the player must go through to go in that direction
		- Ex. door
	- NOTE: a valid connection has to have an ID that exists
  
## Objects
Each object contains the following fields:
- id : a unique identifier (like object name)
- short_desc : a first-glance description of the object
- long_desc : an in-depth description to be printed when object is examined
- in : The location that the object is in, can be multiple (obj door is in room A, room B)
- state : attributes like locked, closed, open.
- actions : actions that can be performed on the object; each action the following fields:
	- allowed: a *no* field that states that this action can never succeed. (e.g. you can try to open the door, but no matter what, you will fail)
	- conditions: prerequisites for given action (e.g. door must be unlocked to open)
		- If an action is not “allowed”, it cannot have conditions.
	- text_success: text that is printed upon success of an action
	- text_fail: text that is printed upon action failure
	- set: sets an object’s *state* upon action (you pull the door; now the door is open)
