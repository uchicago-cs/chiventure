
$fork = """
ITEM Fork
long: "a fork. theres \"nothing\" remarkably special about it."
"""



GAME START Room A END room C

ROOM room A
  $fork
    action: TAKE
      TAKE success: "asdfasdf"
      TAKE failure: "asdfasdf"
  $fork
  $fork2
    property1: "value"
    long desc: "this should override"

$fork2 = """
ITEM fork2
"""