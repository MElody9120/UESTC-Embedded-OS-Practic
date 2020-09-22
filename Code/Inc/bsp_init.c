#include  <stdarg.h>
#include  <stdio.h>

#include "includes.h"

#define SYS_CLOCK			15000000

#if 0
void  BSP_Serial_init(void)
{
	WB_UART_T 		uart;
	
	uart.uart_no = WB_UART_0;
        uart.uiFreq = EXTERNAL_CRYSTAL_CLOCK;
        uart.uiBaudrate = 115200;
        uart.uiDataBits = WB_DATA_BITS_8;
        uart.uiStopBits = WB_STOP_BITS_1;
        uart.uiParity = WB_PARITY_NONE;
        uart.uiRxTriggerLevel = LEVEL_1_BYTE;
		
	sysInitializeUART(&uart);
}

#endif
void BSP_OS_TmrTickInit(void )
{
#if OS_CRITICAL_METHOD == 3                         /* Allocate storage for CPU status register           */
        OS_CPU_SR  cpu_sr;
#endif

        OS_ENTER_CRITICAL();

	sysSetTimerReferenceClock (TIMER0, 15000000);
	sysStartTimer(TIMER0, 100, PERIODIC_MODE);

        OS_EXIT_CRITICAL();
}
#if 0
VOID RTC_SetTime()
{
	   
	RTC_TIME_DATA_T td;
      td.ucClockDisplay = RTC_CLOCK_12;  /* Set 12-hour mode have to set ucAmPm                  */
      td.ucAmPm = RTC_AM;

      td.uYear = 2009;
      td.ucMonth = 1;
      td.ucDay = 3;
      td.ucDayOfWeek = WEDNESDAY;
      td.ucHour = 11;
      td.ucMinute = 59;
      td.ucSecond = 55;
     // RTC_Write(CURRENT_TIME, &td);
}

void BSP_RTC_Init(void)
{
	//RTC_Init();
	//RTC_SetTime();
}
#endif

void  BSP_Init (void)
{
	OS_CPU_InitExceptVect (); //Initialize the vector table  
	//BSP_Serial_init();		//init Uart0 for debug
	BSP_OS_TmrTickInit(); // Initialize the uC/OS-II ticker 
	//BSP_RTC_Init();
}

