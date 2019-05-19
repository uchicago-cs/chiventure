
THIS IS A PROOF OF CONCEPT FOR USING PROTOBUF TO SERIALIZE AND DESERIALIZE

CAN BE IGNORED

to create .c .h from proto file
	make proto

to compile save.c (will run proto as well)
	make serialize

to compile load.c
	make deserialize

to run
	./serialize [Name] [Gender] [Room] {Rooms_discovered} | ./deserialize

