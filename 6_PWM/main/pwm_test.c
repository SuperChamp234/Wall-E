// C Headers
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Components
#include "sra_board.h"

// Select the mode needed by uncommenting its definition
#define MODE NORMAL_MODE

void pwm_task(void *arg)
{

	motor_handle_t motor_a_0;
	motor_handle_t motor_a_1;
	ESP_ERROR_CHECK(enable_motor_driver(&motor_a_0, MOTOR_A_0));
	ESP_ERROR_CHECK(enable_motor_driver(&motor_a_1, MOTOR_A_1));

	// Make the Motors go forward & backward alternatively, at different PWM from 20 to 100 using a ramp function
	while (1)
	{
		//first increase the PWM from 20 to 100 ramping up
		for (int i = 20; i <=  70; i++)
		{
			set_motor_speed(motor_a_0, MOTOR_FORWARD, i);
			set_motor_speed(motor_a_1, MOTOR_FORWARD, i);
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}
		//then decrease the PWM from 100 to 20 ramping down
		//add some delay between the two ramps
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		for (int i = 70; i >= 20; i--)
		{
			set_motor_speed(motor_a_0, MOTOR_FORWARD, i);
			set_motor_speed(motor_a_1, MOTOR_FORWARD, i);
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}
		//add some delay between the two ramps
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	// Basic Function for task creation
	xTaskCreate(&pwm_task, "pwm_task", 4096, NULL, 1, NULL);
}
