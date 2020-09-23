#include "stdio.h"
#include "stdlib.h"

extern void lcdprintf(char *pcStr,...);
//extern int diag_touch_screen(void);
extern void lcdputchar(int pos_x,int pos_y,char c);

int main()
{
	//diag_touch_screen();
	lcdprintf("hello world 2\n");
	lcdputchar(4,8,'a');
	lcdputchar(28,7,'b');
	while(1);
	return 0;
}