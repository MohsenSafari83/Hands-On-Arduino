// Traffic Light Project using Arduino UNO
// LEDs connected to digital pins 12 (Red), 8 (Yellow), and 5 (Green)

const int red = 12;     // Red LED connected to pin 12
const int yellow = 8;   // Yellow LED connected to pin 8
const int green = 5;    // Green LED connected to pin 5

void setup() {
  // Set LED pins as output
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  // Make sure all LEDs are off at the start
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}

void loop() {
  // Green light ON for 5 seconds
  digitalWrite(green, HIGH);
  delay(5000);
  digitalWrite(green, LOW);
  delay(1000);

  // Yellow light ON for 2 seconds
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(yellow, LOW);

  // Red light ON for 5 seconds
  digitalWrite(red, HIGH);
  delay(5000);
  digitalWrite(red, LOW);

  // Yellow light again for 2 seconds before turning green
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(yellow, LOW);
}
