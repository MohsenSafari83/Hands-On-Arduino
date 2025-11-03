// IR Sender Project: Transmits the character 'A' using the NEC protocol.
//
// HARDWARE SETUP:
// - Arduino Uno/Nano
// - IR LED (IR333-A) connected to Digital Pin 3 via a 270-330 Ohm resistor.
//
// LIBRARY REQUIRED:
// - Arduino-IRremote (Ensure version 3.x or later is installed)

#include <IRremote.h> 

// Define the digital pin connected to the IR LED's current-limiting resistor.
// Pin 3 is recommended as it supports the 38kHz carrier frequency via Timer 2.
#define IR_SEND_PIN 3 

void setup() {
  // Initialize Serial communication for debugging and status messages.
  Serial.begin(9600);
  
  // Initialize the IR sender component.
  // IRremote automatically sets up Pin 3 to generate the 38kHz carrier signal.
  // ENABLE_LED_FEEDBACK causes the built-in LED (Pin 13) to blink when transmitting.
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); 
  
  Serial.println(F("IR Sender Initialized ."));
  Serial.print(F("IR LED connected to Pin: "));
  Serial.println(IR_SEND_PIN);
  Serial.println(F("Status: Ready to send data."));
}

void loop() {
  // DATA PAYLOAD: We use the ASCII value of the character 'A' as the Command data.
  // 'A' in ASCII is 65 (decimal) or 0x41 (hexadecimal).
  unsigned long dataToSend = 'A'; 

  // --- NEC PROTOCOL TRANSMISSION ---
  // IrSender.sendNEC(Address, Command, Number_of_Bits);
  // Address: 0x00 (Standard, arbitrary address for our link)
  // Command: dataToSend (0x41)
  // Number_of_Bits: 32 (Standard NEC frame length)
  
  IrSender.sendNEC(0x00, dataToSend, 32); 

  Serial.print(F("Sending ASCII: "));
  Serial.println((char)dataToSend);
  Serial.print(F("  (HEX Command Value: 0x"));
  Serial.print(dataToSend, HEX);
  Serial.println(F(")"));
  
  // Wait 1 second before sending the next command.
  delay(1000); 
}