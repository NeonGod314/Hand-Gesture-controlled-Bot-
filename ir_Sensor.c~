#include <LPC23xx.h>
//port 2 is used for IR sensor


 __irq void IR(void) 
	{
		IO2_INT_CLR = 0xFF;
		IO2_INT_EN_R = 0X10;		//PIN 2.4
	    VICAddress= 0;
	}

int main(){
	//FIO2DIR = 1;				//ir sensor
   	//FIO2SET = 3;
	FIO2CLR = 0XF;
	PINMODE2 = 0xF;
	VICIntEnable |= 1<<17;
	VICVectPriority17 = 9; 
	VICVectAddr17 = (unsigned long) IR;
	IO2_INT_EN_R = 0X10;
	while(1);	 
}
