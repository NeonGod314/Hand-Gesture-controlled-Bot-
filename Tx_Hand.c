#include <LPC23xx.h>

int data1;
int main(void){

		//UART initailzations
		PINSEL0 = 0X40000000;	
		PINSEL1 = 0X00000001;
		U1LCR = 0x83; 
		U1DLM = 0; 
		U1DLL = 78; 
		//U1FDR = 0X21; 
		U1LCR = 0x03; 
		U1FCR = 0x07; 
		U1TER|= 0x80;
		//U1IER=0x01;

		//input interrupts
		PINSEL4 = 0X00000000; 	//pin P2.0,2.1,2.2,2.3,2.4
    FIO2DIR = 0x00000000;  //pins configured as Input  
	
		//uart transmitter
		while(1)
		{	
			if(FIO2PIN0 & 0X01)			{
				data1='f';
			}
			
			else if(FIO2PIN0 & 0X02){
				data1='r';
			}
			
			else if(FIO2PIN0 & 0X04){
				data1='l';
			}
			
			else if(FIO2PIN0 & 0X08){
				data1='b';
			}
			
			else if(FIO2PIN0 & 0x10){
				data1='s';
			}
				U1THR=data1;
				while(!(U1LSR & 0x20));
		}
	
}
