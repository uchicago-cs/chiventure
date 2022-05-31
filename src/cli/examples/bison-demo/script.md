# SCRIPT
Hello! We are the command-line-interface (or CLI) team. 
Our role in chiventure is to process user input; to take it from a raw string and parse into something meaningful for the plethora of functions you all have written.
It is through us and action-management that you implement new user actions.

As a core feature, we weren't left with a codebase that neccesarily needed a lot of adjustment or fixes. 
So this quarter, when decided to find ways to improve chiventure's CLI. 
Our biggest idea was to take the current in-house parsing and in its place use a more robust parsing library.

This is because, while functional, our handmade cli is limiting, and offloading the majority of parsing work to an outside library would allow future teams to worry about higher level features as opposed to grammar and parsing.

As a result of this decision, our focus this quarter was split in two categories.
First, improving the functionality of the current CLI along with addressing requests from other teams
and Second, understanding, documenting, and using an external parsing library.

We will first cover the improvements we made to the existing infrastructure!

## EXISTING CHANGES
*perhaps having stuff hear about the current parser, potentially actions kinds*
***[include more stuff here]***


## BISON
### Bison intro
For our external parsing library, at our TA's recommendation decided on bison/flex, as there aren't many C libraries to pick from in the first place and of the ones we tested, we were actually able to get it working.

Flex is a lexer generator, a program which takes in input and turns it into tokens based on user defined grammar. 

Flex then gives these tokens to bison, which is a parser generator.
A program which, with a user defined grammar, can match series of tokens to different rules and execute C code based of that, exactly what we want to do in chiventure!

We decided that bison would replace the parsing function in chiventure, maintaing the same output as the current parser so all existing operations and functions will work.

### Bison demo 
To start with, we needed bison to replicate the current chiventure parsing. 
This involves recognizing different "kinds" of actions. 
Currently there are 4 "kinds" of actions, which are general formats for actions,

#### basic
For example, `take sword` is a kind1 action, parsed into `take` and `sword`
`go north` is kind2
`use sword on borja` is kind 3
`view stats` 
`look`

All of these are parsed into the same output as current chiventure, however bison is capable of much more. 
#### synonyms
currently, there is a mechanism to add synonyms in chiventure, but it requires a good amount of work.
In bison, adding synonyms is super easy.
We can have
`go north`
`move north`
`travel north`
and 
`walk north`
all have the same output with about one extra line of code

#### prepositions
We can also have bison ignore filler words, 
so I can now say:
`take the pset`
`go to the south`

but not just "to" and "the", we can also do...

`use my sword on borja`
or
`view my stats`

and we can define these on a per command or kind basis!

#### longer names
Another great thing is we can have long noun names be recognized
While we were able to get this to work with quote association in current chiventure, it is quite a large amount of work whereas it is handled automatically by Bison!
So I can say

`take sword of power`
`go to the castle of fire`

### putting it all together
putting it all together we can have commands like:


`use the sword of power on the evil clone of borja`
`use my sword of power on the evil clone of associate instructional professor borja`

### Flow of Presentation:
**Opening about what we were trying to do as the new CLI team**
When trying to find a way to improve the CLI of chiventure, we thought that we couldtake the current in-house parsing and instead use a more robust parsing library.
We decided on bison/flex, as there aren't many C libraries to pick from in the first place and of the ones we tested, we were actually able to get it working.




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



Bison is a general purpose parser generator which solves the limitations above by allowing a grammar to be stated directly, meaning filler wors are removed automatically, multi-word objects can be treated as one token, new synonyms can be added easily and debugging errors specifically due to language is easier. 

Therefore, we decided that bison would then directly replace the current parsing mechanisms. This specifically involves taking the command line input and parsing it into an array of strings.
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


