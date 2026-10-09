#include<lpc21xx.h>
void uart0_init(unsigned int boud)
{
int pclk,result=0;
if(VPBDIV==0x00)
pclk=15000000;
 if(VPBDIV==0x01)
pclk=60000000;
if(VPBDIV==0x02)
pclk=30000000;
result=pclk/(16*boud);
PINSEL0|=0x00000005;
U0LCR=0x83;
U0DLL=(result&0xff);
U0DLM=(result>>8)&0xff;
U0LCR=0x03;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}
#define RDR  (U0LSR&1)
unsigned char uart0_rx()
{
while(RDR==0);
return U0RBR;
}


 void uart0_string( char *p)
 {
 while(*p!=0)
 {
 uart0_tx(*p);
 p++;
 }
 }

 void uart_interger(int num)
 {
 int a[10],i;
 if(num==0)
 {uart0_tx('0');
 }
 if(num<0)
 {
 num=-num;
 uart0_tx('-');
 }
  while(num>0)
  {
   a[i]=num%10+48;
   num=num/10;
   i++;

  }
 for(i=i-1;i>=0;i--)
 {uart0_tx(a[i]);
 }
   }

    