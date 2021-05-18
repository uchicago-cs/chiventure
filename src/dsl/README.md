# DSL

The grammar specifications are contained here: https://github.com/uchicago-cs/chiventure/wiki/DSL-~-DSL-Grammar

The parser needs to be run on a python distribution with the Lark module
installed. A dsl file can be parsed with the following command
```
python src/dsl_parser.py <filename>
```
*note: this assumes you are in the dsl directory. The path to the `dsl_parser.py` file may need to be changed

Currently the dsl grammar supports basic features including rooms, items, 
actions and properties. The `parser.py` file transforms the parsing tree into 
an intermediate stage consisting primarily of python dictionaries. This will 
later be improved to output JSON which is fully compatible with the wdl format.


