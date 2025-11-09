/*
made on 9 november 2025(18 aban 1404)
by mohsen safari
https://github.com/MohsenSafari83
*/

#include <Wire.h>

// I2C Configuration
const int SLAVE_ADDRESS = 8;
// Pin Configuration
const int SLAVE_POT_PIN = A0;  // Input: Potentiometer
const int SLAVE_LED_PIN = 6;   // Output: LED (Must be a PWM pin for analogWrite)

// Global variable to hold the brightness value received from the Master
volatile int master_Brightness = 0; 

void setup() {
  // Join I2C bus as a Slave with address 8
  Wire.begin(SLAVE_ADDRESS); 
  
  // Define handler functions
  Wire.onReceive(receiveEvent); // Called when Master sends data
  Wire.onRequest(requestEvent); // Called when Master requests data

  pinMode(SLAVE_LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("I2C Slave Ready");
}

void loop() {
  // Control Slave's LED using the brightness value received from the Master
  analogWrite(SLAVE_LED_PIN, master_Brightness);

  // Serial.print("Slave LED Brightness: ");
  // Serial.println(masterBrightness);

  delay(50); 
}

// function that executes whenever data is received from master (Wire.beginTransmission)
void receiveEvent(int num_Bytes) {
  // We expect only 1 byte (the brightness value)
  if (num_Bytes == 1) {
    master_Brightness = Wire.read(); // Read the brightness value
  }
}

// function that executes whenever data is requested by master (Wire.requestFrom)
void requestEvent() {
  // Read Slave's potentiometer and map it to PWM range
  int Value = analogRead(SLAVE_POT_PIN);
  int brightness_To_Master = map(potValue, 0, 1023, 0, 255);
  
  // Send the Slave's brightness value back to the Master
  Wire.write(brightness_To_Master); 
}