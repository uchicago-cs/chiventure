# This file contains the code that defines Room class
# Defines a Room class and its methods for conversion to WDL.
import json
from to_wdl.util import PROPERTY_ALIASES, ACTION_ALIASES
from warnings import warn
from collections import ChainMap
from to_wdl.wdl_item import Item

class Room:
    def __init__(self, id: str, contents: dict, default: str):
        """
            Defines a Room class for conversion to WDL, with an id and a list of
            contents and/or properties.
        """
        self.id = id
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
            Converts a Room item to WDL structure using its contents. Generates 
            default values where they are missing, and assembles a list of 
            connections and items for WDL compatibility.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "connections":
                self.wdl_contents["connections"] = self.connections_list()
            elif k == "items":
                self.wdl_contents["items"] = self.items_list()
            else:
                self.wdl_contents[k] = v

        if self.default == "no-defaults":
            warn(f'''warning: no default values generated for {self.id}, wdl file may not run''')
        self.generate_defaults()
        return {self.id: self.wdl_contents}
        
    def generate_defaults(self):
        """
            Ensures thats a Room item can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with default values.
        """

        if self.default == "no-defaults":
            warn(f'''warning: no default values generated for room, wdl file may not run''')
            return
        else:
            # generate default for short description     
            if 'short_desc' not in self.wdl_contents:
                default_id = self.id or "a room"
                self.wdl_contents['short_desc'] = f"{default_id}"
                warn(f'''missing: short description for {default_id}, generated default: {self.wdl_contents['short_desc']}''')
            
            # generate default for long description
            if 'long_desc' not in self.wdl_contents:
                id = self.id or "room"
                short = self.wdl_contents.get('short desc', '')
                default = f"This is a {id}. {short}"
                self.wdl_contents['long_desc'] = f"{default}"
                warn(f'''missing: long description for {id}, generated default: {self.wdl_contents['long_desc']}''')

        
            
    def connections_list(self) -> list:
        """
            Assembles a list of a room's conections, with their directions and 
            desinations included.
        """
        if 'connections' not in self.contents:
            warn(f'''room {self.id} has no connections''')
            return []
        else:
            return list(map(lambda i: {
                'direction': i.upper(),
                'to': self.contents['connections'][i]
            }, self.contents['connections']))

    def items_list(self) -> list:
        """
            Assembles a list of a room's items.
        """
        return list(map(lambda i: i.id, self.contents.get('items',[])))