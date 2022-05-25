function foo(name, order)
    string_success = string.format("You check the name on the recipt and... it says %s! This order is yours!", name)
    string_failure = "You check the name on the recipt and... it says Borja? This order isn't yours!"
    string_confused = "It has the wrong receipt..."

    if (name == nil or order == nil) then
        return "I do not exist!"

    local name2 = string.lower(name)

    if order == "McDonalds" then
        if name2 >= "aaaaaaaa" and name <= "hhhhhhhh" then
            return string_success
        else return string_failure end
    else return string_confused end
end