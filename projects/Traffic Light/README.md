# 🚦Arduino Traffic Light Project

A simple **traffic light simulation** built using an **Arduino Uno** and three LEDs (red, yellow, green).  
This project demonstrates basic digital output control and timing using the `digitalWrite()` and `delay()` functions in Arduino.

---

##  Overview

This mini-project simulates how a real traffic light operates:
1. The **green LED** turns on for a few seconds, allowing "traffic" to pass.  
2. Then the **yellow LED** turns on briefly to indicate a warning.  
3. Finally, the **red LED** turns on to stop traffic before the cycle repeats.

---

##  Components Used

| Component        | Quantity | Description |
|------------------|-----------|-------------|
| Arduino Uno      | 1         | Main microcontroller board |
| Breadboard       | 1         | For circuit assembly |
| LED (Red)        | 1         | Represents stop light |
| LED (Yellow)     | 1         | Represents caution light |
| LED (Green)      | 1         | Represents go light |
| Resistors (220Ω) | 3         | Current limiting resistors for LEDs |
| Jumper Wires     | —         | For connections |
| USB Cable        | 1         | To power and upload code to Arduino |

---

## Circuit Connection

| LED Color | Arduino Pin | Resistor | Ground |
|------------|--------------|-----------|--------|
| Red        | 12           | 220Ω      | GND |
| Yellow     | 8            | 220Ω      | GND |
| Green      | 5            | 220Ω      | GND |

> ⚠️ The **long leg (anode)** of each LED goes to the **resistor → Arduino pin**, and the **short leg (cathode)** goes to **GND**.

---
## How to Run
1. Open [Tinkercad Circuits](https://www.tinkercad.com/circuits) or the Arduino IDE.
2. Wire the components exactly as shown in the circuit diagram.
3. Upload the provided code to your Arduino Uno.
4. Start the simulation (in Tinkercad) or power your Arduino via USB.
5. Observe the LEDs cycling like a real traffic light! 
---
## Preview
! [light](images/traf.jpg)



