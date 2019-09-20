#include <RBDdimmer.h>

int ZC = 2;                           
int PWM = 3;

dimmerLamp dimmer(PWM);   

int i;
int brightness;

void setup() 
{
  Serial.begin(9600);
  
  dimmer.begin(NORMAL_MODE, ON);               
}

void loop() 
{
  Serial.println("Increases Brightness");
  
  for(i = 0; i < 100; i++)  
  {
    brightness = map(i, 1, 100, 35, 70);
    dimmer.setPower(brightness);
    delay(100);
  }

  Serial.println("Decreases Brightness");
  
  for(i = 100; i > 0; i--) 
  {
    brightness = map(i, 1, 100, 35, 70);
    dimmer.setPower(brightness);
    delay(100);
  }
}
