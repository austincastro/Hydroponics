//=============================== PH ASSIGNING
#include <DFRobot_PH.h>
#include <EEPROM.h>

int PH = A1;

DFRobot_PH ph;

//=============================== TMP ASSIGNING
#include <DallasTemperature.h>
#include <OneWire.h>

int TMP = 14;

OneWire oneWire(TMP);
DallasTemperature tmp(&oneWire);

//=============================== LCD ASSIGNING
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//=============================== VARIABLES
int EC = A0;

int i;

float acidity, conductivity, temperature;
float volt[2];

String message;

long prevMillis;
long interval = 1000;

void setup()
{
  Serial.begin(9600);

  ph.begin();
  tmp.begin();

  lcd.begin(16,2);               
  lcd.init();                         
  lcd.backlight();                      
  lcd.clear(); 

  delay(1000);
}

void loop()
{
  unsigned long currentMillis = millis();

  if(currentMillis - prevMillis >= interval)
  {
    prevMillis = currentMillis;

    //get values
    temperature = getTemperature();  
    conductivity = getConductivity();
    acidity = getAcidity();  
    
    //serial print values
    message = String(temperature) + "\t" + String(conductivity) + "\t" + String(acidity) + "\t" + String(volt[0]) + "\t" + String(volt[1]);
    Serial.println(message);

    //lcd print values
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WATER");

    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.setCursor(2,1);
    lcd.print(temperature, 2);
    
    lcd.setCursor(8,0);
    lcd.print("EC:");
    lcd.setCursor(11,0);
    lcd.print(conductivity, 2);

    lcd.setCursor(8,1);
    lcd.print("PH:");   
    lcd.setCursor(11,1);
    lcd.print(acidity, 2);
  }
  
  //calibrate sensors
  ph.calibration(volt[1] * 1000, acidity);
}
