#ifndef  __Talkthrough_DEFINED
	#define __Talkthrough_DEFINED

//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>
#include <ccblkfn.h>
#include <sysreg.h>
#include <fract.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/05000311.h>

//--------------------------------------------------------------------------//
// Symbolic constants														//
//--------------------------------------------------------------------------//
// addresses for Port B in Flash A
#define pFlashA_PortA_Dir	(volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data	(volatile unsigned char *)0x20270004

#define pFlashA_PortB_Dir	(volatile unsigned char *)0x20270007
#define pFlashA_PortB_Data	(volatile unsigned char *)0x20270005

// names for codec registers, used for iCodec1836TxRegs[]
#define DAC_CONTROL_1		0x0000
#define DAC_CONTROL_2		0x1000
#define DAC_VOLUME_0		0x2000
#define DAC_VOLUME_1		0x3000
#define DAC_VOLUME_2		0x4000
#define DAC_VOLUME_3		0x5000
#define DAC_VOLUME_4		0x6000
#define DAC_VOLUME_5		0x7000
#define ADC_0_PEAK_LEVEL	0x8000
#define ADC_1_PEAK_LEVEL	0x9000
#define ADC_2_PEAK_LEVEL	0xA000
#define ADC_3_PEAK_LEVEL	0xB000
#define ADC_CONTROL_1		0xC000
#define ADC_CONTROL_2		0xD000
#define ADC_CONTROL_3		0xE000

// names for slots in ad1836 audio frame
#define INTERNAL_ADC_L0			0
#define INTERNAL_ADC_L1			1
#define INTERNAL_ADC_R0			4
#define INTERNAL_ADC_R1			5
#define INTERNAL_DAC_L0			0
#define INTERNAL_DAC_L1			1
#define INTERNAL_DAC_L2			2
#define INTERNAL_DAC_R0			4
#define INTERNAL_DAC_R1			5
#define INTERNAL_DAC_R2			6

// size of array iCodec1836TxRegs and iCodec1836RxRegs
#define CODEC_1836_REGS_LENGTH	11

// SPI transfer mode
#define TIMOD_DMA_TX 0x0003

// SPORT0 word length
#define SLEN_32	0x001f

// DMA flow mode
#define FLOW_1	0x1000

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
extern fract32 iChannel0LeftIn;
extern fract32 iChannel0RightIn;
extern fract32 iChannel0LeftOut;
extern fract32 iChannel0RightOut;
extern fract32 iChannel1LeftIn;
extern fract32 iChannel1RightIn;
extern fract32 iChannel1LeftOut;
extern fract32 iChannel1RightOut;
extern volatile short sCodec1836TxRegs[];
extern volatile fract32 iRxBuffer1[];
extern volatile fract32 iTxBuffer1[];

//--------------------------------------------------------------------------//
// Prototypes			
void Init_Flags(void);

void Init_Interrupts(void);													//
//--------------------------------------------------------------------------//
// in file Initialisation.c
void Init_EBIU(void);
void Init_Flash(void);
void Init_SDRAM(void);
void Init1836(void);
void Init_Sport0(void);
void Init_DMA(void);
void Init_Sport_Interrupts(void);
void Enable_DMA_Sport(void);
void Enable_DMA_Sport0(void);
void Init_Timer(void);
int DelayEffect(fract32 in);
fract32 Vibrato(fract32 in);

// in file Process_data.c
void Process_Data(void);

// in file ISRs.c
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
EX_INTERRUPT_HANDLER(FlagA_ISR);
EX_INTERRUPT_HANDLER(FlagB_ISR);
EX_INTERRUPT_HANDLER(Timer0_ISR);
// in file fir32.asm
extern int	Overdrive(fract32 sample,fract32 *in_buf,fract32 *h_buf,fract32 **in_index,short fir_length);
extern int	Fir(fract32 sample,fract32 *in_buf,fract32 *h_buf,fract32 **in_index,short fir_length);
extern int	FirDelay(fract32 sample,fract32 *in_buf,fract32 *h_buf,fract32 **in_index,short fir_length);
extern void ini(void);
extern short eS;
extern int y;
extern int LedTimer;
extern int e;
extern int f;
extern int l;
extern int ledBar;
extern fract32 n;
extern float T;
extern int buttonCheck;
extern int yn;
extern int xn;

extern fract32*			pFir1Index;
extern fract32*			pFir2Index;


extern int f32FirDelayBufStart;
extern int* f32FirDelayBufIndex;
extern int f32FirDelayBufCoef;


extern short i;
#endif //__Talkthrough_DEFINED
