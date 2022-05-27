"""This module parses a dsl file and outputs an intermediate stage"""

# for compatibility with python 3.7 and 3.8
from __future__ import annotations

from lark import Lark, Transformer
from lark.lexer import Token
from pathlib import Path
from warnings import warn
import json

import dsl_parser.transformers as trans
import dsl_parser.simple_modifiers as mod


grammar_path = Path(__file__).parent.parent.parent / "grammars"
grammar_f = open(grammar_path / "dsl_grammar.lark")
dsl_grammar = grammar_f.read()
grammar_f.close()

parser = Lark(dsl_grammar, parser='earley', import_paths=[grammar_path])


# main outward-facing function
def export_dict(file_str, debug=False, debug_modes=[]):
    """Parses the language and returns an intermediate stage consisting
    of python dictionaries"""
    tree = parser.parse(file_str)
    if debug and "dsl-tree" in debug_modes:
        print(tree.pretty())
    intermediate = TreeToDict().transform(tree)
    if debug and "intermediate" in debug_modes:
        print(json.dumps(intermediate, indent=2))
    return intermediate



class TreeToDict(Transformer):
    # for documentation of these transformations, see transformers.py
    #game = transform_game

    game = trans.transform_game

    room = trans.transform_room
    
    connections = trans.transform_connections

    item = trans.transform_item

    action = trans.transform_action

    misplaced_property = trans.transform_misplaced

    
    

    #for documentation of the below transformations, see simple_modifiers.py

    ESCAPED_STRING = mod.mod_ESCAPED_STRING
    
    start_g = mod.mod_start_g

    end_g = mod.mod_end_g

    id = mod.mod_id_label

    action_ids = mod.mod_action_ids

    location = mod.mod_location

    phrase = mod.mod_phrase

    connection = tuple
    property = tuple

