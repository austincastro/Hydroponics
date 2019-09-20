void saveMeasurement()
{
  file = SD.open("HOSCA.txt", FILE_WRITE);  
  file.println("Water Properties:");
  file.print("EC.....");
  file.print(conductivity, 2);
  file.println("mS/cm");
  file.print("PH.....");
  file.print(acidity, 2);
  file.println();
  file.print("TEMP...");
  file.print(temperature, 2);
  file.println("°C");
  file.println("=========================");
  file.close(); 
  delay(3500);      
}
