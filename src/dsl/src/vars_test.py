# simple script to test the functionality of the evalVars function

import sys
from lark import Lark, Transformer
import json
from vars_parser import evalVars


def main():
    with open(sys.argv[1]) as f:
        file_str = f.read()
        vars_evaluated = evalVars(file_str, debug=True)
        print(vars_evaluated)


if __name__ == "__main__":
    main()
