# This file contains the code that defines Player class
# Defines a Room class and its methods for conversion to WDL.
import json
from to_wdl.util import PROPERTY_ALIASES, ACTION_ALIASES
from warnings import warn
from collections import ChainMap
from to_wdl.wdl_item import Item

class Player:
    def __init__(self, name: str, contents: dict):
        self.contents = contents
        self.name = name

        self.wdl_contents = {}

    def to_json(self) -> str: 
        """ For internal testing only: converts a game to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)
    
    def to_wdl_structure(self) -> dict:
        """
            Converts a Game to WDL structure using its properties. Generates 
            default values where they are missing.
        """

        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "attributes":
                self.wdl_contents["attributes"] = self.contents["attributes"]
            elif k == "stats":
                self.wdl_contents["stats"] = self.contents["stats"]
        self.generate_defaults()
        return {f"{self.name}": self.wdl_contents}

    def generate_defaults(self):
        """
            Ensures that an Item can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with its default values.
        """
        # generate default for long description
        if 'long_desc' not in self.wdl_contents:
            short_desc = self.wdl_contents.get('short_desc', '')
            default = f"This is a {self.name}. {short_desc}"
            self.wdl_contents['long_desc'] = f"{default}"
            warn(f'''missing: long description for {self.name}, generated default: {self.wdl_contents['long_desc']}''')
                
        # generate default for short description
        if 'short_desc' not in self.wdl_contents:
            self.wdl_contents['short_desc'] = f"{self.name}"
            warn(f'''missing: short description for {self.name}, generated default: {self.wdl_contents['short_desc']}''')