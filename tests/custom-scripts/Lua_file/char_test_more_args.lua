function foo(arg1, arg2, arg3)
  if arg1 == 'a' and arg2 == 'b' and arg3 == 'Z' then return '!' end
  if arg1 == 'a' and arg2 == 'b' then return 'e' end
  if arg1 == 'a' then return 'c' end
  if arg2 == 'b' then return 'd' end
end