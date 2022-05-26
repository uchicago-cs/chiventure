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

def test(f_dsl, f_wdl: str, show: bool) -> bool:
    rv = True
    dsl_path = "tests/dsl_tests/" + f_dsl
    wdl_path = "tests/wdl_expected/" +f_wdl

    out = gen_out(dsl_path)
    expected = open(wdl_path).read()
    len_expected = len(expected)
    len_out = len(out)


    
    for i in range(len_expected):
        if out[i] != expected[i]:
            rv = False
            if show:
                """ compute beginning and end indexes to slice our substring
                """
                beginning = max(0, i - 50)
                end = min(len_expected, len_out, i + 50)

                broken = out[beginning : end]
                expected_substr = expected[beginning : end]
                
                print(f"{f_dsl}: output does not match expected.")
                print(f"Returned:\n.....\n{broken}\n.....")
                print(f"Expected:\n.....\n{expected_substr}\n.....")
    return rv
    


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
    """
    The main testing function. By default, this function will run all tests. 
    Flags can also be provided as cli arguments to change the behavior of testing.
    Flags:
        --file=<test_file>      run one <test_file> in dsl_tests/
        --show                  print differences between the expected and actual outputs
        
    """
    warnings.filterwarnings('ignore')

    tests_run = 0
    passed = 0
    failed = 0
    list_failed = []
    default_files = []

    flags_list = [arg.strip("-") for arg in sys.argv[1:] if arg.startswith("-")]
    args = [arg for arg in sys.argv[1:] if not arg.startswith("-")]
    
    flags = collect_flags(flags_list)

    show = "show" in flags
    
    manual = "file" in flags
    if manual:
        files_to_test = flags.get("file", [])
    else:
        file_to_test = default_files

    for file in files_to_test:
        rv = test(f_dsl = file, f_wdl = file.strip(".dsl") + "_expected.wdl", show = show)
        tests_run += 1
        if rv:
            passed += 1
        else:
            failed += 1
            list_failed.append(file)
    

        

    
    print(f"| Tests run: {tests_run} | Tests passed: {passed} | Tests failed: {failed} |")
    
    if list_failed:
        print(f"List of failed tests:")
        for i in list_failed:
            print(f"\t{i}")
    



if __name__ == "__main__":
    main()

