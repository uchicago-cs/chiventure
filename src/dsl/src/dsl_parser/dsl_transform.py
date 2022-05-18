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