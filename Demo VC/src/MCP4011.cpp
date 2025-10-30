#include "MCP4011.h"

// Function that handles the increment sequence for a single wiper step up
void MCP4011SingleIncrementSequence()
{
    // First set Up/Down before HIGH ChipSelect is set to LOW to avoid an unwanted steps
    digitalWrite(digitalPotentiometerUD, HIGH);

    // Set ChipSelect to LOW to make the increment sequence possible
    digitalWrite(digitalPotentiometerCS, LOW);

    // Set Up/Down to LOW (falling edge part of the sequence)
    digitalWrite(digitalPotentiometerUD, LOW);

    // Delay per datasheet
    delay(1);

    // Set Up/Down to HIGH (rising edge of the sequence)
    digitalWrite(digitalPotentiometerUD, HIGH);

    // Set ChipSelect to HIGH to complete the sequence
    digitalWrite(digitalPotentiometerCS, HIGH);

    // Wiper step tracking
    digitalPotentiometerWiperStep++;

    Serial.println("Single step up done");
}

// Function that handles the decrement sequence for a single wiper step down
void MCP4011SingleDecrementSequence()
{
    // First set Up/Down to LOW before ChipSelect is set to LOW to avoid an unwanted steps
    digitalWrite(digitalPotentiometerUD, LOW);

    // Set ChipSelect to LOW to make the decrement sequence possible
    digitalWrite(digitalPotentiometerCS, LOW);

    // Set Up/Down to HIGH (raising edge of the sequence)
    digitalWrite(digitalPotentiometerUD, HIGH);

    // Delay per datasheet
    delay(1);

    // Set Up/Down to LOW (falling edge of the sequence)
    digitalWrite(digitalPotentiometerUD, LOW);

    // Set ChipSelect to HIGH to complete the sequence
    digitalWrite(digitalPotentiometerCS, HIGH);

    // Wiper step tracking
    digitalPotentiometerWiperStep--;

    Serial.println("Single step up done");
}

// Function that handles multiple wiper step changes
void MCP4011SetWiperStep(int wantedStep)
{
    // Constrain the wantedStep between min and max
    wantedStep = constrain(wantedStep, minPotStep, maxPotStep);

    // Find the difference between the current wiper position and the wanted wiper postion
    int stepDifference = wantedStep - digitalPotentiometerWiperStep;

    // If the the difference is positive
    if(stepDifference > 0)
    {
        // Single wiper step ups until the wanted position is reached
        for(int i = 0; i < stepDifference; i++)
        {
            MCP4011SingleIncrementSequence();
        }
    }
    else if(stepDifference < 0) // If the difference is negative
    {
        // Single wiper step downs until the wanted position is reached
        // -stepDifference to ensure that the for loop executes correctly
        for(int i = 0; i < -stepDifference; i++)
        {
            MCP4011SingleDecrementSequence();
        }
    }
}

// Function that handles the set up of the digital potentiometer
void MCP4011SetUp()
{
    // No matter what the previous wiper position is
    // The function does 64 steps, ensuring that the start wiper position is always 64
    // Allows accurate wiper step tracking 
    for(int i = 0; i <= maxPotStep; i++)
    {
        MCP4011SingleIncrementSequence();
    }
}