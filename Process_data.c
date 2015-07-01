#include "Talkthrough.h"
#include "math.h"

#define N 11
#define J 80000



extern fract32 		f32Fir1Buf [N];
extern fract32      f32Fir2Buf [N];
extern fract32 		f32Fir1Coef [N];
extern fract32 		f32Fir2Coef [N];

extern fract32      f32IIRNumCoef[N];
extern fract32      f32IIRDenCoef[N];
extern fract32      f32IIRYbuf [N];		// y IIR buffer
extern fract32      f32IIRXbuf [N];		// x IIR buffer		 //	    

extern fract32 		f32Fir3Buf [J]={0};


extern fract32*			pFir1Index  	= f32Fir1Buf;
extern fract32*			pFir2Index  	= f32Fir2Buf;

extern fract32*			pIIRNumXIndex  	= f32IIRXbuf;
extern fract32*			pIIRDenYIndex  	= f32IIRYbuf;

extern int f32FirDelayBufStart=0x001295D0;
extern int f32FirDelayBufCoef=0x000094AE8;
extern int* f32FirDelayBufIndex=&f32FirDelayBufStart;

extern int e=0;
extern int f=J-1;
extern int l=J/2;


extern fract32 n=0;;
extern float T=0.0000833;

volatile short		sFir1length 	= N;
volatile long		sFirDelaylength = J;
//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{

	switch(i){
	
	case 0:{//Delay Effect
	
		y = DelayEffect(iChannel0RightIn);     //Calling Delay Effect Function
		iChannel0RightOut=y;
		break;
		}
	case 1:{//Fuzz
	xn = 0.2*Overdrive(iChannel0RightIn,f32Fir1Buf,f32Fir1Coef,&pFir1Index,sFir1length); //Calling Overdrive function
	xn = Fir(xn,f32IIRXbuf,f32IIRNumCoef,&pIIRNumXIndex,sFir1length);                    //IIR BPF
	yn = Fir(iChannel0RightOut,f32IIRYbuf,f32IIRDenCoef,&pIIRDenYIndex,sFir1length);
	iChannel0RightOut =xn-yn;
	
	break;
	}
	case 2:{//Distortion
	y=0.1*Overdrive(iChannel0RightIn,f32Fir1Buf,f32Fir1Coef,&pFir1Index,sFir1length);     
	iChannel0RightOut=y;	
	break;	
	}
	case 3:{//Vibration /Modulator
	y=3*Vibrato(iChannel0RightIn);
	iChannel0RightOut=y;	
	break;	
	}
	case 4:{//Bypass
	iChannel0RightOut=iChannel0RightIn;
	break;	
	}
	default:break;
	}
	
	
}




int DelayEffect(fract32 in){

	int out=0;
	out = 1.5*in + 0.95*f32Fir3Buf[l]+0.65*f32Fir3Buf[e]+0.45*f32Fir3Buf[e/2]+0.25*f32Fir3Buf[e/4];
	f32Fir3Buf[f]=in;
	
	if (e==(J-1))
		{e=0;}
	else
		{e++;}
	
	if (f==(J-1))
		{f=0;}
	else
		{f++;}
		
	if (l==(J-1))
		{l=0;}
	else
		{l++;}

	return out;
}


fract32 Vibrato(fract32 in){
	fract32 out=0;
	
	if(eS)
		out=in*(1+sin(2*3.141592654*T*n)); //Tremolo
	else
		out=in*sin(2*3.141592654*T*n);	//Ring Modulator
	
	if(n==48000){
	n=0;
	}
	else{
	n++;	
	}
	
	return out;
}
