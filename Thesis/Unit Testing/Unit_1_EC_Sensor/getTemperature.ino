

float getTemperature()
{
  float temperature;

  tmp.requestTemperatures();
  temperature = tmp.getTempCByIndex(0);

  return temperature;
}
