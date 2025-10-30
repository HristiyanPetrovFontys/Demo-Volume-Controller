// Bottom level header file, will not be included in other header files

#ifndef INDICATOR_LED_H // part of redefinition protection
#define INDICATOR_LED_H // part of redefinition protection

#include "Globals.h" // Top level header file inclusion

// Function used to get a LED blink
// Parameters:
// -> int ledPin - used to provide the index of the led pin that has to start blinking
// Return type: void -> doesn't return anything just code execution
void blinkLED(int ledPin);

// Function used to update a LED state (has to be constantly updated in main loop)
// Return type: void -> doesn't return anything just code execution
void updateBlink();

#endif // part of redefinition protection