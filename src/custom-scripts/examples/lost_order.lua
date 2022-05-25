function foo(name, order)
    string_success = string.format("You check the name on the recipt and... it says %s! This order is yours!", name)
    string_failure = "You check the name on the recipt and... it says Borja? This order isn't yours!"
    string_confused = "It has the wrong receipt..."

    name2 = string.lower(name)

    if (order and name and name2) then
        if (order == "McDonalds") then
            if (name2 >= "aaaaaaaa" and name2 <= "hhhhhhhh") then 
                return string_success
            else return string_failure end
        else return string_confused end
    else return string_confused end 
end