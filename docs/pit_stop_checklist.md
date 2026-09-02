Before releasing Meteoro onto the track, it's worth reviewing these five points in the pits to avoid surprises or unexpected resets mid-race.

**Pre-Track Checklist (Meteoro v2.0)**

| Check | Control Point | Test Method | Acceptance Criteria | Quick Pit Fix |
| :---: | :--- | :--- | :--- | :--- |
| `[ ]` | **1. 3S Battery** | Measure at XT60 connector with multimeter | Voltage **$\ge 11.8\text{ V DC}$** | Swap for a freshly charged battery |
| `[ ]` | **2. Steering Servo** | Power logic and send 90° signal | Wheels aligned to center | Adjust mechanical linkage or trim |
| `[ ]` | **3. Ultrasonic Sensors** | Clean meshes (Front, Left, Right) | Sensors secure and dust-free | Clean with anti-static brush |
| `[ ]` | **4. I2C Bus** | Check physical fit of SDA/SCL wires | Firm connections without play | Re-seat or replace connectors |
| `[ ]` | **5. IMU Calibration** | Power on with car completely stationary | Wait 5 s to set zero reference | Reboot on a flat surface |

---

**Key Points Step-by-Step**

**1. 3S Battery Voltage**
Measure the voltage directly at the XT60 connector before each run. If the reading drops below 11.8 V (less than 3.93 V per cell), any sudden motor acceleration will trigger a voltage drop (*brownout*) and reset the microcontroller mid-race.

**2. Mechanical Servo Centering**
With the electronics powered on and the signal set to 90°, the front wheels should look straight at a glance. If you notice any deviation, adjust the mechanical pushrod or the servo horn before tweaking code. The hardware should leave the pit table properly aligned.

**3. Cleaning Transducers (RCWL-1601)**
Pit area dust accumulates quickly on the metal meshes of the three ultrasonic sensors. Give them a light brushing and check that the mounts aren't loose; a loose or dirty sensor will pick up false echoes off the walls.

**4. I2C Bus Stability**
Chassis vibrations tend to loosen data (SDA) and clock (SCL) lines. Feel the connectors between the Nano boards and the MPU-6050 IMU to ensure a tight fit. If the I2C bus loses connection while running, orientation readings will freeze.

**5. Inertial IMU Calibration**
Place the vehicle on a firm, level surface before turning on the power switch. Once powered up, do not move the car for at least 5 seconds. The gyroscope needs that time in absolute rest to capture its zero reference and ensure precise 72° turns.
