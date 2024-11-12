/*
 * processes_timers.h
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_PROCESSES_BLE_PROCESSES_TIMERS_H_
#define SF_APP_BLE_PROCESSES_BLE_PROCESSES_TIMERS_H_

wiced_bool_t status_Online = WICED_TRUE;
wiced_bool_t value_inspection=WICED_TRUE;
wiced_bool_t value_le = WICED_FALSE;
wiced_bool_t value_rst = WICED_TRUE;

extern wiced_bool_t value_gap;
extern wiced_bool_t value_AL;
extern wiced_bool_t value_AV;
extern wiced_bool_t value_alrm;
extern wiced_bool_t value_p1;
extern wiced_bool_t value_pV1;

extern wiced_bool_t gap_t1;
extern wiced_bool_t value_gap;

extern wiced_bool_t value_EA;

void                            f_timer_Online( uint32_t data );
void                            f_timer_st_Online( uint32_t data );
void                            f_timer_inspection( uint32_t data );
void                            f_timer_contM( uint32_t data );
void                            f_clear( uint32_t data );
void                            f_clear10( uint32_t data );
void                            f_gap( uint32_t data );
void                            f_timer_return( uint32_t data );
void                            f_timer_returnfA( uint32_t data );
void                            f_timer_returnfAV( uint32_t data );
void                            f_timer_returnfB( uint32_t data );
void                            f_timer_alrm( uint32_t data );
void                            f_timer_EA( uint32_t data );
void                            f_timer_er( uint32_t data );
void                            f_timer_ach( uint32_t data );
void                            f_timer_CER( uint32_t data );

void      						f_timer_driver( uint32_t data );
void      						f_drop_timer( uint32_t data );
void      						f_delete_timer( uint32_t data );
void      						f_send_again( uint32_t data ); /* ************** */
extern void		                send_passenger(void);
extern void						stop_TimerPasenger(void);

extern void start_TOnline(void);
extern void start_TOnline_long(void);
extern void prevention_status(void);
extern void prevention_status2(void);
extern void clear_cont(void);
extern void exam_gpio(void);
extern void clear_SB01(void);
extern void clear_SB10(void);
extern void gap_transferA(void);
extern void gap_transferB(void);
extern void start_alrm(void);
extern void stop_alrm(void);
extern void print_cst(void);
extern void gap_transferER(void);
extern void evalue_ach(void);
extern void clear_cer(void);
extern void send_passenger(void);  /* ******* */

extern void stop_TimerDriver(void);
extern void stop_DropDriver(void);
extern void errace_data(void);
extern void send_again(void);
extern void stop_TmerDelete(void);

#endif /* SF_APP_BLE_PROCESSES_BLE_PROCESSES_TIMERS_H_ */
