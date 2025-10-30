// Bottom level header file, will not be included in other header files

#ifndef DEBOUNCE_H // part of redefinition protection
#define DEBOUNCE_H // part of redefinition protection

#include "Globals.h" // Top level header file inclusion

// Function that deals with matching the program set button number with its corresponding debouncedRead
// Parameters
// -> int button - the program set number for the button that has to be checked
// Return type: bool - If the button is pressed (true) or not (false)
bool debounceDelegate(int button);

// Template debounced read function for active-low buttons
// Parameters
// -> int pin - the Arduino pin to which the button is wired
// -> int &lastButtonState - reference to an int that stores the lastButtonState
// of the particular button which is being checked
// -> unsigned long &lastDebounceTime - reference to an unsigned long that stores the lastDebounceTime
// of the particular button which is being checked
// -> int &buttonState - reference to an int that stores the buttonState
// of the particular button which is being checked
// Return type: bool - If the button is pressed (true) or not (false)
bool debouncedRead(int pin, int &lastButtonState, unsigned long &lastDebounceTime, int &buttonState);


#endif // part of redefinition protection