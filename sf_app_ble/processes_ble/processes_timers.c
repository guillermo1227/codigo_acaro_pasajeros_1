/*
 * processes_timers.c
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */


#include "wiced_hal_wdog.h"
#include "wiced_hal_rand.h"
#include "wiced_hal_nvram.h"

#include "wiced_bt_trace.h"
//#include "wiced_bt_cfg.h"
#if ( defined(CYW20706A2) || defined(CYW20719B1) || defined(CYW20719B0) || defined(CYW20721B1) || defined(CYW20735B0) || defined(CYW43012C0) )
#include "wiced_bt_app_common.h"
#endif
#include "wiced_bt_stack.h"
#include "wiced_timer.h"
#include "wiced_bt_beacon.h"
#include "string.h"
#include "sparcommon.h"
#include "wiced_rtos.h"
//#include "GeneratedSource/cycfg_gatt_db.h"
#ifndef CYW43012C0
#include "wiced_bt_ota_firmware_upgrade.h"
#endif
#include "wiced_hal_puart.h"
#include "wiced_platform.h"
#include "wiced_transport.h"

#include <malloc.h>

#include "wiced_bt_mesh_models.h"
#include "wiced_bt_mesh_app.h"
#include "wiced_bt_mesh_core.h"
#include "processes_timers.h"
#include "config_ports.h"

/*************************************************************
 * Function name: f_timer_Online
 * Description:   timer that prints the total device count,
 * and verifies the devices addressed
 ************************************************************/
void f_timer_Online( uint32_t data )
{
	if(value_rst == WICED_TRUE)
	{
		value_rst = WICED_FALSE;
		gap_transferA();
	}

	//WICED_BT_TRACE( "BLE Online\n" );
	start_TOnline();
    //wiced_start_timer( &timer_Online, clock_Online);
	exam_gpio();
}

/****************************************************
 * Function name: f_timer_st_Online
 * Description:   check if the WiFi module is active
 ****************************************************/
void f_timer_st_Online( uint32_t data )
{
   if(status_Online)
   {
	   WICED_BT_TRACE( "WiFi: Online\n" );
	   status_Online = WICED_FALSE;
	   start_TOnline_long();
	   //wiced_start_timer( &timer_st_Online, clock_st_Online);
   }
   else
   {
	   /*WICED_BT_TRACE( "PIN HIGTH\n" );
	   wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
	   wiced_rtos_delay_milliseconds( 1000, ALLOW_THREAD_TO_SLEEP );
	   wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	   WICED_BT_TRACE( "PIN LOW\n" );*/
	   status_Online = WICED_FALSE;
	   start_TOnline_long();
	   //wiced_start_timer( &timer_st_Online, clock_st_Online);
   }

}


void      f_timer_inspection( uint32_t data )
{
	extern void gap_out_f(void);
	WICED_BT_TRACE("Enter inspection\n");
	value_inspection =  !value_inspection ? WICED_TRUE : WICED_FALSE;
	WICED_BT_TRACE("Value inspection: %d\n", value_inspection);
    prevention_status2();
    gap_out_f();
}

/****************************************************
 * Function name: f_timer_contM
 * Description:   update the counter
 ****************************************************/
void f_timer_contM( uint32_t data )
{
	//WICED_BT_TRACE("limit\n");
	//datac_menviada=-1;
	clear_cont();
}

/****************************************************
 * Function name: f_clear
 * Description:   clears personnel detection
 ****************************************************/
void    f_clear( uint32_t data )
{
	WICED_BT_TRACE("CLEAAAR \n");
	clear_SB01();
}

/****************************************************
 * Function name: f_clear10
 * Description:   clears vehicle detection
 ****************************************************/
void    f_clear10( uint32_t data )
{
	WICED_BT_TRACE("CLEAAAR 10\n");
	clear_SB10();
}

/****************************************************
 * Function name: f_gap
 * Description:   device boarding notification
 * @parameter     data: data with current time
 ****************************************************/
void      f_gap( uint32_t data )
{
	if(!value_le)
	{
	//WICED_BT_TRACE("GAP TR\n");
	if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_05 ) )
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
		 WICED_BT_TRACE( "GAP A\n\r" );
		 gap_transferA();
		 gap_t1 = WICED_FALSE;

	}
	else
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_HIGH);
		 WICED_BT_TRACE( "GAP B\n\r" );
		 gap_transferB();
		 gap_t1 = WICED_TRUE;
		 value_gap =  WICED_TRUE;
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 print_cst();

	}
	}

}

/****************************************************
 * Function name: f_timer_return
 * Description:   boarding request alert ends
 ***************************************************/
void      f_timer_return( uint32_t data )
{
	WICED_BT_TRACE("Enter return\n");
	gap_transferA();
	//wiced_hal_wdog_reset_system ();
	//beacon_set_app_advertisement_data4();
	wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
    value_gap = WICED_TRUE;
}

/******************************************************************
 * Function name: f_timer_returnfA
 * Description:   Timer for deleting proximity alerts in lamps
 * @parameter     data: data with current time
 ******************************************************************/
void      f_timer_returnfA( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfA\n");
    value_AL=WICED_FALSE;
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
}

/*******************************************************************
 * Function name: f_timer_returnfAV
 * Description: Timer for deleting proximity alerts in vehicles
 * @parameter   data: data with current time
 *******************************************************************/
void      f_timer_returnfAV( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfAV\n");
	  value_AV=WICED_FALSE;
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
}

void      f_timer_returnfB( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfB\n");
	wiced_hal_gpio_set_pin_output( LED_GPIO_03, GPIO_PIN_OUTPUT_LOW);
}

/*******************************************
 * Function name: f_timer_alrm
 * Description: led sequences
 * @parameter   data: data with current time
 *******************************************/
void      f_timer_alrm( uint32_t data )
{
	//WICED_BT_TRACE("Enter ALRM\n");
	start_alrm();
	if(value_AL==WICED_FALSE && value_AV==WICED_FALSE)
	{
		value_alrm=WICED_TRUE;
		if(value_p1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
		}
		if(value_pV1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		stop_alrm();
	}
	else if(value_AL==WICED_FALSE && value_AV==WICED_TRUE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_02 ))
		{
			//WICED_BT_TRACE("Pin 09 LOW\n");
			 //wiced_hal_gpio_set_pin_output( LED_GPIO_14, GPIO_PIN_OUTPUT_LOW);
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 09 HIGH\n");
			//wiced_hal_gpio_set_pin_output( LED_GPIO_14, GPIO_PIN_OUTPUT_LOW);
			wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		if(value_p1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
		}


	}
	else if(value_AL==WICED_TRUE && value_AV==WICED_FALSE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_01 ))
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
			 //wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
			//wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);
		}
		if(value_pV1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}

	}
	else if(value_AL==WICED_TRUE && value_AV==WICED_TRUE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_01 ))
		{
			//WICED_BT_TRACE("Pin 14, 09 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14, 09 HIGH\n");
			wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
	}

}

/****************************************************
 * Function name: f_timer_EA
 * Description: man down alert ends
 ***************************************************/
void      f_timer_EA( uint32_t data )
{
	  value_EA = WICED_FALSE;
	  WICED_BT_TRACE("EA  OFF\n");
}

/****************************************************
 * Function name: f_timer_er
 * Description: notification for reader link
 * @parameter   data: data with current time
 ***************************************************/
void      f_timer_er( uint32_t data )
{

	if(!gap_t1)
	{
	if( value_le == WICED_FALSE )
	{
	 gap_transferER();
	 value_le = WICED_TRUE;
	 //wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	}
	else
	{
		 gap_transferA();
		 value_le = WICED_FALSE;
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	}
	}
}

/***********************************************************
 * Function name: f_timer_ach
 * Description: evaluate the devices addressed
 * @parameter   data: data with current time
 ***********************************************************/
void      f_timer_ach( uint32_t data )
{
	evalue_ach();
}

/***************************************************************
 * Function name: f_timer_ach
 * Description: The time has elapsed to clear device detection
 *               using the external reader
 * @parameter   data: data with current time
 ***************************************************************/
void      f_timer_CER( uint32_t data )
{
	clear_cer();
}

/***************************************************************
 * Function name: f_timer_driver
 * Description: The time has elapsed to clear device detection
 *               using the external reader
 * @parameter   data: data with current time
 ***************************************************************/
void      f_timer_driver( uint32_t data )
{
	 wiced_hal_gpio_configure_pin( LED_GPIO_03, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );  /* Risk Zone P05 */
	 stop_TimerDriver();
	 send_again();
}

/***************************************************************
 * Function name: f_drop_timer
 * Description: The time has elapsed to clear the designated driver
 *
 * @parameter   data: void
 ***************************************************************/
void      f_drop_timer( uint32_t data )
{
	stop_DropDriver();
	errace_data();
}

/***************************************************************
 * Function name: f_delete_timer
 * Description: Delete all passengers register, only when reboot device
 * */
void f_delete_timer( uint32_t data )
{
	WICED_BT_TRACE("DEL\n");
	WICED_BT_TRACE("DEL\n");
	stop_TmerDelete();
}

void f_send_again( uint32_t data )
{
	send_passenger();
	stop_TimerPasenger();
}
