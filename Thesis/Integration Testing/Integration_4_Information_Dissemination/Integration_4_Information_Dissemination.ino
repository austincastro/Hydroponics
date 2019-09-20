//=============================== LCD ASSIGNING
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//=============================== GSM ASSIGNING
#include <SoftwareSerial.h>

SoftwareSerial sim800l(12,13);

//=============================== SD ASSIGNING
#include <SPI.h>
#include <SD.h>

int CS = 53;

File myfile;

//=============================== VARIABLES
int BTN = 19;

int state;

boolean lastButton;
boolean currentButton;

//num of system = 639454093726
String num = "+639664400813";
String txt = "Greetings User, this is HOSCA";

void setup()
{
  Serial.begin(9600);
  
  //BUTTON
  pinMode(BTN, INPUT);

  //LCD
  lcd.begin(16,2); 
  lcd.init();     
  lcd.backlight(); 
  lcd.clear();  

  //GSM 
  sim800l.begin(9600);
  
  //SD
  pinMode(CS, OUTPUT);
  SD.begin();
  
  delay(1000);

  //INITIALIZATION
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GSM MODULE");
  lcd.setCursor(0,1);
  lcd.print("Initializing....");
  delay(5000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SD CARD MODULE");
  lcd.setCursor(0,1);
  lcd.print("Initializing....");
  delay(5000);
}

void loop()
{
  Serial.begin("waiting...");
  
  lcd.setCursor(0,0);
  lcd.print("Press the button");
  lcd.setCursor(0,1);

  if(state == 0)
    lcd.print("to send message ");
  else
    lcd.print("to save values  ");

  //check button
  currentButton = debounce(lastButton);
  
  if(lastButton == LOW && currentButton == HIGH)
    state++;

  lastButton = currentButton;  

  //perform action
  if(state == 1)
  {
    Serial.println("Sending...");
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Sending Message.");
    sendNotification();

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Message Sent!!!!");
    delay(3500);

    state = 2;
  }

  if(state == 3)
  {
    Serial.println("Saving...");
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Saving Values...");
    saveMeasurement();
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Values Saved!!!!");
    delay(3500);

    state = 0;
  }
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BTN);
  
  if(last != current)
  {
    delay(5);
    current = digitalRead(BTN);  
  }
  
  return current;
}
