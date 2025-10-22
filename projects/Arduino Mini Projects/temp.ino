// --- LM35 Temperature Sensor Reading with Arduino ---
// Reads temperature from an LM35 sensor and displays it in °C
// Author: [Your Name]
// Date: [optional]

// Define the analog input pin connected to the LM35 sensor
const int tempPin = A5;

// Variables to store readings
float sensorValue = 0.0;   // Raw analog value
float voltage = 0.0;       // Calculated voltage
float temperatureC = 0.0;  // Temperature in Celsius

void setup() {
  // Initialize Serial Monitor for output
  Serial.begin(9600);
  Serial.println("LM35 Temperature Sensor Initialized");
  delay(500);
}

void loop() {
  // Read the analog value (0–1023)
  sensorValue = analogRead(tempPin);

  // Convert analog reading to voltage (assuming 5V reference)
  voltage = sensorValue * (5.0 / 1023.0);

  // LM35 outputs 10 mV per °C → 0.01 V per °C
  temperatureC = voltage / 0.01;

  // Print the temperature with label and 1 decimal place
  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.println(" °C");

  // Wait before the next reading
  delay(500);
}
