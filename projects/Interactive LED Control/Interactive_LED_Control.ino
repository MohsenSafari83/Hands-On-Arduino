// Pin Definitions
#define LED_RED    2
#define LED_YELLOW 4
#define LED_GREEN  6 // PWM pin
#define POT_PIN   A0  // Potentiometer replacing LDR
#define BUTTON_PIN 7

// Variables
String command = "";
bool ledRedState = false;
bool ledYellowState = false;

// Function to map command string to an integer code
int getCommandCode(String cmd) {
  cmd.trim();  // remove newline and spaces
  cmd.toLowerCase(); // convert to lowercase for case-insensitive comparison
  if (cmd == "led red on") return 1;
  else if (cmd == "led red off") return 2;
  else if (cmd == "led yellow on") return 3;
  else if (cmd == "led yellow off") return 4;
  else if (cmd.startsWith("led green brightness:")) return 5;
  else if (cmd == "read pot") return 6;
  else return 0; // unknown command
}

void setup() {
  Serial.begin(9600);

  // Setup LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Setup button
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button connects to GND when pressed

  Serial.println("Interactive LED Control with Potentiometer");
  Serial.println("Commands: led red on/off, led yellow on/off, led green brightness:0-255, read pot");
}

void loop() {
  // Read button
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button pressed -> toggle red and yellow LEDs
    ledRedState = !ledRedState;
    ledYellowState = !ledYellowState;
    digitalWrite(LED_RED, ledRedState ? HIGH : LOW);   // Turn red LED ON/OFF based on state
    digitalWrite(LED_YELLOW, ledYellowState ? HIGH : LOW); // Turn yellow LED ON/OFF based on state
    Serial.println("Button pressed: toggled red and yellow LEDs");
    delay(300); // simple debounce
  }

  // Read Serial input
  if (Serial.available()) {
    command = Serial.readString();
    command.trim(); // remove newline and spaces

    int cmdCode = getCommandCode(command); // get numeric code for the command

    switch(cmdCode) {
      case 1: // led red on
        digitalWrite(LED_RED, HIGH);
        ledRedState = true;
        Serial.println("Red LED turned ON");
        break;
      case 2: // led red off
        digitalWrite(LED_RED, LOW);
        ledRedState = false;
        Serial.println("Red LED turned OFF");
        break;
      case 3: // led yellow on
        digitalWrite(LED_YELLOW, HIGH);
        ledYellowState = true;
        Serial.println("Yellow LED turned ON");
        break;
      case 4: // led yellow off
        digitalWrite(LED_YELLOW, LOW);
        ledYellowState = false;
        Serial.println("Yellow LED turned OFF");
        break;
      case 5: // led green brightness:<value>
        int value = command.substring(21).toInt();  
        // substring(21): extract the numeric part after "led green brightness:"
        // toInt(): convert the extracted substring to an integer and store it in 'value'
        value = constrain(value, 0, 255); 
        // constrain(): limit 'value' to the PWM range (0-255) to avoid invalid values
        analogWrite(LED_GREEN, value);
        Serial.print("Green LED brightness set to ");
        Serial.println(value);
        break;
      case 6: // read pot
        // Read the value from the potentiometer (analog input A0)
        int potValue = analogRead(POT_PIN);  // returns 0-1023

        // Print the raw potentiometer value to the Serial Monitor
        Serial.print("Potentiometer Value: ");
        Serial.println(potValue);

        // Map the potentiometer value from 0-1023 to 0-255 for PWM
        int brightness = map(potValue, 0, 1023, 0, 255);

        // Set the green LED brightness using PWM based on mapped value
        analogWrite(LED_GREEN, brightness);

        // Print the mapped LED brightness value to the Serial Monitor
        Serial.print("Green LED brightness (auto) set to: ");
        Serial.println(brightness);
        break;
      default:
        Serial.println("Unknown command!");
        break;
    }
  }
}
