# This file contains the code that defines Game class
# Defines a Game class and its methods for conversion to WDL.
import json
from to_wdl.util import PROPERTY_ALIASES, ACTION_ALIASES
from warnings import warn
from collections import ChainMap

class Game:
    def __init__(self, contents: dict, default: str):
        """
            Defines a Game class for conversion to WDL, with an id and a list of
            contents and/or properties.
        """
        self.contents = contents
        self.default = default

        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}

    
    def to_json(self) -> str: 
        """ For internal testing only: converts an item to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)

    def to_wdl_structure(self) -> dict:
        """
            Converts a Game to WDL structure using its properties. Generates 
            default values where they are missing.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            if k == "end":
                self.wdl_contents["end"] = {"in_room": v}
            else:
                self.wdl_contents[k] = v
        
        self.generate_defaults()
        return {'GAME': self.wdl_contents}

    def generate_defaults(self):
        """
            Ensures that a Game can be converted to WDL by filling in 
            neccesary information (like an introduction) that is not 
            included with its default values.
        """
        if self.default == "no-defaults":
            warn(f'''warning: no default values generated for game, wdl file may not run''')
        else:
            # generate default for introduction
            if 'intro' not in self.wdl_contents:
                default = self.wdl_contents.get('start') or "room"
                self.wdl_contents['intro'] = f"Welcome! You're in a {default}"
                warn(f'''missing: introduction for game, generated default: {self.wdl_contents['intro']}''')

