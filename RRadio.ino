#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TEA5767N.h>

TEA5767N radio = TEA5767N();
LiquidCrystal_I2C lcd(0x27,20,4);

int ledOn = 2;
int analogPin = 7;

float frequency = 0;
float previousFrequency = 0;
int frequencyInt = 0;

int val = 0; 
int signalStrength = 0;

char line0[16]; 
char line1[16];

void setup() {

  lcd.init();     
  lcd.backlight();
  lcd.setCursor(3,0);
	lcd.print("Rosa Radio");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledOn,OUTPUT);
  digitalWrite(ledOn,HIGH);
  pinMode(analogPin,INPUT);

  radio.setMonoReception();
  radio.setStereoNoiseCancellingOn();

  Serial.begin(9600);
}


void loop() {
 
  
  val = analogRead(analogPin); 

  

  frequencyInt = map(val, 3, 1022, 8700, 10700); //Analog value to frequency from 87.0 MHz to 107.00 MHz 
  float frequency = frequencyInt/100.0f;

  if(frequency - previousFrequency >= 0.1f || previousFrequency - frequency >= 0.1f)
  {

    radio.selectFrequency(frequency);
    previousFrequency = frequency;    
  }



  printFrequency(previousFrequency);
  printSignalStrength();
  delay(100);                   
}

void printFrequency(float frequency) {
  String frequencyString = String(frequency,1);
  lcd.setCursor(0,1);
  lcd.print("             ");
  lcd.setCursor(0,1);
  lcd.print("FM: " + frequencyString+"MHz");
  Serial.println("FM: " + frequencyString+"MHz");
  
}



void printSignalStrength()
{
  signalStrength = radio.getSignalLevel();
  String signalStrenthString = String(signalStrength);
  lcd.setCursor(13,1);
  lcd.print("   ");
  lcd.setCursor(13,1);
  lcd.print("s");
  lcd.print(signalStrenthString);
  Serial.println(signalStrenthString);
}