"""The main script. Transforms a dsl file into a wdl file."""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

# export_dict parses the dsl file and transforms it to an intermediate stage
from dsl_parser.dsl_to_dict import export_dict

# parsed_dict_to_json transforms the intermediate stage to the wdl json output
from to_wdl.dict_to_json import parsed_dict_to_json


import sys
from pathlib import Path
from warnings import warn
import warnings
from vars_parser import evalVars

base_path = Path(__file__).parent.parent

# Formats warning messages
def single_line_warnings(message, category, filename, lineno, file=None, line=None):
    path = Path(filename)
    short_path = Path(*path.parts[-2:])
    return f' %s:%s\t %s: %s \n' % (short_path, lineno, category.__name__, message)
warnings.formatwarning = single_line_warnings

def collect_flags(flags: list) -> dict:
    """Transforms a list of flags into a dictionary mapping flags to options"""

    flags_dict = {}
    for f in flags:
        name = f
        option = None
        if "=" in f:
            name, option = f.split("=")

        if name in flags_dict:
            flags_dict[name].append(option)
        else:
            flags_dict[name] = [option]
    return flags_dict

def main():
    """The main function. The first cli argument is the dsl file. The second
    (optional) argument is the output wdl file. If no output file is provided, 
    it will default to examples/wdl/{filname}.wdl. The following flags can also
    be added
        --no-write            the function will not write to a file
        --ignore-warnings     the function will not issue any warnings

    There is also the debug flag, which has several options
        --debug=vars-tree     prints the variables parsing tree
        --debug=vars          prints the file after evaluating variables
        --debug=dsl-tree      prints the parsing tree for the dsl language
        --debug=intermediate  prints the intermediate stage
        --debug=end           prints the final json file
        --debug=all           does all of the above
    There is also the defaults flags:
        --no-defaults         will not generate any default values
        --some-defaults       only generates the required default values
    Note that multiple debug flags can be specified and the --debug flag 
    defaults to --debug=intermediate"""

    flags_list = [arg.strip("-") for arg in sys.argv[1:] if arg.startswith("-")]
    args = [arg for arg in sys.argv[1:] if not arg.startswith("-")]
    
    # dictionary containing flags and options
    flags = collect_flags(flags_list)
    
    if "ignore-warnings" in flags:
        warnings.filterwarnings('ignore')
    
    no_write = "no-write" in flags
    file_out = None
    if not no_write:
        try:
            file_out = open(args[1], "w")
        except:
            filename = Path(args[0]).stem
            filepath = base_path / f'examples/wdl/{filename}.wdl'

            warn(f"No output file provided. Default to '{filepath}'")
            file_out = open(filepath, "w")
    else:
        warn("The --no-write flag was specified, so no file will be changed by the program")

    with open(args[0]) as f:
        file_str = f.read()

        # boolean debug
        debug = "debug" in flags
        
        # replace None with "intermediate" and "all" with all options
        debug_modes = []
        for mode in flags.get("debug", []):
            if mode is None:
                debug_modes.append("intermediate")
            elif mode == "all":
                debug_modes += ["vars-tree", "vars", "dsl-tree", "intermediate", "end"]
            else:
                debug_modes.append(mode)
        
        # Check Defaults code
        default = ""
        if "no-defaults" in flags and "some-defaults" in flags:
            default= ""
        elif "no-defaults" in flags:
            default = "no-defaults"
        elif "some-defaults" in flags:
            default = "some-defaults"

        

        vars_evaluated = evalVars(file_str, debug=debug, debug_modes=debug_modes)
        intermediate = export_dict(vars_evaluated, debug=debug, debug_modes=debug_modes)
        out_str = parsed_dict_to_json(intermediate, debug=debug, debug_modes=debug_modes, default=default)
        
        if not no_write:
            file_out.write(out_str)
    if file_out:
        file_out.close()

if __name__ == "__main__":
    main()