# for compatibility with python 3.7 and 3.8
from __future__ import annotations

from dsl_parser import export_dict
import sys
from to_wdl import parsed_dict_to_json
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

def main():
    """The main function. The first cli argument is the dsl file. The second
    (optional) argument is the output wdl file. If no output file is provided, 
    it will default to examples/wdl/{filname}.wdl"""

    flags = [arg.replace("-","") for arg in sys.argv[1:] if arg.startswith("-")]
    args = [arg for arg in sys.argv[1:] if not arg.startswith("-")]

    file_out = None
    try:
        file_out = open(args[1], "w")
    except:
        filename = Path(args[0]).stem
        filepath = base_path / f'examples/wdl/{filename}.wdl'

        warn(f"No output file provided. Default to '{filepath}'")
        file_out = open(filepath, "w")

    with open(args[0]) as f:
        file_str = f.read()
        debug = "debug" in flags
        vars_evaluated = evalVars(file_str, debug=debug)
        intermediate = export_dict(vars_evaluated)
        out_str = parsed_dict_to_json(intermediate)
        file_out.write(out_str)
    file_out.close()

if __name__ == "__main__":
    main()