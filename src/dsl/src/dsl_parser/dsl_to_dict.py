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
    

    # the functions below do simple transformations

    def ESCAPED_STRING(self, s: Token) -> str:
        """replace escaped characters with unicode equivalents"""
        decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
        return decoded

    def start_g(self, s: list[str]) -> tuple[str, str]:
        """Labels the start location as "start" """
        return ("start", s[0])

    def end_g(self, s: list[str]) -> tuple[str, str]:
        """labels the end location as "end" """
        return ("end", s[0])

    def id(self, s: list[str]) -> tuple[str, str]:
        """labels the id as an id"""
        return ("id", s[0])

    def action_ids(self, s: list[tuple[str, str]]):
        """Takes a list of ("id", <str>) pairs corresponding to action ids, and
        extracts the action ids into a list. This list is then labelled as
        "action_ids" """
        action_names = [name for _, name in s]
        return ("action_ids", action_names)

    def location(self, s: list[str]) -> tuple[str, str]:
        """Labels the location as a location"""
        return ("location", s[0])

    def phrase(self, s: list[Token]) -> str:
        """Joins a list of strings contained within token objects"""
        return ' '.join(s)


    #for documentation of the below transformations, see simple_transformers.py

    ESCAPED_STRING = mod.mod_ESCAPED_STRING
    
    starg_g = mod.mod_start_g

    end_g = mod.mod_end_g

    id = mod.mod_id_label

    action_ids = mod.mod_action_ids

    location = mod.mod_location

    phrase = mod.mod_phrase

    connection = tuple
    property = tuple

