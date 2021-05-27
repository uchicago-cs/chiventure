# DSL

DSL is an as-yet unnamed domain-specific language that allows users to write human-readable games for `chiventure`.

## Writing a DSL file

`.dsl` files, like the Chiventure `.wdl` files they represent, contain a game, some amount of items, and at least two rooms, each of them with various properties. More information on precise grammar [can be found on the wiki](https://github.com/uchicago-cs/chiventure/wiki/DSL-~-DSL-Grammar). 

### Sample files

Sample DSL files can be found in the `examples/dsl` directory, and their corresponding `.wdl` equivalents in the `examples/wdl` directory. Current examples include:

* **`connected-rooms.dsl`**, a concise DSL implementation of the [`connected-rooms.wdl`](https://github.com/uchicago-cs/chiventure/blob/dev/tests/wdl/examples/wdl/connected-rooms.wdl) example
* **`distaff.dsl`**, a DSL implementation of the `distaff.yaml` game (the game has since been removed from the `dev` branch)
* `long-example.dsl`, a, well, *long* example DSL file designed to showcase the DSL parser's flexibility and versatility
* **`min.dsl`**, essentially the minimum possible DSL file
* `short_example.dsl`, a short, itemless DSL example
* `vars.dsl`, an example that showcases the DSL's variable features

###### While all example `.dsl` files compile to `.wdl`, only some resulting files (the bold ones) will run in Chiventure; the others are either not complete games, contain features not supported by WDL/Chiventure, or both.

## Installing Lark

**The parser needs to be run on a Python distribution with the Lark module
installed.** To install Lark on a personal computer, use
```
pip install lark-parser --upgrade
```
If you are using a conda environment, run
```
conda install -c conda-forge lark-parser
```

#### CS Linux Machines

Installing Lark is a bit more difficult on the CS machines without root privileges, however, it can be done with conda environments.

To create an environment, run 
```
conda create --name <environment name>
```
To use the environment, run 
```
conda activate <environment name> 
```
###### When the environment is being used you should see `(<environment name>) cnetid@linux` as the command prompt. You can also check that the environment is active with `which python`, which should include `.conda` within the path. For more information on conda environments, see [this guide](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#activating-an-environment).

Once the environment is active, Lark can then be installed with 

```
install -c conda-forge lark-parser
```

## Converting a DSL File to WDL

The DSL's primary function is to translate DSL to WDL (the JSON version), 
which can be done (also on a Python distribution with Lark installed) with:

```
python src/parse.py <dsl file> <optional destination>
```
###### By default, the output file will be stored in `examples/wdl/<input-file-name>.wdl`, unless a destination parameter is specified.

#### Debugging Mode

A verbose debugging mode can be enabled using the `--debug` flag:

```
python src/parse.py <dsl file> <optional destination> --debug
```