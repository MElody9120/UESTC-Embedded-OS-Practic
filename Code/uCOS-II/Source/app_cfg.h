/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                                          Atmel AT91SAM9260
*                                                on the
*                                  Atmel AT91SAM9260-EK Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_COM_EN                      DEF_ENABLED       /* DEF_ENABLED = Present, DEF_DISABLED = Not Present         */
#define  APP_CFG_PROBE_OS_PLUGIN_EN                DEF_ENABLED
#define  APP_CFG_PROBE_DEMO_INTRO_EN               DEF_ENABLED

/*
*********************************************************************************************************
*                                            TASKS PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                          2

#define  APP_CFG_TASK_USER_IF_PRIO                        3
#define  APP_CFG_TASK_KBD_PRIO                            4

#define  OS_PROBE_TASK_PRIO                               9
#define  OS_PROBE_TASK_ID                                 9

#define  PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO              10

#define  OS_TASK_TMR_PRIO                        (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                            Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE                    128
#define  APP_CFG_TASK_KBD_STK_SIZE                      128
#define  APP_CFG_TASK_USER_IF_STK_SIZE                  128

#define  OS_PROBE_TASK_STK_SIZE                         128

#define  PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE         128

/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                                    1     /* Task will be created for uC/Probe OS Plug-In             */
#define  OS_PROBE_TMR_32_BITS                             0     /* uC/Probe OS Plug-In timer is a 32-bit timer              */
#define  OS_PROBE_TMR_SEL                                 2     /* Select timer 2 for uC/Probe OS Plug-In timer             */
#define  OS_PROBE_HOOKS_EN                                1     /* Hooks to update OS_TCB profiling members will be included*/

/*
*********************************************************************************************************
*                                      uC/OS-II DCC CONFIGURATION
*********************************************************************************************************
*/

#define  OS_CPU_ARM_DCC_EN                                1


/*
*********************************************************************************************************
*                                        BSP CONFIGURATION
*
* Note(s) : (1) BSP_CFG_SER_COMM_SEL defines the UART to be used to output the system state:
*
*                   BSP_SER_COMM_UART_00           UART #0  is selected to output the system state
*                   BSP_SER_COMM_UART_01           UART #1  is selected to output the system state
*                   BSP_SER_COMM_UART_DBG          UART DBG is selected to output the system state
*            
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL                      BSP_SER_COMM_UART_DBG

/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                                  0
#define  TRACE_LEVEL_INFO                                 1
#define  TRACE_LEVEL_DBG                                  2

#define  APP_CFG_TRACE_LEVEL                       TRACE_LEVEL_INFO
#define  BSP_CFG_TRACE_LEVEL                       TRACE_LEVEL_INFO

#define  APP_CFG_TRACE                             BSP_Ser_Printf           
#define  BSP_CFG_TRACE                             BSP_Ser_Printf               

#define  BSP_TRACE_INFO(x)                        ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_INFO) ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DBG(x)                         ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_DBG)  ? (void)(BSP_CFG_TRACE x) : (void)0)

#define  APP_TRACE_INFO(x)                        ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                         ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)


#endif
