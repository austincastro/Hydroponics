void waterTreatment()
{
  if(count < period / 1000)
  {
    sum[0] += conductivity;
    sum[1] += acidity;
    sum[2] += temperature;

    count++;

    if(count == period / 1000)
    {
      conductivity = sum[0] / count;
      acidity = sum[1] / count;
      temperature = sum[2] / count;

      for(i = 0; i < 3; i++)
        sum[i] = 0;    
    }  

    debug(); //HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA
  }
}
