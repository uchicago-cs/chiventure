# common aliases used by wdl conversion functions.
# Defined here to avoid excessive repeat code throughout modules.

import json

PROPERTY_ALIASES = {
    "short desc": "short_desc",
    "short": "short_desc",
    "long desc": "long_desc",
    "long": "long_desc",
    "introduction": "intro"
}

ACTION_ALIASES = {
    "success": "text_success",
    "failure": "text_fail",
    "fail": "text_fail"
}

def to_json(self) -> str: 
    """ For internal testing only: converts an item to its JSON format """
    return json.dumps(self.to_wdl_structure(),indent=2)
