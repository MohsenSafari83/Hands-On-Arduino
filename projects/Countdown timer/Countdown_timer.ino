// Pin definitions for 7-segment display
const int a = 5;   // Segment A
const int b = 4;   // Segment B
const int c = 10;  // Segment C
const int d = 11;  // Segment D
const int e = 12;  // Segment E
const int f = 6;   // Segment F
const int g = 8;   // Segment G
const int dp = 9;  // Decimal Point (not used in this project)

// Array to easily access segment pins
int segmentPins[7] = {a, b, c, d, e, f, g};

// 7-segment encoding for numbers 0-9
// 1 = segment ON, 0 = segment OFF
byte digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {
  // Set all segment pins as OUTPUT
  for(int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(dp, OUTPUT);       // Decimal Point pin
  digitalWrite(dp, LOW);     // Turn off DP initially
}

// Function to display a single digit (0-9)
void displayDigit(int num){
  for(int i = 0; i < 7; i++){
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}

void loop() {
  // Loop through numbers 0 to 9
  for(int i = 0; i < 10; i++){
    displayDigit(i);   // Show the current number
    delay(1000);       // Wait 1 second
  }
}
