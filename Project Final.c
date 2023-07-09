#include <16f877A.h>//header files
#fuses XT,NOWDT//configuration
#use delay(clock=4000000)//oscilator of 4MHz

#byte ADRESH=0x1E//Equating the ADRESH
#byte ADRESL=0x9E//Equating the ADRESL
#byte PORTA=0x05//Equating the PORTA
#byte PORTB=0x06//Equating the PORTB
#byte PORTC=0x07//Equating the PORTC
#byte PORTD=0x08//Equating the PORTD
#byte TRISA=0x85//Equating the TRISA
#byte TRISB=0x86//Equating the TRISB
#byte TRISC=0x87//Equating the TRISC
#byte TRISD=0x88//Equating the TRISD
#byte TMR2=0x11//Equating the TMR2
#byte ADCON0=0x1f//Equating the ADCON0
#byte ADCON1=0x9f//Equating the ADCON1
#byte T2CON=0x12//Equating the T2CON
#byte CCPR1L=0x15//Equating the CCPR1L
#byte CCP1CON=0x17//Equating the CCP1CON
#byte PR2=0x92//Equating the timer 2 module period register

#bit GO=0x1f.2      //bit of ADCON1 is go               
#bit ON=0x1f.0      //bit of ADCON0 is on
#bit CCP1Y=CCP1CON.4
#bit CCP1X=CCP1CON.5
#bit PWM_PIN=TRISC.2

int RD_ADC(); //Prototype of a function

void main()   //starting main loop
{  float x=0; //defining float variable
   PR2=249;  //set periode frequency
   TRISC=0;  //making portc data direct register output
   ADCON0=0b01000000;//setting up clock of ADC
   ADCON1=0; //all the adcon1 bits are 0
   while(1)//infinite loop
   {
   x=RD_ADC(); // storing the returined value in x 
   CCPR1L=x; //eight mode select bits//setting up the duty cycle
   CCP1Y=0; //LSbs of PWM duty cycle
   CCP1X=0; //LSbs of PWM duty cycle
   PWM_PIN=0;//set trisc,2 as output
   CCP1CON=0b00001100;   //Module mode
   T2CON=0b00000101;    //tmr2=on & prescaler=1:4
   }
}    
int16 RD_ADC()      //function for A-D Conversion
{
int16 value=0;      //defining variable
bit_set(ADCON0,0); //setting the bit 0 which is on
bit_set(ADCON0,2);//setting the bit 1 which is go 
while(bit_test(ADCON0,2)){} //while the adcon0 is working 
value=make16(ADRESH,ADRESL);//storing the ad-result-high and low in value for 10 bits
return value; //returing the value
}

