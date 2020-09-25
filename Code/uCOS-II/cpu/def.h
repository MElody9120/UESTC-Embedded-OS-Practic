/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*   MODULE      : demo.c                                                  *
*   AUTHOR      : osboy			                                          		*
*                 URL  : http://mcuos.com                 		            *
*                 EMAIL: mcuos.com@gmail.com                              *
*   PROCESSOR   : NUC710 ARM7TDMI core from NUVOTON		                    *
*                 URL  : http://www.nuvoton.com  													*
*                                                                         *
* modify by Nuvoton PT50 zswan for NUC710	2009/03/03											*
**************************************************************************/


#ifndef __DEF_H__
#define __DEF_H__

#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* */
/* Module configuration */


/* ********************************************************************* */
/* Interface macro & data definition */

#define U32 unsigned int
#define U16 unsigned short
#define S32 signed int
#define S16 signed short
#define U8  unsigned char
#define S8  signed char

#define False 0
#define True !False

/* Sets the result on bPort */
#define BIT_SET(bPort,bBitMask)        (bPort |= bBitMask)
#define BIT_CLR(bPort,bBitMask)        (bPort &= ~bBitMask)

/* Returns the result */
#define GET_BIT_SET(bPort,bBitMask)    (bPort | bBitMask)
#define GET_BIT_CLR(bPort,bBitMask)    (bPort & ~bBitMask)

/* Returns 0 if the condition is False & a non-zero value if it is True */
#define TEST_BIT_SET(bPort,bBitMask)   (bPort & bBitMask)
#define TEST_BIT_CLR(bPort,bBitMask)   ((~bPort) & bBitMask)


/* ********************************************************************* */
/* Interface function definition */


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__DEF_H__*/