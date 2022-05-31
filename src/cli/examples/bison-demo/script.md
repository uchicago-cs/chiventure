# SCRIPT
### Flow of Presentation:
**Opening about what we were trying to do as the new CLI team**
When trying to find a way to improve the CLI of chiventure, we thought that we couldtake the current in-house parsing and instead use a more robust parsing library.
We decided on bison, as there aren't many C libraries and of the ones we tested we were actually able to get something working.


**preamble about what bison/flex actually is and how it is relevant to chiventure.**
This would involve talking about the current implementation of parsing, along with some of the limitations.
Old implementation bad:
-difficulty removing filler words
-more effort to add synonyms
-unable to specify languages grammar directly
 (less adaptable, harder to specify changes, 
 harder to debug errurs resulting from the language
 rules)
-way less cool and harder to work with


So then, we decided that bison would then directly replace the current parsing mechanisms. This specifically involves taking the command line input and parsing it into an array of strings.
For example, when the user types "go north", this get's put into a list of stringscalled of:
[0] = "go"
[1] = "north"

so to start with, we needed to get bison to reconize the same formatting as chiventure
for example:

start with normal chiventure commands
eg: view stats

using bison has incredible potential for EASILY making commands more versatile and complex

for example, with bison is no longer a hard cap on 4 word limit per action
(WE SHOULD EITHER IMPLEMENT PARSING ON AND or just say we haven't gotten it working yet and put in backlog)

also, as you can see, the lack of a hard cap means we can support ignoring prepositions, articlees and pronouns
eg: go to the north

go north
walk north
travel north - all recognized in current grammar

Before this was a matter of adding the synonym into a
command struct and setting or conditions, now we simply
|synonym


# ACTUAL COMMANDS:
### OG (works as before)
take sword
go north
use sword on Borja
view stats
look

## Bison is Cool! 
### look at it handle prepositions and pronouns!
### (cooler than previous implementation)
take the sword
go to the north
use my sword on borja
view my stats
### look at it handle synonyms!
walk north
move north
travel north

close door 
shut door

take ENSU 
grab ENSU

look 
where

put 
place


### look at it handle more interesting names!
"so instead of just going to the north, we can go to specific places!"
So I could say...:
go to Ryerson 251
take the sword of power
go to the castle of fire
use the sword of power on the evil borja


