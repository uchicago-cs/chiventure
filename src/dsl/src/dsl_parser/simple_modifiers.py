"""This module defines simple transformers/modifiers that perform utility functions"""

from lark.lexer import Token

def mod_ESCAPED_STRING(self, s: Token) -> str:
    """replace escaped characters with unicode equivalents"""
    decoded = bytes(s[1:-1], "utf-8").decode("unicode_escape")
    return decoded

def mod_start_g(self, s: list[str]) -> tuple[str, str]:
    """Labels the start location as "start" """
    return ("start", s[0])

def mod_end_g(self, s: list[str]) -> tuple[str, str]:
    """labels the end location as "end" """
    return ("end", s[0])

def mod_id_label(self, s: list[str]) -> tuple[str, str]:
    """labels the id as an id"""
    return ("id", s[0])

def mod_action_ids(self, s: list[tuple[str, str]]):
    """Takes a list of ("id", <str>) pairs corresponding to action ids, and
    extracts the action ids into a list. This list is then labelled as
    "action_ids" """
    action_names = [name for _, name in s]
    return ("action_ids", action_names)

def mod_location(self, s: list[str]) -> tuple[str, str]:
    """Labels the location as a location"""
    return ("location", s[0])

def mod_phrase(self, s: list[Token]) -> str:
    """Joins a list of strings contained within token objects"""
    return ' '.join(s)