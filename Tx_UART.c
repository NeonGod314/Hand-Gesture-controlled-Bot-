#include <LPC23xx.h>

int main(void){
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
    while(1)
    {
        U1THR='A';
        while(!(U1LSR & 0x20));
    }
while(1);
}
