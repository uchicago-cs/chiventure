# This file contains the code that defines Npc class
# Defines a Npc class and its methods for conversion to WDL.
import json
from to_wdl.util import PROPERTY_ALIASES, ACTION_ALIASES
from warnings import warn
from collections import ChainMap


class Npc:
    def __init__(self, id, location: str, contents: dict, default: str):
        """
            Defines an NPC class for conversion to WDL, with a unique name
            a location, and a list of contents and/or properties
        """
        self.location = location
        self.id = id
        self.contents = contents
        self.default = default

        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}


    def to_json(self) -> str: 
        """ For internal testing only: converts an npc to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)
    
    def to_wdl_structure(self) -> dict:
        """
            Converts an NPC to WDL structure using its properties. Generates 
            default values where they are missing.
        """
        print("in to_wdl_structure for npc")
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "inventory":
                self.wdl_contents["inventory"] = self.inventory_list()
            else:
                self.wdl_contents[k] = v

        self.wdl_contents['in'] = self.location

        if self.default == "no-defaults":
            warn(f'''warning: no default values generated for {self.id}, wdl file may not run''')
        self.generate_defaults()
        return {f"{self.id}": self.wdl_contents}
    
    def inventory_list(self) -> list:
        """
        Assembles a list of an inventory's items
        """
        if 'inventory' not in self.contents:
            return []
        else:
            print("making inventory list")
            out = []
            for name, action_dict in self.contents.get('inventory', {}).items():
                inventory_wdl_dict = {"inventory": name}
                for k,v in inventory_dict.items():
                    inventory_wdl_dict[k] = v
                out.append(inventory_wdl_dict)

        print(out)
        return out


    def generate_defaults(self):
        """
            Ensures that an NPC can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with its default values.
        """
        if self.default == "no-defaults":
            warn(f'''warning: no default values generated for room, wdl file may not run''')
            return
        
        else:
            # generate default for long description
            if 'long_desc' not in self.wdl_contents:
                short_desc = self.wdl_contents.get('short_desc', '')
                default = f"This is a {self.id}. {short_desc}"
                self.wdl_contents['long_desc'] = f"{default}"
                warn(f'''missing: long description for {self.id}, generated default: {self.wdl_contents['long_desc']}''')
                    
            # generate default for short description
            if 'short_desc' not in self.wdl_contents:
                self.wdl_contents['short_desc'] = f"{self.id}"
                warn(f'''missing: short description for {self.id}, generated default: {self.wdl_contents['short_desc']}''')