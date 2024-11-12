/*
 * processes_know_driver.c
 *
 *  Created on: 22 nov 2023
 *      Author: Usuario1
 */

#include "processes_know_driver.h"

/**
 * Function name: Know_driver(wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *status_driver)
 *
 * Summary: This function is divided into 3 parts, 1.- detects the lamp that is attached to the vehicle tag and assigns it as the driver.
 * 2.- As long as the driver is within a range of no more than (1.5 m - 2 m) from the vehicle, he will send the information from that lamp.
 * 3.- If the driver goes out of range, the vehicle tag will forget the assigned driver and will be ready to receive another driver.
 *
 * @param wiced_bt_ble_scan_results_t: LE inquiry result type
 * @param uint8_t *: Pointer to driver status
 *
 * @return none
 */
void Know_driver(wiced_bt_ble_scan_results_t *p_scan_result)
{
	if(status_driver == 0)                                                                         /* 1.- Identify the driver */
	{
		status_driver = 1;
		/* Copy the data */
		memcpy(bdaddr_driver,p_scan_result->remote_bd_addr,6);
		WICED_BT_TRACE("KDV|");
		WICED_BT_TRACE("%02X",bdaddr_driver[0]);
		for(int k=1; k<=5; k++)
		{
			WICED_BT_TRACE(":%02X",bdaddr_driver[k]);
		}
		WICED_BT_TRACE("|\n");

		send_flag = 1;
		wiced_hal_gpio_configure_pin( LED_GPIO_03, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);   		/* Process to indicate driver assignment or driver abandonment */
		start_TimerDriver();
		start_DropDriver();		/* Init the timer for take out the driver */
	}
	else if(status_driver == 1 && memcmp(bdaddr_driver,p_scan_result->remote_bd_addr,6)==0)
	{
		start_DropDriver();
	}
}

void errace_data(void)
{
	memset(bdaddr_driver,'\0',6);
	status_driver = 0;
	wiced_hal_gpio_configure_pin( LED_GPIO_03, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);  	/* Process to indicate driver assignment or driver abandonment */
	WICED_BT_TRACE("KDV|NONE\n");   /* The number 40 is just a piece of information to fill out */
	send_flag = 2;
	start_TimerDriver();
}

void send_again(void)
{
	if(send_flag == 1)
	{
		WICED_BT_TRACE("KDV|");
		WICED_BT_TRACE("%02X",bdaddr_driver[0]);
		for(int k=1; k<=5; k++)
		{
			WICED_BT_TRACE(":%02X",bdaddr_driver[k]);
		}
		WICED_BT_TRACE("|\n");
	}
	else if(send_flag == 2)
	{
		WICED_BT_TRACE("KDV|NONE|\n");   /* The number 40 is just a piece of information to fill out */
	}
}
