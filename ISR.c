#include "Talkthrough.h"

//--------------------------------------------------------------------------//
// Function:	Sport0_RX_ISR												//
//																			//
// Description: This ISR is executed after a complete frame of input data 	//
//				has been received. The new samples are stored in 			//
//				iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		//
//				iChannel1RightIn respectively.  Then the function 			//
//				Process_Data() is called in which user code can be executed.//
//				After that the processed values are copied from the 		//
//				variables iChannel0LeftOut, iChannel0RightOut, 				//
//				iChannel1LeftOut and iChannel1RightOut into the dma 		//
//				transmit buffer.											//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	// copy input data from dma input buffer into variables
	iChannel0LeftIn = iRxBuffer1[INTERNAL_ADC_L0];
	iChannel0RightIn = iRxBuffer1[INTERNAL_ADC_R0];
	iChannel1LeftIn = iRxBuffer1[INTERNAL_ADC_L1];
	iChannel1RightIn = iRxBuffer1[INTERNAL_ADC_R1];

	// call function that contains user code
	Process_Data();				

	// copy processed data from variables into dma output buffer
	iTxBuffer1[INTERNAL_DAC_L0] = iChannel0LeftOut;
	iTxBuffer1[INTERNAL_DAC_R0] = iChannel0RightOut;
	iTxBuffer1[INTERNAL_DAC_L1] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_L2] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_R1] = iChannel1RightOut;
	iTxBuffer1[INTERNAL_DAC_R2] = iChannel1RightOut;
}

EX_INTERRUPT_HANDLER(FlagA_ISR)
{
	static unsigned char ucActiveLED =0x00;
	// confirm interrupt handling
	FIO_ANOM_0311_FLAG_W(0x0100,pFIO_FLAG_C);//*pFIO_FLAG_C = 0x0100, workaround for anomaly 05000311.

	// toggle direction of moving light
	if(i==4){
	i=0;
	}
	else{
	i++;
	}
	
	switch(i){
	case 0:{ucActiveLED=0x20;break;}
	case 1:{ucActiveLED=0x10;break;}
	case 2:{ucActiveLED=0x08;break;}
	case 3:{ucActiveLED=0x04;break;}
	case 4:{ucActiveLED=0x00;break;}
	default:break;
	}
	*pFlashA_PortB_Data=ucActiveLED;
	
	
	
}

EX_INTERRUPT_HANDLER(FlagB_ISR)
{
	
	// confirm interrupt handling
	FIO_ANOM_0311_FLAG_W(0x0200,pFIO_FLAG_C);//*pFIO_FLAG_C = 0x0100, workaround for anomaly 05000311.
	eS=~eS;
	//if(eS)
	//	f=80000-1;
	//else
	//	f=40000-1;
	
}


EX_INTERRUPT_HANDLER(Timer0_ISR){//Not working well yet
	
	static unsigned char ucActive_LED=0x01;
	
	*pTIMER_STATUS=0x0001;
	
	if(y>15)
		{ucActive_LED=0x1F;}
	else{ucActive_LED=0x3F;}
	
	if(y>4095)
		{ucActive_LED=0x0F;}
	
	if(y>65535)
		{ucActive_LED=0x07;}
		
	if(y>1048575)
		{ucActive_LED=0x03;}
			
	if(y>2147483647)
		{ucActive_LED=0x01;}
		
	if(y>2952790015)
		{ucActive_LED=0x00;}
	
	
	*pFlashA_PortB_Data=ucActive_LED;
	
}
