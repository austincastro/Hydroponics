void saveMeasurement()
{
  myfile = SD.open("HOSCA.txt", FILE_WRITE);
  myfile.println("Water Properties:");
  myfile.close();
  delay(3500);   
}
