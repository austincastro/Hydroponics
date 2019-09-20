int EN = 8;
int DIR = 9;
int STEP = 10;

int i;
int revolution = 200;

void setup()
{
  Serial.begin(9600);
  
  pinMode(EN, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void loop()
{
  digitalWrite(EN, LOW); 
  digitalWrite(DIR, HIGH);              //Set the spinning direction clockwise

  for(i = 0; i < revolution; i++)       //Spin the stepper motor 1 revolution quickly
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
  }
  
  delay(1000);  
  digitalWrite(DIR, LOW);               //Set the spinning direction counterclockwise

  for(i = 0; i < revolution; i++)       //Spin the stepper motor 1 revolution quickly
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
  }

  digitalWrite(EN, HIGH);
  delay(1000);
}
