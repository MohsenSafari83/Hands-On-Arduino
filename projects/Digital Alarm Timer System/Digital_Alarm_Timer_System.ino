// ------------------ Auto-Start Countdown Timer with Continuous Alarm ------------------
// This project is a simple digital countdown timer using Arduino and an HT16K33 7-segment display.
// - The timer starts automatically when the Arduino powers on, counting down from a preset value.
// - When the countdown reaches zero, an LED blinks and a buzzer sounds continuously as an alarm.
// - The only user interaction is a single button to stop the alarm completely.
// - Once the alarm is stopped, the program halts entirely (timer and alarm are disabled).
// - Timing is handled using millis() for precise 1-second countdowns without blocking the program.


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_7segment display = Adafruit_7segment();

// Pin definitions
const int BUZZER_PIN = 9;
const int LED_PIN = 6;
const int BUTTON_STOP = 3;   // Stop alarm button

// Timer settings
int timerValue = 2;          // Default countdown (seconds)
bool alarmActive = false;

// Time tracking
unsigned long lastCountMillis = 0;
unsigned long lastAlarmMillis = 0;
bool alarmLEDState = false;

// Button debouncing
bool lastButtonState = HIGH;
unsigned long lastButtonMillis = 0;

void setup() {
  display.begin(0x70);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(BUTTON_STOP, INPUT_PULLUP);

  display.clear();
  display.writeDisplay();
}

void loop() {
  unsigned long currentMillis = millis();

  //  Countdown Timer
  if (timerValue > 0) {
    if (currentMillis - lastCountMillis >= 1000) {
      lastCountMillis = currentMillis;
      timerValue--;
    }
  }

  //  Start Alarm when Timer Reaches Zero 
  if (timerValue <= 0 && !alarmActive) {
    timerValue = 0;  // Ensure non-negative display
    startAlarm();
  }

  //  Alarm Logic 
  if (alarmActive) {
    if (currentMillis - lastAlarmMillis >= 250) {
      lastAlarmMillis = currentMillis;
      alarmLEDState = !alarmLEDState;
      digitalWrite(LED_PIN, alarmLEDState);
      tone(BUZZER_PIN, alarmLEDState ? 1000 : 0);
    }
  }

  //Stop Alarm Button 
  bool buttonState = digitalRead(BUTTON_STOP);
  if (lastButtonState == HIGH && buttonState == LOW && (currentMillis - lastButtonMillis > 200)) {
    lastButtonMillis = currentMillis;
    if (alarmActive) {
      stopAlarmAndHalt();
    }
  }
  lastButtonState = buttonState;

  // Display Update 
  display.print(timerValue);
  display.writeDisplay();
}

// Functions 
void startAlarm() {
  alarmActive = true;
  lastAlarmMillis = millis();
}

void stopAlarmAndHalt() {
  alarmActive = false;
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  // Stop program permanently
  display.clear();
  display.writeDisplay();
  while (true) {
    // Infinite loop → program halts completely
  }
}
