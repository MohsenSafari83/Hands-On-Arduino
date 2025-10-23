// ------------------ LM35 + LED + Buzzer + Serial Monitor ------------------
// This project reads temperature from an LM35 sensor, lights LEDs based on
// the temperature range, and activates a buzzer if temperature exceeds 40°C.

#define LM35_PIN A0
#define LED_RED 2
#define LED_YELLOW 4
#define LED_BLUE 7
#define BUZZER_PIN 8

float tempC;

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("=== LM35 Temperature & Alarm Monitor ===");
  delay(1000);
}

void loop() {
  // Read analog value from LM35
  int sensorValue = analogRead(LM35_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  tempC = voltage * 100.0; // Convert to Celsius (10mV per °C)

  // Turn off all LEDs and buzzer before updating state
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  String status = "";

  // Decide which LED to turn on and whether to trigger buzzer
  if (tempC < 20.0) {
    digitalWrite(LED_BLUE, HIGH);
    status = "🧊 COLD";
  } 
  else if (tempC >= 20.0 && tempC <= 30.0) {
    digitalWrite(LED_YELLOW, HIGH);
    status = "🌤️ NORMAL";
  } 
  else if (tempC > 30.0 && tempC <= 40.0) {
    digitalWrite(LED_RED, HIGH);
    status = "🔥 HOT";
  } 
  else { // temperature > 40°C
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER_PIN, 1000); // 1000 Hz tone
  	delay(500);
  	noTone(BUZZER_PIN);
 	status = "🚨 EXTREME HEAT - SHORT ALARM!";
  }

  // Display readings on Serial Monitor
  Serial.println("---------------------------------");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");
  Serial.print("Status: ");
  Serial.println(status);
  Serial.println("---------------------------------\n");

  delay(2000); // Read every 2 seconds
}
