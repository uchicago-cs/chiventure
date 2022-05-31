function foo(arg1, arg2, arg3)
    if arg1 == 'b' and arg2 == 25 and arg3 == false then return 199 else return 1 end
    if arg1 == 'b' and arg2 == 25 and arg3 == false then return tonumber(199) 
    else return tonumber(arg2) * 4 end
  end
