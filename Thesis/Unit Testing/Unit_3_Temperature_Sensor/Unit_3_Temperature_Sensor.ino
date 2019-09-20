#include <DallasTemperature.h>
#include <OneWire.h>

int TMP[2] = {14,15};

OneWire oneWire[2] = {OneWire (TMP[0]),
                      OneWire (TMP[1])};

DallasTemperature tmp[2] = {DallasTemperature (&oneWire[0]),
                            DallasTemperature (&oneWire[1])};

int i;

float TMP_Value[2];

void setup()
{
  Serial.begin(9600);

  for(i = 0; i < 2; i++)
    tmp[i].begin();
}

void loop()
{
  for(i = 0; i < 2; i++)
  {
    tmp[i].requestTemperatures();          
    Serial.print("Temp: ");

    TMP_Value[i] = tmp[i].getTempCByIndex(0);
    Serial.print(TMP_Value[i]);
    Serial.print("^C ");         

    TMP_Value[i] = tmp[i].toFahrenheit(TMP_Value[i]);    
    Serial.print(TMP_Value[i]);
    Serial.print("^F ");

    Serial.print("\t");
  } 

  Serial.println();
  delay(1000);
}
