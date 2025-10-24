// Pin Definitions
#define LED_RED    2   // Digital pin controlling Red LED
#define LED_YELLOW 4   // Digital pin controlling Yellow LED
#define LED_GREEN  6   // PWM-enabled pin controlling Green LED brightness
#define POT_PIN   A0   // Analog input pin connected to Potentiometer
#define BUTTON_PIN 7   // Digital pin connected to Push Button (with INPUT_PULLUP)


//Global Variables
String command = "";        // Stores the received Serial command text
bool ledRedState = false;   // Stores ON/OFF state of Red LED to be toggled
bool ledYellowState = false;// Stores ON/OFF state of Yellow LED to be toggled
int value = 0;              // Stores Green LED brightness from Serial command (0-255)
int potValue = 0;           // Stores raw analog reading from the potentiometer (0-1023)
int brightness = 0;         // Stores mapped brightness value (0-255) for automatic control


// Converts String commands into numerical codes for switch-case
int get_command_code(String cmd) {
  cmd.trim();        // Remove extra spaces & newline characters
  cmd.toLowerCase(); // Convert to lowercase → case-insensitive command
  if (cmd == "led red on") return 1;
  else if (cmd == "led red off") return 2;
  else if (cmd == "led yellow on") return 3;
  else if (cmd == "led yellow off") return 4;
  else if (cmd.startsWith("led green brightness:")) return 5;
  else if (cmd == "read pot") return 6;
  else return 0; // Unknown command
}


void setup() {
  Serial.begin(9600);

  // Set LED pins as output
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Button uses Pull-Up → Not pressed = HIGH , Pressed = LOW
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Interactive LED Control with Potentiometer");
  Serial.println("Commands:");
  Serial.println(" - led red on/off");
  Serial.println(" - led yellow on/off");
  Serial.println(" - led green brightness:<0-255>");
  Serial.println(" - read pot");
}


void loop() {

  //Button Handling (Toggle LEDs)
  if (digitalRead(BUTTON_PIN) == LOW) {
    ledRedState = !ledRedState;
    ledYellowState = !ledYellowState;

    digitalWrite(LED_RED, ledRedState ? HIGH : LOW);
    digitalWrite(LED_YELLOW, ledYellowState ? HIGH : LOW);

    Serial.println("Button pressed: toggled red and yellow LEDs");
    delay(300); // Simple debounce delay
  }


  // Serial Command Handling
  if (Serial.available()) {
    command = Serial.readString();
    command.trim();

    int cmdCode =get_command_code(command);

    switch (cmdCode) {

      case 1: //  Red LED ON
        digitalWrite(LED_RED, HIGH);
        ledRedState = true;
        Serial.println("Red LED turned ON");
        break;

      case 2: //  Red LED OFF
        digitalWrite(LED_RED, LOW);
        ledRedState = false;
        Serial.println("Red LED turned OFF");
        break;

      case 3: //  Yellow LED ON
        digitalWrite(LED_YELLOW, HIGH);
        ledYellowState = true;
        Serial.println("Yellow LED turned ON");
        break;

      case 4: //  Yellow LED OFF
        digitalWrite(LED_YELLOW, LOW);
        ledYellowState = false;
        Serial.println("Yellow LED turned OFF");
        break;

      case 5: //  Green LED Brightness Control via Serial
        value = command.substring(21).toInt();
        // substring(21): extract only the number after "led green brightness:"
        // toInt(): convert the extracted substring to integer
        value = constrain(value, 0, 255);
        // constrain(): ensure value stays within valid PWM range (0-255)
        analogWrite(LED_GREEN, value);

        Serial.print("Green LED brightness set to: ");
        Serial.println(value);
        break;

      case 6: //  Auto Brightness Control using Potentiometer
        potValue = analogRead(POT_PIN); // ADC value (0-1023)
        Serial.print("Potentiometer Value: ");
        Serial.println(potValue);

        brightness = map(potValue, 0, 1023, 0, 255);
        // map(): convert ADC range to PWM brightness (0-255)
        analogWrite(LED_GREEN, brightness);

        Serial.print("Green LED brightness (auto) set to: ");
        Serial.println(brightness);
        break;

      default:
        Serial.println("Unknown command!");
        break;
    }
  }
}
