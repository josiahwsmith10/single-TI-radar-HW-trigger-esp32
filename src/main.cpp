/* Dual Radar Synchronizer

   Author:  Josiah W. Smith
   Advisor: Murat Torlak

   Notes:
    - Sends a HW trigger to the radar when the string: "r" is sent from the PC over serial.    

   Rev1 - 12/10/2021

   Changelog:
   - Rev1: built but not tested...
*/

#include <Arduino.h>
#include <stdio.h>
#include <string.h>

// Defs
#define RADAR_TRIGGER_PIN 13  // Pin to send radar HW triggers

// Globals
String incomingMessage = "";  // Incoming message Arduino String
char incomingStr[64];         // Incoming message C-string

void sendHWTrigger()
{
  // Send HW trigger to radar 
  // This is the high priority task

  // Send the trigger
  GPIO.out_w1ts = ((uint32_t)1 << RADAR_TRIGGER_PIN);

  // Waits ~125 ns
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  
  GPIO.out_w1tc = ((uint32_t)1 << RADAR_TRIGGER_PIN);
}

int serialParse(char incomingStr[])
{
  // Parse the C-string and execute the command

  // Determine the command type and execute
  if (strcmp(incomingStr, "r") == 0)
  {
    // Received "send HW trigger"
    sendHWTrigger();
  }
}

void setup()
{
  Serial.begin(115200);

  setCpuFrequencyMhz(240);

  pinMode(RADAR_TRIGGER_PIN, OUTPUT);
}

void loop()
{
  // Check if a serial command has been sent
  if (Serial.available() > 0)
  {
    // Read the incoming line
    incomingMessage = Serial.readString();
    incomingMessage.replace("\n", "");
    incomingMessage.toCharArray(incomingStr, sizeof(incomingStr));

    // Parse the input and execute the command
    serialParse(incomingStr);
  }

  // Wait one second between 
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  yield();
}


