void debug()
{
  message = String(temperature) + " " + String(conductivity) + " " + String(acidity);
  Serial.println(message);
}
