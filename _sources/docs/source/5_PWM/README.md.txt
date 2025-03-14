---
title: PWM
---

# Pulse Width Modulation

Pulse Width Modulation (PWM) is a square wave signal in which the duration of the high and low phases can be adjusted. It’s commonly used in embedded systems for controlling power to devices such as LEDs and motors.

A typical PWM signal looks like this:

![PWM waveform](https://www.javatpoint.com/embeddedsystem/images/pwm-avr-microcontroller1.png)

### Key Terms:
- **ON-Time:** Duration when the signal is high.
- **OFF-Time:** Duration when the signal is low.
- **Duty Cycle:** Percentage of the total period during which the signal is high.
- **Period:** Total time duration of one complete cycle (ON-Time + OFF-Time).

## Duty Cycle

The duty cycle indicates how much of the time the PWM signal stays in the HIGH state during a cycle. It is calculated using:

![Duty Cycle Formula](https://www.javatpoint.com/embeddedsystem/images/pwm-avr-microcontroller2.png)

![Duty Cycle Examples](https://upload.wikimedia.org/wikipedia/commons/b/b8/Duty_Cycle_Examples.png)

## Period

The period of a PWM signal is the sum of ON-Time (Ton) and OFF-Time (Toff):

![Period Formula](https://www.javatpoint.com/embeddedsystem/images/pwm-avr-microcontroller3.png)

# PWM: Voltage Regulation

By changing the duty cycle of a PWM signal, we can effectively regulate output voltage. This is widely used in:

- Audio signal modulation  
- LED dimming  
- Analog signal generation  
- Switching regulators  
- Motor speed control  

PWM voltage regulation works on the principle of averaging the PWM signal. The output voltage is proportional to the duty cycle:

![Voltage Regulation Formula](https://www.javatpoint.com/embeddedsystem/images/pwm-avr-microcontroller4.png)

# LED Dimmer

PWM is an efficient technique to control LED brightness with minimal energy loss. Instead of wasting energy via resistors, brightness is modulated by varying the ON/OFF duration of the signal.

- **More ON-time → Brighter LED**  
- **More OFF-time → Dimmer LED**

![LED PWM Dimmer](https://exploreembedded.com/wiki/images/5/54/0_LPC1768_PWM.gif)  
![LED Fade Effect](https://makeabilitylab.github.io/physcomp/esp32/assets/movies/Huzzah32_Fade-optimized.gif)

# PWM for Speed Control

PWM can be used to control the speed of DC motors by modulating the average voltage applied to the motor:

- **Higher Duty Cycle → Higher Average Voltage → Faster Motor Speed**
- **Lower Duty Cycle → Lower Average Voltage → Slower Motor Speed**

The motor doesn't respond instantaneously to voltage; hence, a properly tuned PWM signal gives you finer control over speed.

A PWM controller switches power ON/OFF in rapid pulses. By adjusting the pulse width (duration of ON-Time), we effectively vary motor speed.

# Motor Drivers

Motor drivers act as power amplifiers. They take low-current signals from a controller and convert them into higher-current signals required to drive motors.

The driver used in this workshop is **TB6612FNG** — a dual H-Bridge motor driver IC ideal for DC motors.

# Description of Functions Used

### `esp_err_t enable_motor_driver_a(int mode)`

**Description:** Initializes Motor Driver A in either Parallel or Normal mode.

**Parameters:**
- `mode`:  
  - `1` = Parallel Mode  
  - `2` = Normal Mode

**Returns:**  
- `ESP_OK` if initialization successful  
- `ESP_ERR_INVALID_ARG` if an invalid mode is passed

---

### `esp_err_t enable_motor_driver_b(int mode)`

**Description:** Initializes Motor Driver B in either Parallel or Normal mode.

**Parameters:**
- `mode`:  
  - `1` = Parallel Mode  
  - `2` = Normal Mode

**Returns:**  
- `ESP_OK` if initialization successful  
- `ESP_ERR_INVALID_ARG` if an invalid mode is passed

---

### `esp_err_t set_motor_speed(int motor_id, int direction, float duty_cycle)`

**Description:** Sets the speed and direction of the motor.

**Parameters:**
- `motor_id`: Use one of the following: `MOTOR_A_0`, `MOTOR_A_1`, `MOTOR_B_0`, `MOTOR_B_1`
- `direction`: Use one of the following:
  - `MOTOR_FORWARD`  
  - `MOTOR_BACKWARD`  
  - `MOTOR_STOP`
- `duty_cycle`: Duty cycle to be applied via PWM

**Returns:**  
- `ESP_OK` on success  
- `ESP_FAIL` on error

---

### `void vTaskDelay(const TickType_t xTicksToDelay)`

**Description:** Delays a task for a specified number of ticks. You can convert real-time delay using `portTICK_PERIOD_MS`.

**Parameters:**
- `xTicksToDelay`: Number of ticks to delay execution.

---

### `static BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName, uint32_t usStackDepth, void *const pvParameters, UBaseType_t uxPriority, TaskHandle_t *const pvCreatedTask)`

**Description:** Creates a new FreeRTOS task.

**Parameters:**
- `pvTaskCode`: Function pointer to the task logic (must not return)
- `pcName`: Descriptive name (max length defined by `configMAX_TASK_NAME_LEN`)
- `usStackDepth`: Stack size in bytes
- `pvParameters`: Pointer to parameters passed to the task
- `uxPriority`: Priority of the task (add `portPRIVILEGE_BIT` for privileged tasks)
- `pvCreatedTask`: Pointer to store the handle of the created task

**Returns:**  
- `pdPASS` on success  
- Error code from `projdefs.h` otherwise
