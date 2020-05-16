health_modify = function (a, b)
	if (b == 0)
	a = 0;
	else if (b == 1)
	a = 100;
	else if (b == 2)
	a = 50;
	else 
	error("invalid operation")
	
	return a;
end 
      
