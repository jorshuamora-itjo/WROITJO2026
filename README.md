<div align="center">

# WRO 2026 — Future Engineers
### **Team:** The Pits JO &nbsp;|&nbsp; **Robot:** Meteoro
**Jesús Obrero Technical Institute (ITJO)**

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![WRO 2026](https://img.shields.io/badge/WRO-Future_Engineers_2026-orange?style=for-the-badge)](https://wro-association.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Arduino_Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)

---

> 🇪🇸 **Nota para jueces y evaluadores en español:** Puedes leer la versión oficial traducida al español directamente en [README_ES.md](README_ES.md).

---

</div>

## Engineering Materials

This repository contains all engineering materials, CAD models, schematic diagrams, source code, and technical documentation for the **Meteoro** autonomous vehicle, developed by team **The Pits JO** from **Jesús Obrero Technical Institute (ITJO)** for the **WRO Future Engineers 2026** competition.

### Repository Contents

* **[`README.md`](README.md)**: Main technical documentation in English.
* **[`README_ES.md`](README_ES.md)**: Full technical documentation in Spanish.
* **[`LICENSE`](LICENSE)**: MIT open-source license corresponding to team The Pits JO.
* **[`.gitignore`](.gitignore)**: Configuration file to ignore build binaries and temporary files.
* **[`src/`](src/)**: Control software code for all components programmed for the competition.
* **[`models/`](models/)**: Files for models used by 3D printers, laser cutters, and CNC machines to manufacture vehicle parts.
* **[`photos/`](photos/)**: Unified photo gallery containing official team photos, vehicle views, and assembly/programming logs.
* **[`video/`](video/)**: File containing the direct link to the track demonstration video.
* **[`schematics/`](schematics/)**: Schematic diagrams of electromechanical components, illustrating all parts (electronic components and motors) used in the vehicle and how they connect.
* **[`docs/`](docs/)**: Additional documentation, datasheets, pinout tables, and pit checklists.

---

> **Technical Nomenclature Clarification**
> 
> To avoid redundancy or confusion throughout this document and the entire technical repository:
> 1. **"Pit Dinoco"** (or version 1.1) refers to the first experimental platform built by the team for our first WRO competition.
> 2. **"Meteoro"** (or version 2.0) refers to the current competition prototype, resulting from a comprehensive electromechanical and software redesign.

---

## Introduction

Team **The Pits JO** is composed of 6th-year Technical High School students from **Jesús Obrero Technical Institute (ITJO)**. Our training covers Electronics and Telematics, allowing us to approach vehicle development from a comprehensive mechatronics engineering perspective.

Although in workshop practice all team members collaborate across all tasks during assembly, wiring, programming, and troubleshooting (*"everyone does everything"*), we have defined a responsibility structure aligned with each member's academic specialization:

| Member | Academic Specialization | Main Roles | Key Contributions & Cross-Functional Work |
| :--- | :--- | :--- | :--- |
| **Samuel Castillo** | Industrial Electronics Professional Technician | 3D Mechanical Designer, Maintenance & Electromechanical Integration | CAD modeling of v1.1 and v2.0 chassis, mechanical steering calibration, 3D printing of custom gears, and actuator code routines. |
| **Jorshua Mora** | Industrial Telematics Professional Technician | Lead Software Developer, Vision Specialist & Pit Manager | Base firmware development, PixyCam2 system calibration, corrective maintenance in the pit, and direct support in electrical wiring routing and integration. |
| **Winston Garrido** | Industrial Electronics Professional Technician | PID Control Algorithms, Schematic Designer & Repository Manager | Adaptive PID control tuning, power distribution design, pinout/electrical schematics, and technical GitHub repository structuring. |

By recommendation and express request of our technical mentor, the firmware architectural structure and steering geometry were evaluated under strict repetition tests before final implementation in prototype v2.0.

---

## Critical Analysis and Lessons Learned (Pit Dinoco v1.1)

After completing our first experience in the World Robot Olympiad (WRO), we conducted a rigorous critical analysis of **Pit Dinoco**'s track performance. That first iteration allowed us to identify engineering flaws affecting overall performance:

* **Defective Cable Routing:** The lack of integrated cable channels led to bent wires or wires exposed to friction with moving parts, causing loose contacts during testing.
* **Inadequate Weight Distribution:** Concentrating weight (lithium batteries) in the rear overhang shifted the center of gravity (CG), depriving the front axle of grip. This caused the robot to understeer (*"go straight"*) in 90º turns.
* **Physical Sensor Interference:** Ultrasonic sensors were positioned adjacent to the front wheels, colliding mechanically during maximum turn angles.
* **Improvised Mechanical Couplings:** The steering mechanism used a manually adapted servo arm that, under continuous load, suffered thermal friction deformation (melting or stripping the motor spline).

### Design Pillars for Meteoro v2.0

Based on the lessons learned from Pit Dinoco, we established four design pillars for the **Meteoro** prototype:

1. **Accessibility and Maintainability:** Fast access to batteries and logic modules without disassembling the main structure in the pit.
2. **Thermal and Electrical Cable Management:** Internal routing channels and dedicated passthrough ports to isolate power lines from signal lines.
3. **Mechanical Robustness:** 3D printed parts using high-strength profiles (5 perimeter walls and 20% Gyroid infill) in areas subject to impact or vibration.
4. **Corrected Kinematics:** Integration of F1-style steering based on Ackermann geometry and a Scotch Yoke coupling.

We kept the combination that proved operationally efficient in the previous prototype: 3D printed structural parts, standardized electronics, and complementary mechanical components from LEGO Technic (splined axles, precision bearings, and 40mm diameter by 20mm thick wheels).

---

## Components and Sensors

We replaced traditional HC-SR04 modules with **RCWL-1601** sensors. Despite keeping the same 4-pin physical interface (`VCC`, `TRIG`, `ECHO`, `GND`), these offer substantial improvements in acoustic noise immunity and refresh rates:

| Technical Parameter | Previous Module: HC-SR04 | Current Module: RCWL-1601 | Impact on "Meteoro" Vehicle |
| :--- | :--- | :--- | :--- |
| **Form Factor** | Standard (45 x 20 mm) | Compact (21 x 18 mm) | Allows internal integration into the front wing. |
| **Operating Voltage** | Rigid 5.0V DC | 3.0V - 5.5V DC | Immunity against minor control line fluctuations. |
| **Beam Angle** | approx. 15º (Prone to echoes) | < 12º (Focused beam) | Reduces false readings against diagonal acrylic walls. |
| **Range Accuracy** | ±3 mm | ±1 mm | Stability in error calculation for the PID loop. |

To optimize PID centering response time, we analyzed solutions used by top international WRO teams, referencing the sensor layout of team **GammaVersion** (Spanish WRO Champions 2022/2025 in their *"Gamma Version's Car Review"*).

* **Kinematic Advantage:** Positioning sensors ahead of the front turning axle allows the controller to process wall variations with greater spatial anticipation, initiating corrections before entering a turn.
* **Anti-Collision Structural Protection:** To prevent impact damage in collisions, custom rigid housings were designed to enclose the ultrasonic transducers with a 0.1mm tolerance fit.
* **Spatial Orientation:** To remain within regulatory dimensional limits, side sensors (left and right) were mounted vertically, while the front sensor was kept in a horizontal orientation.

---

## Mechanical Specifications and Steering Kinematics

Meteoro's dimensional design was drafted on graph paper to guarantee compliance with WRO rules (maximum 30cm long x 20cm wide):

* **Total Length:** 26 cm
* **Total Width:** 13 cm
* **Wheel Diameter:** 40 mm (Width: 20 mm)

By relocating the batteries to the center of the lower chassis, the DC traction motor had to be positioned parallel to the rear axle. Since conventional spur gears only operate coplanarly and standard LEGO double-bevel gears did not offer the exact ratio required without changing vehicle dimensions, we custom-designed and 3D-printed a set of **custom 90º bevel gears**.

This ratio **(1:1.5)** maintains an optimal balance for our total mass of **660 g**, providing linear speed without compromising starting torque.

### Ackermann Steering Geometry

To eliminate front tire drag in 90º turns, we implemented Ackermann steering geometry driven by an **MG90S** servomotor mounted on the chassis using a slotted guide and pin mechanism (kinematically based on the Scotch Yoke).

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Where $w = 128\text{ mm}$ (track width) and $L = 165\text{ mm}$ (wheelbase).

After evaluating geometric behaviors (100% Ackermann, Parallel, and Aggressive >100%), the toe line was adjusted by shifting the crossover point 2.5 cm behind the center of the rear axle. This yields balanced behavior:

* **On Straights:** Prevents oscillations or hypersensitivity during small PID corrections.
* **In Turns:** Allows the inner wheel ($\theta_{\text{int}}$) to turn at a wider angle than the outer wheel ($\theta_{\text{ext}}$), preventing front-end scrubbing.

---

## Chassis Layout (Two-Deck Structure)

* **Lower Deck (Base Chassis):** Houses the longitudinally centered 3S Li-ion battery pack, DC motor with custom bevel gearbox, steering servomotor, and front wing with 3 RCWL-1601 sensors. Features a bottom access window for battery replacement without disassembling the upper deck.
* **Upper Deck (F1 Top Shell):** Holds the L298N power driver, PixyCam2 vision camera, and Arduino Nano boards (Master/Slave). Its aerodynamic shape covers the servo and routes wires toward the rear.

---

## Modules and Direct Links

* **Prototype Firmware:** [`src/`](src/)
* **Pinout Connections Table:** [`schematics/`](schematics/)
* **Pit Checklist:** [`docs/`](docs/)

---

<div align="center">

© 2026 **The Pits JO** — Jesús Obrero Technical Institute.  
All rights reserved. Distributed under the [MIT License](LICENSE).

</div>
