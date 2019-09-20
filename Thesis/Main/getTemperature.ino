float getTemperature(int a)
{
  float temperature;

  tmp[a].requestTemperatures();
  temperature = tmp[a].getTempCByIndex(0);  
  
  return temperature;
}
