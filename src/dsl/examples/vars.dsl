
$intro = "hello {name}"
$fork = """
ITEM Fork
long: "a fork. theres \"nothing\" remarkably special about it."
"""



GAME START Room A END room C
  intro: $intro {name: "Name"}

ROOM room A
  $fork
    action: TAKE
      TAKE success: "success"
      TAKE failure: "failure"
  $fork
  $fork2 {room: "room B"}
    property1: "value"
    long desc: "this should override"

$fork2 = """
ITEM fork2 in {room}
"""