#include <avr/io.h>
#include <avr/interrupt.h>
#define _MATH_DEFINES_DEFINED
#define N 20



static unsigned int lookUp1[20];
static unsigned int lookUp2[20];
static double temp;


void setup(){
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin(i*2*M_PI/20)+1); // 120도 차이나게 해줘야 됨.
    lookUp2[i] = (int)(temp+0.5);
  }

  memcpy(lookUp1, lookUp2, sizeof(lookUp2));
  TCCR4A = 0b10110010;
  TCCR4B = 0b00000001;
  TIMSK4 = 0b00000001;

  ICR4   = 799;     
                    
  sei();             

  DDRH = 0b00011000; // Set outputs. pwm 6,7 pin
  pinMode(13,OUTPUT);
}

void loop(){; }

ISR(TIMER4_OVF_vect){
    static int num =0 ;
    static char trig;
    OCR4A = lookUp1[num];
    OCR4B = lookUp2[num];
     if(++num >= 20){
      num=0;
     }
}
