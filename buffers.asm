////////////////////////////////////////////////////////////////////////
//File Name			:	buffers.asm
//
//List of functions	:	
///////////////////////////////////////////////////////////////////////
#define N 11

#define J 80000

.section data1;

.byte4 		_f32Fir1Buf [J];
.byte4 		_f32Fir2Buf [N];


.byte4 		_f32FirDelayBufStart [N];

// ! In Blackfin processors, fract 1.15 is a default. Use a /R32 qualifier (in .BYTE4/R32 or .VAR/R32)
// to support 32-bit initialization for use with 1.31 fracts.
.byte4/R32 	_f32Fir1Coef [N] = "h.dat";
.byte4/R32 	_f32Fir2Coef [N] = "g.dat";	

.byte4/R32 	_f32IIRNumCoef [N] = "num.dat";	 //IIR Numerator Coef Buffer 
.byte4/R32 	_f32IIRDenCoef [N] = "den.dat";	 //IIR Denumerator Coef Buffer 

.byte4/R32 	_f32IIRYbuf [N];		// y IIR buffer
.byte4/R32 	_f32IIRXbuf [N];		// x IIR buffer		 //	

	
//.byte4/R32 	_f32FirDelayCoef [J] = "delay.dat";	

//.global     _f32FirDelayBuf;
.global 	_f32Fir1Buf;
.global 	_f32Fir2Buf;
//.global     _f32FirDelayBufStart
.global 	_f32Fir1Coef;
.global 	_f32Fir2Coef;
.global     _f32IIRDenCoef;
.global     _f32IIRNumCoef;

.global 	_f32IIRYbuf;
.global 	_f32IIRXbuf;
