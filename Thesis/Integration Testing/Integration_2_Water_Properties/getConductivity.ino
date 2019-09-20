float getConductivity()
{
  float conductivity, temperature, voltage;
  float CoefficientTemp, CoefficientVoltage;

  temperature = getTemperature();
  voltage = analogRead(EC) / 1023.0 * 5;
  CoefficientTemp = 1.0 + 0.0185 * (temperature - 25.0);        
  CoefficientVoltage = voltage * 1000.0 / CoefficientTemp;

  //if(CoefficientVoltage < 150)
  //  conductivity = 1000;                                //<1ms/cm
  //else if(CoefficientVoltage > 3300)
  //  conductivity = 20000;                               //>20ms/cm
  //else
  //{
    if(CoefficientVoltage <= 448)
      conductivity = 6.84 * CoefficientVoltage - 64.32;   //01ms/cm< EC <=03ms/cm
    else if(CoefficientVoltage <= 1457)
      conductivity = 6.98 * CoefficientVoltage - 127.00;  //03ms/cm< EC <=10ms/cm
    else
      conductivity = 5.30 * CoefficientVoltage + 2278.00; //10ms/cm< EC < 20ms/cm
    
    conductivity /= 1000;                                 //convert us/cm to ms/cm
  //}

  volt[0] = voltage;
    
  return conductivity;
}
