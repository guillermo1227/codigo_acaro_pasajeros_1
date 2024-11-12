/*
 * observe_function.h
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_GAP_SCAN_OBSERVE_FUNCTION_H_
#define SF_APP_BLE_GAP_SCAN_OBSERVE_FUNCTION_H_

      #define clk_radc 20
      #define clk_radc120 120
	  #define NUM_PASAJEROS 4

	  wiced_timer_t timer_radc;
	  void        f_timer_radc( uint32_t data );

	  uint8_t RSSI_CLOSER = 40;
	  uint8_t RSSI_DRIVER = 78;
	  uint8_t status_driver=0;  /* driver */

extern	uint8_t dla;
extern	uint8_t dlb;
extern	uint8_t dtv;

int cont_returnG = 0;
int cont_returnER = 0;
int8_t datacrl=0;
int8_t datacrv=0;
int8_t datac_t =0;
int8_t datac_v =0;
int8_t datac_t2 =0;
int8_t datac_v2 =0;
uint8_t dataFiltC[2];
uint8_t dataFiltCED[2];
uint8_t dataFiltALV[1];

wiced_bool_t value_Adc=WICED_TRUE;
wiced_bool_t value_ac=WICED_TRUE;
wiced_bool_t value_gap=WICED_TRUE;

uint8_t Filt_comand[3] = { 0x4c,0x46,0x42};
uint8_t Filt_comandA[3] = { 0x4c,0x41,0x42};
uint8_t Filt_comanED[3] = { 0x4c,0x41,0x42};
uint8_t Filt_comanED1[3] = { 0x4c,0x41,0x35};

uint8_t Filt_operate1[12] = { 0x4c,0x34,0x53,0x45,0x43};
uint8_t Filt_operate2[12] = { 0x4c,0x41,0x49,0x52,0x44};
uint8_t Filt_operate3[12] = { 0x53,0x4d,0x41,0x52,0x54};
uint8_t Filt_operate20[12] = { 0x31,0x41,0x35,0x45,0x43};
uint8_t Filt_operate30[12] = { 0x31,0x41,0x49,0x52,0x44};
uint8_t Filt_operate40[16] = { 0x4c,0x34,0x53,0x45,0x43,0x5f,0x45,0x41};
uint8_t Filt_operate101[16] = { 0x4c,0x34,0x53,0x45,0x43,0x20,0x42,0x4c};
uint8_t Filt_operate102[16] = { 0x4c,0x41,0x49,0x52,0x44,0x20,0x42,0x4c};
uint8_t Filt_operate103[16] = { 0x53,0x4d,0x41,0x52,0x54,0x5f,0x42,0x45};
uint8_t Filt_SR[16] = {0x4c,0x41,0x49,0x52,0x44,0x5f,0x53,0x52};
uint8_t Filt_GEOSF[16] = {0x47,0x45,0x4f,0x53, 0x46};
uint8_t Filt_ACARO[16] = {0x41, 0x43, 0x41, 0x52, 0x4f};
//----------------------------------------------
uint8_t Filt_operate5[12] = { 0x4c,0x34,0x31,0x52,0x44};
uint8_t Filt_operate6[12] = { 0x4c,0x34,0x53,0x33,0x43};
uint8_t Filt_AB[5] = { 0x4c,0x34,0x31,0x52,0x44};
uint8_t Filt_ggg[5] = { 0x4c,0x34,0x31,0x52,0x44};
//----------------------------------------------


uint8_t Filt_operate4[12]  = {0x04,0x04,0x04,0x04,0x04,0x04};
//uint8_t Filt_operate5[12]  = {0xcd,0x09,0x0a,0x23,0xaa};
//uint8_t Filt_operate6[12]  = {0xCD,0x59,0x48,0xB4,0x43};
uint8_t Filt_operate7[12]  = {0xDB,0xC4,0x88,0x6E,0xC7};
uint8_t Filt_operate8[12]  = {0xEF,0x73,0xE9,0xA2,0xEA};
uint8_t Filt_operate9[12]  = {0x01,0x01,0x01,0x01,0x01};
uint8_t Filt_operate10[12] = {0xEF,0x73,0xE9,0xA2,0xEA};
uint8_t Filt_operate11[12] = {0x01,0x9D,0x6B,0xC2,0x22};
uint8_t Filt_operate12[12]  = {0xC4,0x62,0x04,0xD2,0xB5};
uint8_t Filt_operate13[12]  = {0x34,0x34,0x34,0x34,0x34};
uint8_t Filt_operate14[12]  = {0x01,0x01,0x01,0x09,0x09};
uint8_t Filt_operate15[12]  = {0x01,0x9D,0x6B,0xC2,0x55};
uint8_t Filt_operate16[12]  = {0x01,0x9D,0x6B,0x44,0x44};
uint8_t Filt_operate17[12]  = {0x01,0x01,0x01,0x09,0x09};
uint8_t Filt_operate18[12]  = {0x01,0x9D,0x6B,0xC2,0x24,0xAA};


uint8_t Filt_operate57[12]  = {0xD0,0x40,0xEF,0x4C,0x83,0xC0};
uint8_t Filt_operate58[12]  = {0x70,0x74,0x14,0xC0,0x8D,0x8A};
uint8_t Filt_operate59[12]  = {0x70,0x74,0x14,0xC0,0x90,0xBA};
uint8_t Filt_operate60[12]  = {0x70,0x74,0x14,0xC0,0x99,0xDC};
uint8_t Filt_operate61[12]  = {0xD0,0x40,0xEF,0x4C,0x82,0x18};

uint8_t Filt_operate62[12]  = {0x01,0x01,0x01,0x01,0x01,0x0C};
uint8_t Filt_operate63[12]  = {0x01,0x01,0x01,0x01,0x01,0x08};
uint8_t Filt_operate64[12]  = {0x01,0x01,0x01,0x01,0x01,0x15};
uint8_t Filt_operate65[12]  = {0x01,0x01,0x01,0x01,0x01,0x0D};

uint8_t Filt_operate66[12]  = {0x01,0x9D,0x6B,0xC2,0x1F,0x44};
uint8_t Filt_operate67[12]  = {0x01,0x9D,0x6B,0xC2,0x24,0xB2};
uint8_t Filt_operate68[12]  = {0x01,0x9D,0x6B,0xC2,0x22,0xE8};
uint8_t Filt_operate69[12]  = {0x01,0x9D,0x6B,0xC2,0x24,0x8E};

uint8_t Filt_operate70[12]  = {0xF8,0xC0,0x10,0xC8,0x86,0x55};
uint8_t Filt_operate71[12]  = {0xFD,0xC2,0x83,0x0E,0x3A,0x38};
uint8_t Filt_operate72[12]  = {0x70,0x74,0x14,0xC0,0x99,0xDC};
uint8_t Filt_operate73[12]  = {0x70,0x74,0x14,0xC0,0x90,0xBA};
uint8_t Filt_operate74[12]  = {0x70,0x74,0x14,0xC0,0x8A,0xD8};
uint8_t Filt_operate75[12]  = {0x70,0x74,0x14,0xC0,0x8B,0x30};

uint8_t Filt_operateBL0[12]  = {0x42,0x4C,0x30};
uint8_t Filt_operateBLE[12]  = {0x42,0x4C,0x45};
uint8_t Filt_operateBL1[12]  = {0x42,0x4C,0x31};
uint8_t Filt_operateBLB[12]  = {0x42,0x4c,0x42};

uint8_t Filt_operateBS0[12]  = {0x42,0x53,0x30};
uint8_t Filt_operateBSL[12]  = {0x42,0x53,0x4C};
uint8_t Filt_operateBS1[12]  = {0x42,0x53,0x31};

uint8_t Filt_operateLAB[12]  = {0x4C,0x41,0x42};

uint8_t dataFilt[5];
uint8_t dataFiltPA[5];
uint8_t dataFiltEA[8];
uint8_t dataFiltBC[5];
uint8_t dataFiltLV[5];
uint8_t dataFiltED[5];
wiced_bool_t value_alrm=WICED_TRUE;
wiced_bool_t value_AL=WICED_FALSE;
wiced_bool_t value_AV=WICED_FALSE;

wiced_bool_t value_pin=WICED_TRUE;
wiced_bool_t value_notif = WICED_FALSE;

//-----------------------------------------

wiced_bool_t value_p1=WICED_FALSE;
wiced_bool_t value_pa1=WICED_FALSE;

wiced_bool_t value_pV1=WICED_FALSE;
wiced_bool_t value_paV1=WICED_FALSE;

wiced_bool_t gap_t1=WICED_FALSE;
wiced_bool_t value_ach=WICED_FALSE;
wiced_bool_t value_achV=WICED_FALSE;
wiced_bool_t value_rah=WICED_FALSE;
wiced_bool_t value_onl=WICED_FALSE;
//------------------------------------------
extern wiced_bool_t value_le;
//-----------------------------------------
wiced_bool_t value_EA=WICED_FALSE;
//-----------------------------------------

int8_t st_Tipe;

int8_t datac_menviada=0;
int8_t datac_menviada2=0;

char *dataV_DM[6] ={0};
char *dataV_DM2[6] ={0};


char dataV_SPI[6] ={0};
char datav_dbs[7] ={0};

char datam_buffer[350];
char datam_buffer2[350];
char datam_buffer3[350];
char datam_buffer4[50];   /* Store the passengers' mac */

char datam_bufferdbs[50];
char datam_bufferact[350];

int data_mc3=0;
int data_mc32=0;
int data_mc33=0;

int data_mcdbs=0;
int data_mc3act=0;
int indice =0;

int cc1 = 0;
int cc4 = 0;

int data_pr=0;
int clk_ach=0;

int data_prV=0;
int clk_achV=0;

int8_t datac_m =0;
int8_t datac_m2=0;
int8_t datac_m3=0;

int8_t datac_mdbs=0;
int8_t datac_mact=0;

int8_t datac_st=0;

int8_t datac_pasaj =0;   /* --> llevar el conteo de pasajeros */
int8_t q;		/* Sacar la longituf de mac_pasajeros */
int8_t data_s6 = 0;
char *valor;
char mac_help[6];

typedef struct
{
	char mac_pasajero[6];
	uint8_t out_value;
}pasajeros;
pasajeros T_pasajeros[4];  /* Total de pasajeros */
//---------------------------------------------------------------
//-----------------------------------------------------------------
int8_t datac_comp  =0;
int8_t datac_compV =0;
//-----------------------------------------------------------------
wiced_bool_t value_notifV = WICED_FALSE;

int8_t datac_menviadaV=0;
int8_t datac_menviadaV2=0;

char *dataV_DMV[6] ={0};
char *dataV_DMV2[6] ={0};

char datam_bufferV[350];
char datam_bufferV2[350];
char datam_bufferV3[350];

int data_mc3V=0;
int data_mc3V2=0;
int data_mc3V3=0;

int ccV1 = 0;
int ccV4 = 0;

int8_t datac_mV =0;
int8_t datac_mV2=0;
int8_t datac_mV3=0;

int8_t datac_stV=0;
uint8_t datac_cfbf2[6];
uint8_t datac_fp[6];
//---------------------------------------------------------------

static void        Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data );
void               start_observe(void);
void               init_event_ADC(void);
void               clear_cont(void);
void               stop_process(void);
void               exam_gpio(void);
void               clear_SB01(void);
void               clear_SB10(void);
void               init_event_gap(void);
void               print_cst(void);
void               event_mlfb(void);
void               clear_cer(void);
void               filt_cfb(uint8_t *data_cfb2);
void               send_passenger(void);

extern void gap_cfb(char *data_cfb);
extern void gap_cfbV(char *data_cfbV);

extern             void prevention_status(void);
extern             void prevention_inspection(void);
extern             void gap_transfer(void);
extern             void stop_timer_st_online(void);
extern             void Start_TimerCont(void);
extern             void timer_clr01(void);
extern             void timer_clr10(void);
extern             void beacon_set_app_advertisement_data3(void);
extern             void start_Treturn(void);
extern             void start_TreturnfA(void);
extern             void start_TreturnfAR(void);
extern             void start_TreturnfAV(void);
extern             void start_TreturnfAVR(void);
extern             void start_TreturnfB(void);
extern             void init_gap(void);
extern             void start_alrm(void);
extern             void start_TreturnEA(void);
extern             void init_event_er(void);
extern             void Start_Timerach(void);
extern             void Stop_Timerach(void);
extern             void start_TreturnCER(void);
extern             void timer_sendpassenger(void);

extern			   void Know_driver(wiced_bt_ble_scan_results_t *p_scan_result);

#endif /* SF_APP_BLE_GAP_SCAN_OBSERVE_FUNCTION_H_ */
