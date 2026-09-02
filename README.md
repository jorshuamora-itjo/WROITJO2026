<div align="center">

# WRO 2026 — Future Engineers
### **Team:** The Pits JO &nbsp;|&nbsp; **Robot:** Meteoro
**Instituto Técnico Jesús Obrero (ITJO)**

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
> To facilitate reading the documentation and avoid confusion throughout this project, we use the following standard:
> 1. **Pit Dinoco (Version 1.1):** Our first experimental car. With it, we learned the fundamentals of the competition and identified the main flaws to correct.
> 2. **Meteoro (Version 2.0):** The definitive competition vehicle. It stems from a complete redesign of the mechanical structure, power circuits, and control software.

---

## Visual Comparison of Prototypes

| Design Criterion | Pit Dinoco ($v1.1$) | Meteoro ($v2.0$) |
| :--- | :--- | :--- |
| **Structure** | Single deck (monolayer) with exposed cables. | Double-deck modular chassis with internal cable routing channels. |
| **Steering** | Simple steering with servo exposed to wear. | Ackermann geometry with a Scotch Yoke mechanism. |
| **Drivetrain** | Visible spur gears. | Longitudinal motor with 90° bevel gears. |
| **Weight Distribution** | Batteries in the rear (caused understeer). | Batteries at the center of the lower chassis (50/50 balance). |
| **Distance Sensors** | HC-SR04 modules glued to the front. | RCWL-1601 sensors integrated inside the F1 front wing. |

---

## Introduction

The team **The Pits JO** consists of 6th-year Technical High School students from **Instituto Técnico Jesús Obrero (ITJO)**. Our academic background covers the fields of Electronics and Telematics, which provided us with the necessary tools to build an autonomous car from scratch.

Although in daily workshop practice we apply the philosophy of *"everyone does everything"* (assembling, soldering, programming, and track testing), we distribute primary responsibilities according to each member's specialty:

| Team Member | Academic Major | Primary Roles | Key Contributions and Cross-Functional Tasks |
| :--- | :--- | :--- | :--- |
| **Samuel Castillo** | Industrial Professional Technician in Electronics | 3D Mechanical Designer, Maintenance, and Electromechanical Integration | Designed the 3D parts and chassis for the  $v1.1$  and  $v2.0$  prototypes, calibrated the steering system, manufactured custom gears, and supported motor testing routines. |
| **Jorshua Mora** | Industrial Professional Technician in Telematics | Lead Software Programmer, Vision Specialist, and Pit Crew | Developed the core code, configured the PixyCam2 vision sensor, managed rapid maintenance in the competition pit area, and assisted with wiring harness assembly. |
| **Winston Garrido** | Industrial Professional Technician in Electronics | PID Control Algorithms, Schematic Designer, and Repository Manager | Calibrated the $PD$ trajectory control system, designed the power distribution network, drew schematic diagrams, and organized all technical documentation on GitHub. |

> **Note on Technical Guidance**  
> Per the recommendation and explicit request of our technical mentor, the architectural structure of the code and the steering geometry underwent rigorous track repeatability testing before being approved and installed on the Meteoro ($v2.0$) prototype.

---

## Diagnosis of Prototype v1.1 ("Pit Dinoco") and Lessons Learned

Upon completing our first competition run with Pit Dinoco, we conducted a detailed behavioral analysis to understand why it committed errors on the track. This analysis revealed four key mechanical and electrical flaws:

* **Exposed and Bent Cables:** Lacking an organized cable path, wires rubbed against moving parts or bent excessively, causing unexpected failures or loose connections.
* **Unbalanced Weight Distribution:** The lithium batteries were positioned at the rear of the car. This made the front end too light, losing grip and causing the car to "push wide" (understeer) in tight 90° turns.
* **Sensor Interference with Wheels:** The ultrasonic sensors were mounted too close to the front wheels. When the steering servo reached full lock, the wheels physically struck the sensors.
* **Steering Wear and Tear:** The mechanical linkage connected to the steering servo was flat and made of basic plastic. Continuous use and frictional heat softened and stripped the plastic, resulting in loss of center alignment.

### New Architectural Design Principles for "Meteoro" (v2.0)

Building upon the lessons learned from Pit Dinoco, we established four core pillars for constructing Meteoro:

1. **Ease of Maintenance:** Design a system where batteries can be swapped or control boards inspected without disassembling the entire vehicle on the workbench.
2. **Electrical Organization and Protection:** Implement internal routing channels to guide wiring and keep power supply cables separate from data/signal lines.
3. **Mechanical Resilience:** 3D print high-impact components using durable infill patterns (20% Gyroid with 5 wall perimeters) to withstand vibrations and potential collisions.
4. **Precise Steering:** Adopt an F1-style steering system driven by Ackermann geometry and a Scotch Yoke mechanism.

---

## Technical Inspirations and Engineering Changes

We retained the combination that yielded excellent durability results: a 3D-printed main chassis (PLA+/PETG), standard electronics, and LEGO Technic mechanical components (cross-axles, precision bushings, and 40 mm diameter by 20 mm wide wheels).

We replaced the traditional HC-SR04 sensors with the **RCWL-1601** model. Although they share identical pinouts (`VCC`, `TRIG`, `ECHO`, and `GND`), this new model offers distinct advantages in form factor and accuracy:

| Technical Parameter | Previous Module: HC-SR04 | Current Module: RCWL-1601 | Impact on the Meteoro Vehicle |
| :--- | :--- | :--- | :--- |
| **Dimensions** | Standard (45 mm  $\times$  20 mm) | Compact (21 mm  $\times$  18 mm) | Allows embedding all three sensors inside the front wing. |
| **Operating Voltage** | Rigid 5.0V DC | 3.0V to 5.5V DC | Withstands minor voltage fluctuations without failure. |
| **Field of View** | $\approx 15^\circ$ (prone to echoes) | $< 12^\circ$ (narrow beam) | Prevents false readings from sound bouncing off diagonal walls. |
| **Measurement Accuracy** | $\pm 3\text{ mm}$ | $\pm 1\text{ mm}$ | Provides stable measurement data to smoothly correct trajectory. |

### Integration of the F1 Front Wing

To improve cornering response time, we studied solutions applied by international WRO teams, drawing inspiration from the sensor layout of team **GammaVersion** (WRO Spain Champions).

* **Kinematic Advantage:** By mounting the sensors ahead of the front wheel axis, the vehicle "sees" walls with spatial anticipation before physically entering the turn.
* **Impact Protection:** We designed rigid plastic housings with a 0.1 mm clearance tolerance to protect sensor capsules against wall scrapes.
* **Spatial Orientation:** To keep the vehicle within maximum allowed dimensions (30 cm  $\times$  20 cm), side sensors are mounted vertically while the front sensor is positioned horizontally.

---

## Mechanical Specifications and Blueprints

Before 3D modeling, we drew full-scale blueprints on graph paper to ensure the car complied with competition rules:

* **Total Length:** 26 cm (Maximum allowed limit: 30 cm)
* **Total Width:** 13 cm (Maximum allowed limit: 20 cm)
* **Wheel Diameter:** 40 mm (Width: 20 mm)

### Drivetrain Re-engineering: Custom 3D Bevel Gears

By relocating the batteries to the center of the lower deck, we had to mount the DC motor longitudinally (parallel to the chassis). Since commercial off-the-shelf parts did not provide the exact gear ratio required, we designed and 3D printed a custom set of **90° bevel gears**:

$$\text{Gear Ratio} = \frac{\text{Driven Gear Teeth}}{\text{Drive Gear Teeth}} = \frac{24}{16} = 1.5$$

This  $1:1.5$  ratio provides the ideal balance between launch acceleration and top speed to propel our car's weight of  $\approx 660\text{ g}$.

---

## Ackermann Steering Mechanism and Axle Convergence

To prevent the front tires from scrubbing or slipping when taking 90° corners, we implemented Ackermann steering geometry driven by an **AD002** servo motor via a pin-guided mechanism (based on the Scotch Yoke).

**Ideal Kinematic Condition:**

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Where  $w = 128\text{ mm}$ (front track width) and  $L = 165\text{ mm}$ (wheelbase between front and rear axles).

**Track Steering Setup:**

We calibrated the steering convergence point 2.5 cm behind the rear axle. This provides optimal handling characteristics:

* **On Straightaways:** The vehicle tracks straight without sharp jerks or weaving.
* **In Turns:** The inner wheel ($\theta_{\text{int}}$) turns at a steeper angle than the outer wheel ($\theta_{\text{ext}}$), executing a clean turn without excessive friction.

---

## Double-Deck Structure and Wiring Routing

Meteoro is divided into two independent levels:

* **Lower Deck (Mechanical Base and Power):** Houses the centered 3S Li-ion battery pack, the drive motor with its 90° gearing, the servo-steered front assembly, and the F1 front wing. It also features a bottom hatch for swapping batteries in seconds.
* **Upper Deck (Logic Control and Vision):** Holds the L298N motor driver, the PixyCam2 camera, and the dual Arduino Nano microcontrollers (Master and Slave). Its enclosure shields the servo motor and keeps all wiring neatly routed through channels.

---

## Navigation Strategy for Meteoro

Meteoro's navigation strategy utilizes a closed-loop monitoring control architecture divided into three core pillars: sensor acquisition and EMA filtering, a Finite State Machine (FSM), and real-time controllers.

### Finite State Machine (FSM) Algorithm Definition

#### RECTA State (Adaptive PD Centering)
On straightaways, the vehicle aims to maintain an equal distance relative to the left and right side walls:

$$e(t) = \frac{\text{US}_{\text{right}} - \text{US}_{\text{left}}}{2}$$

To prevent oscillation or sudden over-corrections caused by small imperfections in the acrylic walls, a **Deadband** of  $\pm 5.0\text{ cm}$  is applied:

* If $|e(t)| \le 5.0\text{ cm} \implies \text{error} = 0$
* If $e(t) > 5.0\text{ cm} \implies \text{error} = e(t) - 5.0$
* If $e(t) < -5.0\text{ cm} \implies \text{error} = e(t) + 5.0$

The final steering angle is computed via Proportional-Derivative (PD) control action:

$$\text{PD Output} = K_p \cdot \text{error} + K_d \cdot \frac{d e(t)}{dt}$$

$$\theta_{\text{steering}} = \theta_{\text{neutral}} + \text{PD Output}$$

Where  $\theta_{\text{neutral}} = 92^\circ$,  $K_p = 10.33$, and  $K_d = 14.0$.

---

#### CURVA State (MPU6050 Gyro-Assisted Turn)
When the front sensor detects a wall at a distance $\le 75.0\text{ cm}$, the FSM transitions to the **CURVA** state:

* **Track Direction Determination (First Corner):** If this is the first corner of the run ($\text{trackDirection} == 0$), side sensor readings are compared:
    * **If `US_left` > `US_right`:** Counter-clockwise direction (65° Steering Angle)
    * **If `US_left` ≤ `US_right`:** Clockwise direction (115° Steering Angle)
  
  This value is stored in  $\text{trackDirection}$ and locks the turn direction for all remaining corners on the circuit.

* **Accumulated Yaw Angle Calculation ($\theta_z$):** Based on the angular velocity measured along the Z-axis ($\omega_z$), the accumulated yaw angle is computed:

$$\theta_z(t) = \theta_z(t - \Delta t) + \left( \frac{\text{Raw Gyro Z} - \text{offset}_z}{131.0} \right) \cdot \Delta t$$

* **Exit Criterion:** The turn remains actively engaged until the absolute value of accumulated rotation meets the target threshold:

$$|\theta_z(t)| \ge \theta_{\text{target}} \quad (\theta_{\text{target}} = 72.0^\circ)$$

---

#### COOLDOWN State (Post-Turn Protection Delay)
Upon completing the  $72^\circ$  turn, the vehicle enters a stabilization period (**COOLDOWN**) for  $1200\text{ ms}$. During this window:

1. The derivative term memory is reset ($\text{previous error} = 0$).
2. Front sensor readings are temporarily ignored to prevent false triggers caused by rotational inertia or exiting side walls.
3. PD control resumes using side sensor measurements to stabilize trajectory before returning to the **RECTA** state.

---

### Sensor Data Filtering (Hybrid EMA Filter)

Ultrasonic sensors occasionally produce outliers or false  $0\text{ cm}$ readings due to acoustic reflections. To mitigate this, the algorithm implements a hybrid **EMA (Exponential Moving Average)** filter with an opening threshold:

```cpp
// If sensor detects open space (> 70 cm) or error (0 cm),
// respond instantly to avoid missing corner openings.
// In normal ranges (close walls), apply EMA smoothing with alpha = 0.4.

float filtrarEMA(float lecturaActual, float lecturaAnterior, float alpha = 0.4) {
    if (lecturaActual == 0 || lecturaActual > 70.0) {
        return lecturaActual; // Instant response for openings/errors
    }
    return (alpha * lecturaActual) + ((1.0 - alpha) * lecturaAnterior);
}
```

---

## Mechanical Design and Evolution

### Post-Mortem Diagnosis and Mechanical Challenges in Pit Dinoco (v1.1)

Performance analysis during our first track competition provided us with the real diagnosis that we could not fully observe during workshop testing. We identified four key mechanical and physical distribution issues:

* **Wiring Organization and Lack of Space:** In an attempt to minimize dimensions on a single layer (single deck), we overcrowded the central area. Signal cables were left exposed to constant friction with moving engine and transmission parts, leading to intermittent failures due to wire wear.
* **Center of Gravity (CG) Imbalance:** Positioning the lithium batteries at the rear shifted the center of gravity away from its ideal balance point. This lack of weight over the front wheels reduced ground traction, resulting in noticeable front-end push (understeer) during 90° turns.
* **Physical Obstruction in Steering:** The front ultrasonic sensors collided directly with the wheels at full lock, limiting the vehicle's turning angle.
* **Steering Arm Wear and Tear:** The original servo arm (3D printed and manually fitted in plastic) failed under continuous use. Constant friction generated heat, eventually stripping the gear teeth and misaligning the steering's neutral point.

---

### Mechanical Architecture Comparison: v1.1 vs v2.0

We retained the combination of materials that yielded solid results: integrating 3D-printed parts (PLA+/PETG), standard electronic components, and LEGO Technic mechanical elements (cross axles, precision bushings, and 40 mm × 20 mm wheels).

However, to address structural weaknesses, we completely redesigned the chassis. The table below details the implemented improvements:

| Constructive Criterion | Initial Prototype: Pit Dinoco (v1.1) | Competitive Prototype: Meteoro (v2.0) | Mechanical and Dynamic Impact |
| :--- | :--- | :--- | :--- |
| **Chassis Distribution** | Single flat layer with exposed components. | Interconnected modular double deck. | Separates the power stage from control electronics and protects components. |
| **Steering Geometry** | Direct central pivot (symmetrical turn). | Ackermann geometry driven by a Scotch Yoke. | Eliminates unwanted tire scrubbing in tight corners. |
| **Rear Drivetrain** | Exposed spur gears on the same plane. | 3D-printed 90° bevel gears. | Allows mounting the motor longitudinally along the chassis, freeing internal space. |
| **Battery Location** | Positioned at the rear (behind the axle). | Centered lower compartment (between both axles). | Balances the center of gravity (50/50) and eliminates front-end understeer. |
| **Sensor Mounting** | Independent brackets beside the wheels. | F1-style front wing with collision protection. | Improves reading anticipation and shields sensors from impacts. |
| **Pit Maintenance** | Complete disassembly required for any change. | Quick-access hatch on the lower deck. | Allows swapping batteries in seconds without touching the electronics. |

---

### Mechanical Re-engineering in Meteoro (v2.0)

#### 1. Integrated F1 Front Wing ("GammaVersion" Inspiration)
Drawing inspiration from the sensor distribution of team **GammaVersion** in WRO, we designed an F1-style front wing structure via 3D printing:

* **Anticipated Readings:** Positioning the three ultrasonic sensors ahead of the front axle allows the system to detect walls with greater anticipation before the vehicle's body enters the turn.
* **Collision Protection:** Sensors snap firmly into rigid housings with a precise 0.1 mm clearance, doubling as a protective bumper.
* **Efficient Layout:** Side sensors are mounted vertically while the central sensor is horizontal to stay within the maximum allowed dimensions of 30 cm × 20 cm.

---

#### 2. Ackermann Steering Geometry
We replaced the simple pivot with an Ackermann geometric steering system driven by a metal-geared **AD002** servo motor, connected via a slotted guide pin mechanism (Scotch Yoke).

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Where  $w = 128\text{ mm}$ (front track width) and  $L = 165\text{ mm}$ (wheelbase).

This configuration forces the inner wheel ($\theta_{\text{int}}$) to turn at a steeper angle than the outer wheel ($\theta_{\text{ext}}$), allowing both to follow the natural cornering arc without scrubbing.

* **Stability Calibration:** We tuned the geometry so that the alignment convergence point sits 2.5 cm behind the center of the rear axle. This keeps the vehicle firm and stable on straightaways without sacrificing agility in 90° turns.

---

#### 3. Redesigned Drivetrain: Custom 90° Bevel Gears
To place the batteries in the center of the lower deck, we oriented the motor longitudinally along the chassis. Since off-the-shelf LEGO parts did not provide the required gear ratio in the available space, we designed and 3D printed a custom pair of **90° bevel gears**:

$$\text{Gear Ratio} = \frac{\text{Driven Teeth}}{\text{Drive Teeth}} = \frac{24}{16} = 1.5$$

This 1:1.5 ratio offers the ideal balance between launch torque and top speed for the vehicle's total weight (660 g).

---

#### 4. Double-Deck Modular Distribution
Meteoro's structure simplifies inspections and repairs by organizing into two levels:

* **Lower Deck (Drivetrain and Power):** Houses the centered 3S Li-ion battery pack, the main motor with its bevel gears, the metal steering servo, and the front wing. Includes a quick-access bottom hatch for swapping batteries conveniently.
* **Upper Deck (Control and Sensors):** Holds microcontrollers, the L298N motor driver, the PixyCam2 camera, and internal routing channels that keep signal cables isolated from power lines.

---

#### 5. Dimensional Verification
Before final CAD modeling, we drafted dimensions on graph paper to guarantee compliance with WRO regulations (30 cm × 20 cm):

* **Total Length:** 260 mm
* **Total Width:** 130 mm
* **Wheel Diameter:** 40 mm (Width: 20 mm)

---

## Electronic Architecture and Power System

In autonomous robotics, software stability depends entirely on the reliability of the underlying electrical system. On our first prototype (Pit Dinoco), we suffered unexpected microcontroller resets due to power interference generated by the main motor and instantaneous current draws from the steering motor.

For Meteoro (v2.0), we completely redesigned the electronic architecture by splitting workload across two networked microcontrollers and constructing isolated, independent power circuits for each system requirement.

---

### Distributed Logic Architecture (Master / Slave via I2C)

To avoid delays in sending motor commands while simultaneously reading sensors, we divided tasks between two Arduino Nano boards interconnected via the I2C data bus (at address `0x08`):

* **Arduino Nano Master:** Functions as the vehicle's "brain." It reads distances from the three ultrasonic sensors, calculates tilt/heading using the MPU6050 gyroscope, performs color recognition with the PixyCam2 camera (connected via SPI bus), and processes mathematical control equations to guide the car.
* **Arduino Nano Slave:** Acts as the system's "muscle." It rapidly receives commands sent by the Master and directly drives the steering servo motor and the L298N driver that powers the main motor.

---

### Pinout Map

To inspect complete, illustrated graphic schematics, please refer to the `schematics/` folder in the repository.

#### Pin Mapping - Arduino Nano Master

| Module / Component | Component Pin | Arduino Nano Pin | Signal Type | Logic Level | System Function |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Left Ultrasonic** | ECHO | D6 | Input | 5.0 V | Echo reception for left wall |
| | TRIG | D7 | Output | 5.0 V | Ultrasonic pulse emission |
| **Right Ultrasonic** | ECHO | D8 | Input | 5.0 V | Echo reception for right wall |
| | TRIG | D9 | Output | 5.0 V | Ultrasonic pulse emission |
| **Front Ultrasonic** | ECHO | D10 | Input | 5.0 V | Echo reception for corner detection |
| | TRIG | D11 | Output | 5.0 V | Ultrasonic pulse emission |
| **Gyroscope (MPU6050)** | SDA | A4 | I2C Data | 5.0 V | Z-axis rotation reading |
| | SCL | A5 | I2C Clock | 5.0 V | Synchronization clock (100 kHz) |
| **I2C Interconnect (Slave)** | SDA | A4 | I2C Data | 5.0 V | Sends steering and speed commands |
| | SCL | A5 | I2C Clock | 5.0 V | Shared clock channel |
| **PixyCam2 Camera** | MOSI / MISO / SCK | D11 / D12 / D13 | SPI Bus | 5.0 V | Visual recognition at 60 frames per second |
| **Logic Power** | 5V / GND | 5V / GND | Power | 5.0 V Reg. | Input from Regulator Channel 1 |

---

#### Pin Mapping - Arduino Nano Slave

| Module / Component | Component Pin | Arduino Nano Pin | Signal Type | Logic Level | System Function |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **AD002 Steering Servo** | Signal (PWM) | D2 | PWM Output | 5.0 V | Angle adjustment for Ackermann steering |
| **L298N Driver (DC Motor)** | IN1 / A1 | D5 | PWM Output | 5.0 V | Speed control for traction |
| | IN2 / A2 | D6 | Digital Output | 5.0 V | Direction of travel (LOW for forward) |
| **I2C Interconnect (Master)** | SDA | A4 | I2C Data | 5.0 V | Receives commands from Master |
| | SCL | A5 | I2C Clock | 5.0 V | Shared clock channel |
| **Logic Power** | 5V / GND | 5V / GND | Power | 5.0 V Reg. | Input from Regulator Channel 2 |

---

### Power Distribution Network and Regulation

The primary power source consists of a 3-cell series lithium battery pack (3S) delivering a nominal voltage of 11.1 V (reaching 12.6 V fully charged).

To completely eliminate voltage drops that triggered system resets, we split current distribution using two independent buck voltage regulators (DSN-MINI-360 Buck modules):

| Power Stage | Input Source | Regulated Output | Powered Components |
| :--- | :--- | :--- | :--- |
| **Lithium Batteries (3S)** | 3 × 3.7 V Pack | 11.1 V - 12.6 V Direct | Power input for main motor (L298N Driver) |
| **Buck Regulator 1 (Channel 1)** | 3S Lithium Pack | 5.0 V DC Regulated | Arduino Nano Master, MPU6050 Gyro, 3 Ultrasonic Sensors, and PixyCam2 |
| **Buck Regulator 2 (Channel 2)** | 3S Lithium Pack | 5.0 V DC Regulated | Arduino Nano Slave and AD002 Steering Servo |
| **Common Ground (GND)** | N/A | 0 V | Joint ground connection for all boards and sensors |

---

### Power Isolation Benefits

* **Protection Against High Current Demands:** When the servo motor executes sharp turns in tight corners, it draws power exclusively from Channel 2. This prevents camera or processor supply voltage from dropping below the 4.5 V operational threshold.
* **Interference Filtering:** The traction motor receives direct power from the battery pack. The isolated buck regulators filter out current spikes and electrical noise generated by the L298N driver.
* **Common Ground Reference:** Despite separate voltage regulation, all ground wires (0 V / GND) tie into a single point to ensure clear, accurate data transmission across the I2C bus.

---

### Reference Electronic Schematics

Visual wiring guides are available in the repository's [`schematics/`](schematics/) folder:

* `schematics/nano_master_diagram.jpg`: Wiring diagram for the Master circuit (Sensors, Vision, I2C, and Power Channel 1).
* `schematics/nano_slave_diagram.jpg`: Wiring diagram for the Slave circuit (Motors, L298N Driver, Servo Motor, and Power Channel 2).
* `schematics/pinout_table.md`: Quick-reference document for connection verification during pit testing.

---

## Software Architecture and Control Logic

### Code Historical Evolution (v1 to v4)

Software development for our vehicle did not happen overnight. Facing the real track taught us that pure theory quickly breaks down when sensors bounce off open corners or when wheels chatter due to numerical noise. Below is the documented evolutionary process of our code revisions stored in the `src/history/` directory leading up to the current implementation in `src/current/`.

* **Version 1: Monolithic and Blocking (`src/history/v1_pid_control.ino`)**
  * **Architecture:** A single Arduino Uno executing all processing tasks sequentially.
  * **Mechanism:** Distance measurement using the `pulseIn()` function, which paused the processor for up to 12 ms per sensor. Reading 3 sensors caused the processor to freeze for over 35 ms per cycle.
  * **Critical Failure:** Upon reaching a corner, the front sensor lost wall detection or read false reflections. The PID algorithm attempted to correct non-existent distances, resulting in abrupt steering maneuvers and collisions with the outer wall.

* **Version 2: State Transition (`src/history/v2_pid_switch.ino`)**
  * **Innovation:** Implemented a Finite State Machine (`RECTA` and `CURVA`) for the first time to decouple lane-centering control from cornering maneuvers.
  * **Control:** Automatic speed reduction upon detecting an approaching wall (set to 80% of maximum speed).
  * **Critical Failure:** The vehicle returned to the `RECTA` state before fully exiting the corner. Detecting the side wall too close immediately after turning, the PID applied an instantaneous counter-steering jerk.

* **Version 3: Timers and Cooldown (`src/history/v3_fsm_cooldown.ino`)**
  * **Innovation:** Introduced the `COOLDOWN_CURVA` constant (1500 ms) to prevent the vehicle from re-entering the turn state immediately after exiting one.
  * **Steering:** First version to record whether the open wall was to the left or right before initiating the fixed maneuver.
  * **Critical Failure:** Relying on fixed duration timings (`DURACION_GIRO = 2500 ms`) caused derailments when battery charge dropped: at lower voltage, the vehicle covered less distance in the same time window, leaving it oriented diagonally.

* **Version 4: Median Filter and Gap Detection (`src/history/v4_median_filter.ino`)**
  * **Innovation:** Incorporated a median filter over 4-sample arrays (`filtroMediana4`) to reject noise spikes caused by wall textures.
  * **Logic:** Detection of lane openings when measured distance exceeded the `distanciaHueco` threshold (90 cm).
  * **Breakthrough Point:** Although the median filter cleaned the signal, array sorting calculations consumed noticeable processor cycles. Furthermore, the vehicle still lacked absolute certainty regarding its rotational angle about its vertical axis.

---

### Software Evolution Comparison Table

| Logic / Performance Criterion | v1 (Monolithic) | v2 (Simple States) | v3 (Cooldown) | v4 (Median Filter) | Current Version (`src/current/`) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Processor** | 1 Arduino Uno | 1 Arduino Uno | 1 Arduino Uno | 1 Arduino Uno | 2 Arduino Nano (I2C) |
| **Ultrasonic Reading** | Blocking `pulseIn()` | Direct `pulseIn()` | Timed `pulseIn()` | Median (4 samples) | NewPing Library + EMA |
| **Turn Detection** | Wall distance | Fixed front threshold | Distance + Time | Gap Detection | Integrated MPU6050 Gyroscope |
| **Noise Filtering** | None (Raw) | Rigid threshold | Rigid threshold | 4-point Median Filter | EMA ($\alpha = 0.4$) + 180 cm Limit |
| **Direction Safety** | Non-existent | Instant reactive | Event lockout | Character memory | Permanent `sentidoPista` (EEPROM/RAM) |

---

### Distributed Network Architecture (Master / Slave)

To guarantee a constant cycle time ($\Delta t$) free of execution delays during motor control signal generation, the current codebase located in `src/current/` divides computational load across two processors communicating over the I2C bus at 100 kHz.

#### Slave Code Analysis (`src/current/nano_slave.cpp`)

The Slave microcontroller acts as a dedicated peripheral controller exclusively managing the physical movement of steering and traction, keeping logic execution isolated from sensor-related timing delays.

##### 1. Interrupts and Safe Buffer
To prevent data corruption while executing motor commands, incoming data received via the `Wire.onReceive(recibirDatosI2C)` event handler is stored in protected variables qualified with the `volatile` keyword:

```cpp
volatile byte anguloRecibido = 90;
volatile byte velRecibida = 255;
volatile bool actualizarMotores = false;
```

The function handling incoming data simply captures transmitted values and sets a flag signal, allowing physical motor activation to occur within the main loop (`loop()`) to avoid freezing I2C communication:

```cpp
void recibirDatosI2C(int cuantosBytes) {
  if (cuantosBytes >= 2) {
    anguloRecibido = Wire.read();    
    velRecibida = Wire.read(); 
    actualizarMotores = true; // Notifies main loop
  }
}
```

##### 2. Progressive Launch Algorithm (`arrancarSuave`)
When launching the car from rest, the electric motor demands an initial current peak (*inrush current*) that can cause electrical noise on the power supply line. The slave firmware prevents this by stepping up speed incrementally over microseconds:

```cpp
void arrancarSuave() {
  digitalWrite(pinB, LOW);
  for (int vel = 0; vel <= velRecibida; vel++) {
    analogWrite(pinA, vel);
    delayMicroseconds(3921); // Acceleration ramp ~1 second total
  }
}
```

### Master Code Analysis (`src/current/nano_master.cpp`)

The Master microcontroller serves as the primary brain: it analyzes surroundings via sensors, measures car turns, manages mode changes, and computes the adjustments required to maintain the ideal path.

---

#### Digital Filtering: Exponential Moving Average (EMA)

To eliminate wheel chatter on straightaways without overloading the processor with complex list-sorting routines, we implemented a data smoothing filter (EMA).

**Mathematical Formulation:**
$$y[k] = \alpha \cdot x[k] + (1 - \alpha) \cdot y[k-1]$$

Where:
* $x[k]$ represents the raw reading obtained by the sensor at current time step $k$.
* $y[k-1]$ is the filtered distance calculated in the previous iteration.
* $\alpha = 0.4$ is the smoothing factor configured through practical testing.

**Spatial Zero Handling (0 cm = 180 cm):**
When the wall disappears at an intersection, the ultrasonic sensors return a value of 0 cm due to echo loss. We interpret this as completely open space by assigning it a theoretical distance of 180.0 cm, avoiding division-by-zero errors or false corrections:

```cpp
float filtrarLectura(float lecturaCruda, float lecturaAnterior) {
  float lecturaProcesada = lecturaCruda;
  if (lecturaCruda <= 0.0) {
    lecturaProcesada = 180.0; // Open space at corner
  }

  // If open space is detected (> 70 cm), allow fast response
  if (lecturaProcesada > 70.0) {
    return lecturaProcesada; 
  }

  // EMA smoothing for fine navigation near walls
  float alpha = 0.4;
  return (alpha * lecturaProcesada) + ((1.0 - alpha) * lecturaAnterior);
}
```

### MPU6050 Gyroscope Inertial Integration

Unlike previous versions, turns in the current version do not rely on bouncing waves off non-existent walls. We calculate rotation by continuously integrating the angular velocity ($\omega_z$) measured by the MPU6050 motion sensor over the I2C connection (address `0x68`):

**Rotation Angle Calculation:**
$$\theta_z = \sum \left( \frac{\text{giroZ}}{131.0} \right) \cdot \Delta t$$

Where the value 131.0 LSB/(°/s) corresponds to the sensitivity scale of ±250°/s configured on the MPU6050 sensor.

```cpp
// In the loop inside CURVA state
float giroZ = (leerGiroscopioZ() - offsetZ) / 131.0; 
anguloZ_acumulado += (giroZ * dt);

if (abs(anguloZ_acumulado) >= ANGULO_OBJETIVO) { // ANGULO_OBJETIVO = 72.0°
  estadoActual = COOLDOWN;
  tiempoInicioCooldown = millis();
}
```

### Finite State Machine and Track Logic

* **Track Direction Memory (`sentidoPista`):** During the first turn of the run (`sentidoPista == 0`), the vehicle analyzes which side offers a larger opening and permanently records the circuit direction. Once assigned, the remaining 11 corners of the run read directly from `sentidoPista`, ignoring erroneous readings caused by acoustic reflections.

#### PD Controller with Deadband (Blue Zone)

In `RECTA` mode, the vehicle stays centered between both walls by measuring the centering difference $e(t)$:

$$e(t) = \frac{\text{distRight} - \text{distLeft}}{2}$$

**Blue Zone Filter (±5 cm):**
To prevent unnecessary corrections caused by wall imperfections or textures on the track, a deadband of ±5 cm is applied:

```cpp
const float ZONA_AZUL = 5.0; 
float error = 0; 

if (abs(distancia_al_centro) <= ZONA_AZUL) {
  error = 0; 
}
else {
  if (distancia_al_centro > 0) error = distancia_al_centro - ZONA_AZUL; 
  else error = distancia_al_centro + ZONA_AZUL;
}
```

**Proportional-Derivative Equation:**
$$u(t) = K_p \cdot e(t) + K_d \cdot \frac{e(t) - e(t-\Delta t)}{\Delta t}$$

* **Proportional Gain ($K_p = 10.33$):** Responds to the magnitude of the vehicle's off-center offset.
* **Derivative Gain ($K_d = 14.0$):** Dampens lateral oscillation by predicting the velocity at which the car approaches the wall.
* **Strict Steering Limit:** The output $u(t)$ is bounded to ±15° around the steering servo's neutral point (92°), restricting the physical steering angle to a window between 57° and 127°.

---

### Code Maintainability and Track Parameter Guide

To streamline the calibration process in the pit area, key dynamic parameters are centralized on lines 22 through 35 of `src/current/nano_master.cpp`:

```cpp
// CRITICAL PARAMETERS TO CALIBRATE ON TRACK
const float DIST_DETECCION_FRONT = 75.0; // Distance (cm) to initiate turn
const float ANGULO_OBJETIVO = 72.0;       // Real MPU6050 degrees to complete corner
const unsigned long TIEMPO_COOLDOWN = 1200;// Immunity window after exiting corner (ms)

// CONTROL CONSTANTS
float Kp = 10.33;  // Proportional Gain for centering
float Kd = 14.0;   // Derivative Gain for centering
```

---

## Deployment and Track Operation Guide

In a fast-paced competition environment like WRO, reaction speed in the pit area is as decisive as the code running on the car. A last-minute tweak or battery swap must not turn into a mess of tangled cables or compilation errors due to missing dependencies.

This field guide allows any team member or evaluator to quickly, safely, and repeatably compile, test, and deploy the software for Meteoro (v2.0).

---

### 1. Pre-Compilation Prerequisites

Before plugging USB cables into the pit computer, ensure the development environment contains the exact tools and libraries used during our performance testing.

**Development Environment (IDE)**
* **Arduino IDE 2.x (Primary Environment):** We recommend Arduino IDE version 2.0 or higher for its integrated serial monitor, real-time code completion, and live variable inspection.
* **PlatformIO (VS Code):** For team members who prefer working from the command line or using advanced version control with Git, the project includes a fully prepared PlatformIO configuration.

**Required Libraries and Dependency Management**
Make sure to install the following libraries via the Arduino IDE Library Manager (`Ctrl + Shift + I` / `Cmd + Shift + I`) before compiling the code:
* **`Servo.h` (Native Library):** Drives PWM signal output (at 50 Hz) to control the Ackermann steering servo motor on the Slave board.
* **`Wire.h` (Native Library):** Enables real-time communication at 100 kHz over the I2C bus between the Master microcontroller (Address `0x00`) and the Slave (Address `0x08`).
* **`Pixy2.h` (By Charmed Labs):** Handles configuration and SPI data transfers for the PixyCam2 vision sensor, responsible for visual signal recognition on the track.
* **`NewPing.h` (By Tim Eckel):** Optimizes distance measurements from the three RCWL-1601 ultrasonic sensors, eliminating blocking delays caused by standard `pulseIn()` calls.

---

### 2. Firmware Flashing Steps (Pit Workflow)

Because the vehicle uses a dual microcontroller architecture, firmware must be uploaded independently to each Arduino Nano board.

**Step 1: Flashing the Arduino Nano Master**
1. Connect the Arduino Nano Master board to the computer using the primary Mini-USB cable.
2. Open the development environment and load the project file: `src/current/first_challenge/master_nano.ino`
3. In the IDE **Tools** menu, configure the following settings:
   * **Board:** Arduino Nano
   * **Processor:** ATmega328P (If uploading fails, switch to *ATmega328P (Old Bootloader)*)
   * **Port:** Select the assigned serial port (e.g., `COM3` on Windows or `/dev/ttyUSB0` on Linux/macOS).
4. Click **Upload** (`Ctrl + U`).
5. Open the Serial Monitor at 115200 baud to confirm that the MPU6050 orientation sensor completes its initial Z-axis calibration.

**Step 2: Flashing the Arduino Nano Slave**
1. Disconnect the Mini-USB cable from the Master board and connect it to the Arduino Nano Slave (actuator node).
2. Open the project file: `src/current/first_challenge/slave_nano.ino`
3. Verify that the selected board remains Arduino Nano with the correct processor setting.
4. Click **Upload** (`Ctrl + U`).
5. Once flashing completes, reconnect the internal power cables.

> **Safety Note:** Temporarily disconnect the main 3S power battery pack while flashing firmware over USB to prevent accidental motor startup on the workbench.

---

### 3. Pre-Track Protocol (Pit Stop Checklist)

To ensure operational stability during official competition runs, the team strictly follows the protocol detailed in the repository file: `pit_stop_checklist.md`.

Key checklist items to review at the pit table before moving Meteoro (v2.0) to the starting area:
* **3S Battery Voltage:** Multimeter reading  $\ge 11.8\text{ V DC}$.
* **Servo Mechanical Adjustment:** Verify centered steering at 90°.
* **Transducer Cleaning:** Wipe dust off the ultrasonic sensors.
* **I2C Bus Test:** Ensure SDA/SCL wiring connections are secure.
* **IMU Calibration:** Place the car on a flat surface before powering on (wait 5 seconds).

---

### 4. Race Run Routine

1. **Positioning:** Place Meteoro (v2.0) inside the 30 cm × 20 cm starting box, aligned parallel to the outer wall.
2. **Logic and Power Activation:** Switch on the main 3S power switch.
3. **Calibration Wait:** Observe the status LED on the Master board until the gyroscope completes its inertial reference calibration.
4. **Launch:** Press the start button. The car executes the `arrancarSuave()` function on the Slave board and begins its autonomous run.

---

### 5. Quick Troubleshooting Guide

| Track Symptom | Probable Cause | Immediate Pit Solution |
| :--- | :--- | :--- |
| **Car does not turn at the first corner** | MPU6050 gyroscope reading failure or frozen I2C bus. | Check SDA/SCL cables and restart the car while keeping it stationary. |
| **Unstable turn / Weaving on straightaways** | Proportional Gain $K_p$ too high or sensor noise. | Adjust $K_p = 10.33$ to $8.5$ in the parameter section of `master_nano.ino`. |
| **Servo motor chatters or loses torque** | Voltage drop on Channel 2 Buck Regulator. | Charge or replace the 3S battery pack. |
| **"Board not found" error during flash** | Incorrect COM port or missing USB chip driver (CH340). | Switch processor setting in the IDE to *ATmega328P (Old Bootloader)*. |

---

## Engineering Logbook and Solved Challenges

During the testing phases of our vehicle Meteoro, the team identified and resolved several technical issues that compromised the stability and precision of the autonomous system. Below, we present the detailed history of the challenges faced and the engineering solutions applied.

---

### Technical Challenges and Implemented Solutions

#### 1. Resets Caused by Sudden Voltage Drops (Brownout)
* **Diagnosis:** When starting the main electric motor, consumption peaks were generated that caused the circuit voltage to drop below 4.5 V. This sudden drop caused unexpected resets of the ATmega328P microcontroller.
* **Solution:** We incorporated a dedicated DSN-MINI-360 Buck voltage regulator to supply a constant, clean 5.0 V exclusively to the entire logic section of the circuit.

#### 2. Interference Between Ultrasonic Sensors (Cross-Talk)
* **Diagnosis:** When emitting `TRIG` pin signals simultaneously across multiple RCWL-1601 sensors, the sound waves bounced back at the same time and interfered with each other, causing a sensor to falsely record the echo sent by a neighboring sensor.
* **Solution:** We established a turn-by-turn measurement schedule, leaving a 15 ms delay between triggers for each sensor. Additionally, we filtered data by taking the median of groups of 4 readings to discard outliers.

#### 3. Steering Adjustment Lockup Due to Error Accumulation (Integral Windup)
* **Diagnosis:** During prolonged turns, the accumulated sum of small deviations locked the `suma_errores` variable at its maximum value. This caused the front wheels to get stuck at an angle when attempting to return to a straight line.
* **Solution:** We set a maximum cap (`LIMITE_INTEGRAL = 1000.0`) to prevent the value from growing excessively and added an instruction to reset the `suma_errores` variable to zero right after completing each turn.

#### 4. Loss of Synchronization in Serial Messages (UART)
* **Diagnosis:** In initial testing, data transmitted between the Master and Slave Arduinos lost the byte arrival sequence, resulting in uncoordinated and unstable movements in the motors and steering.
* **Solution:** We structured a clear message format by assigning a start symbol (`<`), the primary command, and an end symbol (`>`), verifying data validity using a checksum.

---

## Bill of Materials

The selection of components for the Meteoro (v2.0) autonomous vehicle was based on guaranteeing electrical stability, low weight, and rapid response during the run. The following table presents the electronic and mechanical elements used in the prototype, indicating the quantity used, their function within the distributed system, and the link to their datasheet stored in the local folder `docs/datasheets/`.

---

### General Table of Components and Datasheets

| Component | Quantity | Technical Function in Meteoro (v2.0) | Datasheet |
| :--- | :---: | :--- | :---: |
| **Arduino Nano (ATmega328P)** | 2 | **Distributed Processing:**<br>• *Master:* Responsible for reading sensors (RCWL-1601, MPU-6050, PixyCam2) and calculating path corrections (PD control).<br>• *Slave:* Generates electrical PWM signals to control the main motor and steering servo motor. | [Datasheet](docs/datasheets/arduino_nano.PDF) |
| **DSN-MINI-360 Buck Regulator** | 2 | **Isolated Power Regulation:**<br>• *Channel 1:* Steps down main voltage from 11.1 V - 12.6 V to a stable ~5.0 V for logic and sensors.<br>• *Channel 2:* Supplies an independent 5.0 V to the servo motor to prevent sudden power drops to the microcontrollers. | [Datasheet](docs/datasheets/buck_converter_mini_360_dc.pdf) |
| **L298N H-Bridge** | 1 | **Power Module for Drive:**<br>Amplifies current and allows changing the rotation direction of the main 11.1 V DC motor. | [Datasheet](docs/datasheets/control_driver_bridge_h_l298n.PDF) |
| **MPU-6050 Gyroscope / Accelerometer** | 1 | **Inertial Navigation:**<br>Measures vertical-axis yaw rate ($\omega_z$) via the I2C bus to software-calculate precise actual 72° turns. | [Datasheet](docs/datasheets/gyroscope_mpu-6050.md) |
| **RCWL-1601 Ultrasonic Sensor** | 3 | **Environment Reading:**<br>Measures wall distance (Left, Front, and Right) by firing sound bursts at 5.0 V. | [Datasheet](docs/datasheets/ultrasonic_sensor_rcwl-1601.md) |
| **AD002 Servo Motor** | 1 | **Steering Control:**<br>Metal-geared servo configured to adjust front wheels according to the Ackermann steering system. | [Datasheet](docs/datasheets/servo_motor_ad002.md) |
| **Yellow TT DC Motor** | 1 | **Rear Wheel Drive:**<br>DC motor connected to transmission with 90° bevel gears (1:1.5 speed ratio). | [Datasheet](docs/datasheets/tt_motor.md) |
| **3S Li-ion Lithium Batteries** | 3 | **Primary Power Source:**<br>Set of 3 lithium cells in series (11.1 V nominal / 12.6 V fully charged) to power both motors and regulators. | [Datasheet](docs/datasheets/battery_3s.pdf) |

---

### Notes on Organization and Technical Files

The files linked in the **Datasheet** column are part of the static project documentation and are stored in the folder: [`docs/datasheets/`](docs/datasheets/).

---

## Modules and Direct Links

* **Prototype Firmware:** [`src/`](src/)
* **Pinout Table:** [`schematics/`](schematics/)
* **Pit Checklist:** [`docs/`](docs/)

---

## Photographic and Multimedia Registry

### Vehicle Views (WRO Mandatory)

The 5 mandatory photographs are available in the `photos/vehicle/` folder:

* **Front View:** `photos/vehicle/front_view.jpg`
* **Rear View:** `photos/vehicle/rear_view.jpg`
* **Left Side View:** `photos/vehicle/left_view.jpg`
* **Right Side View:** `photos/vehicle/right_view.jpg`
* **Top View:** `photos/vehicle/top_view.jpg`
* **Bottom View** `photos/vehicle/bottom_view.jpg`

---

### Video Demonstration (YouTube)

* **Open Challenge Video:** [Open Challenge Course](https://youtu.be/mJ1lY1bOVQc)

---

## License

This project is distributed under the **MIT** license. See the `LICENSE` file for more details.

---

<div align="center">

© 2026 **The Pits JO** — Jesús Obrero Technical Institute.  
All rights reserved. Distributed under the [MIT License](LICENSE).

</div>
