Lex operators reference: https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dgk/index.html#lex-36741
## To Compile and Run
from the working directory, (`examples/bison-demo`) run the following:
```
mkdir out
make
./parser-bison
```
This will put you into the interactive CLI interface that will communicate with and beparsed by Bison

## Cool Examples
* use my sword on the big rock
* open door
* go north
* go to the north
* travel north 

### Flow of Presentation:

**Opening about what we were trying to do as the new CLI team**
When trying to find a way to improve the CLI of chiventure, we thought that we couldtake the current in-house parsing and instead use a more robust parsing library.
We decided on bison, as there aren't many C libraries and of the ones we tested we were actually able to get something working.


**preamble about what bison/flex actually is and how it is relevant to chiventure.**
This would involve talking about the current implementation of parsing, along with some of the limitations.

So then, we decided that bison would then directly replace the current parsing mechanisms. This specifically involves taking the command line input and parsing it into an array of strings.
For example, when the user types "go north", this get's put into a list of stringscalled of:
[0] = "go"
[1] = "north"

so to start with, we needed to get bison to reconize the same formatting as chiventure
for examplee:

start with normal chiventure commands
eg: view stats

using bison has incredible potential for EASILY making commands more versatile andcomplex

for example, with bison is no longer a hard cap on 4 word limit per action
(WE SHOULD EITHER IMPLEMENT PARSING ON AND or just say we haven't gotten it working yet and put in backlog)

also, as you can see, the lack of a hard cap means we can support ignoringperopositions, articlees and pronouns
eg: go to the north

go north
walk north
travel north - all recognized in current grammar

