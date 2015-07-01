//--------------------------------------------------------------------------//
//																			//
//	 Name: 	Simple Guitar Multi-effect
//
//   By Ilya Grinshpoun 2015				
//	
//   The code Implements four digital guitar effects: Delay, Fuzz, Distortion, Vibrato
//
//	 Switching between the effects with sw1 on the EZKIT
//
//   (based on "talkthrough" example)
//--------------------------------------------------------------------------//

#include "Talkthrough.h"
#include "sysreg.h"
#include "ccblkfn.h"


// left input data from ad1836
fract32 iChannel0LeftIn, iChannel1LeftIn;
// right input data from ad1836
fract32 iChannel0RightIn, iChannel1RightIn;
// left ouput data for ad1836	
fract32 iChannel0LeftOut, iChannel1LeftOut;
// right ouput data for ad1836
fract32 iChannel0RightOut, iChannel1RightOut;
// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{									
					DAC_CONTROL_1	| 0x000,
					DAC_CONTROL_2	| 0x000,
					DAC_VOLUME_0	| 0x3ff,
					DAC_VOLUME_1	| 0x3ff,
					DAC_VOLUME_2	| 0x3ff,
					DAC_VOLUME_3	| 0x3ff,
					DAC_VOLUME_4	| 0x3ff,
					DAC_VOLUME_5	| 0x3ff,
					ADC_CONTROL_1	| 0x000,
					ADC_CONTROL_2	| 0x180,
					ADC_CONTROL_3	| 0x000
					
};
// SPORT0 DMA transmit buffer
volatile fract32 iTxBuffer1[8];
// SPORT0 DMA receive buffer
volatile fract32 iRxBuffer1[8];
short i=4;
int y;
int yn=0;
int xn=0;
short eS=0;
int LedTimer=0;
int ledBar=0;
int buttonCheck=0;




void main(void)
{

	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_EBIU();//External Bs init
	Init_Flash();//Flash init (ports and push buttons connected through flash)
	Init1836();	//Audio Codec Initiation
	Init_SDRAM();//SDRAM INIT for large delay buffer
	Init_Sport0();//S Port init
	Init_DMA(); //DMA init
	Init_Sport_Interrupts();//Init Interrapt for sPort
	Init_Flags();//Init interapt for push button
	Enable_DMA_Sport0();
	Init_Interrupts();//Global Interrapt Enable
	while(1);
}
