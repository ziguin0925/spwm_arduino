#include <avr/io.h>
#include <avr/interrupt.h>
#define _MATH_DEFINES_DEFINED
#define N 20

static unsigned int lookUp1[20];
static unsigned int lookUp2[20];

double temp;
int num_ch;



void setup(){
  
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin(i*2*M_PI/20)+1);
    lookUp2[i] = (int)(temp+0.5); //강제 형변환 (round)
  }

  memcpy(lookUp1, lookUp2, sizeof(lookUp2));

  TCCR3A = 0b10110010; //(Timer/Counter Control Register)
  TCCR3B = 0b00000001;
  TIMSK3 = 0b00000001;//(Interrupt Mask Register)
  ICR3   = 799;     
  sei();             

  DDRE = 0b00011000; // Set outputs. pwm 11,12 pin
  pinMode(13,OUTPUT);
}

void loop(){; }

ISR(TIMER3_OVF_vect){
    static int num =0 ;
    static char trig;
    OCR3A = lookUp1[num];//OC1A
    OCR3B = lookUp2[num];//OC1B
     if(++num >= 20){
      num=0;
     }
}
