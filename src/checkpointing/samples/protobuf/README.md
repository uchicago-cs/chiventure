Commands to test out sample protobuf:
Run these commands in the samples/protobuf directory

to create .c .h from proto file
```
make proto
```
to compile save.c (will run proto as well)
```
make serialize
```

to compile load.c
```
make deserialize
```

to run
```
./serialize [Name] [Gender] [Room] {Rooms_discovered} | ./deserialize
```

This takes in at the command line a single name, a gender in all caps,
a room name, and a number of rooms discovered.

example:
```
./serialize John MALE Dungeon 2 | ./deserialize
```

output:
```
Writing 23 serialized bytes
Received: 
player_info: name = John
gender = 0
location = Dungeon
discovered = 2
```