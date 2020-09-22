	AREA Vect,CODE,READONLY
	CODE32
	ENTRY
   	IMPORT  sysIrqHandler
 	IMPORT  sysFiqHandler
 	IMPORT __main
 	GLOBAL reset_addr
reset_addr       
    b reset_handler       ;reset 
    SPACE 100
reset_handler
	MRC p15,0,R0,c1,c0,0
	BIC R0,R0,#0x2000
	MCR p15,0,R0,c1,c0,0
    MRS R0,CPSR                   ;CPSR->R0
    ;BIC R0,R0,#0xc0               ;enable irq and fiq
    MSR CPSR_c,R0                 ;R0->CPSR
	bl __main
	mov pc,lr
	END