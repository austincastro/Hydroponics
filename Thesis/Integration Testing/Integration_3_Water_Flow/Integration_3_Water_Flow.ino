int FLT[8] = {4,5,6,7,8,9,10,11};
int RLY[8] = {39,40,41,42,43,44,45,46};

int i;
int state;

boolean FLT_Value[8];
boolean Tank_Status[4];
boolean Tank_Capacity[3];

void setup()
{
  Serial.begin(9600);

  for(i = 0; i < 8; i++)
    pinMode(FLT[i], INPUT_PULLUP);
  
  for(i = 0; i < 8; i++)
    pinMode(RLY[i], OUTPUT);   

  delay(1000);    
}

void loop()
{
  tankStatus();

  //cycle wont start unless tank 1 is full
  if(Tank_Capacity[0] == HIGH && Tank_Capacity[1] == LOW && Tank_Capacity[2] == LOW)
    state = 1; 
    
  //tank 1 to tank 2
  if(state == 1)
  {
    Serial.println("tank 1 to tank 2");
    
    if(Tank_Capacity[1] == LOW)
      digitalWrite(RLY[0], HIGH);
    else
      digitalWrite(RLY[0], LOW), delay(5000), state++;
  }

  //tank 2 to tank 3
  if(state == 2)
  {
    Serial.println("tank 2 to tank 3");
    
    if(Tank_Capacity[2] == LOW)
      digitalWrite(RLY[1], HIGH), digitalWrite(RLY[2], HIGH);
    else
      digitalWrite(RLY[1], LOW), digitalWrite(RLY[2], LOW), delay(5000), state++;
  }
  
  //tank 2 dispose
  if(state == 3)
  {
    Serial.println("tank 2 dispose");
    
    if(FLT_Value[5] == LOW)
      digitalWrite(RLY[5], HIGH);
    else
      digitalWrite(RLY[5], LOW), delay(5000), state++;;
  }

  //tank 3 dispose   
  if(state == 4)
  {
    Serial.println("tank 3 dispose");

    if(FLT_Value[6] == LOW)
      digitalWrite(RLY[3], HIGH), digitalWrite(RLY[6], HIGH); 
    else
      digitalWrite(RLY[3], LOW), digitalWrite(RLY[6], LOW), delay(5000), state++;
  }    
}
