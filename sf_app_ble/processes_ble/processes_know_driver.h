/*
 * processes_know_driver.h
 *
 *  Created on: 22 nov 2023
 *      Author: Usuario1
 */

#ifndef SF_APP_BLE_PROCESSES_BLE_PROCESSES_KNOW_DRIVER_H_
#define SF_APP_BLE_PROCESSES_BLE_PROCESSES_KNOW_DRIVER_H_

#include "wiced_bt_ble.h"
#include "wiced_timer.h"
#include "wiced_bt_trace.h"
#include <string.h>
#include "wiced_hal_gpio.h"
#include "config_ports.h"
//#define RSSI_DRIVER 70
#define SIZE 3

BD_ADDR  bdaddr_driver;    // Adress of the bluetoot

uint8_t 	safe_macs, array_mac[SIZE];
int8_t 		array_rssi, send_flag=0;
int 		minor_lamp_rssi=0, position=0;
extern 		uint8_t status_driver;

void Know_driver(wiced_bt_ble_scan_results_t *p_scan_result);
void errace_data(void);
void send_again(void);

extern 			   void start_TimerDriver(void);
extern 			   void start_DropDriver(void);
extern 			   void start_Re_in(void); /* Send Twies the mac to wifi */
extern 			   void stop_Re_in(void); /* Send Twies the mac to wifi */

#endif /* SF_APP_BLE_PROCESSES_BLE_PROCESSES_KNOW_DRIVER_H_ */
