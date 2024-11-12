/*
 * config_ports.h
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_INIT_SYSTEM_CONFIG_PORTS_H_
#define SF_APP_BLE_INIT_SYSTEM_CONFIG_PORTS_H_

//#define PORT_INT_4                               WICED_P04
//#define PORT_INT_14                              WICED_P14	/* Boton de tag vehiculo comentado */
//#define PORT_INT_13                              WICED_P13
//#define PORT_INT_26                              WICED_P26
#define PORT_INT_14                              WICED_P00    /* Boton de placa CYW9208EVB-02 */

//#define LED_GPIO_00                              WICED_P00
#define LED_GPIO_01                              WICED_P01
#define LED_GPIO_02                              WICED_P02
#define LED_GPIO_03                              WICED_P03
#define LED_GPIO_04                              WICED_P04
#define LED_GPIO_05                              WICED_P05
#define LED_GPIO_06                              WICED_P06
#define LED_GPIO_07                              WICED_P07
#define LED_GPIO_08                              WICED_P08
//#define LED_GPIO_11                              WICED_P11
//#define LED_GPIO_13                              WICED_P13
//#define LED_GPIO_14                              WICED_P14
//#define LED_GPIO_16                              WICED_P16
//#define LED_GPIO_17                              WICED_P17
//#define LED_GPIO_25                              WICED_P25
#define LED_GPIO_P26                              WICED_P26



extern void button_cback_26( void *data, uint8_t port_pin );
extern void button_cback_4( void *data, uint8_t port_pin );

extern void gap_out_f(void);


#endif /* SF_APP_BLE_INIT_SYSTEM_CONFIG_PORTS_H_ */
