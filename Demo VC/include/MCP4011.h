// Bottom level header file, will not be included in other header files

#ifndef MCP4011_H // part of redefinition protection
#define MCP4011_H // part of redefinition protection

#include "Globals.h" // Top level header file inclusion

// Function that deals with a single increment sequence of the wiper of the MCP4011 chip
// Return type: void -> doesn't return anything just code execution
void MCP4011SingleIncrementSequence();

// Function that deals with a single decrement sequence of the wiper of the MCP4011 chip
// Return type: void -> doesn't return anything just code execution
void MCP4011SingleDecrementSequence();

// Function that deals with a multiple steps up or down
// Parameters:
// -> int wantedStep - used to pass the new position to which wiper should go
// Return type: void -> doesn't return anything just code execution
void MCP4011SetWiperStep(int wantedStep);

// Function that deals with the set up of the MCP4011 chip
// Return type: void -> doesn't return anything just code execution
void MCP4011SetUp();

#endif // part of redefinition protection