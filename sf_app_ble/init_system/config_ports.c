/*
 * config_ports.c
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
#include "config_ports.h"


/***********************************************************
 * Function name: set_outPuts
 * Description: output and input pin declaration,
 *              interrupt declaration
 ***********************************************************/
void set_outPuts(void)
{
    /* Configure LED PIN as input and initial outvalue as high */
	//wiced_hal_gpio_configure_pin( LED_GPIO_00, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	wiced_hal_gpio_configure_pin( LED_GPIO_01, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	wiced_hal_gpio_configure_pin( LED_GPIO_02, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	wiced_hal_gpio_configure_pin( LED_GPIO_03, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	wiced_hal_gpio_configure_pin( LED_GPIO_04, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	wiced_hal_gpio_configure_pin( LED_GPIO_05, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
    wiced_hal_gpio_configure_pin( LED_GPIO_06, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
    wiced_hal_gpio_configure_pin( LED_GPIO_07, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
    wiced_hal_gpio_configure_pin( LED_GPIO_08, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
    wiced_hal_gpio_configure_pin( LED_GPIO_P26, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
    //wiced_hal_gpio_configure_pin( LED_GPIO_11, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
	//wiced_hal_gpio_configure_pin( LED_GPIO_13, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	//wiced_hal_gpio_configure_pin( LED_GPIO_14, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	//wiced_hal_gpio_configure_pin( LED_GPIO_16, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	//wiced_hal_gpio_configure_pin( LED_GPIO_17, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	//wiced_hal_gpio_configure_pin( LED_GPIO_25, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW );
	//wiced_hal_gpio_configure_pin( LED_GPIO_26, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_LOW);
	//wiced_hal_gpio_configure_pin(PORT_INT_14, ( GPIO_INPUT_ENABLE | GPIO_PULL_UP_DOWN_NONE | GPIO_EN_INT_FALLING_EDGE ), GPIO_PIN_OUTPUT_HIGH ); /* Boton normal comentado */
    wiced_hal_gpio_configure_pin(PORT_INT_14, ( GPIO_INPUT_ENABLE | GPIO_PULL_UP | GPIO_EN_INT_FALLING_EDGE ), GPIO_PIN_OUTPUT_HIGH );  /* Boton tarjeta de evaluacion CYW verde */
	//wiced_hal_gpio_configure_pin(PORT_INT_26, ( GPIO_INPUT_ENABLE | GPIO_PULL_UP_DOWN_NONE | GPIO_EN_INT_FALLING_EDGE ), GPIO_PIN_OUTPUT_HIGH );
	//wiced_hal_gpio_register_pin_for_interrupt( PORT_INT_13, button_cback_4, 0 );
	wiced_hal_gpio_register_pin_for_interrupt( PORT_INT_14, button_cback_26, 0 );
}


