# DSL

DSL is a domain-specific language with the following [grammar specifications](https://github.com/uchicago-cs/chiventure/wiki/DSL-~-DSL-Grammar) that allows users to write human-readable games for `chiventure`.

## Writing a DSL file

[...]

## Using the DSL

### Installing Lark

The parser needs to be run on a Python distribution with the Lark module
installed.

To install Lark on a personal computer, use
```
pip install lark-parser --upgrade
```
If you are using a conda environment, run
```
conda install -c conda-forge lark-parser
```


#### CS Linux Machines
Installing lark is a bit more difficult without root privileges, however, it can be done with conda environments.
To create an environment, run `conda create --name cs220-dsl` (the name can be anything). To use the environment, run `conda activate cs220-dsl`. When the environment is being used you should see `(cs220-dsl) name@linux` as the command prompt. You can also check that the environment is active with `which python`, which should include `.conda` within the path. Once this environment is active, Lark can then be installed with `install -c conda-forge lark-parser`.

For more information on conda environments, refer to https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#activating-an-environment.

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