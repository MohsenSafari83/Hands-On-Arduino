// IR Receiver Project: Decodes the NEC protocol and displays the received character.
//
// HARDWARE SETUP:
// - Arduino Uno/Nano
// - IR Receiver Module (VS838) connected to Digital Pin 2.
//   - VS838 VCC -> Arduino 5V
//   - VS838 GND -> Arduino GND
//   - VS838 OUT -> Digital Pin 2
//
// LIBRARY REQUIRED:
// - Arduino-IRremote (Ensure version 3.x or later is installed)

#include <IRremote.h> 

// Define the digital pin connected to the VS838 OUT pin.
#define IR_RECEIVE_PIN 2

void setup() {
  // Initialize Serial communication.
  Serial.begin(9600);
  
  // Initialize the IR receiver component.
  // The library automatically uses Pin 2 as an external interrupt source (if possible).
  // ENABLE_LED_FEEDBACK causes the built-in LED (Pin 13) to blink when a signal is received.
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  
  Serial.println(F("IR Receiver Initialized ---"));
  Serial.print(F("IR Receiver connected to Pin: "));
  Serial.println(IR_RECEIVE_PIN);
  Serial.println(F("Waiting for IR signals..."));
}

void loop() {
  // Check if a signal was received AND successfully decoded.
  if (IrReceiver.decode()) { 
    
    Serial.println(F("----------------------------------------"));
    
    // 1. PROTOCOL CHECK: Ensure the received signal matches the expected NEC protocol.
    if (IrReceiver.decodedIRData.protocol == NEC) { 
      
      // The command byte (our character) is stored in the 'command' field.
      uint16_t command = IrReceiver.decodedIRData.command; 
      char receivedChar = (char)command;
      
      Serial.print(F("  -> Protocol: NEC  |  Received HEX Command: 0x"));
      Serial.println(command, HEX);
      
      // 2. DATA EXTRACTION: Check if the command is a printable ASCII character.
      if (command >= 32 && command <= 126) {
          Serial.print(F("  ==> Received Character: "));
          Serial.println(receivedChar); 
      } else {
          Serial.println(F("  ==> Non-printable character received."));
      }
      
    } else {
      // Handle cases where an unknown or unwanted IR signal is received.
      Serial.print(F("  -> Received Other Protocol (Type: "));
      Serial.print(IrReceiver.decodedIRData.protocol);
      Serial.println(F(")"));
    }
    
    // 3. RESUME RECEIVING: Prepare the receiver to look for the next signal.
    IrReceiver.resume(); 
    Serial.println(F("----------------------------------------"));
  }
}