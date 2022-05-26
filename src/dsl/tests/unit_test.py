"""This module evaluates references to variables in a dsl file."""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

import sys, os



sys.path.append(os.path.abspath(os.path.join('..', 'dsl/src')))

# parsed_dict_to_json transforms the intermediate stage to the wdl json output
from to_wdl.dict_to_json import parsed_dict_to_json

# export_dict parses the dsl file and transforms it to an intermediate stage
from dsl_parser.dsl_to_dict import export_dict



import json
from warnings import warn
import warnings
from vars_parser import evalVars



# Right now, most testing is done simply by providing a DSL file 
# and eyeballing the produced WDL file to check for discrepancies. 
# It would be beneficial to have a more robust method to test the 
# DSL to WDL parsing and conversion, so we hope to implement unit 
# tests for certain aspects of a Chiventure game, including rooms, 
# actions, and variables.


def gen_out(dsl_path: str) -> str:
    
    file_out = None

    with open(dsl_path) as f:
        file_str = f.read()

        # boolean debug
        debug =  False
        
        # replace None with "intermediate" and "all" with all options
        debug_modes = []
           
        # Check Defaults code
        default = ""


        vars_evaluated = evalVars(file_str, debug=debug, debug_modes=debug_modes)
        intermediate = export_dict(vars_evaluated, debug=debug, debug_modes=debug_modes)
        out_str = parsed_dict_to_json(intermediate, debug=debug, debug_modes=debug_modes, default=default)

        return out_str

def test(f_dsl, f_wdl: str) -> Bool:
    dsl_path = "tests/dsl_tests/" + f_dsl
    wdl_path = "tests/wdl_expected/" +f_wdl

    out = gen_out(dsl_path)
    expected = open(wdl_path).read()
    len_expected = len(expected)
    len_out = len(out)
    for i in range(len_expected):
        if out[i] != expected[i]:
            """ compute beginning and end indexes to slice our substring
            """
            beginning = max(0, i - 50)
            end = min(len_expected, len_out, i + 50)

            broken = out[beginning : end]
            expected_substr = expected[beginning : end]

            print(f"room_test: output does not match expected.")
            print(f"Returned:\n.....\n{broken}\n.....")
            print(f"Expected:\n.....\n{expected_substr}\n.....")
            return False
    return True
    



def main():
    warnings.filterwarnings('ignore')
    print("in main")
    test("room_test.dsl", "room_test_expected.wdl")
"""
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
"""

if __name__ == "__main__":
    main()
