#include<lpc21xx.h>
#include"header.h"
  void adc_init(void)
  {
  PINSEL1|=0x15400000;
  ADCR=0x00200400;
  
  }
   u32 adc_read(u8 num){
  u32 temp;
  ADCR|=(1<<num);
  ADCR|=(1<<24);
  while(((ADDR>>31)&1)==0);
  ADCR^=(1<<24);
  ADCR^=(1<<num);
  temp=(ADDR>>6)&0x3ff;
  return temp;
  }
