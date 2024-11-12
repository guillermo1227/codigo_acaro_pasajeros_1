/*
 * ports_services.c
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */






#include "wiced_bt_dev.h"
#include "sparcommon.h"

#include "wiced_hal_gpio.h"
#include "wiced_hal_mia.h"
#include "wiced_gki.h"
#include "wiced_platform.h"
#include "wiced_timer.h"
#include "wiced_bt_trace.h"
#include "wiced_hal_puart.h"
#include "wiced_bt_stack.h"
#include "ports_services.h"
#include "config_ports.h"

/*********************************************************************************************
 * Function name: button_cback_26
 * Description:   interruption service for boarding requests
 * @param[in]     data: optional data
 * @param[in]     port_pin: designated pin in the event
 *********************************************************************************************/
void button_cback_26( void *data, uint8_t port_pin )
{
	//WICED_BT_TRACE("\n *************************************************** \n");
	/*if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_06 ) )
	{
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		 WICED_BT_TRACE( "GAP A\n\r" );
		 gap_transferA();
		 gap_t1 = WICED_FALSE;

	}
	else
	{
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
		 WICED_BT_TRACE( "GAP B\n\r" );
		 gap_transferB();
		 gap_t1 = WICED_TRUE;
	}*/
	//stop_process();
	//gap_transfer();
	if(value_gap==WICED_TRUE)
	{
	init_gap();
	}
}

/*********************************************************************************************
 * Function name: button_cback_4
 * Description:   interruption service for boarding requests
 * @param[in]     data: optional data
 * @param[in]     port_pin: designated pin in the event
 *********************************************************************************************/
void button_cback_4( void *data, uint8_t port_pin )
{
	/*if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_13 ) )
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_13, GPIO_PIN_OUTPUT_LOW);
		 WICED_BT_TRACE( "Interrup2 LOW\n\r" );

	}
	else
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_13, GPIO_PIN_OUTPUT_HIGH);
		 WICED_BT_TRACE( "Interrup2 HIGH\n\r" );
	}*/

	WICED_BT_TRACE( "Interrup2 HIGH\n\r" );
	if(value_gap==WICED_FALSE)
	{
	init_event_gap();
	}
	else
	{
		init_event_er();
	}
}

/***********************************************************
 * Function name: init_event_SER
 * Description: interruption service to accept addresses and
 *              to send link requests with external reader
 ***********************************************************/
void init_event_SER(void)
{
	WICED_BT_TRACE( "Interrup2 HIGH\n\r" );
	if(value_gap==WICED_FALSE)
	{
	init_event_gap();
	}
	else
	{
		init_event_er();
	}
}

/*********************************************************************************************
 * Function name: init_event_RAC
 * Description:   interruption service for boarding requests
 *********************************************************************************************/
void init_event_RAC(void)
{
	if(value_gap==WICED_TRUE)
	{
	init_gap();
	}
}
