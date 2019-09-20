#include <SoftwareSerial.h>

SoftwareSerial sim800l(12,13);

//num of system = 639454093726
String num = "+639664400813";
String txt = "Hello, this is Hydroponics";

void setup() 
{
  Serial.begin(9600);
  sim800l.begin(9600);

  Serial.println("GSM SIM800L BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("s : to send message");
  Serial.println("t : to test information");
  Serial.println();
}

void loop() 
{
  if(Serial.available() > 0)
    switch(Serial.read())
    {
      case 's':
        sendMessage();
        break;

      case 't':
        testInformation();
        break;
    }

  if(sim800l.available() > 0)
    Serial.write(sim800l.read());
}

void sendMessage()
{
  sim800l.println("AT+CMGF=1");                   //Sets the GSM Module in Text Mode
  delay(1000);
  sim800l.println("AT+CMGS=\"" + num + "\"\r");   //Sets the mobile number to receive the text
  delay(1000);
  sim800l.println(txt);                           //The text you want to send
  delay(100);
  sim800l.println((char)26);                      //ASCII code of CTRL+Z
  delay(1000);
}

void testInformation()
{
  sim800l.println("AT");                          //Once the handshake test is successful, it will back to OK
  delay(250);
  sim800l.println("AT+CSQ");                      //Signal quality test, value range is 0-31 , 31 is the best
  delay(250);
  sim800l.println("AT+CCID");                     //Read sim information to confirm whether the sim is plugged
  delay(250);
  sim800l.println("AT+CREG?");                    //Check whether it has registered in the network
  delay(250);
}
