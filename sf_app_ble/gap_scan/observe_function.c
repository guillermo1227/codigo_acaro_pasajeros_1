/*
 * observe_function.c
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */




#include "wiced_bt_ble.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_mesh_models.h"
#include "wiced_bt_trace.h"
#include "wiced_timer.h"
#include "wiced_bt_mesh_app.h"
#include "wiced_platform.h"
#include "wiced_rtos.h"
#include "wiced_hal_wdog.h"
#include "wiced_hal_rand.h"
#include "wiced_hal_nvram.h"

#ifdef HCI_CONTROL
#include "wiced_transport.h"
#include "hci_control_api.h"
#endif

#include "wiced_memory.h"
#include "wiced_bt_cfg.h"

#include "observe_function.h"
#include "config_ports.h"
#include "wiced_hal_gpio.h"

/******************************************
 * Function name: start_observe
 * Description: start the scanner
 ******************************************/
void    start_observe(void)
{
	wiced_bt_ble_observe (1,0 , Observer_scan_result_cback);
}


/********************************************************************************
 * Function name: Observer_scan_result_cback
 * Description: Main scanner,Lamp and vehicle filterPacket Relay Vehicles
 *              performs device counting, proximity alerts and
 *              data reception from the external reader
 * @parameter   p_adv_data:  url name
 * @parameter   p_scan_result: shows mac address and uuid
 ********************************************************************************/
void Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data )
{
    wiced_result_t         status;
    wiced_bool_t           ret_status;
    uint8_t                length;
    uint8_t                i = 0;
    uint8_t *              p_data;

   	uint8_t *p_name=NULL;
    p_name= &p_adv_data[5];
    uint8_t data_long=NULL;
    data_long=strlen(p_name);

    wiced_bt_device_address_t static_addr;
    wiced_bt_dev_read_local_addr(static_addr );
    uint8_t dataFilt5[6];
    uint8_t dataFiltR[6];
    uint8_t data_flt[6];
    uint8_t dataFilter[3];
    uint8_t dataFilterED[3];
    uint8_t dataFilterED2[3];
    uint8_t dataFiltcer[6];
    uint8_t dataFiltcerMED[6];

    //-----------------------------------------------------------------------------------
    memcpy(dataFilterED, p_name, 3);
    //------------------------------------------------------------------------------
    if(memcmp(Filt_comanED1, dataFilterED, sizeof(dataFilterED))  == 0 ||
       memcmp(Filt_comanED1, dataFilterED, sizeof(dataFilterED))  == 0)
    {
    	/*WICED_BT_TRACE("Data Name ED:");
	    wiced_hal_puart_print(p_name);
	    WICED_BT_TRACE( "\n");*/
    	memcpy(dataFiltcerMED, &p_name[3], 6);

	    if( memcmp(static_addr, dataFiltcerMED, sizeof(dataFiltcerMED)) == 0)
	    {
	    	memcpy(dataFiltCED, &p_name[9], 2);
	    	memcpy(dataFiltALV, &p_name[11], 1);
	    	WICED_BT_TRACE("Data Name ED:");
		    wiced_hal_puart_print(p_name);
		    WICED_BT_TRACE( "\n");
	    	WICED_BT_TRACE("Data mac ED: %B\n", dataFiltcerMED);
	    	WICED_BT_TRACE("DatacrlED1: %d, %d\n",dataFiltCED[0],dataFiltCED[1]);
	    	WICED_BT_TRACE("DatacrlALV: %d\n",dataFiltALV[0]);
	        if(dataFiltCED[0]>0 && dataFiltCED[0]<230)
	        {
				  value_p1=WICED_TRUE;
				  value_pa1=WICED_FALSE;
	  			    if(value_alrm)
	  			    {
	  		        	wiced_hal_gpio_set_pin_output(LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
	  			    }
	        };
	        if(dataFiltCED[1]>0 && dataFiltCED[1]<230)
	        {
				  value_pV1=WICED_TRUE;
				  value_paV1=WICED_FALSE;
  			    if(value_alrm)
  			    {
  		        	wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
  			    }

	        };
	        value_onl=WICED_TRUE;
			start_TreturnCER();

	    }
	    else
	    {
	    	//WICED_BT_TRACE("Return\n");
	    	return;
	    }
    }
    //--------------------------------------------------------------------------
    memcpy(dataFilter, &p_name[6], 3);

    if(memcmp(Filt_comand, dataFilter, sizeof(dataFilter))  == 0 ||
       memcmp(Filt_comandA, dataFilter, sizeof(dataFilter))  == 0)
    {
    	//WICED_BT_TRACE("Data Name ER:");
	    //wiced_hal_puart_print(p_name);
	    //WICED_BT_TRACE( "\n");
	    memcpy(dataFiltcer, &p_name[9], 6);

	    if( memcmp(static_addr, dataFiltcer, sizeof(dataFiltcer)) == 0)
	    {
	    	 memcpy(dataFiltC, &p_name[15], 2);
	    	//WICED_BT_TRACE("Data mac: %B\n", dataFiltcer);
			datacrl=p_name[15];
			//WICED_BT_TRACE("Datacrl: %d\n",datacrl);
	        if(dataFiltC[0]>0 && dataFiltC[0]<230){wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);};
	        if(dataFiltC[1]>0 && dataFiltC[1]<230){wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);};
	        value_onl=WICED_TRUE;
			start_TreturnCER();
	    }
	    else
	    {
	    	//WICED_BT_TRACE("Return\n");
	    	return;
	    }

    }
   //----------------------------------------------------------------------------

    if ( p_scan_result )
    {
    	memcpy(dataFilt5,p_scan_result->remote_bd_addr,6);
    	memcpy(dataFilt, p_name, 5);
         if(p_scan_result->rssi>=-125 //&& memcmp(Filt_operate72, dataFilt5, sizeof(dataFilt5)) == 0
        		 ){
    	if(//value_pin==WICED_TRUE

		   memcmp(static_addr, dataFilt5, sizeof(dataFilt5)) != 0
		    /*memcmp(Filt_operate64, dataFilt5, sizeof(dataFilt5)) == 0 ||
			memcmp(Filt_operate64, dataFilt5, sizeof(dataFilt5)) == 0*/)
    	{
    	   if(memcmp(Filt_operate1, dataFilt, sizeof(dataFilt))  == 0 ||
    	      memcmp(Filt_operate2, dataFilt, sizeof(dataFilt))  == 0 ||
			  memcmp(Filt_ggg, dataFilt, sizeof(dataFilt))  == 0 ||
    	      memcmp(Filt_operate30, dataFilt, sizeof(dataFilt)) == 0 ||
    	      memcmp(Filt_operate20, dataFilt, sizeof(dataFilt)) == 0 )
    	   {//filtro de nombres

    		   memcpy(data_flt,p_scan_result->remote_bd_addr,6);
    		   /* Filtro de macs en Ceros */
    		   if(data_flt[0]<1 || data_flt[1]<1 || data_flt[2]<1 || data_flt[3]<1 || data_flt[4]<1 || data_flt[5]<1)
    		   {
    			   data_flt[0]=0xFF;
    			   data_flt[1]=0xFF;
    			   data_flt[2]=0xFF;
    			   data_flt[3]=0xFF;
    			   data_flt[4]=0xFF;
    			   data_flt[5]=0xFF;
    			   //WICED_BT_TRACE( "Return1\n");
    			   //return;
    		   }
      	      /*WICED_BT_TRACE("BNM:%B,BSF,%d,", p_scan_result->remote_bd_addr, p_scan_result->rssi);
      	      WICED_BT_TRACE( "%B\n", static_addr );
    	      wiced_hal_puart_print(p_name);
    	      WICED_BT_TRACE( "\n");*/
				//WICED_BT_TRACE_ARRAY(datam_buffer, 40, "BUFFER LAMPARAS-");

				//WICED_BT_TRACE_ARRAY(datam_buffer2, 40, "BUFFER LAMPARAS-2");
				//WICED_BT_TRACE_ARRAY(datam_buffer3, 18, "BUFFER LAMPARAS-3");


    	      //----------------------------------------------------------
    	      st_Tipe =
    	      (memcmp(Filt_operate1,  dataFilt, sizeof(dataFilt)) == 0 ? 0x00 :
    	      (memcmp(Filt_operate20, dataFilt, sizeof(dataFilt)) == 0 ? 0x01 :
    	      (memcmp(Filt_operate30, dataFilt, sizeof(dataFilt)) == 0 ? 0x0b :
    	      (memcmp(Filt_ggg,  dataFilt, sizeof(dataFilt)) == 0 ? 0x0a :
    		  (memcmp(Filt_operate2,  dataFilt, sizeof(dataFilt)) == 0 ? 0x0a : 0x14 )))));
    	      //-----------------------------------------------------------
    		  //WICED_BT_TRACE("NUMERO1:%d  \n",st_Tipe);


    	      //------------------------------------------------------------------

    			if(st_Tipe==0x00 || st_Tipe==0x01)
    			{
    				//WICED_BT_TRACE("Numero de lamparas2 xx:%d  \n",datac_m2); //Puesto por mi, aqui no va quitar, descomentar ---->
    			   memcpy(dataV_DM,data_flt,6);
    		   	   char *p_dataDm = strstr(datam_buffer,dataV_DM);
    			   if(!p_dataDm)
    			   {
    				   if( gap_t1 == WICED_FALSE )
    				   {
						  memcpy(&datam_buffer[data_mc3],dataV_DM,6);
						  data_mc3+=6;
						  datac_m++;
						  if(!value_notif)
						  {
							  wiced_hal_gpio_set_pin_output(LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
							  value_p1=WICED_TRUE;
							  value_pa1=WICED_FALSE;
							  //WICED_BT_TRACE("PIN 14 HIGH xx:%d  \n",datac_m);
							  //change_PWM();
						  }

							//WICED_BT_TRACE("No contiene lamparas\n");
						  //wiced_hal_gpio_set_pin_output( LED_GPIO_27, GPIO_PIN_OUTPUT_LOW);
//						 WICED_BT_TRACE("Numero de lamparas xx:%d  \n",datac_m);   //Comentado ---->
//						 WICED_BT_TRACE("Numero de lamparas2 xx:%d  \n",datac_m2); //Comentado ---->
//						 WICED_BT_TRACE("Numero de lamparas3 xx:%d  \n",datac_comp); //Comentado -->
							//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASA");

							//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARASA2");
							//WICED_BT_TRACE_ARRAY(datam_buffer3, 18, "BUFFER LAMPARASA3");
							if(datac_comp>datac_m2)
							{

								memcpy(datam_buffer2,datam_buffer,data_mc3-6);
								datac_m2=datac_m-1;
								data_mc32=data_mc3-6;
								wiced_hal_gpio_set_pin_output(LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
								value_p1 = WICED_TRUE;
								value_pa1=WICED_FALSE;
								//WICED_BT_TRACE("COPEARRRRRRRRRRRRRRRRRRRRR\n");
								//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASA");
								//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARASA2");
							}

	 //--------------------------------------------------------------------------------
					       // WICED_BT_TRACE("DATA1 %d, %d\n", dataFiltC[0], dataFiltC[1]);

					        if(dataFiltCED[0]>230){dataFiltCED[0]=0;};
					        if(dataFiltCED[1]>230){dataFiltCED[1]=0;};
							if(datac_m > datac_menviada)
							{
								datac_v2 = datac_mV - datac_menviadaV2;
								if(gap_t1 == WICED_FALSE)
								{
									if(datac_v2>dataFiltC[1])
									{
										WICED_BT_TRACE("CVL%d,",datac_v2);
									}
									else
									{
										WICED_BT_TRACE("CVL%d,",dataFiltCED[1]);
									}
								}
								else
								{
									WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2); //  SCV1
								}

								datac_t2 = datac_m - datac_menviada2;
								if(gap_t1 == WICED_FALSE)
								{
									if(datac_t2 > dataFiltCED[0])
									{
										WICED_BT_TRACE("%d",datac_t2);
									}
									else
									{
										WICED_BT_TRACE("%d",dataFiltCED[0]);
									}
								}
								else
								{
									WICED_BT_TRACE("%d\n",datac_m - datac_menviada2); //  SCL1
								}

								if( value_AL==WICED_TRUE || value_AV==WICED_TRUE )
								{
									WICED_BT_TRACE(",1\n");
								}
								else
								{
									WICED_BT_TRACE(",0\n");
								}

							}


	 //-----------------------------------------------------------------------------------------
    				   }
    				   else
    				   {
    					        //WICED_BT_TRACE("Fuera del buffer\n");
    				   }
    			   }
    			   else
    			   {
    				   /*if ( GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
    				   {
    				     char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
    				     if(!p_dataDm2)
    				     {
    				     memcpy(&datam_buffer2[data_mc32],dataV_DM,6);
    				     data_mc32+=6;
    				     datac_m2++;
    				     WICED_BT_TRACE("Si contiene lamparas\n");
    				     }
    				   }*/

    				   //------------------------------------------------
    				    if (gap_t1== WICED_TRUE && st_Tipe==0x01 )
						   {
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
							 memcpy(&datam_buffer2[data_mc32],dataV_DM,6);

							 data_mc32+=6;
							 datac_m2++;
							 //WICED_BT_TRACE("Si contiene lamparas\n");
							 //WICED_BT_TRACE("Aumento 1 datac_m2 %d\n",datac_m2);

							 if(datac_pasaj < NUM_PASAJEROS) /* Copiar 4 macs abordadas para mandarlas a wifi */
							 {
								 /* Voy a buscar donde esta disponible para guardar */
								 for(uint8_t i=0;i<4;i++)
								 {
									 if(strlen(T_pasajeros[i].mac_pasajero) == 0)
									 {
										 memcpy(&T_pasajeros[i].mac_pasajero,dataV_DM,strlen(dataV_DM)); /* Copy of mac struct */
										 WICED_BT_TRACE("PCM|%d|",i+1);
										 WICED_BT_TRACE("%02X:%02X",T_pasajeros[i].mac_pasajero[0],T_pasajeros[i].mac_pasajero[1]);
										 WICED_BT_TRACE(":%02X:%02X",T_pasajeros[i].mac_pasajero[2],T_pasajeros[i].mac_pasajero[3]);
										 WICED_BT_TRACE(":%02X:%02X",T_pasajeros[i].mac_pasajero[4],T_pasajeros[i].mac_pasajero[5]);
										 WICED_BT_TRACE("|1|\n");
										 datac_pasaj++;
										 break;
									 }
								 }
							 }

							 }
						   }
    				    else if (value_p1== WICED_FALSE)
    				    {
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
							 memcpy(&datam_buffer2[data_mc32],dataV_DM,6);
							 data_mc32+=6;
							 datac_m2++;
							 //WICED_BT_TRACE("Aumento 2 datac_m2 %d\n",datac_m2);
							 }
    				    }
    				    else if(value_p1 == WICED_TRUE)
    				    {

							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(p_dataDm2)
							 {
    							 char *p_dataDm3 = strstr(datam_buffer3,dataV_DM);
								 if(!p_dataDm3)
								 {
								 memcpy(&datam_buffer3[data_mc33],dataV_DM,6);
								 data_mc33+=6;
								 datac_m3++;
								 //WICED_BT_TRACE("Si contiene lamparasB2\n");
								 }

							 }


    				    }
    				   //------------------------------------------------

    				   //------------------------------------------------
    				   /*if (value_p1== WICED_FALSE)
						   {
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
							 memcpy(&datam_buffer2[data_mc32],dataV_DM,6);
							 data_mc32+=6;
							 datac_m2++;
							 WICED_BT_TRACE("Si contiene lamparas\n");
							 }
						   }*/
    				   //------------------------------------------------

    			   }
    			   timer_clr01();
    			   //WICED_BT_TRACE("RSSI: %d\n",p_scan_result->rssi);
    			   memcpy(dataFiltPA, &p_name[6], 3);

    			   //------Filtro modulo A
    	    	   if(memcmp(Filt_operateBL0, dataFiltPA, sizeof(dataFiltPA))  == 0 ||
    	    	      memcmp(Filt_operateBLE, dataFiltPA, sizeof(dataFiltPA))  == 0 ||
    	    	      memcmp(Filt_operateBL1, dataFiltPA, sizeof(dataFiltPA)) == 0 ||
    	    	      memcmp(Filt_operateBL1, dataFiltPA, sizeof(dataFiltPA)) == 0 )
    	    	   {//filtro A
    			   //---------------------------------------------------------------------------
    			   if(p_scan_result->rssi>=-dla &&  gap_t1 == WICED_FALSE)
    			   {
    					if(datac_m > datac_menviada)
    					{
    						/*if((datac_m - datac_menviada2)!=0)
    						{
    							//WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
    		    			    start_TreturnfA();
    						}*/

							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    			    start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

    					}
    					else
    					{
    						/*if((datac_menviada - datac_menviada2)!=0)
    						{
    							//WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
    		    		        start_TreturnfA();
    						}*/
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    		        start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

    					}

    			   }
    			   //----------------------------------------------------------
    	    	   }
    	    	   //------Filtro modulo B

    			   //------Filtro modulo B
    	           else if(memcmp(Filt_operateBS0, dataFiltPA, sizeof(dataFiltPA)) == 0 ||
    	    	           memcmp(Filt_operateBSL, dataFiltPA, sizeof(dataFiltPA)) == 0 ||
    	    	           memcmp(Filt_operateBS1, dataFiltPA, sizeof(dataFiltPA)) == 0 ||
    	    	           memcmp(Filt_operateBS1, dataFiltPA, sizeof(dataFiltPA)) == 0 )
    	    	   {//filtro B
    			   //---------------------------------------------------------------------------
    			   if(p_scan_result->rssi>=-dlb &&  gap_t1 == WICED_FALSE)
    			   {
    					if(datac_m > datac_menviada)
    					{
    						/*if((datac_m - datac_menviada2)!=0)
    						{
    							//WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
    		    			    start_TreturnfA();
    						}*/

							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    			    start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

    					}
    					else
    					{
    						/*if((datac_menviada - datac_menviada2)!=0)
    						{
    							//WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
    		    		        start_TreturnfA();
    						}*/
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    		        start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

    					}

    			   }
    			   //----------------------------------------------------------
    	    	   }
    	    	   //------Filtro modulo B

    	    	   //-----------Filtro ED
    	    	   memcpy(dataFiltED, &p_name[6], 3);
    	    	   if(memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED))  == 0 ||
    	    	      memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED))  == 0 ||
    	    	      memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED)) == 0 )
    	    	   {
        			   if(p_scan_result->rssi>=-125 &&  gap_t1 == WICED_FALSE)
        			   {
        					if(datac_m > datac_menviada)
        					{
        						/*if((datac_m - datac_menviada2)!=0)
        						{
        							//WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
        		    			    //WICED_BT_TRACE("RSSI FILT\n");
        		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
        		    			    start_TreturnfA();
        						}*/

    							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
    							 if(!p_dataDm2)
    							 {
    	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    	    		    			    value_AL=WICED_TRUE;
    	    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
    	    		    			    //start_TreturnfA();
    	    		    			    start_TreturnfAR();
    	    		    			    if(value_alrm)
    	    		    			    {
    	    		    			   	  value_alrm=WICED_FALSE;
    	    		    			      start_alrm();
    	    		    			    }

    							 }

        					}
        					else
        					{
        						/*if((datac_menviada - datac_menviada2)!=0)
        						{
        							//WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
        		    			    //WICED_BT_TRACE("RSSI FILT\n");
        		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
        		    		        start_TreturnfA();
        						}*/
    							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
    							 if(!p_dataDm2)
    							 {
    	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
    	    		    			    value_AL=WICED_TRUE;
    	    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
    	    		    		        //start_TreturnfA();
    	    		    		        start_TreturnfAR();
    	    		    			    if(value_alrm)
    	    		    			    {
    	    		    			   	  value_alrm=WICED_FALSE;
    	    		    			      start_alrm();
    	    		    			    }

    							 }

        					}

        			   }
    	    	   }
    	    	   //-----------------------------------
    			}

    	      //-------------------------------------------------------------------
      	      //-------------------------------------------------------------------

    			if(st_Tipe==0x0a || st_Tipe==0x0b)
    			{
    			   memcpy(dataV_DMV,data_flt ,6);
    		   	   char *p_dataDmV = strstr(datam_bufferV,dataV_DMV);
    			   if(!p_dataDmV)
    			   {
    				   if( gap_t1 == WICED_FALSE )
    				   {
							  memcpy(&datam_bufferV[data_mc3V],dataV_DMV,6);
							  data_mc3V+=6;
							  datac_mV++;
							  if(!value_notifV)
							  {
								  wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
								  value_pV1=WICED_TRUE;
								  value_paV1=WICED_FALSE;
								  //WICED_BT_TRACE("PIN 04 HIGH xx:%d  \n",datac_mV);
								  //change_PWM();
							  }
							  //WICED_BT_TRACE("No contiene en vehiculos\n");
							  //wiced_hal_gpio_set_pin_output( LED_GPIO_27, GPIO_PIN_OUTPUT_LOW);
		//----------------------------------------------------------------------------------

							//WICED_BT_TRACE("Numero de vehiculos xx:%d  \n",datac_mV);
							//WICED_BT_TRACE("Numero de vehiculos2 xx:%d  \n",datac_mV2);
							//WICED_BT_TRACE("Numero de vehiculos3 xx:%d  \n",datac_compV);
							//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSA");
							//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2");
							if(datac_compV>datac_mV2)
							{

								memcpy(datam_bufferV2,datam_bufferV,data_mc3V-6);
								datac_mV2=datac_mV-1;
								data_mc3V2=data_mc3V-6;
								wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
								value_pV1 = WICED_TRUE;
								value_paV1=WICED_FALSE;
								//WICED_BT_TRACE("COPEARRRRRRRRRRRRRRRRRRRRR2\n");
								//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSA");
								//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2");
							}

		//----------------------------------------------------------------------------------
							 //--------------------------------------------------------------------------------

					        //WICED_BT_TRACE("DATA2 %d, %d\n", dataFiltCED[0], dataFiltCED[1]);

					        if(dataFiltCED[0]>230){dataFiltCED[0]=0;};
					        if(dataFiltCED[1]>230){dataFiltCED[1]=0;};
													if(datac_mV > datac_menviadaV)
													{
														datac_v2 = datac_mV - datac_menviadaV2;
														if(gap_t1 == WICED_FALSE)
														{
															if(datac_v2>dataFiltCED[1])
															{
																WICED_BT_TRACE("CVL%d,",datac_v2);
															}
															else
															{
																WICED_BT_TRACE("CVL%d,",dataFiltCED[1]);
															}
														}
														else
														{
															WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2); //  SCV1
														}

														datac_t2 = datac_m - datac_menviada2;
														if(gap_t1 == WICED_FALSE)
														{
															if(datac_t2 > dataFiltCED[0])
															{
																WICED_BT_TRACE("%d",datac_t2);
															}
															else
															{
																WICED_BT_TRACE("%d",dataFiltCED[0]);
															}
														}
														else
														{
															WICED_BT_TRACE("%d\n",datac_m - datac_menviada2); //  SCL1
														}

														if( value_AL==WICED_TRUE || value_AV==WICED_TRUE )
														{
															WICED_BT_TRACE(",1\n");
														}
														else
														{
															WICED_BT_TRACE(",0\n");
														}

													}


							 //-----------------------------------------------------------------------------------------
    				   }
    				   else
    				   {
    					   //WICED_BT_TRACE("Fuera del buffer en vehiculos\n");
    				   }
    			   }
    			   else
    			   {
    				   /*if ( GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ))
    				   {
    				     char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
    				     if(!p_dataDmV2)
    				     {
    				     memcpy(&datam_bufferV2[data_mc3V2],dataV_DMV,6);
    				     data_mc3V2+=6;
    				     datac_mV2++;
    				     WICED_BT_TRACE("No contiene en vehiculos2 \n");
    				     }
    				   }
    				   else
    				   {
    					   WICED_BT_TRACE("SI CONTIENE EN VEHICULOS\n");
    				   }*/


    				   //---------------------------------------------------
    				   if ( gap_t1== WICED_TRUE && st_Tipe==0x0b)
					   {
							 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
							 if(!p_dataDmV2)
							 {
							 memcpy(&datam_bufferV2[data_mc3V2],dataV_DMV,6);
							 data_mc3V2+=6;
							 datac_mV2++;
							 //WICED_BT_TRACE("No contiene en vehiculos2 \n");
							 }
					   }

						else if (value_pV1== WICED_FALSE)
						{
								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(!p_dataDmV2)
								 {
								 memcpy(&datam_bufferV2[data_mc3V2],dataV_DMV,6);
								 data_mc3V2+=6;
								 datac_mV2++;
								 //WICED_BT_TRACE("Si contiene lamparas2\n");
								 }
						}
						else if(value_pV1 == WICED_TRUE)
						{

								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(p_dataDmV2)
								 {
								 char *p_dataDmV3 = strstr(datam_bufferV3,dataV_DMV);
									 if(!p_dataDmV3)
									 {
									 memcpy(&datam_bufferV3[data_mc3V3],dataV_DMV,6);
									 data_mc3V3+=6;
									 datac_mV3++;
									 //WICED_BT_TRACE("Si contiene lamparas2\n");
									 }

								 }


						}
					   /*else
					   {
						   //WICED_BT_TRACE("SI CONTIENE EN VEHICULOS\n");
					   }*/
    				   //----------------------------------------------------
    			   }
    			     timer_clr10();
    			     //------------------------------------------------------------
    	   			   //WICED_BT_TRACE("RSSIV: %d\n",p_scan_result->rssi);

      			   memcpy(dataFiltPA, &p_name[6], 3);

      			   //------Filtro modulo A
      	    	   if(memcmp(Filt_operateBL0, dataFiltPA, sizeof(dataFiltPA))  == 0 ||
      	    	      memcmp(Filt_operateBLE, dataFiltPA, sizeof(dataFiltPA))  == 0 ||
      	    	      memcmp(Filt_operateBL1, dataFiltPA, sizeof(dataFiltPA)) == 0 ||
      	    	      memcmp(Filt_operateBLB, dataFiltPA, sizeof(dataFiltPA)) == 0 )
      	    	   {//filtro A
        			   if(p_scan_result->rssi>=-dtv &&  gap_t1 == WICED_FALSE)
        			   {
        					if(datac_mV > datac_menviadaV)
        					{
								 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(!p_dataDmV2)
								 {
		    		    			    //WICED_BT_TRACE("RSSI FILTV\n");
		    		    			    value_AV=WICED_TRUE;
		    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
		    		    			    start_TreturnfAV();
		    		    			    if(value_alrm)
		    		    			    {
		    		    			   	  value_alrm=WICED_FALSE;
		    		    			      start_alrm();
		    		    			    }

								 }
        					}
        					else
        					{
								 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(!p_dataDmV2)
								 {
		    		    			    //WICED_BT_TRACE("RSSI FILTV\n");
		    		    			    value_AV=WICED_TRUE;
		    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
		    		    			    start_TreturnfAV();
		    		    			    if(value_alrm)
		    		    			    {
		    		    			   	  value_alrm=WICED_FALSE;
		    		    			      start_alrm();
		    		    			    }

								 }
        					}

        			   }

      	    	   }
    			     //-------------------------------------------------------------Fitl A

    	    	   //-----------Filtro ED
    	    	   memcpy(dataFiltED, &p_name[6], 3);
    	    	   if(memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED))  == 0 ||
    	    	      memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED))  == 0 ||
    	    	      memcmp(Filt_operateLAB, dataFiltED, sizeof(dataFiltED)) == 0 )
    	    	   {
        			   if(p_scan_result->rssi>=-125 &&  gap_t1 == WICED_FALSE)
        			   {
        					if(datac_mV > datac_menviadaV)
        					{
								 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(!p_dataDmV2)
								 {
		    		    			    //WICED_BT_TRACE("RSSI FILTV\n");
		    		    			    value_AV=WICED_TRUE;
		    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
		    		    			    //start_TreturnfAV();
		    		    			    start_TreturnfAVR();
		    		    			    if(value_alrm)
		    		    			    {
		    		    			   	  value_alrm=WICED_FALSE;
		    		    			      start_alrm();
		    		    			    }

								 }
        					}
        					else
        					{
								 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
								 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
								 if(!p_dataDmV2)
								 {
		    		    			    //WICED_BT_TRACE("RSSI FILTV\n");
		    		    			    value_AV=WICED_TRUE;
		    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
		    		    			    //start_TreturnfAV();
		    		    			    start_TreturnfAVR();
		    		    			    if(value_alrm)
		    		    			    {
		    		    			   	  value_alrm=WICED_FALSE;
		    		    			      start_alrm();
		    		    			    }

								 }
        					}

        			   }
    	    	   }
    			}

    			//-----------------------------------------------------------------

    			//-----------------------------------------------------------------
    			/*WICED_BT_TRACE("Numero de lamparas xx:%d  \n",datac_m);
    			WICED_BT_TRACE("Numero de lamparas2 xx:%d  \n",datac_m2);
    			WICED_BT_TRACE("Numero de lamparas3 xx:%d  \n",datac_comp);
    			WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARAS");
    			WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2");
    			WICED_BT_TRACE("Numero de lamparas st:%d  \n",datac_st);
    			WICED_BT_TRACE("Conteo enviado: %d\n",datac_menviada);
    			WICED_BT_TRACE("Conteo enviado2: %d\n",datac_menviada2);

    			WICED_BT_TRACE("Numero de vehiculos xx:%d  \n",datac_mV);
    			WICED_BT_TRACE("Numero de vehiculos2 xx:%d  \n",datac_mV2);
    			WICED_BT_TRACE("Numero de vehiculos3 xx:%d  \n",datac_compV);
    			WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOS");
    			WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2");
    			WICED_BT_TRACE("Numero de vehiculos st:%d  \n",datac_stV);
    			WICED_BT_TRACE("Conteo vehiculos: %d\n",datac_menviadaV);*/


    			 if(datac_m > datac_menviada)
    			 {
    				 //WICED_BT_TRACE("PIN HIGH XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX:%d  \n",datac_m);
    				 value_pa1=WICED_FALSE;
    				 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
    				 value_p1= WICED_TRUE;
    				 //change_PWM();
    			 }

    			 if(datac_mV > datac_menviadaV)
    			 {
    				 //WICED_BT_TRACE("PIN HIGH XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX:%d  \n",datac_mV);
    				 value_paV1=WICED_FALSE;
    				 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
    				 value_pV1= WICED_TRUE;
    				 //change_PWM();
    			 }
    	   }
    	   else if (memcmp(Filt_operate6, dataFilt, sizeof(dataFilt)) == 0)
    	   {

    		   wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
    		   //WICED_BT_TRACE("SPIN 17 HIGH\n");
    		   start_TreturnfA();
    	   }

    	   //-----------------------------------------------------------------------------
    	          	else if(memcmp(Filt_operate5, dataFilt, sizeof(dataFilt)) == 0 ||
    	          	    	memcmp(Filt_operate5, dataFilt, sizeof(dataFilt)) == 0 )
    	          	{
    	          		if(gap_t1== WICED_FALSE)
    	          		{
    	   				if(value_gap)
    	   				{
    	   					value_gap= WICED_FALSE;
    	   					value_le = WICED_TRUE;
    	   					wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
    	   					wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
    	   					wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
    	   					WICED_BT_TRACE("greeen\n");
    	   				}
    	   			  //gap_transfer();
    	   				WICED_BT_TRACE("greeen\n");
    	   				   start_Treturn();
    	          		}
    	          	}
    	   //-----------------------------------------------------------------------

//-----------------------------------------------------------------------------


		   	       memcpy(dataFiltR,p_scan_result->remote_bd_addr,6);
		   	    /*
		   	   	if(memcmp(Filt_operate1, dataFilt, sizeof(dataFilt)) == 0 ||
		   	    	   memcmp(Filt_operate1, dataFilt, sizeof(dataFilt)) == 0 ){//filtro de nombres

		   	      	      WICED_BT_TRACE("BNM");
		   				  for(int k=0; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  WICED_BT_TRACE("NAME:");
		   				  wiced_hal_puart_print(p_name);
		   				  WICED_BT_TRACE(",LAMP,%d\n",p_scan_result->rssi);
		   	      	     // WICED_BT_TRACE( "%B\n", static_addr );
		   	    	      //wiced_hal_puart_print(p_name);
		   	    	}
		   	    	else if(memcmp(Filt_operate2, dataFilt, sizeof(dataFilt)) == 0 ||
		   	    	    	memcmp(Filt_operate2, dataFilt, sizeof(dataFilt)) == 0 )
		   	    	{
		   	      	      WICED_BT_TRACE("BNM");
		   				  for(int k=0; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  WICED_BT_TRACE("NAME:");
		   				  wiced_hal_puart_print(p_name);
		   				  WICED_BT_TRACE(",VEHI,%d\n",p_scan_result->rssi);
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );
		   	    	}
		   	    	else if(memcmp(Filt_operate3, dataFilt, sizeof(dataFilt)) == 0 ||
		   	    	    	memcmp(Filt_operate3, dataFilt, sizeof(dataFilt)) == 0 )
		   	    	{
		   	      	      WICED_BT_TRACE("BNM");
		   				  for(int k=0; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  WICED_BT_TRACE(",BEAC,%d\n",p_scan_result->rssi);
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );
		       		      wiced_hal_gpio_set_pin_output( LED_GPIO_11, GPIO_PIN_OUTPUT_HIGH);
		       		      //WICED_BT_TRACE("SPIN 11 HIGH\n");
		   				  start_TreturnfB();
		   	    	}*/
		   //--------------------------------------------------------------------
		   	   	//-----------------------------------------------------------
		   		memcpy(dataFiltEA, p_name, 8);
		   	   	if(memcmp(Filt_operate40, dataFiltEA, sizeof(dataFiltEA)) == 0 ||    //L4SEC_EA
		   	    	   memcmp(Filt_operate40, dataFiltEA, sizeof(dataFiltEA)) == 0 ){//filtro de nombres



		   	   		/* Descometar */
//		   	   		  WICED_BT_TRACE("BNM|");
//	   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
//	   				  for(int k=1; k<=5; k++)
//	   				  {
//	   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
//	   				  }
//	   				  //WICED_BT_TRACE("NAME:");
//	   				  //wiced_hal_puart_print(p_name);
//	   				  WICED_BT_TRACE(",LAMP,%d",p_scan_result->rssi);
//	   				  WICED_BT_TRACE(",1\n");


	   	      	     // WICED_BT_TRACE( "%B\n", static_addr );
	   	    	      //wiced_hal_puart_print(p_name);
//------------------------------------------------------------------
  					if(datac_m > datac_menviada)
  					{
  						/*if((datac_m - datac_menviada2)!=0)
  						{
  							//WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
  		    			    //WICED_BT_TRACE("RSSI FILT\n");
  		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
  		    			    start_TreturnfA();
  						}*/

							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    			    start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

  					}
  					else
  					{
  						/*if((datac_menviada - datac_menviada2)!=0)
  						{
  							//WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
  		    			    //WICED_BT_TRACE("RSSI FILT\n");
  		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
  		    		        start_TreturnfA();
  						}*/
							 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
							 if(!p_dataDm2)
							 {
	    		    			    //WICED_BT_TRACE("RSSI FILT\n");
	    		    			    value_AL=WICED_TRUE;
	    		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	    		    		        start_TreturnfA();
	    		    			    if(value_alrm)
	    		    			    {
	    		    			   	  value_alrm=WICED_FALSE;
	    		    			      start_alrm();
	    		    			    }

							 }

  					}

//-------------------------------------------------------------
		   				  //value_EA = WICED_TRUE;
		   				  //start_TreturnEA();
		   	    	}
		   	   	   else if(memcmp(Filt_operate101, dataFiltEA, sizeof(dataFiltEA)) == 0 ||    //L4SEC BL
		   	    	   memcmp(Filt_operate101, dataFiltEA, sizeof(dataFiltEA)) == 0 ){//filtro de nombres

		   	   		   /* Descomentar */
//		   	      	      WICED_BT_TRACE("BNM|");
//		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
//		   				  for(int k=1; k<=5; k++)
//		   				  {
//		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
//		   				  }
//		   				  //WICED_BT_TRACE("NAME:");
//		   				  //wiced_hal_puart_print(p_name);
//		   				  WICED_BT_TRACE(",LAMP,%d",p_scan_result->rssi);
//		   				  WICED_BT_TRACE(",0\n");

		   	      	     // WICED_BT_TRACE( "%B\n", static_addr );
		   	    	      //wiced_hal_puart_print(p_name);
		   	    	}
		   	    	else if(memcmp(Filt_operate102, dataFiltEA, sizeof(dataFiltEA)) == 0 ||
		   	    	    	memcmp(Filt_operate102, dataFiltEA, sizeof(dataFiltEA)) == 0 )
		   	    	{
		   	      	      /*WICED_BT_TRACE("BNM:");
		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
		   				  for(int k=1; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  //WICED_BT_TRACE("NAME:");
		   				  //wiced_hal_puart_print(p_name);
		   				  WICED_BT_TRACE(",VEHI,%d",p_scan_result->rssi);
		   				  WICED_BT_TRACE(",0\n");*/
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );
		   	    	}
		   	    	else if(memcmp(Filt_SR, dataFiltEA, sizeof(dataFiltEA)) == 0 ||
		   	    	    	memcmp(Filt_SR, dataFiltEA, sizeof(dataFiltEA)) == 0 )
		   	    	{
		   	       		if(gap_t1== WICED_FALSE)
		   	       		{
		   					if(value_gap)
		   					{
		   						value_gap= WICED_FALSE;
		   						value_le = WICED_TRUE;
		   						wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
		   						wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
		   						wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
		   					}
		   					WICED_BT_TRACE("greeen1111\n");
		   				  //gap_transfer();
		   					   start_Treturn();
		   	       		}
		   	    	}
		   	         memcpy(dataFiltBC, &p_name[9], 5);
		   	         //WICED_BT_TRACE("NAMEXXXX:");
		   	         //wiced_hal_puart_print(&p_name[9]);
		   	         //WICED_BT_TRACE("\n");
		   	    	 if(memcmp(Filt_operate103, dataFiltBC, sizeof(dataFiltBC)) == 0 ||
		   	    		memcmp(Filt_operate103, dataFiltBC, sizeof(dataFiltBC)) == 0  )    //SMART_BE
		   	    	{
		   	      	      WICED_BT_TRACE("BNM|");
		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
		   				  for(int k=1; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  WICED_BT_TRACE(",BEAC,%d",p_scan_result->rssi);
		   				  WICED_BT_TRACE(",0\n");
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );
		       		      //wiced_hal_gpio_set_pin_output( LED_GPIO_03, GPIO_PIN_OUTPUT_HIGH);
		       		      //WICED_BT_TRACE("SPIN 11 HIGH\n");
		   				  //start_TreturnfB();
		   	    	}

		   	    	 if(memcmp(Filt_ACARO, dataFiltBC, sizeof(dataFiltBC)) == 0 ||
		   	    			memcmp(Filt_ACARO, dataFiltBC, sizeof(dataFiltBC)) == 0)//ACARO
		   	    	 {
		   	    		WICED_BT_TRACE("BNM|");
		   	    		WICED_BT_TRACE("%02X",dataFiltR[0]);
		   	    		for(int k=1; k<=5; k++)
		   	    		{
		   	    			WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   	    		}
		   	    		WICED_BT_TRACE(",BEAC,%d",p_scan_result->rssi);
		   	    		WICED_BT_TRACE(",0\n");
		   	    	 }

		   	    	 if(memcmp(Filt_GEOSF, dataFiltBC, sizeof(dataFiltBC)) == 0 ||    		//GEOSF
		   	    	    	memcmp(Filt_GEOSF, dataFiltBC, sizeof(dataFiltBC)) == 0  )
		   	    	{
		   	      	      WICED_BT_TRACE("BNM|");
		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
		   				  for(int k=1; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  WICED_BT_TRACE(",GEOSF,%d",p_scan_result->rssi);
		   				  WICED_BT_TRACE(",0\n");
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );
		       		      //wiced_hal_gpio_set_pin_output( LED_GPIO_03, GPIO_PIN_OUTPUT_HIGH);
		       		      //WICED_BT_TRACE("SPIN 11 HIGH\n");
		   				  //start_TreturnfB();
		   	    	}

		   	      memcpy(dataFiltLV, p_name, 5);

		   	    	 if(memcmp(Filt_operate1, dataFiltLV, sizeof(dataFiltLV)) == 0 ||     //L4SEC
		   	    	    	memcmp(Filt_operate1, dataFiltLV, sizeof(dataFiltLV)) == 0 )
		   	    	{

		   	    		 /* Descomentar */
//		   	      	      WICED_BT_TRACE("BNM|");
//		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
//		   				  for(int k=1; k<=5; k++)
//		   				  {
//		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
//		   				  }
//		   				  //WICED_BT_TRACE("NAME:");
//		   				  //wiced_hal_puart_print(p_name);
//		   				  WICED_BT_TRACE(",LAMP,%d",p_scan_result->rssi);
//		   				  WICED_BT_TRACE(",0\n");
		   	      	     // WICED_BT_TRACE( "%B\n", static_addr );
		   	    	      //wiced_hal_puart_print(p_name);

		   	    	}

		   	    	 else if(memcmp(Filt_operate2, dataFiltLV, sizeof(dataFiltLV)) == 0 ||    //LAIRD
		   	    	    	memcmp(Filt_operate2, dataFiltLV, sizeof(dataFiltLV)) == 0 )
		   	    	{

		   	      	      WICED_BT_TRACE("BNM|");
		   	      	      WICED_BT_TRACE("%02X",dataFiltR[0]);
		   				  for(int k=1; k<=5; k++)
		   				  {
		   				    WICED_BT_TRACE(":%02X",dataFiltR[k]);
		   				  }
		   				  //WICED_BT_TRACE("NAME:");
		   				  //wiced_hal_puart_print(p_name);
		   				  WICED_BT_TRACE(",VEHI,%d",p_scan_result->rssi);
		   				  WICED_BT_TRACE(",0\n");
		   	    	      //WICED_BT_TRACE( "%B\n", static_addr );

		   	    	}

		   	    	 else if(memcmp(Filt_AB, dataFiltLV, sizeof(dataFiltLV)) == 0 ||
		   	    	    	memcmp(Filt_AB, dataFiltLV, sizeof(dataFiltLV)) == 0 )
		   	    	{

			   	       		if(gap_t1== WICED_FALSE)
			   	       		{
			   					if(value_gap)
			   					{
			   						value_gap= WICED_FALSE;
			   						value_le = WICED_TRUE;
			   						wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
			   						wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
			   						wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
			   					}
			   					WICED_BT_TRACE("greeen2222\n");
			   				  //gap_transfer();
			   					   start_Treturn();
			   	       		}

		   	    	}
		   	   	//-----------------------------------------------------------

    	 }


    	//--------------------------------------------------------------------------------
    	        //uint8_t dataFilt5[6];

    	    	 uint8_t                 length3;
    	    	 uint8_t *               p_data3;
    	    	uint8_t Filt_MAC4[6]  = {0x31, 0x31, 0xFF, 0xFF, 0xFF, 0xFF};
    	    	uint8_t filt_sl[6];
    	    	 uint8_t data_flt2[6];

    	    	char *dataV_DM3334[30] ={0};
    	    	  	 char datam_fff[30];
    	    	  	 char datam_fff22[30];
    	    	  	char *substr2 = "CASASFCASCO";

    	    	  	uint8_t datam_fff3[30];

    	    	  	 char Filt_ddf2[2]  = {'S', 'F',};

    	             memcpy(data_flt2,p_scan_result->remote_bd_addr,6);

    	                 if(data_flt2[0]<1 || data_flt2[1]<1 || data_flt2[2]<1 || data_flt2[3]<1 || data_flt2[4]<1 || data_flt2[5]<1)
    	      		   {
    	      			   data_flt2[0]=0xFF;
    	      			   data_flt2[1]=0xFF;
    	      			   data_flt2[2]=0xFF;
    	      			   data_flt2[3]=0xFF;
    	      			   data_flt2[4]=0xFF;
    	      			   data_flt2[5]=0xFF;
    	      			  // WICED_BT_TRACE( "Return2\n");
    	      			   //return;
    	      		   }

    	    	  	memcpy(dataV_SPI,data_flt2,6);
    	    	  	//memcpy(datac_fp,data_flt2,6);        //  ------------> Se va a mover a otra parte para desbordamieto por boton

    	    		 if(memcmp(Filt_MAC4, dataV_SPI, sizeof(dataV_SPI)) != 0 && gap_t1== WICED_FALSE)
    	    		 {
    	    			 /*WICED_BT_TRACE("URL:");
    	    			 wiced_hal_puart_print(&p_data[3]);
    	    			 WICED_BT_TRACE("\n");*/
    	    		 //p_data = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_16SRV_COMPLETE, &length );
    	    		 //WICED_BT_TRACE_ARRAY(p_data,40,"Data server %B");
    	    		 //p_data = wiced_bt_ble_check_advertising_data( p_adv_data, 0x01   , &length1 );
    	    		 //WICED_BT_TRACE_ARRAY(p_data,40,"Data server1 %B");
    	    		 p_data3 = wiced_bt_ble_check_advertising_data( p_adv_data, 0x03, &length3 );
    	    		 //WICED_BT_TRACE_ARRAY(p_data3,40,"Data server3 %B");

    	    		 //WICED_BT_TRACE("Data server1: %B\n",&p_data3[8]);
    	    		 //WICED_BT_TRACE("Data server2: %B\n",&p_data3[9]);
    	    		 if(p_data3[8]=='S')
    	    		 {
    	    			 //WICED_BT_TRACE("Data server3: %B\n",&p_data3[8]);
    	    			 memcpy(datam_fff3,&p_data3[8],sizeof(datam_fff3));
    	    			 //memcpy(dataV_DM3334,datam_fff3,sizeof(datam_fff3));

    	    		 }
    	    		 else if(p_data3[9]=='S')
    	    		 {
    	    			 //WICED_BT_TRACE("Data server4: %B\n",&p_data3[9]);
    	    			 memcpy(datam_fff3,&p_data3[9],sizeof(datam_fff3));
    	    			 //memcpy(dataV_DM3334,datam_fff3,sizeof(datam_fff3));
    	    		 }
    	    		 else
    	    		 {
    	    			 return;
    	    		 }


    	    		 //memcpy(datam_fff2,dt,30);

    	    		 char *substr3 =datam_fff3;
    	    		 //WICED_BT_TRACE_ARRAY(substr3,40,"Data server5: %B");
    	    		    char *substr2 = "SP";
    	    		    //char *substrSL = "SL";
    	    		    char *substrSL = "SL";
    	    		    char *substrSA = "SA";
    	    		    char *substrSB = "SB";
    	    		    //char *substrx = "";



    	    		        //char *sK = strstr( substr3,substr);
    	    	   		if (strstr(substr3,substr2) == NULL)      /* No esta */
    	    	   		{
    	    	   			 //WICED_BT_TRACE("SSSSSSSS7\n");
    	    				      /*indice = sK - substr3;
    	    				      WICED_BT_TRACE("3BACK La cadena '%s',  en la posición %d\n", sK, indice);
    	    				      indice = substr- sK;
    	    					  WICED_BT_TRACE("4BACK La cadena '%s',  en la posición %d\n", sK, indice);*/
    	    	   		}
    	    	   		else
    	    	   		{
    	    	   			//WICED_BT_TRACE("NNNNNNNNRRR7\n");
    	    				      //indice = sK - substr3;
    	    				      //WICED_BT_TRACE("3BACK La cadena '%s',  en la posición %d\n", sK, indice);
    	    				      //indice = substr3- sK;
    	    					  //WICED_BT_TRACE("4BACK La cadena '%s',  en la posición %d\n", sK, indice);
    	//----------------------------------------------------------------------------------------
    						 char *p_dataDBS = strstr(datam_buffer2,dataV_SPI);
    						 if(p_dataDBS)
    						 {
    							 char *p_dataDBS2 = strstr(datam_bufferdbs,dataV_SPI);
    							 if(!p_dataDBS2)
    							 {
    							 memcpy(&datam_bufferdbs[data_mcdbs],dataV_SPI,6);
    							 data_mcdbs+=6;
    							 datac_mdbs++;
    							 //WICED_BT_TRACE("Si contiene lamparasB2\n");
    				    			//WICED_BT_TRACE_ARRAY(datam_bufferdbs, 18, "BUFFER LAMPARAS2");
    				    			//WICED_BT_TRACE("Numero de lamparas st:%d ********************----> \n",datac_mdbs);      /* ----------->   Estaba comentado, no es necesario  */
    				    			//WICED_BT_TRACE("\n Mac encontrada %B \n",p_dataDBS);     /* Aaqui lleva el conteo con datam_buffer2  y el contador 2, en ellos lleva el conteo final */
    							 }

    						 }
    	//----------------------------------------------------------------------------

    	    	         		 //WICED_BT_TRACE("Data server1: %B\n",&p_data3[8]);
    	    	         		 //WICED_BT_TRACE("Data server2: %B\n",&p_data3[9]);


    	    	}

    	    	   		//-----------------------------------------
    	    	   		//----------------------------------------------------------------------------------
    	    	   		memcpy(datac_fp,data_flt2,6);   /* Aqui se agrega este linea para desabordamiento por boton */
    	    	   		if (strstr(substr3,substrSL) != NULL)
    	    	   		{
    	    	   			 WICED_BT_TRACE("SLB\n");
    	    				      /*indice = sK - substr3;
    	    				      WICED_BT_TRACE("3BACK La cadena '%s',  en la posición %d\n", sK, indice);
    	    				      indice = substr- sK;
    	    					  WICED_BT_TRACE("4BACK La cadena '%s',  en la posición %d\n", sK, indice);*/
    	    	   		}
    	    	   		else if (strstr(substr3,substrSA) != NULL && memcmp(datac_cfbf2, datac_fp, sizeof(datac_fp)) == 0)
    	    	   		{

    		   	      	      WICED_BT_TRACE("CAR#");
    		   	      	      WICED_BT_TRACE("%02X",substr3[2]);
    		   				  for(int k=3; k<=7; k++)
    		   				  {
    		   				    WICED_BT_TRACE(":%02X",substr3[k]);
    		   				  }
    		   				  //WICED_BT_TRACE("NAME:");
    		   				  //wiced_hal_puart_print(p_name);

    		   				  if(datam_fff3[8]==0)
    		   				  {
    		   					WICED_BT_TRACE("|0");
    		   				  }
    		   				  else if(datam_fff3[8]==1)
    		   				  {
    		   					WICED_BT_TRACE("|1");
    		   				  }
    		   				  else if(datam_fff3[8]==2)
    		   				  {
    		   					WICED_BT_TRACE("|2");
    		   				  }
    		   				  else if(datam_fff3[8]==3)
    		   				  {
    		   					WICED_BT_TRACE("|3");
    		   				  }
    		   				  else if(datam_fff3[8]==4)
    		   				  {
    		   					WICED_BT_TRACE("|4");
    		   				  }
    		   				    WICED_BT_TRACE("\n");

    	    				      /*indice = sK - substr3;
    	    				      WICED_BT_TRACE("3BACK La cadena '%s',  en la posición %d\n", sK, indice);
    	    				      indice = substr- sK;
    	    					  WICED_BT_TRACE("4BACK La cadena '%s',  en la posición %d\n", sK, indice);*/
    	    	   		}
    	    	   		else if (strstr(substr3,substrSB) != NULL && memcmp(datac_cfbf2, datac_fp, sizeof(datac_fp)) == 0)
    	    	   		{
    	    	   			WICED_BT_TRACE("NBC#%s\n",&substr3[2]);
    	    	   		}

    	    	   		//----------------------------------------------------------------------------------
    	    	   		//------------------------------------------
//    	    	   		if (strstr(substr3,substrSL) != NULL)
//    	    	   		{
//    	    	   		 if(substr3[4]==2 || substr3[4]==4 || substr3[4]==6)
//    	    	   		 {
//    	    	   			memcpy(filt_sl,p_scan_result->remote_bd_addr,6);
//    	    	   			//WICED_BT_TRACE("Enter: \n");
//    			   	   		  WICED_BT_TRACE("BNM:");
//    		   	      	      WICED_BT_TRACE("%02X",filt_sl[0]);
//    		   				  for(int k=1; k<=5; k++)
//    		   				  {
//    		   				    WICED_BT_TRACE(":%02X",filt_sl[k]);
//    		   				  }
//    		   				  //WICED_BT_TRACE("NAME:");
//    		   				  //wiced_hal_puart_print(p_name);
//    		   				  WICED_BT_TRACE(",LAMP,%d",p_scan_result->rssi);
//    		   				  WICED_BT_TRACE(",1\n");
//    	    	   		 }
//    	    	   		}
    	    		 }
    	    	//--------------------------------------------------------------------------------------------------
    	//--------------------------------------------------------------------------------

    }

    }
    else
    {
        //WICED_BT_TRACE( "Scan completed :\r\n" );
    }
    //-----------------------------------------------------------------------
        	   //-----------Filtro ED

        	    memcpy(dataFilterED2, p_name, 3);
        	    //------------------------------------------------------------------------------
        	    if(memcmp(Filt_comanED1, dataFilterED2, sizeof(dataFilterED2))  == 0 ||
        	       memcmp(Filt_comanED1, dataFilterED2, sizeof(dataFilterED2))  == 0)
        	    {
        	    	//WICED_BT_TRACE("DatacrlALV2: %d\n",dataFiltALV[0]);
        	    	if(dataFiltALV[0]== 4 || dataFiltALV[0]== 12)
        	    	{
        	    		//WICED_BT_TRACE("DatacrlALV3: %d\n",dataFiltALV[0]);
     			   if(p_scan_result->rssi>=-125 &&  gap_t1 == WICED_FALSE)
     			   {
     				  //WICED_BT_TRACE("SERALAAAAAAAAAAAAAAAAAAAARM\n");
     					if(datac_m > datac_menviada)
     					{
     						/*if((datac_m - datac_menviada2)!=0)
     						{
     							//WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
     		    			    //WICED_BT_TRACE("RSSI FILT\n");
     		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
     		    			    start_TreturnfA();
     						}*/

     						 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
     						 if(!p_dataDm2)
     						 {
         		    			    //WICED_BT_TRACE("RSSI FILT\n");
         		    			    value_AL=WICED_TRUE;
         		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
         		    			    //start_TreturnfA();
         		    			    start_TreturnfAR();
         		    			    if(value_alrm)
         		    			    {
         		    			   	  value_alrm=WICED_FALSE;
         		    			      start_alrm();
         		    			    }

     						 }

     					}
     					else
     					{
     						/*if((datac_menviada - datac_menviada2)!=0)
     						{
     							//WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
     		    			    //WICED_BT_TRACE("RSSI FILT\n");
     		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
     		    		        start_TreturnfA();
     						}*/
     						 char *p_dataDm2 = strstr(datam_buffer2,dataV_DM);
     						 if(!p_dataDm2)
     						 {
         		    			    //WICED_BT_TRACE("RSSI FILT\n");
         		    			    value_AL=WICED_TRUE;
         		    		        wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
         		    		        //start_TreturnfA();
         		    		        start_TreturnfAR();
         		    			    if(value_alrm)
         		    			    {
         		    			   	  value_alrm=WICED_FALSE;
         		    			      start_alrm();
         		    			    }

     						 }

     					}

     			   }
        	    }
     			   //----------------------------------------------
        	    	if(dataFiltALV[0]== 8 || dataFiltALV[0]== 12)
        	    	{
    			   if(p_scan_result->rssi>=-125 &&  gap_t1 == WICED_FALSE)
    			   {
    					if(datac_mV > datac_menviadaV)
    					{
    						 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
    						 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
    						 if(!p_dataDmV2)
    						 {
        		    			    //WICED_BT_TRACE("RSSI FILTV\n");
        		    			    value_AV=WICED_TRUE;
        		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
        		    			    //start_TreturnfAV();
        		    			    start_TreturnfAVR();
        		    			    if(value_alrm)
        		    			    {
        		    			   	  value_alrm=WICED_FALSE;
        		    			      start_alrm();
        		    			    }

    						 }
    					}
    					else
    					{
    						 //WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
    						 char *p_dataDmV2 = strstr(datam_bufferV2,dataV_DMV);
    						 if(!p_dataDmV2)
    						 {
        		    			    //WICED_BT_TRACE("RSSI FILTV\n");
        		    			    value_AV=WICED_TRUE;
        		    			    wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
        		    			    //start_TreturnfAV();
        		    			    start_TreturnfAVR();
        		    			    if(value_alrm)
        		    			    {
        		    			   	  value_alrm=WICED_FALSE;
        		    			      start_alrm();
        		    			    }

    						 }
    					}

    			   }
        	    }
        	    }

    		   //--------------------------------------------------------------------
}

/********************************************************************************
 * Function name: init_event_ADC
 * Description: the adc ends the events
 ********************************************************************************/
void init_event_ADC(void)
{
	if(!value_Adc)
	{

	  wiced_init_timer( &timer_radc, f_timer_radc, 0, WICED_SECONDS_TIMER );
	  wiced_start_timer( &timer_radc, 60);
      stop_timer_st_online();
      wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		//value_Adc= WICED_FALSE;
       //WICED_BT_TRACE("ADC REPORT \n");
	}

}

/********************************************************************************
 * Function name: f_timer_radc
 * Description: reset by adc
 ********************************************************************************/
void        f_timer_radc( uint32_t data )
{
	//WICED_BT_TRACE("ADC TIMER \n");
	wiced_hal_wdog_reset_system ();
}


/********************************************************************************
 * Function name: clear_cont
 * Description: Deletion processes, updating of counted and addressed devices
 ********************************************************************************/
void clear_cont(void)
{
	wiced_bt_ble_observe (0,0 , Observer_scan_result_cback);


	//-------------------------------------------------------------------------------------
	if(datac_mdbs>0 && datac_m2>0)
	{
		for(int c=0; c < datac_m2; c++)
		{
			/*WICED_BT_TRACE_ARRAY(datam_buffer,20,"Abuffer dbs1: %B");
			WICED_BT_TRACE_ARRAY(datam_bufferdbs,20,"Abuffer dbs2: %B");
			WICED_BT_TRACE_ARRAY(datam_buffer2,20,"ADatam2: %B");
			WICED_BT_TRACE_ARRAY(datam_buffer3,20,"ADatam3: %B");
			WICED_BT_TRACE_ARRAY(datam_bufferact,20,"ADatamact: %B");
			WICED_BT_TRACE("Admdbs: %d, dmdbs:%d, dm1:%d, dmc1:%d, dm2:%d, dmc2:%d, dmact:%d, dmcact:%d,dm3:%d, dmc3:%d\n", datac_mdbs, data_mcdbs, datac_m, data_mc3,  datac_m2, data_mc32, datac_mact, data_mc3act, datac_m3, data_mc33);*/
			memcpy(datav_dbs,&datam_buffer2[c*6],6);
			//WICED_BT_TRACE("FILT: %B\n", datav_dbs);
			 char *p_datadbs = strstr(datam_bufferdbs,datav_dbs);
			 if(p_datadbs)
			 {
					indice = p_datadbs - datam_buffer2;
				/*WICED_BT_TRACE_ARRAY(datam_buffer,20,"Bbuffer dbs1: %B");
				WICED_BT_TRACE_ARRAY(datam_bufferdbs,20,"Bbuffer dbs2: %B");
				WICED_BT_TRACE_ARRAY(datam_buffer2,20,"BDatam2: %B");
				WICED_BT_TRACE_ARRAY(datam_buffer3,20,"BDatam3: %B");
				WICED_BT_TRACE_ARRAY(datam_bufferact,20,"BDatamact: %B");
				WICED_BT_TRACE("Admdbs: %d, dmdbs:%d, dm1:%d, dmc1:%d, dm2:%d, dmc2:%d, dmact:%d, dmcact:%d,dm3:%d, dmc3:%d\n", datac_mdbs, data_mcdbs, datac_m, data_mc3,  datac_m2, data_mc32, datac_mact, data_mc3act, datac_m3, data_mc33);*/
			 }
			 else
			 {
				 memcpy(&datam_bufferact[data_mc3act],&datam_buffer2[c*6],6);
				 data_mc3act+=6;
				 datac_mact++;
					/*WICED_BT_TRACE_ARRAY(datam_buffer,20,"B2buffer dbs1: %B");
					WICED_BT_TRACE_ARRAY(datam_bufferdbs,20,"B2buffer dbs2: %B");
					WICED_BT_TRACE_ARRAY(datam_buffer2,20,"B2Datam2: %B");
					WICED_BT_TRACE_ARRAY(datam_buffer3,20,"B2Datam3: %B");
					WICED_BT_TRACE_ARRAY(datam_bufferact,20,"B2Datamact: %B");
					WICED_BT_TRACE("Admdbs: %d, dmdbs:%d, dm1:%d, dmc1:%d, dm2:%d, dmc2:%d, dmact:%d, dmcact:%d,dm3:%d, dmc3:%d\n", datac_mdbs, data_mcdbs, datac_m, data_mc3,  datac_m2, data_mc32, datac_mact, data_mc3act, datac_m3, data_mc33);*/
			 }

			/*	WICED_BT_TRACE_ARRAY(datam_buffer,20,"Cbuffer dbs1: %B");
				WICED_BT_TRACE_ARRAY(datam_bufferdbs,20,"Cbuffer dbs2: %B");
				WICED_BT_TRACE_ARRAY(datam_buffer2,20,"CDatam2: %B");
				WICED_BT_TRACE_ARRAY(datam_buffer3,20,"CDatam3: %B");
				WICED_BT_TRACE_ARRAY(datam_bufferact,20,"CDatamact: %B");
				WICED_BT_TRACE("Admdbs: %d, dmdbs:%d, dm1:%d, dmc1:%d, dm2:%d, dmc2:%d, dmact:%d, dmcact:%d,dm3:%d, dmc3:%d\n", datac_mdbs, data_mcdbs, datac_m, data_mc3,  datac_m2, data_mc32, datac_mact, data_mc3act, datac_m3, data_mc33);*/
		}

		memcpy(datam_buffer2,datam_bufferact,350);
		datac_m2=datac_mact;
		//datac_m2=0;
		data_mc32=data_mc3act;
		datac_comp=0;
		datac_mdbs=0;
		data_mcdbs=0;
		memset(datam_bufferdbs,'\0',350);
		datac_mact=0;
		data_mc3act=0;
		memset(datam_bufferact,'\0',350);
		datac_m3=0;
		data_mc33=0;
		memset(datam_buffer3,'\0',350);
		cc1 = 0;
		/*WICED_BT_TRACE_ARRAY(datam_buffer,20,"Dbuffer dbs1: %B");
		WICED_BT_TRACE_ARRAY(datam_bufferdbs,20,"Dbuffer dbs2: %B");
		WICED_BT_TRACE_ARRAY(datam_buffer2,20,"DDatam2: %B");
		WICED_BT_TRACE_ARRAY(datam_buffer3,20,"DDatam3: %B");
		WICED_BT_TRACE_ARRAY(datam_bufferact,20,"DDatamact: %B");
		WICED_BT_TRACE("Admdbs: %d, dmdbs:%d, dm1:%d, dmc1:%d, dm2:%d, dmc2:%d, dmact:%d, dmcact:%d,dm3:%d, dmc3:%d\n", datac_mdbs, data_mcdbs, datac_m, data_mc3,  datac_m2, data_mc32, datac_mact, data_mc3act, datac_m3, data_mc33);*/
	}


	//----------------------------------------------------------------------------------------

    if(datac_m > datac_st)
    {
   	 //WICED_BT_TRACE("Nueva cuenta lamparas\n");
   	 datac_st=datac_m;
   	 value_notif = WICED_FALSE;
   	 //wiced_hal_gpio_set_pin_output( LED_GPIO_27, GPIO_PIN_OUTPUT_LOW);
    }
    else
    {
   	 //WICED_BT_TRACE("Misma cuenta lamparas\n");
   	 value_notif = WICED_TRUE;
    }


    //-----------------------------------------------
    if(datac_mV > datac_stV)
    {
   	 //WICED_BT_TRACE("Nueva cuenta lamparas\n");
   	 datac_stV=datac_mV;
   	 value_notifV = WICED_FALSE;
   	 //wiced_hal_gpio_set_pin_output( LED_GPIO_27, GPIO_PIN_OUTPUT_LOW);
    }
    else
    {
   	 //WICED_BT_TRACE("Misma cuenta lamparas\n");
   	 value_notifV = WICED_TRUE;
    }
    //-----------------------------------------------


      datac_menviada=datac_m;
      datac_menviada2=datac_m2;

   //-----------------------------------------------
      datac_menviadaV=datac_mV;
      datac_menviadaV2=datac_mV2;
   //----------------------------------------------
    Start_TimerCont();
   /* data_mc3=0;
    datac_m=0;
    memset(datam_buffer,'\0',4000);
	WICED_BT_TRACE( "CLEAR\n\r" );
	wiced_bt_ble_observe (1,0 , Observer_scan_result_cback);*/

	/*if(datac_m > datac_m2 && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		memcpy(datam_buffer,datam_buffer2,350);
		datac_m=datac_m2;
		//datac_m2=0;
		data_mc3=data_mc32;
		WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ1");
		WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ1");
	}
	else if(datac_m > datac_m2 && GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		memcpy(datam_buffer,datam_buffer2,350);
		datac_m=datac_m2;
		//datac_m2=0;
		data_mc3=data_mc32;
		WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ2");
		WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ2");
	}
	else if (datac_m == datac_m2 && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		//memcpy(datam_buffer,datam_buffer2,350);
		//datac_m=datac_m2;
		//datac_m2=0;
		//data_mc3=data_mc32;
		//data_mc3=0;
		//memset(datam_buffer2,'\0',350);
		wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);
		WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ3");
		WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ3");
	}
	else if (datac_m == datac_m2 && GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		//memcpy(datam_buffer,datam_buffer2,350);
		//datac_m=datac_m2;
		datac_comp=datac_m2;
		datac_m2=0;
		data_mc3=data_mc32;
		data_mc32=0;
		memset(datam_buffer2,'\0',350);
		WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ4");
		WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ4");
	}*/

    //-----------------------------------------------------------------------------------------

    /* <---- ------Borrar abordado------ ----> */
    if(datac_m > datac_m2 && value_p1)
    	{
			if(gap_t1 == WICED_FALSE)
			{
				if(datac_m2 == datac_m3)
				{
				memcpy(datam_buffer,datam_buffer2,350);
				datac_m=datac_m2;
				//datac_m2=0;
				data_mc3=data_mc32;
				//-------------------------------------
				datac_m3=0;
				data_mc33=0;
				memset(datam_buffer3,'\0',350);
				//-------------------------------------
				cc1 = 0;
				//-------------------------------------
				//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ1");
				//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ1");

				/* -------------------------		Agregar pasajeros		----------------------------- */
				int8_t m=0, total_t = datac_pasaj;  /* Integer used to add */
				for(q=0; q<4;q++)
				{
					if(strlen(T_pasajeros[q].mac_pasajero) != 0)
					{
						//WICED_BT_TRACE("\n 1- Mac a comparar %B \n",&T_pasajeros[q].mac_pasajero);
						memcpy(mac_help,T_pasajeros[q].mac_pasajero,6);
						valor = strstr(datam_buffer,mac_help);
						if(valor == NULL || valor == 0)
						{
							WICED_BT_TRACE("PCO|%d|",q+1);
							WICED_BT_TRACE("%02X:%02X",T_pasajeros[q].mac_pasajero[0],T_pasajeros[q].mac_pasajero[1]);
							WICED_BT_TRACE(":%02X:%02X",T_pasajeros[q].mac_pasajero[2],T_pasajeros[q].mac_pasajero[3]);
							WICED_BT_TRACE(":%02X:%02X",T_pasajeros[q].mac_pasajero[4],T_pasajeros[q].mac_pasajero[5]);
							WICED_BT_TRACE("|2|\n");
							memset(T_pasajeros[q].mac_pasajero,0, 6);  /* Limpio esta parte de mi cadena */
							total_t --; /* Se fue */
						}
						//else
							//WICED_BT_TRACE("\n Si esta la lampara[%d]: %s \n", q+1 ,mac_help);

						memset(mac_help,0,6);
					}
				}
				datac_pasaj = total_t;
				//WICED_BT_TRACE("\n Total de lamparas guardadas %d \n",datac_m2);
				/* ------ Seccion donde voy a meter a mi arreglo una mac si el numero de abordados es mayor a 4 y se va una, buffer3 ------ */
				if(datac_pasaj < datac_m2 && datac_pasaj < 4)  // Con el datac_m2 es el que dice cuantas lamapras se encuentran actualmnte
				{
					/* Primero paso todo a datam_buffer4 de mis datos */
					data_s6 = 0;
					for(q=0; q<4;q++)
					{
						if(strlen(T_pasajeros[q].mac_pasajero) != 0){
							memcpy(&datam_buffer4[data_s6], &T_pasajeros[q].mac_pasajero, 6);
							//WICED_BT_TRACE("\n Copio de mi arreglo: %B \n",&datam_buffer4[data_s6]);
							data_s6 = data_s6 + 6;
						}
					}
					//WICED_BT_TRACE("\n ************** Cantidad de pasajeros %d, longitud de mi arreglo %d \n",datac_pasaj, strlen(datam_buffer4)/6);
					data_s6 = 0;
					for(q=0;q<datac_m2;q++)
					{
						memcpy(mac_help,&datam_buffer2[data_s6],6);
						valor = strstr(&datam_buffer4[0],mac_help);
						//WICED_BT_TRACE("\n longitud[%d] %d\n",strlen(T_pasajeros[q].mac_pasajero), q);
						if((valor == NULL || valor == 0) && datac_pasaj < 4 && strlen(T_pasajeros[q].mac_pasajero) == 0)
						{
							T_pasajeros[q].out_value=1; /* <---------- Take the position of the new passenger ----------> */
							memcpy(&T_pasajeros[q].mac_pasajero,&datam_buffer2[data_s6],6);
							datac_pasaj++;
							data_s6 = data_s6 + 6;
						}
						else if((valor != NULL || valor != 0) && datac_pasaj < 4 && strlen(T_pasajeros[q].mac_pasajero) == 0)
						{
							q--;
							data_s6 = data_s6 + 6;
						}
						else if((valor != NULL || valor != 0) && datac_pasaj < 4 && strlen(T_pasajeros[q].mac_pasajero) != 0)
						{
							data_s6 = data_s6 + 6;
						}

						memset(mac_help,0,6);
						if(datac_pasaj == 4 || datac_pasaj == datac_m2)
						{
							break;   /* Salirce del ciclo for */
						}
					}
					/* Mandare infromacion en un timer posterior */
					//WICED_BT_TRACE("\n ************** Cantidad de pasajeros %d \n",datac_pasaj);
					timer_sendpassenger();
				}
//										WICED_BT_TRACE("\n Como se encuntra mi arreglo despues %d y como queda m %d\n",datac_pasaj, m);
//										for(q=0;q<4; q++)
//										{
//											WICED_BT_TRACE("%B\n",&T_pasajeros[q].mac_pasajero);
//										}
				/* ------------------------------------------------------------------------------------------------------------ */
				}
				else
				{
					cc1 ++;
					if(cc1 == 3) //3
					{
						memcpy(datam_buffer,datam_buffer3,350);
						datac_m=datac_m3;
						//datac_m2=0;
						data_mc3=data_mc33;

						//----------------------------
						memcpy(datam_buffer2,datam_buffer3,350);
						datac_m2=datac_m3;
						//datac_m2=0;
						data_mc32=data_mc33;
						//----------------------------
						//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ11");
						//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ11");
						cc1 = 0;
					}
				}
			}
			else
			{
				//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ1");
				//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ1");
				//WICED_BT_TRACE("NO ENTRO EN 1\n");
				cc1 = 0;
			}
			//WICED_BT_TRACE("CC1 %d\n", cc1);
    	}
    	else if(datac_m > datac_m2 && !value_p1)
    	{
    		memcpy(datam_buffer,datam_buffer2,350);
    		datac_m=datac_m2;
    		datac_menviada=datac_m;//  cambio
    		//datac_m2=0;
    		data_mc3=data_mc32;
    		//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ2");
    		//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ2");
    	}
    	else if (datac_m == datac_m2 && value_p1)
    	{
    		//memcpy(datam_buffer,datam_buffer2,350);
    		//datac_m=datac_m2;
    		//datac_m2=0;
    		//data_mc3=data_mc32;
    		//data_mc3=0;
    		//memset(datam_buffer2,'\0',350);
    		value_pa1=WICED_TRUE;
    		wiced_hal_gpio_set_pin_output(LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
    		value_p1 = WICED_FALSE;
    		//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ3");
    		//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ3");
    	}
    	else if (datac_m == datac_m2 && !value_p1)
    	{
			if(gap_t1 == WICED_FALSE)
			{
				cc4 ++;
				if(cc4 == 5)
				{
					//memcpy(datam_buffer,datam_buffer2,350);
					//datac_m=datac_m2;
					datac_comp=datac_m2;
					datac_m2=0;
					data_mc3=data_mc32;
					data_mc32=0;
					memset(datam_buffer2,'\0',350);
					//----------------------------------
					datac_m3=0;
					data_mc33=0;
					memset(datam_buffer3,'\0',350);
					//----------------------------------
					//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ4");
					//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ4");
    		        cc4 = 0;
				}
			}
			else
			{
	    		//WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARASZZ4");
	    		//WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2ZZ4");
				//WICED_BT_TRACE("NO ENTRO EN 4\n");
				cc4 = 0;
			}
			//WICED_BT_TRACE("CC4 %d\n", cc4);
    	}
    //-----------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------

	/*if(datac_mV > datac_mV2 && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ))
	{
		memcpy(datam_bufferV,datam_bufferV2,350);
		datac_mV=datac_mV2;
		//datac_mV2=0;
		data_mc3V=data_mc3V2;
		WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ1");
		WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ1");
	}
	else if(datac_mV > datac_mV2 && GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ))
	{
		memcpy(datam_bufferV,datam_bufferV2,350);
		datac_mV=datac_mV2;
		//datac_m2=0;
		data_mc3V=data_mc3V2;
		WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ2");
		WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ2");
	}
	else if (datac_mV == datac_mV2 && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ))
	{
		//memcpy(datam_buffer,datam_buffer2,350);
		//datac_m=datac_m2;
		//datac_m2=0;
		//data_mc3=data_mc32;
		//data_mc3=0;
		//memset(datam_buffer2,'\0',350);
		wiced_hal_gpio_set_pin_output( LED_GPIO_11, GPIO_PIN_OUTPUT_LOW);
		WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ3");
		WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ3");
	}
	else if (datac_mV == datac_mV2 && GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ))
	{
		//memcpy(datam_buffer,datam_buffer2,350);
		//datac_m=datac_m2;
		datac_compV=datac_mV2;
		datac_mV2=0;
		data_mc3V=data_mc3V2;
		data_mc3V2=0;
		memset(datam_bufferV2,'\0',350);
		WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ4");
		WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ4");
	}*/

    //---------------------------------------------------------------------

	if(datac_mV > datac_mV2 && value_pV1)
	{
		if(gap_t1 == WICED_FALSE)
		{
			if(datac_mV2 == datac_mV3)
			{
				memcpy(datam_bufferV,datam_bufferV2,350);
				datac_mV=datac_mV2;
				//datac_mV2=0;
				data_mc3V=data_mc3V2;
				//-------------------------------------
				datac_mV3=0;
				data_mc3V3=0;
				memset(datam_bufferV3,'\0',350);
				//-------------------------------------
				ccV1 = 0;
				//-------------------------------------
				//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ1");
				//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ1");
			}
			else
			{
				ccV1 ++;
				if(ccV1 == 3)
				{
					memcpy(datam_bufferV,datam_bufferV3,350);
					datac_mV=datac_mV3;
					//datac_m2=0;
					data_mc3V=data_mc3V3;

					//----------------------------
					memcpy(datam_bufferV2,datam_bufferV3,350);
					datac_mV2=datac_mV3;
					//datac_m2=0;
					data_mc3V2=data_mc3V3;
					//----------------------------
					//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ11");
					//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ11");
					ccV1 = 0;
				}
			}
		}
		else
		{
			//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ1");
			//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ1");
			//WICED_BT_TRACE("NO ENTRO EN 1 VEHICULOS");
			ccV1 = 0;
		}
		//WICED_BT_TRACE("CCV1 %d\n", ccV1);
	}
	else if(datac_mV > datac_mV2 && !value_pV1)
	{
		memcpy(datam_bufferV,datam_bufferV2,350);
		datac_mV=datac_mV2;
		datac_menviadaV=datac_mV;//  cambio
		//datac_m2=0;
		data_mc3V=data_mc3V2;
		//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ2");
		//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ2");
	}
	else if (datac_mV == datac_mV2 && value_pV1)
	{
		//memcpy(datam_buffer,datam_buffer2,350);
		//datac_m=datac_m2;
		//datac_m2=0;
		//data_mc3=data_mc32;
		//data_mc3=0;
		//memset(datam_buffer2,'\0',350);
		value_paV1=WICED_TRUE;
		wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		value_pV1 = WICED_FALSE;
		//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ3");
		//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ3");
	}
	else if (datac_mV == datac_mV2 && !value_pV1)
	{
		if(gap_t1 == WICED_FALSE)
		{
			ccV4 ++;
			if(ccV4 == 5)
			{
				//memcpy(datam_buffer,datam_buffer2,350);
				//datac_m=datac_m2;
				datac_compV=datac_mV2;
				datac_mV2=0;
				data_mc3V=data_mc3V2;
				data_mc3V2=0;
				memset(datam_bufferV2,'\0',350);
				//----------------------------------
				datac_mV3=0;
				data_mc3V3=0;
				memset(datam_bufferV3,'\0',350);
				//----------------------------------
				//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ4");
				//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ4");
				 ccV4 = 0;
			}
		}
		else
		{
			//WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOSZZ4");
			//WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2ZZ4");
			//WICED_BT_TRACE("NO ENTRO EN 4 EN VEHIUCLOS\n");
			ccV4 = 0;
		}
		//WICED_BT_TRACE("CCV4 %d\n", ccV4);
	}

    //--------------------------------------------------------------------
	//WICED_BT_TRACE("GAP: %d\n",gap_t1);

	//-----------------------------------------------------------------------------------------
	WICED_BT_TRACE( "OBSERVE START--------------------------------\n\r" );
	wiced_bt_ble_observe (1,0 , Observer_scan_result_cback);

}

/* Send again the passenger, but only if the number of the aborded persons is bigger than the passenger value */
void send_passenger(void)
{
	for(uint8_t q=0;q<4;q++)
	{
		if(T_pasajeros[q].out_value == 1)
		{
			WICED_BT_TRACE("PCM|%d|",q+1);
			WICED_BT_TRACE("%02X:%02X",T_pasajeros[q].mac_pasajero[0],T_pasajeros[q].mac_pasajero[1]);
			WICED_BT_TRACE(":%02X:%02X",T_pasajeros[q].mac_pasajero[2],T_pasajeros[q].mac_pasajero[3]);
			WICED_BT_TRACE(":%02X:%02X",T_pasajeros[q].mac_pasajero[4],T_pasajeros[q].mac_pasajero[5]);
			WICED_BT_TRACE("|1|\n");
			T_pasajeros[q].out_value = 0;
		}
	}
}

/****************************************************************
 * Function name: stop_process
 * Description:   the detection indicator LEDs turn off
 ****************************************************************/
void stop_process(void)
{
	 //WICED_BT_TRACE( "CLREVENT\n\r" );
	 //value_notif = WICED_TRUE;
	 value_p1=WICED_FALSE;
	 value_pa1=WICED_TRUE;

	 value_pV1=WICED_FALSE;
	 value_paV1=WICED_TRUE;

	 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);

}


/****************************************************************
 * Function name: exam_gpio
 * Description:   prints the total count of detected devices
 *                and examines the addressed devices
 ****************************************************************/
void exam_gpio(void)
{
	/*if( GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ) && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ) )
	{
		WICED_BT_TRACE("SPP01\n");

	}
	else if(GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ) && GPIO_PIN_OUTPUT_LOW == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		WICED_BT_TRACE("SPP10\n");
	}
	else if(GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_11 ) && GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_09 ))
	{
		WICED_BT_TRACE("SPP11\n");
	}
	else
	{
		WICED_BT_TRACE("SPP00\n");
	}*/
    //--------------------------------------------------------------------------------------
	/*if( value_pV1 == WICED_FALSE && value_p1 == WICED_TRUE )
	{
		WICED_BT_TRACE("SBZ01\n");

	}
	else if(value_pV1 == WICED_TRUE && value_p1 == WICED_FALSE)
	{
		WICED_BT_TRACE("SBZ10\n");
	}
	else if(value_pV1 == WICED_TRUE && value_p1 == WICED_TRUE)
	{
		WICED_BT_TRACE("SBZ11\n");
	}
	else
	{
		WICED_BT_TRACE("SBZ00\n");
	}*/
	//----------------------------------------------------------------------------------
	if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_P26 ))
	{
		 wiced_hal_gpio_set_pin_output( LED_GPIO_P26, GPIO_PIN_OUTPUT_HIGH);
	}
	else
	{
		wiced_hal_gpio_set_pin_output( LED_GPIO_P26, GPIO_PIN_OUTPUT_HIGH);
	}

	if(value_pa1==WICED_TRUE && datac_comp>0)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_01 ) )
		{
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			if(value_p1==WICED_TRUE)
			{
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
			}
		}
	}

	//-----------------------------------------------------------------

	if(value_paV1==WICED_TRUE && datac_compV>0)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_02 ) )
		{
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			if(value_pV1==WICED_TRUE)
			{
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
			}
		}
	}

	//-----------------------------------------------------------------
	    //WICED_BT_TRACE("DatacrlED2: %d, %d\n",dataFiltCED[0],dataFiltCED[1]);
	//-----------------------------------------------------------------
        //WICED_BT_TRACE("DATA %d, %d\n", dataFiltC[0], dataFiltC[1]);

        if(dataFiltCED[0]>230){dataFiltCED[0]=0;};
        if(dataFiltCED[1]>230){dataFiltCED[1]=0;};
	if(datac_mV > datac_menviadaV)
	{
		datac_v = datac_mV - datac_menviadaV2;
		if(gap_t1 == WICED_FALSE)
		{
			if(datac_v>dataFiltCED[1])
			{
				WICED_BT_TRACE("CVL%d,",datac_v);
			}
			else
			{
				WICED_BT_TRACE("CVL%d,",dataFiltCED[1]);
			}
		}
		else
		{
			WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
		}
	}
	else
	{
		datac_v = datac_menviadaV - datac_menviadaV2;

		if(gap_t1 == WICED_FALSE)
		{
			if(datac_v>dataFiltCED[1])
			{
				WICED_BT_TRACE("CVL%d,",datac_v);
			}
			else
			{
				WICED_BT_TRACE("CVL%d,",dataFiltCED[1]);
			}
		}
		else
		{
			WICED_BT_TRACE("CVL%d,",datac_menviadaV - datac_menviadaV2); //  SCL3
		}

	}

	//-----------------------------------------------------------------
	//-----------------------------------------------------------------

	if(datac_m > datac_menviada)
	{
		//WICED_BT_TRACE("%d",datac_m - datac_menviada2);  //  SCL2
		datac_t = datac_m - datac_menviada2;
		if(gap_t1 == WICED_FALSE)
		{
			if(datac_t > dataFiltCED[0])
			{
				WICED_BT_TRACE("%d",datac_t);
			}
			else
			{
				WICED_BT_TRACE("%d",dataFiltCED[0]);
			}
		}
		else
		{
			WICED_BT_TRACE("%d",datac_m - datac_menviada2);  //  SCL2
		}
	}
	else
	{
		//WICED_BT_TRACE("%d",datac_menviada - datac_menviada2); //  SCL3
		datac_t = datac_menviada - datac_menviada2;

		if(gap_t1 == WICED_FALSE)
		{
			if(datac_t > dataFiltCED[0])
			{
				WICED_BT_TRACE("%d",datac_t);
			}
			else
			{
				WICED_BT_TRACE("%d", dataFiltCED[0]);
			}
		}
		else
		{
			WICED_BT_TRACE("%d",datac_menviada - datac_menviada2); //  SCL3
		}
	}
	if( value_AL==WICED_TRUE || value_AV==WICED_TRUE )
	{
		WICED_BT_TRACE(",1\n");
	}
	else
	{
		WICED_BT_TRACE(",0\n");
	}

	//-----------------------------------------------------------------


	//----------------------------------------------------------------
	if(gap_t1 == WICED_TRUE)
	{
		cont_returnG ++;
		if(cont_returnG==30)
		{
			init_gap();
		}
	}
	else
	{
		cont_returnG = 0;
	}
	//WICED_BT_TRACE("cont_G%d\n",cont_returnG);
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	if(value_le == WICED_TRUE)
	{
		cont_returnER ++;
		if(cont_returnER==30)
		{
			init_event_er();
		}
	}
	else
	{
		cont_returnER = 0;
	}

	if(value_p1==WICED_FALSE && dataFiltCED[0]==0)
	{
		wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
	}

	if(value_pV1==WICED_FALSE && dataFiltCED[1]==0)
	{
		wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
	}

	if(value_onl==WICED_FALSE)
	{
		 WICED_BT_TRACE("OFR\n");
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_25, GPIO_PIN_OUTPUT_HIGH);
	}
	else
	{
		 WICED_BT_TRACE("ONR\n");
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_25, GPIO_PIN_OUTPUT_LOW);
	}
    //if(dataFiltCED[0]>230 && value_p1==WICED_FALSE){wiced_hal_gpio_set_pin_output( LED_GPIO_14, GPIO_PIN_OUTPUT_LOW);};
    //if(dataFiltCED[1]>230 && value_pV1==WICED_FALSE){wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);};
	//WICED_BT_TRACE("cont_G%d\n",cont_returnG);
	//----------------------------------------------------------------

	//WICED_BT_TRACE("SCL:%d\n",datac_menviada);
	//WICED_BT_TRACE("SCV:%d\n",datac_mV);
	//WICED_BT_TRACE_ARRAY(datam_buffer2, 50, "Lamparas abordadas:");
	//WICED_BT_TRACE_ARRAY(datam_bufferV2, 50, "Vehiculos abordados");
	/*WICED_BT_TRACE("Numero de lamparas xx:%d  \n",datac_m);
	WICED_BT_TRACE("Numero de lamparas2 xx:%d  \n",datac_m2);
	WICED_BT_TRACE("Numero de lamparas comp xx:%d  \n",datac_comp);
	WICED_BT_TRACE("Numero de lamparas3 xx:%d  \n",datac_m3);
	WICED_BT_TRACE_ARRAY(datam_buffer, 18, "BUFFER LAMPARAS");
	WICED_BT_TRACE_ARRAY(datam_buffer2, 18, "BUFFER LAMPARAS2");
	WICED_BT_TRACE_ARRAY(datam_buffer3, 18, "BUFFER LAMPARAS3");
	WICED_BT_TRACE("Numero de lamparas st:%d  \n",datac_st);
	WICED_BT_TRACE("Conteo enviado: %d\n",datac_menviada);
	WICED_BT_TRACE("Conteo enviado2: %d\n",datac_menviada2);

	WICED_BT_TRACE("Numero de vehiculos xx:%d  \n",datac_mV);
	WICED_BT_TRACE("Numero de vehiculos2 xx:%d  \n",datac_mV2);
	WICED_BT_TRACE("Numero de vehiculos comp xx:%d  \n",datac_compV);
	WICED_BT_TRACE("Numero de vehiculos3 xx:%d  \n",datac_mV3);
	WICED_BT_TRACE_ARRAY(datam_bufferV, 18, "BUFFER VEHICULOS");
	WICED_BT_TRACE_ARRAY(datam_bufferV2, 18, "BUFFER VEHICULOS2");
	WICED_BT_TRACE_ARRAY(datam_bufferV3, 18, "BUFFER VEHICULOS3");
	WICED_BT_TRACE("Numero de vehiculos st:%d  \n",datac_stV);
	WICED_BT_TRACE("Conteo vehiculos: %d\n",datac_menviadaV);
	WICED_BT_TRACE("Conteo vehiculos2: %d\n",datac_menviadaV2);*/
	/*if(datac_menviada2>0)
	{
		WICED_BT_TRACE("Init RTX \n");
		gap_cfb(datam_buffer2);

	}*/
//	if(datac_menviada2>0 && value_ach == WICED_FALSE)
//	{
//		Start_Timerach();
//		value_ach = WICED_TRUE;
//		WICED_BT_TRACE("ENTER RETR\n");
//	}

//	if(datac_menviadaV2>0 && value_ach == WICED_FALSE)
//	{
//		Start_Timerach();
//		value_achV = WICED_TRUE;
//		WICED_BT_TRACE("ENTER RETRV\n");
//	}

}

/*******************************************************
 * Function name: clear_SB01
 * Description:   clears personnel detection
 *******************************************************/
void clear_SB01(void)
{
	wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
	value_p1=WICED_FALSE;
	value_pa1=WICED_FALSE;
	value_notif=WICED_FALSE;
}

/*******************************************************
 * Function name: clear_SB10
 * Description:   clears personnel vehicle
 *******************************************************/
void   clear_SB10(void)
{
	wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
	value_pV1=WICED_FALSE;
	value_paV1=WICED_FALSE;
	value_notifV=WICED_FALSE;
}

/*******************************************************
 * Function name: init_event_gap
 * Description:   boarding request is confirmed
 *******************************************************/
void init_event_gap(void)
{
  if(!value_gap)
	{
	  WICED_BT_TRACE("Init event gap \n");
	  beacon_set_app_advertisement_data3();
	  //prevention_status();
	  wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	  wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
	}
}

/**************************************************************
 * Function name: print_cst
 * Description:   prints the total count of detected devices
 **************************************************************/
void print_cst(void)
{
	//-----------------------------------------------------------------

	if(datac_mV > datac_menviadaV)
	{
		WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
	}
	else
	{
		WICED_BT_TRACE("CVL%d,",datac_menviadaV - datac_menviadaV2); //  SCL3
	}

	//-----------------------------------------------------------------
	//-----------------------------------------------------------------

	if(datac_m > datac_menviada)
	{
		WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
	}
	else
	{
		WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
	}
	if( value_AL==WICED_TRUE || value_AV==WICED_TRUE )
	{
		WICED_BT_TRACE(",1\n");
	}
	else
	{
		WICED_BT_TRACE(",0\n");
	}
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------

	if(datac_mV > datac_menviadaV)
	{
		WICED_BT_TRACE("CVL%d,",datac_mV - datac_menviadaV2);  //  SCL2
	}
	else
	{
		WICED_BT_TRACE("CVL%d,",datac_menviadaV - datac_menviadaV2); //  SCL3
	}

	//-----------------------------------------------------------------
	//-----------------------------------------------------------------

	if(datac_m > datac_menviada)
	{
		WICED_BT_TRACE("%d\n",datac_m - datac_menviada2);  //  SCL2
	}
	else
	{
		WICED_BT_TRACE("%d\n",datac_menviada - datac_menviada2); //  SCL3
	}
	if( value_AL==WICED_TRUE || value_AV==WICED_TRUE )
	{
		WICED_BT_TRACE(",1\n");
	}
	else
	{
		WICED_BT_TRACE(",0\n");
	}
	//-----------------------------------------------------------------

}

/**************************************************************************
 * Function name: event_mlfb
 * Description:   the mac address of the linked external reader is saved
 **************************************************************************/
void               event_mlfb(void)
{
	if(datac_menviada2>0)
	{
	WICED_BT_TRACE("Event MLFB\n");
	gap_cfb(&datam_buffer2[data_pr]);
	WICED_BT_TRACE("Event MLF %B\n",&datam_buffer2[data_pr]);
	data_pr+=6;
	}
	WICED_BT_TRACE("Cbuf %d\n",datac_menviada2);

}

/*******************************************************
 * Function name: evalue_ach
 * Description: transmission of addressed devices
 *******************************************************/
void evalue_ach(void)
{
	if(datac_menviada2>0 && datac_menviadaV2>0 && value_rah==WICED_FALSE)
	{
		value_rah=WICED_TRUE;
		Start_Timerach();
		WICED_BT_TRACE("Event MLFB\n");
		gap_cfb(&datam_buffer2[data_pr]);
		WICED_BT_TRACE("Event MLF %B\n",&datam_buffer2[data_pr]);
		data_pr+=6;
		clk_ach++;

			if(clk_ach>=datac_menviada2)
			{
				data_pr=0;
				clk_ach=0;
				WICED_BT_TRACE("CLK ACH Clear PR:%d, ACH:%d \n",data_pr,clk_ach);
			}
	}
	else if(datac_menviada2>0 && datac_menviadaV2>0 && value_rah==WICED_TRUE)
	{
		value_rah=WICED_FALSE;
	    Start_Timerach();
		WICED_BT_TRACE("Event MLFBV\n");
		gap_cfbV(&datam_bufferV2[data_prV]);
		WICED_BT_TRACE("Event MLFV %B\n",&datam_bufferV2[data_prV]);
		data_prV+=6;
		clk_achV++;

			if(clk_achV>=datac_menviadaV2)
			{
				data_prV=0;
				clk_achV=0;
				WICED_BT_TRACE("CLKV ACH Clear PR:%d, ACH:%d \n",data_prV,clk_achV);
			}
	}
	else if(datac_menviada2>0 && datac_menviadaV2==0 )
	{
		Start_Timerach();
		WICED_BT_TRACE("Event MLFB2\n");
		gap_cfb(&datam_buffer2[data_pr]);
		WICED_BT_TRACE("Event MLF2 %B\n",&datam_buffer2[data_pr]);
		data_pr+=6;
		clk_ach++;

			if(clk_ach>=datac_menviada2)
			{
				data_pr=0;
				clk_ach=0;
				WICED_BT_TRACE("2CLK ACH Clear PR:%d, ACH:%d \n",data_pr,clk_ach);
			}
	}
	else if(datac_menviada2==0 && datac_menviadaV2>0 )
	{
	    Start_Timerach();
		WICED_BT_TRACE("Event MLFBV2\n");
		gap_cfbV(&datam_bufferV2[data_prV]);
		WICED_BT_TRACE("Event MLFV2 %B\n",&datam_bufferV2[data_prV]);
		data_prV+=6;
		clk_achV++;

			if(clk_achV>=datac_menviadaV2)
			{
				data_prV=0;
				clk_achV=0;
				WICED_BT_TRACE("2CLKV ACH Clear PR:%d, ACH:%d \n",data_prV,clk_achV);
			}
	}

	if(datac_menviada2==0 && datac_menviadaV2==0 )
	{
		value_ach = WICED_FALSE;
		Stop_Timerach();
		WICED_BT_TRACE("Stop ACH\n");
	}
	/*else
	{
		value_ach = WICED_FALSE;
		Stop_Timerach();
		WICED_BT_TRACE("Stop ACH\n");
	}
	WICED_BT_TRACE("Cbuf %d\n",datac_menviada2);
*/
	//-----------------------------------------------------------------
	/*if(datac_menviadaV2>0)
	{
    Start_Timerach();
	WICED_BT_TRACE("Event MLFBV\n");
	gap_cfbV(&datam_bufferV2[data_prV]);
	WICED_BT_TRACE("Event MLFV %B\n",&datam_bufferV2[data_prV]);
	data_prV+=6;
	clk_achV++;

		if(clk_achV==datac_menviadaV2)
		{
			data_prV=0;
			clk_achV=0;
			WICED_BT_TRACE("CLKV ACH Clear PR:%d, ACH:%d \n",data_prV,clk_achV);
		}
	}
	else
	{
		value_achV = WICED_FALSE;
		Stop_Timerach();
		WICED_BT_TRACE("Stop ACHV\n");
	}
	WICED_BT_TRACE("CbufV %d\n",datac_menviadaV2);*/
	//-----------------------------------------------------------------
}

/*******************************************************
 * Function name: clear_cer
 * Description:   external reader counting
 *                data is deleted
 *******************************************************/
void      clear_cer(void)
{
	WICED_BT_TRACE("CLEAR CER\n");
	dataFiltCED[0]=0;
    dataFiltCED[1]=0;
    if(value_p1==WICED_FALSE){wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);};
    if(value_pV1==WICED_FALSE){wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);};
    value_onl=WICED_FALSE;
}

/*******************************************************
 * Function name: filt_cfb
 * Description:   the mac address of the added external
 *                reader is configured
 *******************************************************/
void                filt_cfb(uint8_t *data_cfb2)
{
	memcpy(datac_cfbf2,data_cfb2,6);
	WICED_BT_TRACE("Data Filt: %B\n",datac_cfbf2);
}
