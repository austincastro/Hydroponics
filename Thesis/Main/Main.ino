//=============================== EC ASSIGNING
#include <DFRobot_EC.h>
#include <EEPROM.h>

int EC = A0;

DFRobot_EC ec;

//=============================== PH ASSIGNING
#include <DFRobot_PH.h>
#include <EEPROM.h>

int PH = A1;

DFRobot_PH ph;

//=============================== TMP ASSIGNING
#include <DallasTemperature.h>
#include <OneWire.h>

int TMP[2] = {14,15};

OneWire oneWire[2] = {OneWire (TMP[0]),
                      OneWire (TMP[1])};

DallasTemperature tmp[2] = {DallasTemperature (&oneWire[0]),
                            DallasTemperature (&oneWire[1])};

//=============================== LCD ASSIGNING
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd[3] = {LiquidCrystal_I2C (0x27,16,2),
                            LiquidCrystal_I2C (0x26,16,2), 
                            LiquidCrystal_I2C (0x25,16,2)};

//=============================== GSM ASSIGNING
#include <SoftwareSerial.h>

SoftwareSerial sim800l(12,13);

//=============================== SD ASSIGNING
#include <SPI.h>
#include <SD.h>

int CS = 53;

File file;

//=============================== DIMMER ASSIGNING
#include <RBDdimmer.h>

int ZC = 2;
int PWM = 3;

dimmerLamp dimmer(PWM);   

//=============================== VARIABLES
int BTN = 19;
int FLT[8] = {4,5,6,7,8,9,10,11};
int RLY[8] = {39,40,41,42,43,44,45,46};

int i;
int balance, brightness, count, duration, phase;

float acidity, conductivity, temperature;
float volt[2], sum[3];
float threshold[6] = {1,2,1,2,1,2};

//num of system = 639454093726
String message;
String num = "+639664400813";
String txt[2] = {"Greetings User, Please add nutrient solution",
                 "Greetings User, Please press the button in 10 hrs"};

boolean state;
boolean FLT_Value[8];
boolean Tank_Status[4];
boolean Tank_Capacity[3];

unsigned long currentMillis;
unsigned long prevMillis[2];
long interval;

long second = 1000;
long minute = second * 60;
long hour = minute * 60;
long day = hour * 24;
long period = second * 30;

/*
  Lettuce properties
  pH: 5.5-6.6 pH
  EC: 0.8-1.2 mS/cm
  Temp: 21.1-23.9 ^C
  
  Kangkong properties
  pH: 6.5-6.8 pH
  EC: 0.4-1.8 mS/cm
  Temp: 23.9-29.4 ^C

  Actual Properties
  pH:
  EC: 0.0-2.0 mS/cm
  Temp:

  disregard pag negative values
  14-16 light, 10-12 night, 14 light & 10 night nlng (hrs)
  
  printMessage numbers are just printing numbers not phase numbers

  to be reset:
  balance  -> for text
  phase    -> for order
  duration -> for 3 days 
*/

void setup()
{
  Serial.begin(9600);

  //DIMMER
  dimmer.begin(NORMAL_MODE, ON);
  
  brightness = map(0, 1, 100, 35, 70);
  dimmer.setPower(brightness);
  
  //RELAY
  for(i = 0; i < 8; i++)
    pinMode(RLY[i], OUTPUT);

  for(i = 0; i < 8; i++)
    digitalWrite(RLY[i], LOW);
      
  //EC
  ec.begin();

  //PH
  ph.begin();

  //TMP
  for(i = 0; i < 2; i++)
    tmp[i].begin();

  //FLT
  for(i = 0; i < 8; i++)
    pinMode(FLT[i], INPUT_PULLUP);

  //LCD
  for(i = 0; i < 3; i++)
  {
    lcd[i].begin(16,2); 
    lcd[i].init();     
    lcd[i].backlight(); 
    lcd[i].clear();  
  }

  //GSM 
  sim800l.begin(9600);
  
  //SD
  pinMode(CS, OUTPUT);
  SD.begin();
  
  //BUTTON
  pinMode(BTN, INPUT);

  //INITIALIZATION
  for(i = 0; i < 3; i++)
  {
    lcd[i].setCursor(2,0);
    lcd[i].print("Initializing");
    lcd[i].setCursor(5,1);  
    lcd[i].print("LCD #");
    lcd[i].setCursor(10,1);
    lcd[i].print(i + 1);
  }

  delay(10000);

  //STARTING
  for(i = 0; i < 3; i++)
    lcd[i].clear();
}

void loop()
{
  currentMillis = millis();

  tankStatus();

  //================================================= PHASE 1: GATHERING              
  if(phase == 0)
  {
    Serial.println("PHASE 1: GATHERING");

    if(Tank_Capacity[0] == LOW)
    {
      printMessage(0);
      count = 0;
    }

    else
    {
      printMessage(1);
      delay(3000);
      phase++;  
    }
  }

  //================================================= PHASE 2: FIRST TRANSFERENCE
  if(phase == 1)
  {
    Serial.println("PHASE 2: FIRST TRANSFERENCE");
    
    if(Tank_Capacity[1] == LOW)
    {
      printMessage(2);
      digitalWrite(RLY[0], HIGH);  
    }

    else
    {
      digitalWrite(RLY[0], LOW);
      phase++;
    }
  }

  //================================================= PHASE 3: TREATMENT
  if(phase == 2)
  {
    Serial.println("PHASE 3: TREATMENT");
    
    printMessage(3);
    
    if(count < period / 1000)
      balance = 0;
   /* else if(acidity > threshold[1])
      phase = 10;
    else if(acidity < threshold[0])
      phase = 10;
    else if(conductivity > threshold[3])
      phase = 10;
    else if(conductivity < threshold[2])
      phase = 11; */
    else
    {
      printMessage(6);
      saveMeasurement();

      printMessage(7);
      delay(3500);
      phase++;
    }
  }

  //================================================= PHASE 4: SECOND TRANSFERENCE
  if(phase == 3)
  {
    Serial.println("PHASE 4: SECOND TRANSFERENCE");
    
    if(Tank_Capacity[2] == LOW)
    {
      printMessage(8);
      digitalWrite(RLY[1], HIGH);    
    }

    else
    {
      digitalWrite(RLY[1], LOW);
      phase++;
    }
  }

  //================================================= PHASE 5: FIRST DISPOSAL
  if(phase == 4)
  {
    Serial.println("PHASE 5: FIRST DISPOSAL");
        
    if(FLT_Value[5] == LOW)
    {
      printMessage(10);  
      digitalWrite(RLY[2], HIGH);
    }

    else
    {
      digitalWrite(RLY[2], LOW);
      phase++;
    }
  }

  //================================================= PHASE 6: STABILIZED
  if(phase == 5)
  {
    Serial.println("PHASE 6: STABILIZED");
        
    printMessage(9);

    if(temperature < threshold[4])
      digitalWrite(RLY[7], HIGH);
    else
      digitalWrite(RLY[7], LOW);  

    if(duration >= 72)
      phase = 12;   

    if(digitalRead(BTN) == HIGH)
      phase++;
  }

  //================================================= PHASE 7: SECOND DISPOSAL
  if(phase == 6)
  {
    Serial.println("PHASE 7: SECOND DISPOSAL");
        
    if(FLT_Value[6] == LOW)
    {
      printMessage(10);
      digitalWrite(RLY[3], HIGH);   
    }

    else
    {
      digitalWrite(RLY[3], LOW);
      phase = 0;
    }
  }

  //================================================= SPECIAL PHASE 10: FAILURE DISPOSAL
  if(phase == 10)
  {
    Serial.println("SPECIAL PHASE 10: FAILURE DISPOSAL");
    
    if(FLT_Value[5] == LOW)
    {
      printMessage(10);
      digitalWrite(RLY[2], HIGH);
    }

    else
    {
      digitalWrite(RLY[2], LOW);
      phase = 0;
    }
  }

  //================================================= SPECIAL PHASE 11: FAILURE NOTIFICATION
  if(phase == 11)
  {
    Serial.println("SPECIAL PHASE 11: FAILURE NOTIFICATION");

    if(balance < 1)
    {
      printMessage(4);
      sendNotification(0);

      printMessage(5);
      delay(3500);
      balance = 1;
    }

    else
      phase = 2;
  }

  //================================================= SPECIAL PHASE 12: END NOTIFICATION
  if(phase == 12)
  {
    Serial.println("SPECIAL PHASE 12: END NOTIFICATION");

    if(balance < 2)
    {
      printMessage(4);
      sendNotification(1);

      printMessage(5);
      delay(3500);
      balance = 2, duration = 0;
    }

    else
      phase = 5;
  }
  
  //================================================= MAIN CYCLE
  if(currentMillis - prevMillis[0] >= second)
  {
    prevMillis[0] = currentMillis;

    if(phase == 2)
    {
      temperature = getTemperature(0);
      acidity = getAcidity();
      conductivity = getConductivity();
      
      waterTreatment();
    }

    if(phase == 5)
      temperature = getTemperature(1);  
  }

  //================================================= LIGHT CYCLE
  if(currentMillis - prevMillis[1] >= interval)
  {
    prevMillis[1] = currentMillis;

    state = !state;

    if(state == HIGH)
    {
      brightness = map(100, 1, 100, 35, 70);
      dimmer.setPower(brightness);
      
      interval = hour * 14;
      duration += 14;
    }

    else
    {
      brightness = map(0, 1, 100, 35, 70);
      dimmer.setPower(brightness);

      interval = hour * 10;
      duration += 10;
    }    
  }

  //================================================= CALIBRATION
  //ec.calibration(volt[0], conductivity);
  ph.calibration(volt[1], acidity);
}
