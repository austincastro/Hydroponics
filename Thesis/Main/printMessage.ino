void printMessage(int a)
{ 
  for(i = 0; i < 3; i++)
    lcd[i].setCursor(0,0);

  //1ST ROW   
  switch(a)
  {
    case 0: //=====================================================
      for(i = 0; i < 3; i++)
        lcd[i].print("Collecting Water");
         
      break;

    case 1: //=====================================================
      for(i = 0; i < 3; i++)
        lcd[i].print("Starting Cycle..");
      
      break;

    case 2: //=====================================================
      for(i = 0; i < 3; i++)
        lcd[i].print("Tank 1 -> Tank 2");
      
      break;

    case 3: //=====================================================
      message = "EC: " + String(conductivity, 2) + "mS/cm   ";
      lcd[0].print(message);

      message = "TEMP: " + String(temperature, 2) + "^C   ";
      lcd[1].print(message);

      message = "PH: " + String(acidity, 2) + "        ";
      lcd[2].print(message);

      break;

    case 4:
      for(i = 0; i < 3; i++)
        lcd[i].print("Sending Message.");
          
      break;
      
    case 5:
      for(i = 0; i < 3; i++)
        lcd[i].print("Message Sent!!!!");
        
      break;
      
    case 6:
      for(i = 0; i < 3; i++)
        lcd[i].print("Saving Values...");
        
      break;
      
    case 7:
      for(i = 0; i < 3; i++)
        lcd[i].print("Values Saved!!!!");
        
      break;
      
    case 8: //=====================================================
      for(i = 0; i < 3; i++)
        lcd[i].print("Tank 2 -> Tank 3");
        
      break;

    case 9: //=====================================================
      if(state == HIGH)
        message = "ON";
      else
        message = "OFF";

      message = "LED is " + message + "       ";
      lcd[0].print(message);
           
      message = "TEMP: " + String(temperature, 2) + "^C   "; 
      lcd[1].print(message);
      
      lcd[2].print("Press to Dispose"); 
        
      break;

    case 10: //=====================================================
      for(i = 0; i < 3; i++)
        lcd[i].print("Disposing Water!");
        
      break;
  }

  //2ND ROW
  for(i = 0; i < 3; i++)
  {
    if(Tank_Capacity[i] == HIGH)
      message = "Full  ";
    else if(FLT_Value[i + 4] == LOW)
      message = "Filled";
    else
      message = "Empty "; 

    lcd[i].setCursor(0,1); 
    message = "Tank " + String(i + 1) + " is " + message;
    lcd[i].print(message);     
  }
}
