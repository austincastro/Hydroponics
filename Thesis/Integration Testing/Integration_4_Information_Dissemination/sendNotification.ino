void sendNotification()
{
  sim800l.println("AT+CMGF=1");                 
  delay(1000);
  sim800l.println("AT+CMGS=\"" + num + "\"\r"); 
  delay(1000);
  sim800l.println(txt);                        
  delay(500);
  sim800l.println((char)26);                
  delay(1000);
}
