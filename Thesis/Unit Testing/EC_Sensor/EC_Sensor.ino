//=============================== EC ASSIGNING
#include <DFRobot_EC.h>
#include <EEPROM.h>

int EC = A0;

DFRobot_EC ec;

//=============================== TMP ASSIGNING
#include <DallasTemperature.h>
#include <OneWire.h>

int TMP = 14;

OneWire oneWire(TMP);
DallasTemperature tmp(&oneWire);

//=============================== VARIABLES
float conductivity, temperature, voltage;

long prevMillis;
long interval = 1000;

void setup()
{
  Serial.begin(9600);
  
  ec.begin();    
  tmp.begin();
}

void loop()
{
  unsigned long currentMillis = millis();    

  if(currentMillis - prevMillis >= interval)
  {
    prevMillis = currentMillis;

    voltage = analogRead(EC) / 1023.0 * 5000;
    temperature = getTemperature();
    conductivity = ec.readEC(voltage, temperature);

    Serial.print("Temp: ");
    Serial.print(temperature, 2);
    Serial.print("°C");

    Serial.print("\t");
    
    Serial.print("EC: ");
    Serial.print(conductivity, 2);
    Serial.println("mS/cm");
  }

  ec.calibration(voltage, temperature);
}
