# Documentation of Action Specifications
General (applies to all supported actions)


------


### Requirements:
Error: Prints object cannot be/is not [requirement missing]<br>


### Effects:
Prints confirmation of action<br>
Changes to state may or may not be printed<br>


Open [object]
------
### Requirements:
Object must be able to be opened<br>
Object must be reachable<br>
Object must be closed<br>


### Effects:
Change object state from closed to open <br>
Objects in opened object now reachable<br>
OR<br>
Objects behind object now reachable<br>
OR<br>
Object dependent effect on state<br>


Close [object]
------


### Requirements:


Object must be able to be opened<br>
Object must be reachable<br>
Object must be open<br>


### Effects:


Change object state from open to closed<br>
Objects in closed object no longer reachable<br>
OR<br>
Objects behind object no longer reachable<br>
OR<br>
Object dependent effect on state<br>


Push [object]
------


### Requirements:


Object must be pushable<br>
Object must be reachable<br>
Player must be strong enough to push object(?)<br>


### Effects:


Object may now be no longer pushable<br>
Object dependent effect on state<br>


Pull [object]
------


### Requirements:


Object must be pullable<br>
Object must be reachable<br>
Player must be strong enough to pull object(?)<br>


### Effects:


Object may now be no longer pullable<br>
Object dependent effect on state<br>


Look at [object] / Examine [object]
------


### Requirements:


Object must be observable<br>
Object must be in field of view<br>


### Effects:


Print long description of object<br>


Turn on [object]
--------------


### Requirements:
Object must be switchable<br>
Object must be reachable<br>
Object must be off<br>


### Effects:
Change object state to “on”<br>
Object dependent effect on state<br><br>




Turn off [object]
----------
### Requirements:
Object must be switchable<br>
Object must be reachable<br>
Object must be on<br>


### Effects:
Change object state to “off”<br>
Object dependent effect on state<br><br>


Talk to [object]
---------
### Requirements:
Object must be an NPC<br>
Object must be reachable<br>
Object must be talkable to<br>


### Effects:
Object dependent effect on state<br>
Print what the player says(?)<br>
Print NPC response<br><br>


Give [object1] on [object2]
------------
### Requirements:
Object1 must be in inventory<br>
Object2 must be an NPC (has own inventory?)<br>
Object2 must be reachable<br>
Object2 must have object1 in wantobjects [list of object names](?)<br> 


### Effects:
Remove object1 from player inventory<br>
Put object1 in object2 inventory(?)<br>
Remove object1 from object2 wantobject list(?)<br>
Object dependent effect on state<br>
Print NPC message<br><br>


Go [direction]
---------
### Requirements:
Reachable room must be in direction<br>




### Effects:
Move player to room in direction<br>
Print brief description of room<br>
Entering room has effect on state(?)<br><br>




Pick up / Take [object]
--------------


### Requirements:
Object must be reachable<br>
Object must be takeable<br>
Player must have inventory space for object (if implemented)


### Effects:
Take object out of room (changes room description and state)<br>
Put object in player inventory<br>
Decrease player inventory space(?)<br>
Object is now always reachable to player unless dropped<br><br>


Drop [object]
----------
### Requirements:
Object must be in inventory<br>
Object must be droppable(if implemented)<br>


### Effects:
Take object out of player inventory<br>
Increase player inventory space(?)<br>
Put object in room(changes room description and state)<br><br>


Use [object]
---------
### Requirements:
Object must be usable<br>
Object must be reachable<br>


### Effects:
Object dependent effect on state<br>
Print effect of object use<br>
Object may no longer be usable and/or in inventory or room (changes to object state)<br><br>


Use [object1] on [object2]
------------
### Requirements:
Object must be reachable<br>
Object2 must be in object interations [list of object names] of object1(if implemented)<br>


### Effects:
Object dependent effect on state<br>
Print effect of use<br>
Objects may no longer be usable and/or in inventory or room (changes to objects’ state)<br>


Drink [object] / Consume [object]
---------
### Requirements:
Object must be reachable<br>
Object must be liquid<br>




### Effects:
Object dependent effect on state<br>
Changes to object state (may no longer be consumable)<br>
May change player state<br>


Eat [object] / Consume [object]
---------
### Requirements:
Object must be reachable<br>
Object must be solid<br>


### Effects:
Object dependent effect on state<br>
Changes to object state (may no longer be consumable)<br>
May change player state<br>