

/****************************************************************************************************
 *                      电子科技大学嵌入式软件工程中心 版权所有										*
 *																									*
 *                  Copyright (C) 2006 UESTC ESEC													*
 ****************************************************************************************************/

/*
 * $Log:应用程序启动主文件 文件名 ,v$
 *
 * Revision 0.1  日期 时间	系统自动创建
 * 创建本文件
 */

/**
 * @file ucos_TaksManager.c
 * @brief
 *	<li>
 * 		功能: uC/OS任务管理演示
 *	</li>
 *  <li>
 * 		设计思想：这个程序演示基本的任务管理。程序启动具有两个不同优先级的任务，完成任务的挂起和被唤醒的系列动作。
 *  </li>
 *  <p>
 *  	注：本程序只具备演示功能，不能保证适用于您的真实应用。如需使用，请根据您的实际需要修改本程序。
 *  </p>
 *
 * <p>
 * 		部门：电子科技大学嵌入式软件工程中心
 * </p>
 */

/******************************************* 引用部分 ************************************************/
#include "includes.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "NUC900_reg.h"
#include "wblib.h"
#include "NUC900_vpost.h"
#include "NUC900_i2c.h"

extern void lcdprintf(char *pcStr,...);
extern int diag_touch_screen(void);
extern void lcdputchar(int pos_x,int pos_y,char c);
/******************************************* 定义部分 ************************************************/
#define	TASK_STK_SIZE			4096              	// Size of each task's stacks (# of WORDs)
#define	N_TASKS					6                  	// Number of identical tasks
#define	TASK_START_ID			0		             	// Application tasks IDs

OS_STK		TaskStk[N_TASKS][TASK_STK_SIZE];	// Tasks stacks
OS_STK		TaskStartStk[TASK_STK_SIZE];		  // TaskStart  task stack
INT8U		TaskData[N_TASKS];					      // Parameters to pass to each task

OS_EVENT *q1;
INT32U	count=0;							            // Initialize count
char adc_value[12]="Times:";
#undef sysPrintf
#define sysPrintf printf
/******************************************* 声明部分 ************************************************/

static		void	Task0(void *pdata); 		    // Function prototypes of tasks
static		void	Task1(void *pdata);
static		void	Task2(void *pdata);
static		void	Task3(void *pdata);

static int volatile LCD_BUFF_BASE;  // printf 
static		void	TaskStart(void *pdata);		  // Function prototypes of Startup task
static		void	TaskStartCreateTasks(void);	// Function prototypes of creat task

/******************************************* 实现部分 ************************************************/
/**

 * @brief
 * main()函数，应用程序入口函数。
 * @param[in]	无。
 * @return 操作成功返回0；\n
 *         出现问题返回1；
 * @author Melody
 * @Last update 2020-09-17 19:33:08
 */

void printfLcd(int cl)  // printf Lcd (color)
{

	LCDFORMATEX lcdformatex;
    UINT32 		*pframbuf=NULL;
    int			i;int j;int size=0;int k=0;
    
	lcdformatex.ucVASrcFormat = VA_SRC_RGB565;
    vpostLCMInit(&lcdformatex);
	pframbuf = vpostGetFrameBuffer();
	LCD_BUFF_BASE = (int) pframbuf;
		
	for(j=1;j<=120;j++)
	{
		for(i=1;i<=240;i+=2)
   	 {
    	size=cl;  // color
    	k+=2;
    	*pframbuf++ =size;
    	
   	 }
   	 size+=1;
	}
	         
	outpw(REG_AIC_GEN, inpw(REG_AIC_GEN) | 0x01);    
}


void cleanLcd()  // clean lcd 
{

	LCDFORMATEX lcdformatex;
    UINT32 		*pframbuf=NULL;
    int			i;int j;int size=0;int k=0;
    
	lcdformatex.ucVASrcFormat = VA_SRC_RGB565;
    vpostLCMInit(&lcdformatex);
	pframbuf = vpostGetFrameBuffer();
	LCD_BUFF_BASE = (int) pframbuf;
		
	for(j=1;j<=240;j++)
	{
		for(i=1;i<=320;i+=2)
   	 {
    	size=0x0;  // color
    	k+=2;
    	*pframbuf++ =size;
    	
   	 }
   	 size+=1;
	}
	         
	outpw(REG_AIC_GEN, inpw(REG_AIC_GEN) | 0x01);    

}


int  main (void)
{
	INT8U err=err;
	void *Msg1[6];
	OSInit();	
	q1=OSQCreate(&Msg1[0],6);
	lcdprintf("");
	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 4);
	OSStart();	// Start multitasking

	return 0;
}

/**
 * @brief
 * TaskStart()函数，启动任务。
 * @param[in]	void *。
 * @return 无\n
 * @author Melody 
 * @last update 2020-09-22 21:54:50
 */
void	TaskStart(void *pdata)
{
#if OS_CRITICAL_METHOD == 3 					// Allocate storage for CPU status register
	OS_CPU_SR  cpu_sr;
	cpu_sr = cpu_sr;							// Avoid warnings
#endif

	pdata = pdata;								// Prevent compiler warning
	
	BSP_Init();
	OSStatInit();
	TaskStartCreateTasks();						// Create all the application tasks

	OSTaskSuspend(OS_PRIO_SELF);				// Suspend the TaskStart
}

/**
 * @brief
 * TaskStartCreateTasks()函数，创建多任务。
 * @param[in]	void *。
 * @return 无
 * @author Melody
 * @last update 2020-09-22 21:55:23
 */
void  TaskStartCreateTasks (void)
{
	INT8U  i;

	for (i = 0; i < N_TASKS; i++)				// Create tasks
	{
		TaskData[i] =  i;						// Each task will display its own information
	}

	OSTaskCreate(Task0, (void *)&TaskData[0], &TaskStk[0][TASK_STK_SIZE - 1], 5);
	OSTaskCreate(Task1, (void *)&TaskData[1], &TaskStk[1][TASK_STK_SIZE - 1], 6);
	OSTaskCreate(Task2, (void *)&TaskData[2], &TaskStk[2][TASK_STK_SIZE - 1], 7);
	OSTaskCreate(Task3, (void *)&TaskData[3], &TaskStk[3][TASK_STK_SIZE - 1], 8);
}

/**
 * @brief
 * Task0()函数，执行一个任务，打印当前的CPU使用情况。
 * @param[in]	void *。
 * @return 无
 * @author Melody
 * @last Update 2020-09-22 14:43:29
 */
 
void  Task0 (void *pdata)
{
	INT8U i=i;
	INT8U err=err;
	i=*(int*)pdata;


	for(;;)
	{

	lcdprintf(" CPUUsage:%d %%\n",OSCPUUsage); //添加一个空在要打印的字符前，不然会吃字符

	OSTimeDlyHMSM(0,0,0,500); //标准时设置。
	err=OSTaskResume(6);
	}
	
	
}

/**
 * @brief
 * 	Task1()函数，执行一个任务，根据CPU占用显示不同的色块。
 * @param[in]		void *。
 * @return 无
 * @author Melody
 * @last Update 2020-09-17 19:32:47
 */

void  Task1 (void *pdata) // printf color picture
{
	
	INT8U i=i;
	INT8U err=err;
	i=*(int*)pdata;
	for(;;){
		
		if((OSCPUUsage % 10) == 2)
		{
			printfLcd(0xF123); //RED
			OSTimeDlyHMSM(0,0,0,500);
			err=OSTaskSuspend(6);
			
		}
		else if((OSCPUUsage % 10) == 3)
		{
			printfLcd(0x7BEF);  //GRAY
			OSTimeDlyHMSM(0,0,0,500);
			err=OSTaskSuspend(6);
			
		}
		else if((OSCPUUsage % 10) == 5 ||(OSCPUUsage % 10) == 6 )
		{	
			printfLcd(0xF077);//Purple
			OSTimeDlyHMSM(0,0,0,500);
			err=OSTaskSuspend(6);
			
		}
		else
		{
			printfLcd(0xFFFF);  //white
			OSTimeDlyHMSM(0,0,0,500);
			err=OSTaskSuspend(6);
			
		}
	}
	
}

/**
 * @brief
 * 	Task2()函数，执行一个任务，发送消息队列。
 * @param[in] void *。
 * @return 无
 * @author Melody
 * @last Update 2020-09-22 14:44:19
 */

void Task2(void *pdata)
{

	INT8U i,j;
	INT8U err;
	INT8U note=1;
	INT16U del=3;
	OS_EVENT *q;
	OS_Q_DATA data;
	static char *s[]={
						"Melody",
						"Lixiaobailing",
						"ck!p",
						"gyb",
						"115",
						"Nier:Automata"
    };
	pdata=pdata;
	for(;;)
	{
	for(i=0;i<6;i++)
	{
		err=OSQPostFront(q1,(void*)s[i]);
		
		switch(err)
		{
			case OS_NO_ERR:
			OSTimeDlyHMSM(0,0,0,500);
			break;
			case OS_Q_FULL:
			OSTimeDlyHMSM(0,0,0,150);
			break;
			default:
			break;
		}
		
	}
	}
}

/**
 * @brief
 * 	Task3()函数，执行一个任务，收消息队列,并清屏。
 * @param[in]		void *。
 * @return 无
 * @author Melody
 * @last Update 2020-09-22 15:50:46
 */


void	Task3 (void *pdata) 
{	
  INT8U err;
  INT8U id;
  int i = 0;
  void *mg;
  
  id=*(int*)pdata;
  for(;;)
  {
  	
  	mg=OSQPend(q1,0,&err);
  	switch(err)
  	{
  		case OS_NO_ERR:
  		lcdprintf(" Got Message %s\n",(char*)mg);
		i ++;
  		OSTimeDlyHMSM(0,0,0,500);
  		if(i == 5) {
			  cleanLcd();
			  i = 0;
		  }
  		break;
  		default:
  		OSTimeDlyHMSM(0,0,0,250);
  		break;
  	}
  
  }
	
}