float getConductivity()
{
  float conductivity, temperature, voltage;
  
  voltage = analogRead(EC) / 1023.0 * 5000;
  temperature = getTemperature(0);
  conductivity = ec.readEC(voltage, temperature);

  volt[0] = voltage;
    
  return conductivity;
}
