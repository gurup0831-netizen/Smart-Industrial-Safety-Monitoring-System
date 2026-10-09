#include<lpc21xx.h>
#include"header.h"
#include<stdio.h>
#define PIR ((IOPIN0>>4)&1)
#define flame ((IOPIN0>>5)&1)
int main(){
 char s[200],f;
int adcount;
float vout,temp;
IODIR0=7<<17;
IOSET0=7<<17;
lcd_init();
uart0_init(9600);
adc_init();
while(1){
///temp
adcount=adc_read(1);
vout=(adcount*3.3)/1023;
temp=(vout-0.5)/0.01;
sprintf(s,"\r\nTemperature=%.2f degrec\n",temp);
uart0_string(s);
lcd_cmd(0x01);
lcd_cmd(0x80);
sprintf(s,"Temp=%.2f c",temp);
lcd_string(s);
//delay_sec(1);
 if(PIR)
 {
  uart0_string("\r\nPIR:worker didected\n");
 }
 else {
	 uart0_string("\r\nPIR:worker not didected\n");
	  }
if(flame==0)
 { f=1;
  uart0_string("\r\nFLAME: fire dectected\n");
//  IOCLR0=1<<17;
//IOSET0=1<<18;
//IOSET0=1<<19;
 }
 else
	 {f=0;
	 uart0_string("\r\nFLAME: NO fire\n");
	}
	 delay_ms(100);
	 

if(f||temp>40)
{  uart0_string("\r\nMachine satus: not safe");
uart0_string("\r\nLED satus: 18 on");
f=0;
IOCLR0=1<<17;
IOCLR0=1<<18;
IOSET0=1<<19;
lcd_cmd(0xc0);
lcd_string("not safe");
//delay_ms(100);

//IOSET0=1<<19;
}
else
  { uart0_string("\r\nMachine satus:  safe");
uart0_string("\r\nLED satus: 11,19on");
IOSET0=1<<19;
IOCLR0=1<<18;
IOSET0=1<<17;
lcd_cmd(0xc0);
lcd_string("safe");
//delay_ms(100);
}
uart0_string("\r\n");
delay_sec(2);
}
 }
