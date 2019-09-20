//=============================== TMP ASSIGNING
#include <DallasTemperature.h>
#include <OneWire.h>

int TMP = 14;

OneWire oneWire(TMP);
DallasTemperature tmp(&oneWire);

//=============================== VARIABLES
int EC = A0;

float conductivity, temperature, voltage;
float CoefficientTemp, CoefficientVoltage;

long prevMillis;

void setup()
{
  Serial.begin(9600);
  
  tmp.begin();
}

void loop() 
{
  unsigned long currentMillis = millis();
  
  if(currentMillis - prevMillis >= 1000)
  {
    prevMillis = currentMillis;

    temperature = getTemperature();
    voltage = analogRead(EC) / 1023.0 * 5000;
    CoefficientTemp = 1.0 + 0.0185 * (temperature - 25.0);        
    CoefficientVoltage = voltage / CoefficientTemp;

    if(CoefficientVoltage < 150)
      Serial.println("No solution!");                         //<1ms/cm
    else if(CoefficientVoltage > 3300)
      Serial.println("Out of the range!");                    //>20ms/cm
    else
    {
      if(CoefficientVoltage <= 448)
        conductivity = 6.84 * CoefficientVoltage - 64.32;     //01ms/cm< EC <=03ms/cm
      else if(CoefficientVoltage <= 1457)
        conductivity = 6.98 * CoefficientVoltage - 127.00;    //03ms/cm< EC <=10ms/cm
      else
        conductivity = 5.30 * CoefficientVoltage + 2278.00;   //10ms/cm< EC < 20ms/cm
      
      conductivity /= 1000;                                   //convert us/cm to ms/cm
    }
   
    Serial.print("Voltage:");
    Serial.print(voltage);                                    //0 to 4995 (mV)
    Serial.print("   ");

    Serial.print("Temp:");
    Serial.print(temperature);                                //temperature (^C)
    Serial.print("   ");
    
    Serial.print("EC:");
    Serial.print(conductivity);                               //conductivity (mS/cm)
    Serial.println();
  }
}
