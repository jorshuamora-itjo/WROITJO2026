# Pinout and Electronic Connections Table

This document describes the detailed electrical architecture, complete pin mapping for the Arduino Nano boards (Master and Slave), communication buses (I2C and SPI), and the two-channel regulated power distribution network powered by lithium batteries.

---

## 1. Pin Mapping - Arduino Nano Master (Navigation, Vision and Sensors)

The Master Arduino Nano processes visual information from the PixyCam2 via SPI, distance measurements from the three RCWL-1601 ultrasonic sensors and angular data from the MPU6050 gyroscope, executing PID control and calculating the steering setpoint.

| Component / Module | Component Pin | Arduino Nano Pin | Signal Type | Voltage Level | Description / Function |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Left Ultrasonic (RCWL-1601)** | ECHO | D6 | Input | 5.0V Logic | Return pulse duration measurement |
| | TRIG | D7 | Output | 5.0V Logic | Ultrasonic pulse trigger |
| **Right Ultrasonic (RCWL-1601)** | ECHO | D8 | Input | 5.0V Logic | Return pulse duration measurement |
| | TRIG | D9 | Output | 5.0V Logic | Ultrasonic pulse trigger |
| **Front Ultrasonic (RCWL-1601)** | ECHO | D10 | Input | 5.0V Logic | Return pulse duration measurement |
| | TRIG | D11 | Output | 5.0V Logic | Ultrasonic pulse trigger |
| **Gyroscope (MPU6050)** | SDA | A4 (SDA) | I2C Data | 5.0V Logic | Data bus for Z-axis angular velocity estimation |
| | SCL | A5 (SCL) | I2C Clock | 5.0V Logic | I2C clock synchronization (100 kHz) |
| **I2C Interconnection (Slave)** | SDA | A4 (SDA) | I2C Data | 5.0V Logic | Sends angle and speed to Slave Nano (0x08) |
| | SCL | A5 (SCL) | I2C Clock | 5.0V Logic | Shared I2C bus clock |
| **PixyCam2 Camera** | SPI MOSI | D11 / ICSP | SPI Data Out | 5.0V Logic | Control and initialization commands |
| | SPI MISO | D12 / ICSP | SPI Data In | 5.0V Logic | 60 FPS reading of color blocks and signatures |
| | SPI SCK | D13 / ICSP | SPI Clock | 5.0V Logic | High-speed SPI communication clock |
| **Master Logic Power** | 5V / VIN | 5V | Power In | 5.0V Reg. | 5.0V output from DSN-MINI-360 Buck (Channel 1) |
| | GND | GND | Ground | 0V | Unified ground point |

---

## 2. Pin Mapping - Arduino Nano Slave (Actuators)

The Slave Arduino Nano handles commands sent by the Master via I2C, and controls the servomotor and DC motor.

| Component / Module | Component Pin | Arduino Nano Pin | Signal Type | Voltage Level | Description / Function |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Steering Servomotor** | Signal (PWM) | D2 | PWM Output | 5.0V Logic | Angle control for Ackermann steering mechanism |
| **L298N H-Bridge Motor Driver (DC Motor)** | IN1 / A1 | D5 | PWM Output | 5.0V Logic | PWM speed modulation for traction motor |
| | IN2 / A2 | D6 | Output | 5.0V Logic | Rotation direction (Set to LOW for forward motion) |
| **I2C Interconnection (Master)** | SDA | A4 (SDA) | I2C Data | 5.0V Logic | Bus for receiving commands from Master Nano |
| | SCL | A5 (SCL) | I2C Clock | 5.0V Logic | Shared I2C bus clock |
| **Slave Logic Power** | 5V / VIN | 5V | Power In | 5.0V Reg. | 5.0V output from DSN-MINI-360 Buck (Channel 2) |
| | GND | GND | Ground | 0V | Unified ground point |

---

## 3. Power System Architecture and Buck Regulators

The primary power source consists of 3 Series Lithium Batteries (3S) delivering a nominal voltage of 11.1V (up to 12.6V fully charged). Power is distributed through two independent step-down converters (DSN-MINI-360 Buck) to isolate dynamic motor current draw from sensitive digital logic.

| Power Stage / Module | Input Source | Regulated Output | Powered Components |
| :--- | :--- | :--- | :--- |
| **Lithium Batteries (3S Series)** | 3x 3.7V Li Battery | 11.1V - 12.6V Direct | VM power input for TB6612FNG Driver (DC Motor) |
| **DSN-MINI-360 Regulator (Channel 1)** | 3S Lithium Pack | 5.0V DC Reg. | Master Arduino Nano, MPU6050 Gyroscope, 3x US-016, and PixyCam2 |
| **DSN-MINI-360 Regulator (Channel 2)** | 3S Lithium Pack | 5.0V DC Reg. | Slave Arduino Nano, Ackermann Servomotor |
| **Common Ground (GND)** | N/A | 0V (GND) | Common physical ground connection for all boards and sensors |
