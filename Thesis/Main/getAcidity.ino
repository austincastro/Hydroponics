float getAcidity()
{
  float acidity, temperature, voltage;
  
  voltage = analogRead(PH) / 1023.0 * 5000;
  temperature = getTemperature(0);
  acidity = ph.readPH(voltage, temperature);

  volt[1] = voltage;
  
  return acidity;
}
