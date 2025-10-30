#include "RotaryEncoder.h"

int currentStateCLK;
int lastStateCLK;

int HandleRotaryEncoderRotationalInput()
{
    // Read the current state of CLK
    currentStateCLK = digitalRead(rotaryEncoderCLK);
    
    // If last and current state of CLK are different, then pulse occurred
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1) 
    {
        // Remember last CLK state
        lastStateCLK = currentStateCLK;
        
        // If the DT state is different than the CLK state then
        if (digitalRead(rotaryEncoderDT) != currentStateCLK) 
        {
            // Encoder is rotating CCW
            return -1;
        }
        else 
        {
            // Encoder is rotating CW
            return 1;
        }
    }
    
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
    return 0; // No change
}