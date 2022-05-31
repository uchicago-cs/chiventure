"""This module runs tests on dsl test files (in dsl_tests), and checks 
for discrepancies from their expected outputs (in wdl_expected).

For instructions on running tests, see the README.md, as well as the DSL tutorial 
on the Chiventure Wiki page.

"""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

import sys, os
from pathlib import Path    
import json
from warnings import warn
import warnings


sys.path.append(os.path.abspath(os.path.join('..', 'dsl/src')))

# parsed_dict_to_json transforms the intermediate stage to the wdl json output
from to_wdl.dict_to_json import parsed_dict_to_json

# export_dict parses the dsl file and transforms it to an intermediate stage
from dsl_parser.dsl_to_dict import export_dict
from vars_parser import evalVars
from parse import convert_to_wdl


def gen_out(dsl_path: str) -> str:
    """
    Runs the DSL parsing and conversion algorithm on a single file.
    Instead of outputting to a file, we output everything as a string.
    All debug flags are turned off.
    """
    with open(dsl_path) as f:
        out_str = convert_to_wdl(file_str = f.read(), debug = False, debug_modes = [], default = "")

        return out_str

def run_test(f_dsl, f_wdl: str, show: bool) -> bool:
    """
        Compares output from gen_out with the expected output
        stored in one of the wdl_expected files
        f_dsl : the name of the dsl file we are running. Must be stored in tests/dsl_tests
        f_wdl : the name of the wdl file we are comparing to. Must be stored in tests/wdl_expected
        show  : main function will pass the show flag to determine if we want to print discrepancies
                between expected and actual output.
    """
    rv = True
    dsl_path = "tests/dsl_tests/" + f_dsl
    wdl_path = "tests/wdl_expected/" + f_wdl

    out = gen_out(dsl_path)
    expected = open(wdl_path).read()
    len_expected = len(expected)
    len_out = len(out)


    for i in range(len_expected):
        if out[i] != expected[i]:
            
            if show:
                """ 
                if '--show' is passed from the command line, we will print out the 
                first discrepancy between actual and expected outputs, as well as the surrounding
                100 characters to provide the user more context as to where the error is occuring.
                """

                beginning = max(0, i - 50) # We need to compute beginning and end indexes to slice our substring.
                end = min(len_expected, len_out, i + 50)

                broken = out[beginning : end]
                expected_substr = expected[beginning : end]
                
                print(f"{f_dsl}: output does not match expected.")
                print(f"Returned:\n.....\n{broken}\n.....")
                print(f"Expected:\n.....\n{expected_substr}\n.....")
            return False
    return True
    


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
    Flags can also be provided to change the behavior of testing.
    Flags:
        --file=<test_file>      run one <test_file> in dsl_tests/
                                this flag can be repeated
                                if we want to test multiple files at once

        --show                  print differences between
                                the expected and actual outputs
    
    the function will print out a summary of tests, 
    and also a list of failed tests (if any)
    """

    warnings.filterwarnings('ignore')

    # summary statistics
    tests_run = 0
    passed = 0
    failed = 0
    list_failed = []

    #get a list of all files in the tests/dsl_test subdir
    default_files = os.listdir("tests/dsl_tests")

    # get flags, if any
    flags_list = [arg.strip("-") for arg in sys.argv[1:] if arg.startswith("-")]
    args = [arg for arg in sys.argv[1:] if not arg.startswith("-")]
    
    flags = collect_flags(flags_list)
    show = "show" in flags
    manual = "file" in flags

    if manual:
        files_to_test = flags.get("file", [])
    else:
        files_to_test = default_files

    # test all files that we want to test
    for file in files_to_test:
        rv = run_test(f_dsl = file, f_wdl = os.path.splitext(file)[0] + "_expected.wdl", show = show)
        tests_run += 1
        if rv:
            passed += 1
        else:
            failed += 1
            list_failed.append(file)
    
    """print summary statistics of running tests"""
    print(f"| Tests run: {tests_run} | Tests passed: {passed} | Tests failed: {failed} |")
    
    """print a list of failed tests, if any"""
    if list_failed:
        print(f"List of failed tests:")
        for i in list_failed:
            print(f"\t{i}")
    return
    



if __name__ == "__main__":
    main()

