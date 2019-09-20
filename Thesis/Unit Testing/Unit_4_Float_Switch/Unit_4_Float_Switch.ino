int FLT[8] = {4,5,6,7,8,9,10,11};

int i;

void setup()
{
  Serial.begin(9600);  

  for(i = 0; i < 8; i++)
    pinMode(FLT[i], INPUT_PULLUP);
}

void loop()
{
  for(i = 0; i < 8; i++)
  {
    Serial.print(digitalRead(FLT[i]));
    Serial.print(" ");
  }

  Serial.println();
}
