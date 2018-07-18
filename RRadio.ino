#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>
#include <LiquidCrystal.h>

TEA5767 radio;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  radio.init();
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1000);                       
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);                       
}
