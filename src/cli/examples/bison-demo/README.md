# README
Lex operators reference: https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dgk/index.html#lex-36741
## To Compile and Run
from the working directory, (`examples/bison-demo`) run the following:
```
mkdir out
make
./parser-bison
```
This will put you into the interactive CLI interface that will communicate with and beparsed by Bison


# What this demo is meant to show:
this demo it meant to show the parsing capabilities of bison relevant to our project.
Generally, this is increasing the versatility of bison and offloading the work to an external library.

Specifically, it shows bison handling the same input that the current handmade chiventure parser can handle. 
It shows bison taking the same input and giving the same output, for example:

```
take sword
go north
use sword on Borja
view stats
look
```

all are parsed into their actions and arguments. 
this is almost always just each word, except for the `use` command which removes the `on` and leaves just the two arguments.

However, bison can do much more!

Bison can very easily handly prepositions and pronouns!
For each command you can define how it handles filler words like "the" "to" "my" "their", etc...
this makes commands more verbose without impacting how chiventures operations will see them.
For example, all the following work:

```
take the sword
go to the north
use my sword on borja
view my stats
```

It is also exceptionally easy to handle synonyms, all of the following groups of commands have the same output:

```
walk north
move north
travel north

close door 
shut door

take ENSU 
grab ENSU

look 
where

put midterm on fire
place midterm on fire
```


finally, one of the best things about bison is that it can super easily handle tokens that are longer than one word. This allowed more complicated names of nouns!

```
go to Ryerson 251
take the sword of power
go to the castle of fire
use the sword of power on the evil borja
```

all of these are parsed into the normal format of strings for each action and item/path.


