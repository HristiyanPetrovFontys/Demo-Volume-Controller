#include "Debounce.h" // Include Debounce header files
#include "MCP4011.h" // Include MCP4011 header files
#include "RotaryEncoder.h" // Include Rotary encoder header file
#include "IndicatorLEDs.h" // Include Indicator LEDs header file

// If code has to be made faster Serial.begin(9600) and all serial.prints can be removed.
// Those lines have no functional importance on the program.


void setup() 
{
  // Push buttons pin initialisation
  pinMode(boardTopPushButton, INPUT);
  pinMode(boardMidllePushButton, INPUT);
  pinMode(boardBottonPushBtton, INPUT);

  // Rotary encoder pin initialisation
  pinMode(rotaryEncoderButton, INPUT);
  pinMode(rotaryEncoderDT, INPUT);
  pinMode(rotaryEncoderCLK, INPUT);

  // Digital potentiometer pin initialisation
  pinMode(digitalPotentiometerUD, OUTPUT);
  pinMode(digitalPotentiometerCS, OUTPUT);

  // LED pin initialisation
  pinMode(blueRGBLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // MCP4011 digital potentiometer set up
  MCP4011SetUp();

  // Staff limit set to default (max)
  staffLimit = maxPotStep;

  Serial.begin(9600);  
}

void loop() 
{
  // Constants updating of the non-blocking LED blink
  updateBlink();

  // Top board push button handling
  if (debounceDelegate(1) && staffLimit < 63) // Is the button pressed and is the new staff limit possible
  {
    // Increment staff limit
    staffLimit++;

    // Log in serial monitor
    Serial.print("Staff limit set to: ");
    Serial.println(staffLimit);
  }

  // Middle board push button handling
  if(debounceDelegate(2) && staffLimit > 0) // Is the button pressed and is the new staff limit possible
  {
    // Decrement staff limit
    staffLimit--;

    // If the current wiper step bigger than the new limit
    if(digitalPotentiometerWiperStep > staffLimit)
    {
      // Set wiper step to the new limit
      MCP4011SetWiperStep(staffLimit);
    }

    // Log in serial monitor
    Serial.print("Staff limit set to: ");
    Serial.println(staffLimit);
  }

  // Bottom board push button handling
  if(debounceDelegate(3)) // Is the button pressed
  {
    // Is the system not already muted
    if(!isMuted)
    {
      // Save the current wiper position
      temporaryWiperStep = digitalPotentiometerWiperStep;

      // Set the wiper postion to 0(minPotStep)
      MCP4011SetWiperStep(minPotStep);

      // Flag the system as muted
      isMuted = true;

      // Turn on the Red indicator LED
      digitalWrite(redLED, HIGH);

      // Log in serial monitor
      Serial.print("System is muted.");
    }
    else // System is already muted
    {
      // Return the wiper position to the memorised value
      MCP4011SetWiperStep(temporaryWiperStep);

      // Flag the system as not muted
      isMuted = false;

      // Set the variable used to temporarily store the wiper step to default (0)
      temporaryWiperStep = 0;

      // Turn off the red indicator LED
      digitalWrite(redLED, LOW);

      // Loh in serial monitor
      Serial.print("System is unmuted.");
    }
  }
  
  /* logic is the same as bottomBoardPushButton possible duplication at runtime
  if(debounceDelegate(rotaryEncoderPushButton))
  {

  }
  */

  // Runtime variable used to store the rotation of the rotary encoder
  // +1 - CW
  // -1 - CCW
  //  0 - No rotation
  int detectedRotation = HandleRotaryEncoderRotationalInput();

  // If CW and the wanted wiper step is possible
  if(detectedRotation == 1 && digitalPotentiometerWiperStep < staffLimit)
  {
    // Single wiper step up
    MCP4011SetWiperStep(digitalPotentiometerWiperStep + 1);

    // Green LED blink
    blinkLED(greenLED);

    // Log in serial monitor
    Serial.print("Increment -> MCP4011 wiper position set to: ");
    Serial.println(digitalPotentiometerWiperStep);
  }
  
  // If CCW and the wanted wiper step is possible
  if(detectedRotation == -1 && digitalPotentiometerWiperStep > minPotStep)
  {
    // Single wiper step down
    MCP4011SetWiperStep(digitalPotentiometerWiperStep - 1);

    // Blue LED blink
    blinkLED(blueRGBLED);

    // Log in serial monitor
    Serial.print("Decrement -> MCP4011 wiper position set to: ");
    Serial.println(digitalPotentiometerWiperStep);
  }
}