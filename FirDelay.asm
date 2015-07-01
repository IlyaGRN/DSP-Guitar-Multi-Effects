////////////////////////////////////////////////////////////////////////
//File Name			:	fir32.asm
//
//List of functions	:	Fir32
///////////////////////////////////////////////////////////////////////
.section program;

//Global Functions
.global	_FirDelay;


//************************************************************************************
//Name		:	Fir32
//Task		:	Applay Fir Filter. The input and output signals are 32 Bit
//Author	: 
//Date		:	28/12/2005
//Input		:	R0 <---- Input sample (32 bit)
//				I1 <---- R1 <---- Address of the input array (32 bit)
//				I0 <---- R2 <---- Address of the coef array (32 bit)
//				[FP+ 20] <-- Input buffer index
//				[FP+ 24] <-- Number of coef 
//
//Output	:	R0 <-- Output <-- conv(input array , coef array )
//
//Registers	:	R0 , R1 , R2 , R3 , R4 , A0 , A1 , B1, B0 , I0 , I1 , L0 , L1
//				P0 , P2 
//Remarks	:	fract32	Fir32(fract32 sample,fract32 *in_buf,fract32 *h_buf,short *in_index,short fir_length);
//Updates	:
//************************************************************************************
_FirDelay: 
	LINK 4; 
	B1 = R1; 			// B1 <-- Input buff start 
	
	R3 = [FP+ 20];		
	P3 = R3;
	     
	R3 = [FP+ 24];      // R3 <-- Filter Length              
	P2 = R3 ;			// P2 <-- Filter Length  
	          
	I0 = R2;			// I0 , B0 <-- Coef buff start 
	B0 = R2 ; 
  
	R1 = [P3];			// R3 <-- Input buffer index
	I1 = R1;			// I1 <-- Input buffer current index    
  
	R3 = R3 << 2;		       
	L1 = R3;			//L1 = fir_length * 4   (32 bit)
	L0 = R3;			//L0 = fir_length * 4   (32 bit)            
	M1 = 8;
	
	[I1] = R0;			// Input buffer <-- New sample
  	nop;nop;      	
	A1 = A0 = 0 || R0 = [ I0++ ] || R1 = [ I1-- ];		
	LSETUP(FIR32_START,FIR32_END) LC1=P2;				// R0 <-- h[k] 	|| R1.H <-- x[n-k]
		
	
	    FIR32_START:	A0 += R0.H*R1.H, A1 += R0.H*R1.L (M);		
		FIR32_END:		R3 = (A1+=R1.H*R0.L)(M) || R0 = [ I0++ ] || R1 = [ I1-- ];	
		
	A1 = A1 >>> 15 || I1+=M1;
	A0 += A1;	
 	R6 = A0;
 	
	
 	
	R0 = R6;					// R0 <-- conv(x,h)					
	R3 = I1;
	[P3] = R3;					// Update the Input buffer index
	L1 = 0;			// Stop cyclic buffers
	L0 = 0;			// Stop cyclic buffers     
    unlink;
    RTS;  
    
 
    
_FirDelay.end: 




/*
_Fir32: 
	LINK 4; 
	B1 = R0; 			// B1 <-- Input buff start 
	R0 = R0 + R2;		// R0 <-- Input buffer current index 
	I1 = R0;			// I1 <-- Input buffer current index    
	     
	R2 = [FP+ 20];                    
	P2 = R2 ;			// P2 <-- Filter Len  
	          
	I0 = R1;			// I0 , B0 <-- Coef buff start 
	B0 = R1 ; 
	             
	R3 = R2 << 2;		       
	L1 = R3;			//L1 = fir_length * 4   (32 bit )
	L0 = R3;			//L0 = fir_length * 4   (32 bit)            
	        
	R4 = [FP+ 24];		// R4 <-- Shift   
	        
	R1 = 0 ; NOP;        	
	A1 = A0 = 0 || R0 = [ I0++ ] || R1 = [ I1-- ];		
	LSETUP(FIR32_START,FIR32_END) LC1=P2;				// R0 <-- h[k] 	|| R1.H <-- x[n-k]
		FIR32_START:	A0 += R0.H*R1.H, A1 += R0.H*R1.L (M);		
		FIR32_END:		R3 = (A1+=R1.H*R0.L)(M) || R0 = [ I0++ ] || R1 = [ I1-- ];	
		
	A1 = A1 >>> 15;
	A0 += A1;		
	A0 = ASHIFT A0 by R4.L; 	// Shift the result by the input shift parameter 
	R0 = A0;					// R0 <-- conv(x,h)					
		
    p0 = [fp+4];				// P0 <-- Back address 
    unlink;
    jump(P0);
	    
_Fir32.end: NOP;
*/
