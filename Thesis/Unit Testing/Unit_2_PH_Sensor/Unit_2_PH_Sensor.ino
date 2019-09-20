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

//=============================== VARIABLES
float acidity, temperature, voltage;

long prevMillis;

void setup()
{
  Serial.begin(9600);
  
  ph.begin();    
  tmp.begin();
}

void loop()
{
  unsigned long currentMillis = millis();    

  if(currentMillis - prevMillis >= 1000)
  {
    prevMillis = currentMillis;

    voltage = analogRead(PH) / 1023.0 * 5000;
    temperature = getTemperature();
    acidity = ph.readPH(voltage, temperature);

    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print("°C");

    Serial.print("\t");

    Serial.print("PH: ");
    Serial.print(acidity);
    Serial.println();
  }

  ph.calibration(voltage, temperature);
}
