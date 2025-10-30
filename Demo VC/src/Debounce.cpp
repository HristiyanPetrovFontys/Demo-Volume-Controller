#include "Debounce.h"

// delay in millisecons used to determine a stable putton press state
const unsigned long debounceDelay = 50; //ms

// lastDebounceTime variables for all the buttons
unsigned long lastStaffVolumeUpDebounceTime = 0,
              lastStaffVolumeDownDebounceTime = 0,
              lastStaffMuteDebounceTime = 0,
              lastUserMuteDebounceTime = 0;

// currentState variables for all the buttons
int currentStaffVolumeUpState = HIGH,
    currentStaffVolumeDownState = HIGH,
    currentStaffMuteState = HIGH,
    currentUserMuteState = HIGH;

// lastState variables for all the buttons
int lastStaffVolumeUpState = HIGH,
    lastStaffVolumeDownState = HIGH,
    lastStaffMuteState = HIGH,
    lastUserMuteState = HIGH;

// Template button debounce function which works with multiple of variable via reference passing
// allowing the function to directly change the value of each of the refferenced variables
bool debouncedRead(int pin, int &lastButtonState, unsigned long &lastDebounceTime, int &buttonState)
{
    // Read the current state of the button
    int reading = digitalRead(pin);
  
    // If the reading has changed (due to noise or actual press)
    if (reading != lastButtonState) 
    {
        // Reset the timer
        lastDebounceTime = millis();
    }
  
    // If enough time has passed since the last reading change
    if ((millis() - lastDebounceTime) > debounceDelay) 
    {
        // If the reading has been stable and is different from the current state
        if (reading != buttonState) 
        {
            buttonState = reading;
      
            // Detect a single button *press* event 
            if (buttonState == LOW) 
            {
                lastButtonState = reading;

                // Button press detected
                return true;
            }
        }
    }
  
    // Update the last button state for the next iteration
    lastButtonState = reading;

    // No button press detected
    return false;
}


// Routes button debouncing to the appropriate button handler based on the
// button identifier. Each button has its own state variables to track
// debouncing independently.
bool debounceDelegate(int button)
{
    // Function runtime variable defined at the start of the function
    // Memory used gets released at the end of function execution
    // Used to give a holder for the debounced read output
    bool pressed = false;
    
    switch (button){
        case topBoardPushButton:
            // Handle top board push button (staff volume up)
            pressed = debouncedRead(boardTopPushButton, lastStaffVolumeUpState, lastStaffVolumeUpDebounceTime, currentStaffVolumeUpState);
            if (pressed) 
            {
                Serial.println("Staff volume up button was pressed.");
            }
            return pressed;
            break;
        case middleBoardPushButton:
            // Handle middle board push button (staff volume down)
            pressed = debouncedRead(boardMidllePushButton, lastStaffVolumeDownState, lastStaffVolumeDownDebounceTime, currentStaffVolumeDownState);
            if (pressed) 
            {
                Serial.println("Staff volume down button was pressed.");
            }
            return pressed;
            break;
        case bottomBoardPushButton:
            // Handle bottom board push button (staff mute)
            pressed = debouncedRead(boardBottonPushBtton, lastStaffMuteState, lastStaffMuteDebounceTime, currentStaffMuteState);
            if (pressed) 
            {
                Serial.println("Staff mute button was pressed.");
            }
            return pressed;
            break;
        case rotaryEncoderPushButton:
            // Handle rotary encoder push button (user mute)
            pressed = debouncedRead(rotaryEncoderButton, lastUserMuteState, lastUserMuteDebounceTime, currentUserMuteState);
            if (pressed) 
            {
                Serial.println("User mute button was pressed.");
            }
            return pressed;
            break;
        default:
            // Invalid button identifier
            return false;
            break;
    }
}

