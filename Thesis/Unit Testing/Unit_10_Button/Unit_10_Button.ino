int BTN = 19;

void setup()
{
  Serial.begin(9600);
  
  pinMode(BTN, INPUT);
}                               

void loop()
{
  Serial.println(digitalRead(BTN));
}
