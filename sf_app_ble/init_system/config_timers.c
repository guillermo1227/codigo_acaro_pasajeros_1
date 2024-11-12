/*
 * config_timers.c
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
#include "config_timers.h"

wiced_timer_t timer_Online;
wiced_timer_t timer_st_Online;
wiced_timer_t timer_inspection;
wiced_timer_t timer_contM;
wiced_timer_t timer_Clear;
wiced_timer_t timer_Clear10;
wiced_timer_t timer_gap;
wiced_timer_t timer_return;
wiced_timer_t timer_returnfA;
wiced_timer_t timer_returnfAV;
wiced_timer_t timer_returnfB;
wiced_timer_t timer_alrm;
wiced_timer_t timer_EA;
wiced_timer_t timer_er;
wiced_timer_t timer_ach;
wiced_timer_t timer_cer;

wiced_timer_t timer_driver;     //Turn on ligth for indicate the driver
wiced_timer_t timer_count_RSSI; //RSSI
wiced_timer_t timer_drop_driver; //drop driver
wiced_timer_t timer_delete; //delete all passenger
wiced_timer_t timer_send;

/***********************************************************
 * Function name: config_clk_timers
 * Description: calibration data conversion
 ***********************************************************/
void config_clk_timers(void)
{
	wiced_init_timer( &timer_Online, f_timer_Online, 0, WICED_MILLI_SECONDS_TIMER );
    wiced_init_timer( &timer_st_Online, f_timer_st_Online, 0, WICED_MILLI_SECONDS_TIMER );
    wiced_init_timer(&timer_inspection, f_timer_inspection, 0, WICED_SECONDS_TIMER);
    wiced_init_timer( &timer_contM, f_timer_contM, 0, WICED_MILLI_SECONDS_TIMER );
    wiced_init_timer( &timer_Clear, f_clear, 0, WICED_SECONDS_TIMER );
    wiced_init_timer( &timer_Clear10, f_clear10, 0, WICED_SECONDS_TIMER );
    wiced_init_timer( &timer_gap, f_gap, 0, WICED_SECONDS_TIMER );
    wiced_init_timer(&timer_return, f_timer_return, 0, WICED_SECONDS_TIMER);
    wiced_init_timer(&timer_returnfA, f_timer_returnfA, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer(&timer_returnfAV, f_timer_returnfAV, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer(&timer_returnfB, f_timer_returnfB, 0, WICED_SECONDS_TIMER);
    wiced_init_timer(&timer_alrm, f_timer_alrm, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer(&timer_EA,  f_timer_EA, 0, WICED_SECONDS_TIMER);
    wiced_init_timer( &timer_er, f_timer_er, 0, WICED_SECONDS_TIMER );
    wiced_init_timer( &timer_ach, f_timer_ach, 0, WICED_MILLI_SECONDS_TIMER );
    wiced_init_timer( &timer_cer, f_timer_CER, 0, WICED_MILLI_SECONDS_TIMER );

    wiced_init_timer( &timer_driver, f_timer_driver, 0, WICED_MILLI_SECONDS_TIMER );  /* Turn on the led driver */
    wiced_init_timer( &timer_drop_driver, f_drop_timer, 0, WICED_MILLI_SECONDS_TIMER ); /* Timer to left the driver */
    wiced_init_timer( &timer_delete, f_delete_timer, 0, WICED_SECONDS_TIMER); /* Timer to left the driver */
    wiced_init_timer( &timer_send, f_send_again, 0, WICED_SECONDS_TIMER);
}

/***********************************************************
 * Function name: start_BTimers
 * Description: counting timer
 ***********************************************************/
void start_BTimers(void)
{
    wiced_start_timer( &timer_Online, 3000);
    //wiced_start_timer( &timer_st_Online, clock_st_Online);
	wiced_start_timer( &timer_contM, 4000);
	wiced_start_timer( &timer_delete,2);
}


/***********************************************************
 * Function name: start_TOnline
 * Description: activity indicator timer
 ***********************************************************/
void start_TOnline(void)
{
	 wiced_start_timer( &timer_Online, clock_Online);
}

/***********************************************************
 * Function name: start_TOnline_long
 * Description: WiFi module activity checker timer
 ***********************************************************/
void start_TOnline_long(void)
{
	//wiced_start_timer( &timer_st_Online, clock_st_Online);
}

/***********************************************************
 * Function name: stop_TOnline
 * Description: WiFi module activity checker timer
 ***********************************************************/
void stop_TOnline(void)
{
	wiced_stop_timer(&timer_Online);
	wiced_start_timer( &timer_Online, clock_Online_long);
}

/***********************************************************
 * Function name: prevention_inspection
 * Description: calibration data conversion
 ***********************************************************/
void prevention_inspection(void)
{
	  /* if (wiced_init_timer(&timer_inspection, f_timer_inspection, 0, WICED_SECONDS_TIMER) == WICED_SUCCESS)
	    {
		   WICED_BT_TRACE("Init timer inspection\n");
		   wiced_start_timer( &timer_inspection, clock_inspection);
	    }*/
	   WICED_BT_TRACE("Init timer inspection\n");
	   wiced_start_timer( &timer_inspection, clock_inspection);
}

/***********************************************************
 * Function name: stop_timer_st_online
 * Description: stops WiFi module activity checker timer
 ***********************************************************/
void stop_timer_st_online(void)
{
	wiced_stop_timer( &timer_st_Online);
}

/***********************************************************
 * Function name: Start_TimerCont
 * Description: counting timer
 ***********************************************************/
void Start_TimerCont(void)
{
	wiced_start_timer( &timer_contM, 4000);
}

/***********************************************************
 * Function name: timer_clr01
 * Description: timer that clears the first
 *              personnel detection
 ***********************************************************/
void   timer_clr01(void)
{
	wiced_start_timer( &timer_Clear, clock_clear5);
	//wiced_stop_timer( &timer_Online);
	//wiced_start_timer( &timer_Online, clock_Online);
}

/***********************************************************
 * Function name: timer_clr10
 * Description: timer that deletes the first
 *              vehicle stop
 ***********************************************************/
void   timer_clr10(void)
{
	wiced_start_timer( &timer_Clear10, clock_clear5);
	//wiced_stop_timer( &timer_Reportcxn_ncr);
	//wiced_start_timer( &timer_Reportcxn_ncr, clock_cxn_ncr1);
}

/***********************************************************
 * Function name: init_gap
 * Description: starts the timer for boarding request
 ***********************************************************/
void   init_gap(void)
{
	wiced_start_timer( &timer_gap, clock_gap1);
}

/***********************************************************
 * Function name: start_Treturn
 * Description: starts the timer to clear
 *          the risk zone detection alert
 ***********************************************************/
void start_Treturn(void)
{
	wiced_start_timer( &timer_return, clock_return5);
}

/***********************************************************
 * Function name: start_TreturnfA
 * Description: activates proximity alarm timer on personal
 ***********************************************************/
void start_TreturnfA(void)
{
	wiced_start_timer( &timer_returnfA, 1000);
}

/***********************************************************
 * Function name: start_TreturnfAR
 * Description: timer that clears proximity alarm
 *              received from external reader
 ***********************************************************/
void start_TreturnfAR(void)
{
	wiced_start_timer( &timer_returnfA, 6000);
}

/***********************************************************
 * Function name: start_TreturnfAV
 * Description: activates proximity alarm timer on vehicles
 ***********************************************************/
void start_TreturnfAV(void)
{
	wiced_start_timer( &timer_returnfAV, 1000);
}

/***********************************************************
 * Function name: start_TreturnfAVR
 * Description: timer that clears proximity alarm
 *              received from external reader
 ***********************************************************/
void start_TreturnfAVR(void)
{
	wiced_start_timer( &timer_returnfAV, 6000);
}

/***********************************************************
 * Function name: start_TreturnfB
 * Description: starts the timer to clear
 *          the risk zone detection alert
 ***********************************************************/
void start_TreturnfB(void)
{
	wiced_start_timer( &timer_returnfB, 10);
}

/**************************************************************
 * Function name: start_alrm
 * Description: starts the timer that indicates proximity
 * alert detection and activates the flashing signal
 **************************************************************/
void start_alrm(void)
{
	wiced_start_timer( &timer_alrm, clock_alrm);
}

/**************************************************************
 * Function name: stop_alrm
 * Description: stops the timer that indicates the proximity
 *         alert detection and activates the flashing signal
 **************************************************************/
void stop_alrm(void)
{
	 wiced_stop_timer( &timer_alrm);
}

/***********************************************************
 * Function name: start_TreturnEA
 * Description: timer that clears the man down alert
 ***********************************************************/
void start_TreturnEA(void)
{
	wiced_start_timer( &timer_EA, clock_EA);
}

/***********************************************************
 * Function name: init_event_er
 * Description: timer that activates a link request
 *              with the external reader
 ***********************************************************/
void init_event_er(void)
{
	wiced_start_timer( &timer_er, clock_gap1);
}

/***********************************************************
 * Function name: Start_Timerach
 * Description: timer that sends the addressed
 *              devices to the external reader
 ***********************************************************/
void Start_Timerach(void)
{
	wiced_start_timer( &timer_ach, 1000);
}

/***********************************************************
 * Function name: Stop_Timerach
 * Description: stops the timer that sends the addressed
 *              devices to the external reader
 ***********************************************************/
void Stop_Timerach(void)
{
	wiced_stop_timer( &timer_ach);
}

/*************************************************************
 * Function name: start_TreturnCER
 * Description: timer that clears the device count data that
 *              has been detected on the external reader
 *************************************************************/
void start_TreturnCER(void)
{
	wiced_start_timer( &timer_cer, 7000);
}

/*************************************************************
 * Function name: start_TimerDriver
 * Description: timer that init the time of erase of the driver
 *
 *************************************************************/
void start_TimerDriver(void)
{
	wiced_start_timer( &timer_driver, 950);
}

/*************************************************************
 * Function name: stop_TimerDriver
 * Description: timer that stop the time of erase of the driver
 *
 *************************************************************/

void stop_TimerDriver(void)
{
	wiced_stop_timer( &timer_driver);
}

/*************************************************************
 * Function name: start_TimerDriver
 * Description: timer used to start the time to drop the driver
 *
 *************************************************************/
void start_DropDriver(void)
{
	wiced_start_timer( &timer_drop_driver, 900);
}

/*************************************************************
 * Function name: stop_TimerDriver
 * Description: timer used to start the time to drop the driver
 *
 *************************************************************/
void stop_DropDriver(void)
{
	wiced_stop_timer( &timer_drop_driver);
}

void stop_TmerDelete(void)
{
	wiced_stop_timer( &timer_delete);
}


void timer_sendpassenger(void)
{
	wiced_start_timer( &timer_send, 3);
}

void stop_TimerPasenger(void)
{
	wiced_stop_timer( &timer_send);
}
