function foo(g1)
    if g1 == 0 then return "You open the chest and find... no coins! You are humble :)"
    else return string.format("You shake the chest and find... %i gold coins!", g1) end
end 