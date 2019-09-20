#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd[3] = {LiquidCrystal_I2C (0x27,16,2),
                            LiquidCrystal_I2C (0x26,16,2), 
                            LiquidCrystal_I2C (0x25,16,2)};

int FLT[8] = {4,5,6,7,8,9,10,11};

int i;

boolean FLT_Value[8];
boolean Tank_Status[4];
boolean Tank_Capacity[3];

void setup()
{
  Serial.begin(9600);
  
  for(i = 0; i < 8; i++)
    pinMode(FLT[i], INPUT_PULLUP);

  for(i = 0; i < 3; i++)
  {
    lcd[i].begin(16,2); 
    lcd[i].init();     
    lcd[i].backlight(); 
    lcd[i].clear();  
  }

  delay(1000);
}

void loop()
{
  tankStatus();
  
  //lcd print tank names
  for(i = 0; i < 3; i++)
  {
    lcd[i].setCursor(0,0);
    lcd[i].print("Tank");
    lcd[i].setCursor(5,0);
    lcd[i].print(i + 1);
    lcd[i].setCursor(7,0);
    lcd[i].print("is");
  }

  //lcd print tank status 
  for(i = 0; i < 3; i++)
  {
    lcd[i].setCursor(10,0);

    if(Tank_Capacity[i] == HIGH)
      lcd[i].print("Full  ");
    else if(FLT_Value[i + 4] == LOW)
      lcd[i].print("Filled");
    else
      lcd[i].print("Empty ");        
  }  

  //serial print tank status 
  for(i = 0; i < 3; i++)
  {
    if(Tank_Capacity[i] == HIGH)
      Serial.print("FULL ");
    else if(FLT_Value[i + 4] == LOW)
      Serial.print("FILLED ");
    else
      Serial.print("EMPTY ");
  }

  Serial.println();
}
