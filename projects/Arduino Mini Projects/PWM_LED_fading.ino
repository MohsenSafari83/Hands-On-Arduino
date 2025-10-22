#define LED_PIN 5   // Define the PWM pin connected to the LED

void setup()
{
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // --- Gradually Increase LED Brightness ---
  // The for loop increases PWM duty cycle from 0 to 255
  // This causes the LED to slowly brighten
  for (int i = 0; i < 255; i++)
  {
    analogWrite(LED_PIN, i);  // Output PWM signal with current duty cycle
    delay(5);                 // Small delay for smooth fading
  }

  // --- Gradually Decrease LED Brightness ---
  // The for loop decreases PWM duty cycle from 255 to 0
  // This causes the LED to slowly dim
  for (int i = 255; i > 0; i--)
  {
    analogWrite(LED_PIN, i);  // Output PWM signal with current duty cycle
    delay(5);                 // Small delay for smooth fading
  }
}
