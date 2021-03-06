/*
 ____/'¬_         /\
{-_-_ ^  \_______//
     /           \
     \ _  _____  /
     || ||     |||
     || ||     |||  
BadTail Projects ALL RIGHTS GRANTED this is OPEN SOURCE and 
without any Implied or Otherwise "Gaurantees" of a 
Particular Part in Whole or Function
and free to use in any or all parts.........
Libraries are part of Standard GNU License........
Rod Con ..... The Road to Contentment.............

This is a just one Reliable approach to IOT Logging, put it on the SDCARD then
PUSH The Data to the Remote Server Seperately allowing Local Analyssis and backup.


MQ-2 Methane Sensor Logging

*/

#include <SD.h>


const int chipSelect = 4;

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int ledPin = 13;                 // LED connected to digital pin 13

int sensorValue = 0;        // value read from the sensor



void setup() {
  Serial.begin(9600); 
  Serial.println("MQ-2 Digital GAS Sensor Logging Starting....");
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  return;
  }
  Serial.println("card initialized.");
delay(2000); 
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // determine alarm status
  if (sensorValue >= 750)
  {
    digitalWrite(ledPin, HIGH);   // sets the LED on
  }
  else
  {
  digitalWrite(ledPin, LOW);    // sets the LED off
  }

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);  
        File dataFile1 = SD.open("gaslog.CSV", FILE_WRITE);
    if (dataFile1) {
      dataFile1.print("Sensor Value =  ");
      dataFile1.print(sensorValue);
      dataFile1.print(" Alarm Status =  ");
      dataFile1.println(" Disabled ");
      dataFile1.close();
    delay(5000);// Pause here to ensure when power off FILE CLOSED!!
      }         // Wait for Pin 13 LED (SPI Activity) to Flash before power off!
    else {
      Serial.println("error opening gaslog.CSV");
    }  

  // wait 10000 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading and limit file size:
  delay(10000);
}

