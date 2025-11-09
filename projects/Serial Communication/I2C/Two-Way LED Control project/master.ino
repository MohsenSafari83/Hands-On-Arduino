/*
made on 9 november 2025(18 aban 1404)
by mohsen safari
https://github.com/MohsenSafari83
*/
#include <Wire.h>

// I2C Configuration
const int SLAVE_ADDRESS = 8;
// Pin Configuration
const int MASTER_POT_PIN = A1;  // Input: Potentiometer
const int MASTER_LED_PIN = 5 ;   // Output: LED (Must be a PWM pin for analogWrite)

void setup() {
  Wire.begin(); // Join the I2C bus as a Master
  pinMode(MASTER_LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("I2C Master Ready");
}

void loop() {
  //1. SEND DATA (Master Potentiometer -> Slave LED) 
  //Read from A1 & Save to value
  int Value = analogRead(MASTER_POT_PIN);
  // Map 0-1023 to 0-255 for PWM
  int brightness_To_Send = map(Value, 0, 1023, 0, 255);

  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write("Master value :  ");         // sends these bytes
  Wire.write(brightness_To_Send);  // sends one byte
  Wire.endTransmission(); // Stop transmitting

  // Serial.print("Master Sent to Slave: ");
  // Serial.println(brightnessToSend);


  // 2. REQUEST DATA (Slave Potentiometer -> Master LED) 
  int bytes_Received = Wire.requestFrom(SLAVE_ADDRESS, 1); // request 1 byte from slave device #8

  if (bytes_Received == 1) {
    int brightness_Received = Wire.read(); // receive a byte as character

    // Control Master's LED with data from Slave's Potentiometer
    analogWrite(MASTER_LED_PIN, brightness_Received);
    
    Serial.print("Master Received from Slave: ");
    Serial.println(brightness_Received);
  }

  delay(50); // Small pause for stability
}