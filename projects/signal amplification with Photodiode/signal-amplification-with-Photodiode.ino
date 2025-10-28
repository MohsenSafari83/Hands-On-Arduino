// Arduino Photodiode + OpAmp Light Sensor Example
// Reads the amplified voltage from a photodiode TIA circuit on A0
// Converts the voltage to photocurrent (nA) and prints results to Serial


// Pin and Circuit Definitions 
// Analog input pin connected to the Op-Amp output
const int sensor_Pin = A0;

// Arduino ADC reference voltage (typically 5V for most boards)
const float Vref = 5.0;

// Feedback resistor value in the Transimpedance Amplifier (TIA)
// Rf converts photocurrent into output voltage: Vout = Iph * Rf
const float Rf = 1000000.0;    // 1 Megaohm

 
void setup() {
  // Initialize Serial communication for data output
  Serial.begin(9600);  
}

void loop() {
  // Step 1: Read raw ADC value from A0 (range 0 - 1023 for 10-bit ADC)
  int raw_ADC = analogRead(sensor_Pin);  

  // Step 2: Convert raw ADC value to voltage
  // Formula: V = (ADC_value / ADC_max) * Vref
  float voltage = (raw_ADC * Vref) / 1023.0;

  // Step 3: Convert voltage to photocurrent using the TIA resistor
  // Formula: Iph = Vout / Rf
  float photocurrent = voltage / Rf;   // in Amperes

  // Output
  // Print raw ADC value
  Serial.print("ADC: ");
  Serial.print(raw_ADC);
  
  // Print converted voltage
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);  // 3 decimal places
  Serial.print(" V");
  
  // Print calculated photocurrent in nanoamperes for readability
  Serial.print(" | Photocurrent: ");
  Serial.print(photocurrent * 1e9, 2); // nA with 2 decimal places
  Serial.println(" nA");
  
  // Step 4: Delay for 200ms between readings
  // Adjust delay for faster/slower sampling
  delay(200);
}
