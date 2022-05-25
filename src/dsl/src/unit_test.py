"""This module evaluates references to variables in a dsl file."""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

# export_dict parses the dsl file and transforms it to an intermediate stage
from dsl_parser.dsl_to_dict import export_dict


import json
from warnings import warn

# Right now, most testing is done simply by providing a DSL file 
# and eyeballing the produced WDL file to check for discrepancies. 
# It would be beneficial to have a more robust method to test the 
# DSL to WDL parsing and conversion, so we hope to implement unit 
# tests for certain aspects of a Chiventure game, including rooms, 
# actions, and variables.

def room_test(room -> dict, json -> json) -> bool:
    #TODO: unit testing for components in room
    for key, value in room.items()
        if key == "short desc":
            short_desc = value
        elif key == "long desc":
            long_desc = value
        elif key == "action":
            action_result = action_test(value, json)
        elif key == "item":
            item_result = item_test(value, json)
    file = json.loads(json)
    if (json["short desc"] == short_desc) and (json["long desc"] == long_desc) 
        and action_result and item_result:
        return True
    return False

def action_test(action -> dict, wdl -> json) -> bool:
    #TODO: unit testing for components in action
    for key, value in action.items()
        if key == "action":
            action = value
        elif key == "condition":
            condition = value
        elif key == "text_success":
            text_success = value
        elif key == "text_fail":
            text_fail = value
    file = json.loads(json)
    if (json["action"] == action) and (json["condition"] == condition) 
        and (json["text_success"] == text_success) and (json["text_fail"] == text_fail):
        return True
    return False

def item_test(item -> dict, wdl -> json) -> bool:
    for key, value in item.items()
        if key == "ITEM":
            item_name = value
    file = json.loads(json)
    if (json["ITEM"] == item_name):
        return True
    return False

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
        
        while key, value in intermediate.items():
            if key == "ROOM":
                room_test(value, out_str)
        if not no_write:
            file_out.write(out_str, out_str)
    if file_out:
        file_out.close()