function foo(arg1, arg2)
    -- Arguments of an object don't have to be of the same type!
    if arg1 == 'X' and arg2 == 'Y' then return 100 end

    result = arg1 + arg2
    return result
end