#include <avr/io.h>
#include <avr/interrupt.h>
#define _MATH_DEFINES_DEFINED
#define N 20



static unsigned int lookUp1[20];
static unsigned int lookUp3[20];
static unsigned int lookUp4[20];
static double temp;
static int num1 = 0, num3 = 0, num4 = 0;


void setup(){

// lookUp1 table
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin((i/20)*2*M_PI)+1); //기본
    lookUp1[i] = (int)(temp+0.5);
  }

// lookUp3
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin((i/20)*2*M_PI - M_PI/3)+1); // 120도 차이
    lookUp3[i] = (int)(temp+0.5);
  }

  
// lookUp5
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin((i/20)*2*M_PI - 2*M_PI/3)+1); // 240도 차이
    lookUp4[i] = (int)(temp+0.5);
  }

// Set Register
  TCCR1A = 0b10110010;
  TCCR1B = 0b00000001;
  TIMSK1 = 0b00000001;
  ICR1  = 799;


  TCCR3A = 0b10110010; 
  TCCR3B = 0b00000001;
  TIMSK3 = 0b00000001;
  ICR3   = 799;     
  
  
  TCCR4A = 0b10110010;
  TCCR4B = 0b00000001;
  TIMSK4 = 0b00000001;
  ICR4   = 799;     
                    
  sei();             
  DDRB = 0b01100000; // Set outputs. pwm 11,12 pin 
  DDRE = 0b00011000; // Set outputs. pwm 2,5 pin 
  DDRH = 0b00011000; // Set outputs. pwm 6,7 pin 

  
  pinMode(13,OUTPUT);
}

void loop(){; }

// 핸들링

ISR(TIMER1_OVF_vect){
    OCR1A = lookUp1[num1];
    OCR1B = lookUp1[num1];
     if(++num1 >= 20){
      num1=0;
     }
}

ISR(TIMER3_OVF_vect){
    OCR3A = lookUp3[num3];
    OCR3B = lookUp3[num3];
    if(++num3 >= 20){
      num3=0;
     }
}

ISR(TIMER4_OVF_vect){
    OCR4A = lookUp4[num4];
    OCR4B = lookUp4[num4];
    if(++num4 >= 20){
      num4=0;
     }
}



/*



lookUptable 함수로 구현.

TCNTn가 0에 도달하면 TOVn Flag로 인해 ISR이 실행되는지 확인.
TCNTn이 0에 도달하고 ISR이 실행되는거면 
1. ISR 외부(loop문 내부?)에서 TCNTn이 799가 될 때 num의 값 증가 시키기
2. TCNT가 OCRnA가 일치할 때 num값 증가 시키키(TCNT가 하강시 OCRnA와 만나면 증가, TCNT가 0이 되면 또 증가함(2번 증가하게 됨) TCNT가 상승시 일치하면 num을 증가시킬 수 있나?)

ex) if(TCNT1==799){num1++; num이 20이상이 되지 않도록도 필요 } 



동시에 변해야 하니까 아래와 같이 해도 되지 않을까?

static int num1=0;

ISR(TIMER1_OVF_vect){
    OCR1A = lookUp1[num];
    OCR1B = lookUp1[num];
    OCR3A = lookUp3[num];
    OCR3B = lookUp3[num];
    OCR4A = lookUp4[num];
    OCR4B = lookUp4[num];
    
    if(++num >= 20){
      num=0;
    }
}

*/
