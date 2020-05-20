### WDL Action Blocks

These are the intermediary structs that represent action sequences, which WDL team
will provide to Custom Actions team for compiling into ASTs.

The list of blocks is represented by a node that works with utlist.

(No useful functionality for now, because the main usage is in the creation of a 
new sequence from JSON data, which is dependent on the JSON object structures, which is
still a work-in-progress for now.)