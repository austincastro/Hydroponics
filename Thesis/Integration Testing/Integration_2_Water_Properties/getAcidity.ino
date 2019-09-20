float getAcidity()
{
  float acidity, temperature, voltage;
  
  voltage = analogRead(PH) / 1023.0 * 5;
  temperature = getTemperature();
  acidity = ph.readPH(voltage * 1000, temperature);

  volt[1] = voltage;
  
  return acidity;
}
