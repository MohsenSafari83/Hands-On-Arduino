# Arduino Photodiode Light Sensor System

## Introduction
A **photodiode** is a semiconductor device that converts light energy (photons) into electrical energy (electrons). When exposed to light, it generates a small current or voltage that can be amplified and measured. Small photodiodes are typically used for **light intensity sensing**, while large-area photodiodes are used for **solar power generation**.

In this project, we will be using the **BPW34 Photodiode** with an **Op-Amp conditioning circuit** and **Arduino** to build a light-intensity measurement system.

---

## Light Sensors Overview

Light sensors are passive optoelectronic devices that convert light energy into electrical signals. Their purpose is to detect the **intensity** of light within a specific region of the electromagnetic spectrum, including:

- Infrared (IR)
- Visible light
- Ultraviolet (UV)

Because they convert **photons into electrical signals**, they are often classified as **photoelectric devices** or **photo sensors**.

---

## Categories of Photoelectric Devices

There are two main categories of photoelectric devices:

1. **Energy-Generating Devices**
   - Generate electrical energy when illuminated  
   - Examples: Photovoltaic cells, photo-emissive devices

2. **Property-Changing Devices**
   - Modify electrical characteristics when exposed to light  
   - Examples: Photoresistors (LDR), photoconductors, phototransistors

---

## Photoconductive Light Sensors

A **photoconductive light sensor** does not produce electricity directly. Instead, its **electrical resistance changes** when light strikes the device.

### Light Dependent Resistor (LDR)
- A **Photoresistor** is the most common photoconductive sensor
- Resistance decreases when light intensity increases
- Used in simple light-activated circuits like night lamps or basic detectors

LDRs are convenient for general light sensing but lack the precision and speed required for high-performance optical measurements.

---

## Photodiodes

A **photodiode** is a semiconductor diode designed to detect photons and convert them into current. Structurally similar to a standard PN-junction diode, it features:

- A transparent encapsulation or optical lens to expose the PN-junction to light
- Higher sensitivity particularly to **IR and red light wavelengths**
- Very fast response time compared with LDRs

### PIN Photodiodes
A **PIN photodiode** places an intrinsic (I) region between P and N layers. Benefits include:

- Higher sensitivity
- Lower noise
- Faster response and wider bandwidth

The **BPW34** used in this project is a **PIN photodiode**, making it suitable for accurate and fast optical measurements.

---

## Photodiode Applications

Photodiodes are used in a wide range of optoelectronic systems including:

- Solar tracking systems
- Light intensity meters (Lux sensors)
- Position sensing modules
- Photo-interrupters and object detectors
- High-speed optical communication
- Medical sensors such as pulse detection
- Security laser alarms

---

## Project Scope

This project demonstrates:

- Using the **BPW34 Photodiode** in a **transimpedance amplifier (Op-Amp) circuit**
- Amplifying its response for **Arduino ADC measurement**
- Creating a functional and precise **light-intensity sensor**

The result provides a strong foundation for more advanced applications such as optical communication or directional light tracking.

---
## Summary

| Feature | LDR | Photodiode |
|--------|-----|-------------|
| Response Speed | Slow | Very Fast |
| Sensitivity | Medium | High |
| IR Detection | Limited | Excellent |
| Electrical Output | Resistance change | Current/voltage generation |
| Precision Applications | No | Yes |

This project uses a **photodiode + op amp** for accurate light measurement ideal for scientific and embedded system applications.

