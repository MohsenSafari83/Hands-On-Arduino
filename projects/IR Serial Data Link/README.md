#   Serial Communication Link Circuit
![Project Overview](images/Project-Overview.png)

# Arduino Infrared (IR) Serial Link

This project demonstrates a simple and robust **wireless serial communication link** between two Arduino boards using **Infrared (IR)** technology and the **NEC protocol**.  
It implements a basic digital data transmission system using an **IR LED (IR333)** and an **IR receiver module (VS838)**.

---

## Project Overview

The goal of this project is to reliably send a simple character (e.g., `'A'`) from one Arduino (Sender) to another (Receiver).  
The system uses the **NEC protocol** and a **38 kHz carrier frequency** to reduce noise from ambient light.

- **Protocol:** NEC (32-bit data frame)  
- **Carrier Frequency:** **38 kHz** (managed by the IRremote library)  
- **Data Sent:** ASCII character `'A'` (**0x41**)

---

## Prerequisites

### Hardware Components

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino Uno | 2 | One for Sender, one for Receiver |
| IR LED | 1 | **IR333** (Peak Wavelength: **940 nm**) |
| IR Receiver Module | 1 | **VS838** (Carrier frequency **38 kHz**) |
| Resistor | 1 | **270 Ω** or **330 Ω** (current-limiting for the IR LED) |
| Breadboards / Wires | – | For circuit assembly |

### Software / Libraries

- **Arduino IDE**  
- **IRremote Library:** (Version 3.x or later recommended)  
  Install via:  
  `Sketch > Include Library > Manage Libraries...`  
  Then search for **"IRremote"**

---

##  Circuit Diagram and Wiring

### 1.  IR Sender Circuit

To generate the **38 kHz** carrier signal, connect the IR LED to **Pin 3** (supports PWM).

- IR LED **Anode (long leg)** → **330 Ω resistor**  
- Resistor output → **Digital Pin 3**  
- IR LED **Cathode (short leg)** → **GND**

---

### 2.  IR Receiver Circuit

The **VS838** module needs no external components—just proper power and signal connections.

- **VCC (right pin)** → **5 V**  
- **GND (middle pin)** → **GND**  
- **OUT (left pin)** → **Digital Pin 2**

---

##  Arduino Code

### 1. Sender Code (`Sender.ino`)

This code sends the ASCII character `'A'` (**0x41**) every second using the NEC protocol with address **0x00**.


#### Output of Sender

Below is what the output of the Sender looks like in the Arduino Serial Monitor:

![output of sender](images/senderout.)

---

### 2. Receiver Code (`Receiver.ino`)

This code listens on **Pin 2**, decodes incoming NEC signals, and extracts the command byte (our character).
#### Output of Reciver

Below is what the output of the Reciver looks like in the Arduino Serial Monitor:

![output of reciver ](images/reciverout.)


