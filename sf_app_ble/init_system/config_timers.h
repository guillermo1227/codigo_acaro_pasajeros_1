/*
 * config_timers.h
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_
#define SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_


#define clock_Online       1000
#define clock_st_Online    8000
#define clock_Online_long  10000
#define clock_inspection   20
#define clock_clear5	   (5)
#define clock_gap1	        1
#define clock_return5      5
#define clock_alrm         350
#define clock_EA           4




void config_clk_timers(void);
void start_BTimers(void);
void start_TOnline(void);
void start_TOnline_long(void);
void stop_TOnline(void);
void prevention_inspection(void);
void stop_timer_st_online(void);
void Start_TimerCont(void);
void   timer_clr01(void);
void   timer_clr10(void);
void   init_gap(void);
void start_Treturn(void);
void start_TreturnfA(void);
void start_TreturnfAR(void);
void start_TreturnfAV(void);
void start_TreturnfAVR(void);
void start_TreturnfB(void);
void start_alrm(void);
void stop_alrm(void);
void start_TreturnEA(void);
void init_event_er(void);
void Start_Timerach(void);
void Stop_Timerach(void);
void start_TreturnCER(void);
void start_TimerDriver(void); /* Turn on ones the driver led */
void stop_TimerDriver(void);  /* Stop driver led */
void timer_sendpassenger(void);

void start_Re_in(void);  /* Send ones the mac in */
void stop_Re_in(void);  /* Stop ones mac, in and out */
void stop_TmerDelete(void); /* Stop timer delete */
void stop_TimerPasenger(void);

extern void      f_timer_Online( uint32_t data );
extern void      f_timer_st_Online( uint32_t data );
extern void      f_timer_inspection( uint32_t data );
extern void      f_timer_contM( uint32_t data );
extern void      f_clear( uint32_t data );
extern void      f_clear10( uint32_t data );
extern void      f_gap( uint32_t data );
extern void      f_timer_return( uint32_t data );
extern void      f_timer_returnfA( uint32_t data );
extern void      f_timer_returnfAV( uint32_t data );
extern void      f_timer_returnfB( uint32_t data );
extern void      f_timer_alrm( uint32_t data );
extern void      f_timer_EA( uint32_t data );
extern void      f_timer_er( uint32_t data );
extern void      f_timer_ach( uint32_t data );
extern void      f_timer_CER( uint32_t data );

extern void      f_timer_driver( uint32_t data );
extern void      f_drop_timer( uint32_t data );
extern void      f_count_RSSI( uint32_t data );   // Funcion el timer externa
extern void      f_delete_timer( uint32_t data ); /* Timer used to delet passengers */
extern void      f_send_again( uint32_t data );

#endif /* SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_ */
