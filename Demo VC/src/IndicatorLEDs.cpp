#include "IndicatorLEDs.h"

// Duration of the LED blink is milliseconds
const long blinkDuration = 200;

// Timestamp when the current blink started
unsigned long blinkStartTime = 0;

// Pin number of the currently blinking LED (-1 if no LED is blinking)
int blinkingPin = -1;

// Turns on the specified LED and starts tracking its blink duration.
// If another LED is currently blinking, it will be turned off first
// to ensure only one LED blinks at a time.
void blinkLED(int ledPin)
{
    // Turn off the previously blinking LED first to prevent multiple LEDs being on
    if (blinkingPin != -1) 
    {
      digitalWrite(blinkingPin, LOW);
    }
    
    // Turn on the new LED and start tracking the blink
    digitalWrite(ledPin, HIGH);
    blinkStartTime = millis();
    blinkingPin = ledPin;
}

// Checks if the current blink duration has elapsed and turns off the LED
// if necessary. Has called repeatedly in the main loop to ensure LEDs
// are turned off after the blink duration expires.
// 
// Non-blocking implementation that doesn't use delay().

void updateBlink() 
{
  // Check if an LED is blinking and if the blink duration has elapsed
  if (blinkingPin != -1 && (millis() - blinkStartTime >= blinkDuration)) 
  {
    // Turn off the LED and clear the blinking state
    digitalWrite(blinkingPin, LOW);
    blinkingPin = -1;
  }
}