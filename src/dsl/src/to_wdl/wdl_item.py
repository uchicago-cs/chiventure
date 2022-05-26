# This file contains the code that defines Item class
# Defines a Item class and its methods for conversion to WDL.
import json
from to_wdl.util import PROPERTY_ALIASES, ACTION_ALIASES
from warnings import warn
from collections import ChainMap


class Item:
    def __init__(self, location: str, contents: dict, default: str):
        """
            Defines an Item class for conversion to WDL, with an id, a location, 
            and a list of actions and/or properties.
        """
        self.location = location
        self.contents = contents
        self.default = default
        assert 'id' in self.contents, "Item is missing an id"
        self.id = self.contents['id']

        # self.wdl_contents stores what will be outputted so we don't lose the
        # original input from the parser
        self.wdl_contents = {}

    def to_json(self) -> str: 
        """ For internal testing only: converts an item to its JSON format """
        return json.dumps(self.to_wdl_structure(),indent=2)

    def to_wdl_structure(self) -> dict:
        """
            Converts an Item to WDL structure using its properties. Generates 
            default values where they are missing, and assembles a list of 
            actions for WDL compatibility.
        """
        for k, v in self.contents.items():
            if k in PROPERTY_ALIASES:
                self.wdl_contents[PROPERTY_ALIASES[k]] = v
            elif k == "actions":
                self.wdl_contents["actions"] = self.actions_list()
            elif k not in ['id']:
                self.wdl_contents[k] = v

        self.wdl_contents['in'] = self.location
        if "actions" not in self.wdl_contents:
            self.wdl_contents["actions"] = []
        self.generate_defaults()

        # currently lowercase items do not seem to be recognized by chiventure
        wdl_id = self.id
        if not self.id.isupper():
            wdl_id = self.id.upper()
            warn(f"Chiventure requires that item ids be uppercase. Replacing {self.id} with {wdl_id}.")

        return {wdl_id: self.wdl_contents}

    def generate_defaults(self):
        """
            Ensures that an Item can be converted to WDL by filling in 
            neccesary information (like short and long description) that is not 
            included with its default values.
        """
        if self.default == "no-defaults":
           warn(f'''warning: no default values generated for item, wdl file may not run''')
           return
        
        else: #generate required defaults (for some-defaults flag) and maybe generate all defaults
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

            if self.default == "":
            # generate default interaction text for actions
                for i in self.wdl_contents.get('actions', []):
                    if 'text_success' not in i:
                        i['text_success'] = f"You {i['action'].lower()} the {self.id}."
                        warn(f'''missing: success text for action {i['action']} for item {self.id}, generated default: {i['text_success']}''')
                    if 'text_fail' not in i:
                        i['text_fail'] = f"You cannot {i['action'].lower()} the {self.id}."
                        warn(f'''missing: failure text for action {i['action']} for item {self.id}, generated default: {i['text_fail']}''')
            

    # to do: action conditions -- how?
    def actions_list(self) -> list:
        """
            Assembles a list of an item's actions, with their success and 
            failure text included.
        """
        out = []
        for name, action_dict in self.contents.get('actions', {}).items():
            action_wdl_dict = {"action": name}
            for k,v in action_dict.items():
                if k in ACTION_ALIASES:
                    action_wdl_dict[ACTION_ALIASES[k]] = v
                else:
                    action_wdl_dict[k] = v
            out.append(action_wdl_dict)
 
        return out