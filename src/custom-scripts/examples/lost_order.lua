function whose_order(name, order)
  string_success = string.format("You check the name on the recipt and... it says %name! This order is yours!", name)
  string_failure = string.format("You check the name on the recipt and... it says Borja? This order isn't yours!")
  
  if order[0] == "M" then
    if name[0] >= 'a' and name[0] <= 'h' or name[0] >= 'A' and name[0] <= 'I' then 
      return string_success end
    else return string_failure end
  if order[0] == "W" then
    if name[0] >= 'i' and name[0] <= 'p' or name[0] >= 'I' and name[0] <= 'P' then
      return string_success end
    else return string_failure end
  return string_success end
end 