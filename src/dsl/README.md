# DSL

DSL is an as-yet unnamed domain-specific language that allows users to write human-readable games for `chiventure`.

## Writing a DSL file

`.dsl` files, like the Chiventure `.wdl` files they represent, contain a game, some amount of items, and at least two rooms, each of them with various properties. More information on precise grammar [can be found on the wiki](https://github.com/uchicago-cs/chiventure/wiki/DSL-~-DSL-Grammar). 

### Sample files

Sample DSL files can be found in the `examples/dsl` directory, and their corresponding `.wdl` equivalents in the `examples/wdl` directory. Current examples include:

#### Chiventure-valid
- **`connected-rooms.dsl`**, a concise DSL implementation of the [`connected-rooms.wdl`](https://github.com/uchicago-cs/chiventure/blob/dev/tests/wdl/examples/wdl/connected-rooms.wdl) example
- **`connected-vars.dsl`**, a stripped-down version of the `connected-rooms` example written in 11 lines using variables
- **`distaff.dsl`**, a DSL implementation of the `distaff.yaml` game (the game has since been removed from the `dev` branch)
- **`min.dsl`**, essentially the minimum possible DSL file

#### Chiventure-invalid
- `long-example.dsl`, a, well, *long* example DSL file designed to showcase the DSL parser's flexibility and versatility
- `short_example.dsl`, a short, itemless DSL example
- `vars.dsl`, an example that showcases the DSL's variable features

###### While all example `.dsl` files compile to `.wdl`, files incompatible with Chiventure are either not complete games, contain features not supported by WDL/Chiventure, or both.

## Installing Lark

**The parser needs to be run on a Python distribution with the Lark module
installed. The parser runs on Python versions 3.7 and greater, but we recommend Python 3.9.** 

### Installation from Conda Environment File (preferred option)
If `conda` is installed on your computer (which is the case for the CS Linux machines), the environment can be installed with
```
conda env create -f conda_environment.yml
```
###### This assumes your current directory is `src/dsl`; the path to the `.yml` file may need to be changed

The environment can then be activated with 

```
conda activate cs220-dsl
```

###### When the environment is being used you should see `(<environment name>) cnetid@linux` as the command prompt. You can also check that the environment is active with `which python`, which should include `.conda` within the path. For more information on conda environments, see [this guide](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#activating-an-environment).

### Manual Installation

To install Lark on a computer where you have root privileges, use
```
pip install lark-parser --upgrade
```
If you are using a conda environment, run
```
conda install -c conda-forge lark-parser
```

Once the environment is active, Lark can then be installed with 

```
install -c conda-forge lark-parser
```

## Converting a DSL File to WDL

### Creating a `.wdl` File

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

### Running Your `.dsl` File in Chiventure

If it only contains supported features, you can then run your newly created game in Chiventure. From the `src/dsl` directory, assuming you've built Chiventure: 

```
../../build/chiventure examples/wdl/<filename>.wdl
```