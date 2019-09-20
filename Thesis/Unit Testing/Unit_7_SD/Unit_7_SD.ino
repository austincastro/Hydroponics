#include <SPI.h>
#include <SD.h>

int CS = 53;

File myfile;

void setup() 
{
  Serial.begin(9600);                 

  //============================================================================
  //INITIALIZE MICRO SD CARD
  Serial.println("INITIALIZING MICRO SD CARD...");
  pinMode(CS, OUTPUT);

  if(SD.begin())
    Serial.println("Micro SD Card Initialized Successfully");
  else
    Serial.println("Error While Initializing Micro SD Card");
}

void loop() 
{
  if(Serial.available() > 0)
    switch(Serial.read())
    {
      case 's':
        SaveMeasurement();
        break;
    }
}

void SaveMeasurement()
{
  //============================================================================
  //CREATE TXT FILE
  Serial.println("CREATING TXT FILE...");
  myfile = SD.open("test.txt", FILE_WRITE);

  if(myfile)
    Serial.println("File Created Successfully");
  else
    Serial.println("Error While Creating File");

  //============================================================================
  //WRITE MESSAGE
  Serial.println("WRITING MESSAGE...");
  myfile.println("Initial Water Properties:");
  
  if(myfile)                       
    Serial.println("Message Written Successfully");
  else
    Serial.println("Error While Writing Message");   

  //============================================================================
  //CLOSE TXT FILE
  Serial.println("CLOSING TXT FILE...");
  myfile.close();  

  if(!myfile)
    Serial.println("File Closed Successfully");
  else
    Serial.println("Error While Closing File");

  //============================================================================
  //OPEN TXT FILE
  Serial.println("OPENING TXT FILE...");
  myfile = SD.open("test.txt");            

  if(myfile)
    Serial.println("File Opened Successfully");
  else
    Serial.println("Error While Opening File");

  //============================================================================
  //READ MESSAGE
  Serial.println("READING MESSAGE...");
  while(myfile.available()) 
    Serial.write(myfile.read());            
      
  if(myfile)
    Serial.println("Message Read Successfully");  
  else 
    Serial.println("Error While Reading Message");   

  //============================================================================
  //CLOSE TXT FILE
  Serial.println("CLOSING TXT FILE...");
  myfile.close();  

  if(!myfile)
    Serial.println("File Closed Successfully");
  else
    Serial.println("Error While Closing File");
}
