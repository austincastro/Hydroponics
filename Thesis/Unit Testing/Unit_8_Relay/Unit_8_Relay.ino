int RLY[8] = {39,40,41,42,43,44,45,46};

int i;

String msg;

void setup()
{
  Serial.begin(9600);
  
  for(i = 0; i < 8; i++)
    pinMode(RLY[i], OUTPUT);  
}

void loop()
{
  for(i = 0; i < 8; i++)
  {
    msg = "Relay #" + String(i + 1) + " is ON";
    Serial.println(msg);
    
    digitalWrite(RLY[i], HIGH);
    delay(1000);

    msg = "Relay #" + String(i + 1) + " is OFF";
    Serial.println(msg);
    
    digitalWrite(RLY[i], LOW);
    delay(1000);
   
  }
}
