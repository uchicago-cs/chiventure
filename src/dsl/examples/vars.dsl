# Define variables
$intro = "hello {firstname} {lastname}"
$fork = """
ITEM Fork
long: "a fork. theres \"nothing\" remarkably special about it."
"""


GAME START Room A END room C
  intro: $intro {firstname: "John", lastname: "Smith"}

ROOM room A
  $fork
    action: TAKE
      TAKE success: "success"
      TAKE failure: "failure"
  $fork
  $fork2 {room: "room B"}
    property1: "value"
    long desc: "this should override"

# Variables can be defined anywhere
$fork2 = """
ITEM fork2 IN {room}
"""