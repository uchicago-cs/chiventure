# DSL

DSL is a domain-specific language with the following [grammar specifications](https://github.com/uchicago-cs/chiventure/wiki/DSL-~-DSL-Grammar) that allows users to write human-readable games for `chiventure`.

## Writing a DSL file

[...]

## Using the DSL

### Installing Lark

The parser needs to be run on a Python distribution with the Lark module
installed. [...]

### Parsing DSL

A dsl file can be parsed with the following command:
```
python src/dsl_parser.py <filename>
```
> **Note:** this assumes you are in the dsl directory. The path to the `dsl_parser.py` file may need to be changed.

### DSL to WDL

The DSL's primary function is to translate DSL to WDL (the JSON version), 
which can be done (also on a Python distribution with Lark installed) with:

```
python src/parse.py <dsl file> <optional destination>
```
> **Note:** By default, the output file will be stored in 
`wdl/input-file-name.wdl`, unless a destination parameter is specified.