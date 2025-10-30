// Top level head files, will be included in other header files

#ifndef GLOBALS_H // part of redefinition protection
#define GLOBALS_H // part of redefinition protection

// Top level arduino library inclusion,
// no need to include in other files which already have the top level header file
#include <Arduino.h> 

// ========== Global variables ==========

// ========== Pin names ==========

// Push button pins
const int boardTopPushButton = 2;
const int boardMidllePushButton = 3;
const int boardBottonPushBtton = 4;

// Rotary encoder pins
const int rotaryEncoderButton = 6;
const int rotaryEncoderDT = 7;
const int rotaryEncoderCLK = 8;

// Digital potentiometer pins
const int digitalPotentiometerUD = 9;
const int digitalPotentiometerCS = 10;

// LED pins
const int blueRGBLED = 11;
const int redLED = 12;
const int greenLED = 13;


// ========== Constants ==========

// Push asignment for debounce
const int topBoardPushButton = 1;
const int middleBoardPushButton = 2;
const int bottomBoardPushButton = 3;
const int rotaryEncoderPushButton = 4;

// Absolute wiper step limits
const int minPotStep = 0;
const int maxPotStep = 63;

// ========== Non-Constants declaration ==========

// variable for tracking the digital potentiometer wiper step (volume)
extern int digitalPotentiometerWiperStep;

// variable for setting the staffLimit
extern int staffLimit;

// variable to signal if the system is muted
extern bool isMuted;

// variavle for temporarily saving the current wiper step
extern int temporaryWiperStep;


#endif // part of redefinition protection