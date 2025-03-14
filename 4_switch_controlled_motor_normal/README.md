---
title: Switch Controlled Motor (Normal Mode)
---

# Switch Controlled Motor (Normal Mode)

## About the Project

### Motor Driver Modes

The SRA board is equipped with two TB6612FNG motor drivers, enabling control of up to four motors. Each driver can independently operate two motors and supports two modes of operation: **Normal Mode** and **Parallel Mode**.

This project focuses on the **Normal Mode** configuration.

#### Normal Mode

<p align="center">
  <img width="460" height="300" src="./normal_mode.jpeg" alt="Normal Mode Motor Driver Configuration">
</p>

- Each TB6612FNG motor driver can control two motors, using two GPIO pins per motor (IN1 and IN2).
- With two drivers, up to four motors can be controlled using eight GPIOs from the ESP32.
- Example:
  - If **IN1 = HIGH (Pin 32)** and **IN2 = LOW (Pin 33)**, Motor 1 moves forward.

#### Motor Control Table

| IN1 (Pin 32) | IN2 (Pin 33) | Motor Action         |
|-------------|--------------|----------------------|
| HIGH        | HIGH         | Move Motor Forward   |
| HIGH        | LOW          | Move Motor Forward   |
| LOW         | HIGH         | Move Motor Backward  |
| LOW         | LOW          | Stop Motor           |

> 📝 Note: The above table illustrates how the switch-controlled normal mode algorithm determines motor behavior based on GPIO states.

- In **Normal Mode**, each motor channel can supply up to **1.2A current**, allowing full 4-motor control through the board.

---

## Working

- Activates GPIO switches to receive input from the **Line Sensor Array (LSA)**.
- Enables one of the two **TB6612FNG motor drivers**.
- Uses LSA readings to determine motor behavior.
- Drives the motors in **Normal Mode** based on LSA input logic.
