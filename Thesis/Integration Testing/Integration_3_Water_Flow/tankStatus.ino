void tankStatus()
{
  //sense float switches
  for(i = 0; i < 8; i++)
    FLT_Value[i] = digitalRead(FLT[i]);
   
  //per tank status
  for(i = 0; i < 4; i++)
  {
    if(FLT_Value[i] == HIGH && FLT_Value[i + 4] == LOW)
      Tank_Status[i] = HIGH;  
    else
      Tank_Status[i] = LOW;   
  }

  Tank_Status[2] *= Tank_Status[3];
  
  //per area status
  for(i = 0; i < 3; i++)
  {
    if(Tank_Status[i] == HIGH)
      Tank_Capacity[i] = HIGH;
    else
      Tank_Capacity[i] = LOW;     
  }

  FLT_Value[6] *= FLT_Value[7];
}
