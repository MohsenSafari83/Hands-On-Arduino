# Introduction To I2C Communication

**I2C**, **I²C**, or **IIC** (*Inter-Integrated Circuit*) is a very popular **serial communication protocol** that’s widely used by different sensors and modules in embedded systems.  
It consists of **2 pins only** (one for serial data and one for the serial clock). Hence the name, **TWI (Two-Wire Interface)**.

---

> Note
The I2C Pins (**SDA** and **SCL**) are the Arduino analog input pins **A4** and **A5** respectively.  
If you’re going to use the Arduino I2C communication, you’ll not be able to use those 2 pins as analog input channels for the ADC or whatever.

---

## Arduino I2C Speed (Frequency)
The default Arduino I2C Speed is **100kHz**, and it can be increased up to a maximum of **400kHz** as stated earlier.

---

## Arduino I2C Applications
There are so many modules and sensors that we can interface with Arduino using the I2C bus, which include (but are not limited to):
- LCD displays
- Real Time Clocks (RTC)
- EEPROM modules
- Temperature sensors (e.g., LM75, BME280)
- MPU6050 accelerometer & gyroscope
- And many more...

---

##  Arduino Wire Library (I2C Library)
To use Arduino’s I2C module, we’ll be using the **built-in Wire library**.  
This library handles all initialization and operations that you’d need to perform with the I2C serial communication.

###  Wire Include
To be able to use the I2C Wire library, include it as shown below:
```cpp
#include <Wire.h>
```
## Arduino I2C Setup Functions (Wire Library)

First of all, you need to initialize the serial I2C module using the Wire.begin() function.
It can initialize the I2C as a master device or as a slave device.

For master initialization:
``` cpp
Wire.begin();     // Initialize As A Master I2C Device
```
For slave initialization (with address = 0x0A):
```cpp
Wire.begin(0x0A); // Initialize As A Slave I2C Device With Address = 0x0A
```
### Wire.end()

Disables the Wire library, reversing the effect of Wire.begin().
To use the Wire library again after this, call Wire.begin() again.

This function can be helpful if you want to switch the I2C operation mode from master to slave (or vice versa) during runtime without restarting the whole microcontroller.
This may be a rare condition, but it’s doable.
# Arduino I2C LCD Interfacing

Now, let’s move to interfacing the **I2C LCD 16×2 display** with Arduino.  
We’ll cover the **pinout**, **wiring diagram**, **LCD contrast control**, and the **I2C LCD device address**.

---

##  I2C LCD Pinout

| Pin | Description |
|-----|-------------|
| **GND** | Ground pin |
| **VCC** | Power supply input pin (+5V) |
| **SDA** | Serial Data Line for I2C LCD interface |
| **SCL** | Serial Clock Line for I2C LCD interface |

---

##  Wiring I2C LCD With Arduino

Here is the wiring diagram for the I2C LCD display with Arduino:

![Wiring I2C LCD With Arduino](images/LCD-interfacing-with-arduino.png)
### Example Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C MyLCD(0x27, 16, 2); // Creates I2C LCD Object (Address=0x27, Cols=16, Rows=2)

void setup() {
  MyLCD.init();        // Initialize the LCD
  MyLCD.backlight();   // Turn on backlight

  MyLCD.setCursor(0, 0); // (Column, Row)
  MyLCD.print("Counter Value:");
}

void loop() {
  // Example: Display counter or sensor data here
}
```
> This setup allows you to display messages easily on a 16×2 LCD using only two communication lines (SDA and SCL), making your wiring cleaner and freeing up Arduino pins for other components.

##  Summary Table

| Feature / Concept         | Details / Value |
|---------------------------|----------------|
| Communication Protocol    | I2C (Two-Wire Interface) |
| I2C Pins on Arduino       | SDA = A4, SCL = A5 |
| Default I2C Speed         | 100 kHz |
| Maximum I2C Speed         | 400 kHz |
| Arduino Library           | Wire.h, LiquidCrystal_I2C.h |
| LCD Size                  | 16×2 characters (2 rows × 16 columns) |
| LCD Backlight Control     | MyLCD.backlight() |
| LCD Initialization        | MyLCD.init() |
| Cursor Positioning        | MyLCD.setCursor(column, row) |
| Display Text              | MyLCD.print("Your Text") |
| Advantages of I2C LCD     | Fewer wires, multiple modules on one bus, saves Arduino pins |



