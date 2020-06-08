The game is now loadable and beatable, but several parts of it are not functional as intended

- most items cannot be interacted with aside from LOOKing at them- upon review of other test games, it seems that 
  interactivity beyond LOOKing and TAKEing is not functional, as the ability to have actions update attributes of other 
  objects was never implemented.

-the end room is enterable by simply typing GO DOWN from the first room, despite the locked trapdoor. 

As a note, there were several quirks of the WDL that made this process difficult, and I am logging them here for future reference. 

- success and failure text are not optional 
- it appears that all item names must be in all caps to function
- indentation was a serious problem. for no discernable reason, the entire item block needs to be indented one space more
  than the rest of the file. also, despite conflicting documentation throughout the existing WDL code, the success and failure
  text of an action within an item must be indented in line with the action itself and not tabbed out.
