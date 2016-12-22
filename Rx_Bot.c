#include <LPC23xx.h>

int data1;

__irq void uart(void) {
    while((U1LSR & 0X01)==1)
    {
        data1=U1THR ;
    }
    VICVectAddr=0;
 }

 __irq void IR(void)
{	
	//stop	
	IOCLR0 = 0x00000090; //P0.4,0.7 goes LOW	
	
	IO2_INT_CLR = 0xFF;
	IO2_INT_EN_R= 0X10;        //PIN 2.4    
	VICVectAddr =0    ;
}

int main(){
		//RX uart
		PINSEL0=0X40000000;    
		PINSEL1=0X00000001;
		U1LCR = 0x83;
		U1DLM = 0;
		U1DLL = 78;
		//U1FDR =0X21;
		U1LCR = 0x03;
		U1FCR = 0x07;
		//U1TER|=0x80;
		U1IER=0x0F;     
		//PCONP|=0x10;
		VICVectAddr7= (unsigned long) uart ;
		VICVectPriority7 = 0;
		VICIntSelect=0;
		VICIntEnable|= 1<<7;

		//IR sensor
		PINSEL4=0X00000000; //2.4
    FIO2DIR = 0;                
    FIO2SET = 3;
    FIO2CLR = 0XF;
    PINMODE2 = 0xF;
    VICIntEnable = 17;
		VICVectPriority17 = 0;
    VICIntEnable |= 1<<17;
    VICVectAddr17 = (unsigned long) IR;
		IO2_INT_EN_R = 0X10;

		//Initializations for motor driver pins
		IODIR0 = 0x000003F0 ; //pin P0.4,0.5,0.6,0.7,0.8,0.9 configured as output
		IOCLR0 = 0x000003F0 ; //pin P0.4,0.5,0.6,0.7,0.8,0.9 goes LOW

		while(1){
		if(data1=='r'){
			IOCLR0 = 0x000000C0;//P0.6,P0.7 goes LOW
			IOSET0 = 0x00000030;//P0.4,P0.5 goes HIGH
		}
	
		else if(data1=='l'){
			IOCLR0 = 0x00000210;//P0.4,P0.9 goes LOW
			IOSET0 = 0x00000180;//P0.4,P0.5 goes HIGH
		}

		else if(data1=='f'){
			IOCLR0 = 0x00000240; //pin P0.4,0.5,0.6,0.7,0.8,0.9 goes LOW
			IOSET0 = 0x000001B0; //P0.4,0.5,0.7,0.8 goes HIGH
		}
		
		else if(data1=='b'){
			IOCLR0 = 0x00000120; //P0.5,0.8 goes LOW	
			IOSET0 = 0x000002D0; //P0.4,0.5,0.7,0.8 goes HIGH
		}
	
		else if(data1=='s'){
			IOCLR0 = 0x00000090; //P0.4,0.7 goes LOW	
		}
	}	
}

