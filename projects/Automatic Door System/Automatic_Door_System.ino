// Project: Automatic Door Opening and Closing System
// Hardware: Arduino UNO, Ultrasonic Sensor (HC-SR04), Servo Motor, 16x2 I2C LCD, Red & Green LEDs

#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library to control I2C LCD
#include <Servo.h>               // Library to control Servo motor

// Pin Definitions

const int trigPin = 9;       // Ultrasonic sensor trigger pin
const int echoPin = 10;      // Ultrasonic sensor echo pin
const int redLEDPin = 4;     // Red LED pin (Door Closed Indicator)
const int greenLEDPin = 5;   // Green LED pin (Door Open Indicator)
const int servoPin = 3;      // PWM pin connected to Servo motor signal


// Constants
const int distanceThreshold = 30;       // Threshold distance (cm) to open the door
const int openPosition = 90;            // Servo angle for door open
const int closePosition = 0;            // Servo angle for door closed
const unsigned long openDuration = 5000; // Duration to keep door open (milliseconds)

// Objects
LiquidCrystal_I2C lcd(0x27, 16, 2); // Create LCD object: address 0x27, 16x2 display
Servo myServo;                       // Create Servo object

// Variables
bool doorOpen = false;               // Tracks door state
unsigned long doorOpenTime = 0;      // Records the time when door was opened
// Setup function
void setup() {
  Serial.begin(9600);   // Initialize serial monitor for debugging

  lcd.init();            // Initialize LCD
  lcd.backlight();       // Turn on LCD backlight

  // Initialize Ultrasonic Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LED pins
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  // Initialize Servo motor
  myServo.attach(servoPin);       // Attach Servo to PWM pin
  myServo.write(closePosition);   // Start with door closed

  // Set initial LED state
  digitalWrite(redLEDPin, HIGH);   // Red LED on (door closed)
  digitalWrite(greenLEDPin, LOW);  // Green LED off
}

// Main Loop
void loop() {
  // Measure Distance using Ultrasonic Sensor
  
  long duration, distance;
  digitalWrite(trigPin, LOW);      // Clear trigger pin
  delayMicroseconds(2);            // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH);     // Send pulse
  delayMicroseconds(10);           // Pulse duration 10 microseconds
  digitalWrite(trigPin, LOW);      // Stop pulse
  duration = pulseIn(echoPin, HIGH); // Read the echo pulse duration
  distance = (duration / 2) / 29.1;  // Convert pulse duration to cm

  // Door Control Logic
  if (distance < distanceThreshold) {  // Person detected within threshold
    if (!doorOpen) {                   // Door is currently closed
      myServo.write(openPosition);     // Open the door
      digitalWrite(redLEDPin, LOW);   // Turn off Red LED
      digitalWrite(greenLEDPin, HIGH);// Turn on Green LED
      doorOpen = true;                 // Update door state
      doorOpenTime = millis();         // Record the time door was opened
    }
  } else {                             // No person detected
    // Check if door has been open for the specified duration
    if (doorOpen && millis() - doorOpenTime >= openDuration) {
      myServo.write(closePosition);    // Close the door
      digitalWrite(redLEDPin, HIGH);   // Turn on Red LED
      digitalWrite(greenLEDPin, LOW);  // Turn off Green LED
      doorOpen = false;                 // Update door state
    }
  }

  // Display Status on LCD
  lcd.clear(); // Clear previous LCD content

  if (doorOpen) {
    // Calculate remaining time before door closes
    unsigned long remainingTime = (openDuration - (millis() - doorOpenTime)) / 1000;
    lcd.setCursor(0, 0);
    lcd.print("Door : OPEN");          // Show door status
    lcd.setCursor(0, 1);
    lcd.print("Closing in: ");
    lcd.print(remainingTime);          // Show countdown
    lcd.print(" sec");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Door : CLOSED");        // Show door status
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);               // Show measured distance
    lcd.print(" cm");
  }

  // Delay 1 second before next measurement
  delay(1000);
}
