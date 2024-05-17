#include <avr/io.h>
#include <avr/interrupt.h>
#define _MATH_DEFINES_DEFINED
#include <math.h>



static unsigned int lookUp1[40];
static unsigned int lookUp3[40];
static unsigned int lookUp4[40];
static double temp;
static int num=0;


void setup(){

// lookUp1 table
  for(int i = 0; i < 40; i++){ 
    temp = 400*(sin((i/40)*2*M_PI)+1); //기본
    lookUp1[i] = (int)(temp+0.5);
  }

// lookUp3
  for(int i = 0; i < 40; i++){ 
    temp = 400*(sin((i/40)*2*M_PI - M_PI/3)+1); // 120도 차이
    lookUp3[i] = (int)(temp+0.5);
  }

  
// lookUp5
  for(int i = 0; i < 40; i++){ 
    temp = 400*(sin((i/40)*2*M_PI - 2*M_PI/3)+1); // 240도 차이
    lookUp4[i] = (int)(temp+0.5);
  }

// Set Register
  // Use lookup table 
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

  //TCNT가 799가 될때 마다 lookup table num 1씩 증가.
  TCCR2A = 0b00000010; // 00 00 00 : Normal port operation, OCnA/OCnB/OCnC disconnected ( 10 waveform은 상관없음)
  TCCR2B = 0b00011001;
  TIMSK2 = 0b00000001;
  ICR2  = 799;

  
  sei();             
  DDRB = 0b01100000; // Set outputs. pwm 11,12 pin 
  DDRE = 0b00011000; // Set outputs. pwm 2,5 pin 
  DDRH = 0b00011000; // Set outputs. pwm 6,7 pin 

  
  pinMode(13,OUTPUT);
}

void loop(){; }




ISR(TIMER2_OVF_vect){
    OCR1A = lookUp1[num];
    OCR1B = lookUp1[num];
    OCR3A = lookUp3[num];
    OCR3B = lookUp3[num];
    OCR4A = lookUp4[num];
    OCR4B = lookUp4[num];
    
    if(++num >= 40){
      num=0;
    }
}



/*
lookUptable 데이터 개수가 40개 이면 지령파는 500Hz
맞는지 아두이노 꼽아서 spwm주기 계속 확인하기


TCNTn(clock)이 ICRn(Top)에 도달했다가 0(bottom)에 도달하면 ISR이 실행
따라서 다른 인터럽트 서비스에 FastPWM으로 799가 되면 lookuptable의 num숫자가 증가하도록 설정
lookuptable 이용하는 레지스터 n = 1,3,4
num변환 시키는 레지스터 n = 2
(TIMER2_OVF_vect의 인터럽트 서비스 루틴( ISR(){} )에서 다른 레지스터를 건들일 수 있는지 확인하기)

삼각파는 10kHz로 고정
제어를 할 때 lookup table을 이용해서 한다고 하면 runtime에 테이블 생성이 가능하지만 주파수가 바뀔 때 정확한 값을 대입하는 것에 문제가 있을 거라 생각이 됨. 
1. 주파수가 빨라지게 되면 lookup table의 배열 개수가 작아져야함.
2. 주파수가 바뀌기 전의 num을 대입했을 때의 값과 주파수가 바뀐 후에 num을 대입했을 때의 값이 어느정도 맞아야 된다고 생각.

{
 방법 : 1. 동적으로 lookuptable 생성, 바뀌기 전 주파수의 주기와 바뀌고 난 후 주파수의 주기 비율에 따라 num의 값을 제어. (정수여야함. map으로 제어한다든지)
        2. 모든 주파수(지령파)에 따른 lookup table 생성(메모리가 가능하다면). 주기 비율에 따라 num의 값을 제어.
        3. 한 주기 도중에 지령파 제어신호가 들어와도 주파수를 바로 바꾸지 않고 한 주기가 끝난 후에 바뀐 주파수로 시작하도록 하기.
        4. 그냥 주파수 제어 하지말기.
}


물어볼거
1. 레지스터에 대한 정보가 부족하므로 어떤 레지스터가 필요한지, 어떤 레지스터를 건들여야 하는지 물어봐주셈.
2. 일반적인 mcu에서는 로직을 어떻게 짜는지 물어봐주셈.

*/


