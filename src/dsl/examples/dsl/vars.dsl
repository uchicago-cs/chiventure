# Define variables
$intro = "hello {firstname} {lastname}"
$fork = """
ITEM Fork
    long desc: "a fork. theres \"nothing\" remarkably special about it."
"""


GAME START Room A END room C
  # quotations around substitutions are optional unless you wish to include
  # escape characters
  intro: $intro {firstname: John, lastname: "Smith"}

ROOM room A
  $fork
    action: TAKE
      TAKE success: "success"
      TAKE failure: "failure"
  $fork2 { room: "room B" }
    property1: "value"
  $fork
    long desc: "this should override the other long description"

# Variables can be defined anywhere
$fork2 = """
ITEM fork2 IN {room}
"""
