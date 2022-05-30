function foo(name, order)
  string_success = string.format("You check the name on the recipt and... it says %s! This order is yours!", name)
  string_failure = string.format("You check the name on the recipt and... it says Borja? This order isn't yours!")
  string_confused = "It has the wrong receipt..."

  name2 = string.lower(name)

  if order == "Wingstop" then
    if name2 > "hhhhhhhh" and name2 < "pppppppp" then 
      return string_success
    else return string_failure end
  else return string_confused end
end