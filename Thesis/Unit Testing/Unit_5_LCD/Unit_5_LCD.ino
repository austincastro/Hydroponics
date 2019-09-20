#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd[3] = {LiquidCrystal_I2C (0x27,16,2),
                            LiquidCrystal_I2C (0x26,16,2),
                            LiquidCrystal_I2C (0x25,16,2)};

int i;

void setup()
{
  Serial.begin(9600);
  
  for(i = 0; i < 3; i++)
  {
    lcd[i].begin(16,2);
    lcd[i].init();      
    lcd[i].backlight();     
    lcd[i].clear();      
  }
}

void loop()
{
  for(i = 0; i < 3; i++)
  {
    lcd[i].clear(); 
    lcd[i].setCursor(0,0);
    lcd[i].print("Hydroponics!");
  }

  Serial.println("Print in 1st Row");
  delay(1000);

  for(i = 0; i < 3; i++)
  {
    lcd[i].clear(); 
    lcd[i].setCursor(0,1);
    lcd[i].print("Tank #");
    lcd[i].setCursor(6,1);
    lcd[i].print(i + 1);
  }

  Serial.println("Print in 2nd Row");
  delay(1000);
}
