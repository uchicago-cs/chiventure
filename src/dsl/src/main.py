from dsl_parser import export_dict
import sys
from to_wdl import parsed_dict_to_json
from pathlib import Path
from warnings import warn
import warnings

base_path = Path(__file__).parent.parent

def single_line_warnings(message, category, filename, lineno, file=None, line=None):
    return f' %s:%s: %s:%s \n' % (filename, lineno, category.__name__, message)
warnings.formatwarning = single_line_warnings

def main():
    file_out = None
    try:
        file_out = open(sys.argv[2], "w")
    except:
        filename = Path(sys.argv[1]).stem
        filepath = base_path / f'wdl/{filename}.wdl'

        warn(f"No output file provided. Default to '{filepath}'")
        file_out = open(filepath, "w")
    with open(sys.argv[1]) as f:
        file_str = f.read()

        intermediate = export_dict(file_str)
        out_str = parsed_dict_to_json(intermediate)
        file_out.write(out_str)
    file_out.close()

if __name__ == "__main__":
    main()