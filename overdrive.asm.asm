
.section program;

//Global Functions
.global	_Overdrive;


//************************************************************************************
	// This function implementing filtering and overdriving
	// It consists from a regular cyclic convolution stage, then saturation stage
//************************************************************************************
_Overdrive: 
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
 	
 	//Distortion
 	R3.l=0x0000;
 	R3.h=0x0000;
 	CC = R3 <R6;
 		if CC jump Sat1;
 	
 	CC = R6< R3 ;
 		if CC jump Sat2;
 
 		
 	k:
	R0 = R6;					// R0 <-- conv(x,h)					
	R3 = I1;
	[P3] = R3;					// Update the Input buffer index
	L1 = 0;			// Stop cyclic buffers
	L0 = 0;			// Stop cyclic buffers     
    unlink;
    RTS;  
    
      Sat1:
    	R6.l=0xFFFA;//Overdriving the input
    	R6.h=0x7FFF;//Overdriving the input
    	jump k;
    	
    Sat2:
    	R6.l=0x0002;//Overdriving the input
    	R6.h=0x800F;//Overdriving the input
    	jump k;
    
  
_Overdrive.end: 




