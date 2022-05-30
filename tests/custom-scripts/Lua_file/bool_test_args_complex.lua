function foo(arg1, arg2, arg3)
  if arg1 then
      if arg1 and arg2 or arg3 then
          return arg2 or arg3 
      elseif not arg1 then
          return arg2 and arg3 end
  else return arg 3 end 
end 