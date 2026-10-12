

 
--[[ function returning the max between two numbers --]]
function max(num1, num2)

  if(num1 > num2) then
        result = num1;
   else result = num2;
  end

  return result; 
  
end



function main()
  
  number1 = 3;
  number2 = 8;

  Console_Printf("------------------------------------------------------------------------\n");  

  Console_Printf("Lua version %s\n", _VERSION);
   
  Console_Printf("De %d y %d el mayor es %d \n", number1, number2, max(number1, number2));

  Console_Printf("Numeros aleatorio de 1 a 100: \n");
  
  for i=0,10,1 do
    Console_Printf("%d ", RandBetween(1,100));
  end
  
  TracePrintColor(1, "Prueba de envio %.2f con cadena %s", 10.45, "hola radiola"); 
  
  Console_Printf("\nIntroduce una tecla:");
  Console_Printf("[%c]\n", Console_GetChar());

  Console_Printf("\n"); 

  return 10;
  
end 


return main()