function foo(g1)
    if g1 == '0' then return "You open the chest and... no coins! You are humble :)"
    else return string.format("You shake the chest once more and find... %i gold coins!", g1) end
end 