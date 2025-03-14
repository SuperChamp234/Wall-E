---
title: MPU6050 Sensor
---
# MPU6050

The MPU6050 is a 6-axis motion tracking device that integrates a MEMS gyroscope and accelerometer and communicates via the I2C bus. It is commonly used in embedded systems for tracking motion and orientation.

- **I2C Communication**: The system processor communicates with MPU6050 as an I2C master. Default address is 0x68 (can be changed to 0x69).
- **Auxiliary Master Capability**: MPU6050 can act as an I2C master to external sensors like a compass.
- **Voltage Compatibility**: It is a 3.3V device, directly compatible with ESP32.

![MPU6050 Diagram](https://lh5.googleusercontent.com/zS7Xrh9qRU7qUwhcF6BoJwzG7Pex7cvjD3yFqS_rJA35Nuj-rDkpS9uEt6EjqmGwzEEe3k-jNw2ENILxgxKWGLO5hW6j1er4oaKXk-ciVyrCC4GvzMDzwR9l0u5CrtsNRpAI7LRqf7U)

## Inertial Measurement Unit (IMU)

An IMU is used to detect motion and orientation. It typically includes:
- A **gyroscope** for angular velocity
- An **accelerometer** for linear acceleration
- Optionally, a **magnetometer**

The number of axes across these sensors defines its Degrees of Freedom (DoF). MPU6050 is a 6-DOF IMU (3-axis accelerometer + 3-axis gyroscope).

## Initializing the MPU6050

When powered on, the MPU6050 starts in **SLEEP mode**. To use it:

1. Send a **start condition**
2. Send **device address (0x68)** with write bit
3. Send register address **0x6B (PWR_MGMT_1)**
4. Send **0x00** to disable sleep
5. Send **stop condition**

![Power-Up Procedure](https://lh5.googleusercontent.com/HsUgcO1ojRlHZgbtl1Pyk7aWiUjs1x7XnhI5oYsa8C2gCqAbfqOGpr9fnjk0TBxWHmoIfJEQLqHUqe4Kh3KsjMLKSHAD6jQMsiEwrNyA3KLSeHiNLC3tDjzjAKN_nENu8FMp0tYS60E)

The **0x00** byte clears register 107 (PWR_MGMT_1), disabling SLEEP and CYCLE modes, powering on the sensor.

## Accelerometer

An **accelerometer** measures linear acceleration (in m/s² or g-forces). The MPU6050 uses a **MEMS accelerometer**:
- It has **movable capacitor plates** that change capacitance with movement
- Voltage changes with capacitance → interpreted as acceleration

![MEMS Accelerometer](https://lastminuteengineers.com/wp-content/uploads/arduino/MEMS-Accelerometer-Working.gif)

## Reading Accelerometer Data

Accelerometer values are stored in 6 registers:
- Each axis (X, Y, Z) has **MSB + LSB = 16-bit signed integer**
- These values are **burst-read** from the sensor

![Accelerometer Registers](https://lh4.googleusercontent.com/ePwQEj_TeMRQU83M7t2RsXGJD2q37z-B3kSlcLdU85L4XeKxkefT_fAYHNRpRjGOYI8r0bbQWd64I7emYms9x4ST6jEAdBlcC2wdibE)

## Calculating Euler Angles from Accelerometer

From accelerometer data, **roll and pitch angles** can be computed:

\[ \theta = \arctan\left(\frac{A_{X.OUT}}{A_{Y.OUT}}\right) \]

(Reference: [DigiKey Inclination Sensing](https://www.digikey.com/en/articles/using-an-accelerometer-for-inclination-sensing))

## Gyroscope

A **gyroscope** measures angular velocity (degrees/second). MPU6050 uses a **MEMS gyroscope** that works on the **Coriolis effect**.

[Watch the Coriolis effect explanation](https://www.youtube.com/watch?v=ti4HEgd4Fgo&t=236s)

## Reading Gyroscope Data

Same structure as the accelerometer:
- X, Y, Z axes → each has MSB and LSB = 16-bit signed values
- Sensor output is in raw units
- **Sensitivity = 131 units/°/s** (default scale)
- **Degrees/sec = raw_value / 131**
- Angular displacement obtained by **integrating over time**

![Gyroscope Readout](https://lh3.googleusercontent.com/dQ-SZL7kp5WEnFb-KXFH-FDvF7yv_2J28ycODkipFfFAAMN1lYAk0rPzKg7DaPcNDYk-BdUEJQSzApxxESam_7tnbsIOcLenjofFoUiCpAhsyuMtkWaFMcZPJrK5EMJyX9GCNHSNeeo)

## Complementary Filter

A complementary filter blends gyroscope and accelerometer data:
- **Gyroscope** is accurate short-term but drifts over time
- **Accelerometer** is noisy short-term but stable long-term

Blended output:
\[ \theta = \alpha \cdot (\theta_{gyro}) + (1 - \alpha) \cdot (\theta_{accel}) \]

Typically, \( \alpha \approx 0.96 \) or higher for smoother tracking.

## Reading Register Data

To burst read multiple registers:
1. Send start condition
2. Send device address + write bit
3. Send starting register address (e.g., 0x3B for accel X MSB)
4. Send repeated start + device address + read bit
5. Read successive bytes from device
6. Send NACK after last byte and stop condition

## Function Overview

| Function | Description |
|---------|-------------|
| `i2c_write(reg, data)` | Write data to a given register |
| `i2c_read_burst(start_reg, num_bytes)` | Read multiple sequential registers |
| `read_accel()` | Read accelerometer data and return x, y, z values |
| `read_gyro()` | Read gyroscope data and return x, y, z values |
| `calculate_angles()` | Compute Euler angles from accel/gyro data |

## Code Flowchart

A high-level flow of the code:

```
Start → I2C Init → MPU6050 Init
           ↓
    Read Accel Data → Compute Angles (Roll, Pitch)
           ↓
    Read Gyro Data  → Integrate Gyro Readings
           ↓
   Apply Complementary Filter
           ↓
         Display Output
```