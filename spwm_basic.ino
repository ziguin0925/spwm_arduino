#include <avr/io.h>
#include <avr/interrupt.h>

#define _MATH_DEFINES_DEFINED

#define N 20

//http://artoa.hanbat.ac.kr/lecture_data/microprocessor/2014/%EC%A0%9C7%EC%9E%A5%20%ED%83%80%EC%9D%B4%EB%A8%B8%EC%99%80%20PWM%20(HBE-MCU-Multi%20AVR).pdf

/*

지령파의 한 주기안에 삼각파가 20개 들어가도록 설정, 지령파가 변할수록 동적으로 lookUp table의 배열도 바뀌어야 함.
ICR1 최대 0-799로 설정 (0에서 799까지 증가후 799에서 0으로 내려감.)

*/
static unsigned int lookUp1[20];
static unsigned int lookUp2[20];

double temp;
int num_ch;
/*
lookUp1[]={듀티 결정}
sizeof(lookUp1): 지령파 내의 삼각파 갯수 결정 
*/


void setup(){
  
  for(int i = 0; i < 20; i++){ 
    temp = 400*(sin(i*2*M_PI/20)+1);
    lookUp2[i] = (int)(temp+0.5); //강제 형변환 (round)
  }

  memcpy(lookUp1, lookUp2, sizeof(lookUp2));

/*
  for (int i = 0; i < N / 2; i++)
	{
		num_ch = lookUp1[i];
		lookUp1[i] = lookUp1[N - i - 1]; // 요소가 20개일때 마지막 요소는 9
		lookUp1[N - i - 1] = num_ch;
	}

  lookUp2 가 완전한 spwm의 파형이 안나오므로 com레지스터 인터럽트를 OC1A가 켜질 때와 반대로 되도록 설정함.
*/
    // Register initilisation, see datasheet for more detail.
    TCCR1A = 0b10110010; //(Timer/Counter Control Register)

       /*10 TCNT가 OCR1A와 일치해지면 1출력(COM1A1, COM1A0)
         11 (COM1B1, COM1B0) reverse
         00
         10 WGM1 1:0 
       */
    TCCR1B = 0b00000001;
       /*000
         00 WGM1 3:2 
         001 prescale= 1.

         TCCR1A의 WGM1 1:0과  TCCR1B WGM1 3:2 합치면 1110(option = Fast PWM, TOP=ICR1 )
         1000 : PWM,Phase and Frequency
         TOP : OCRnA
         Update of OCRnx at : BOTTOM
         TOVn Flag Set on : BOTTOM
Correct
       */
    TIMSK1 = 0b00000001;//(Interrupt Mask Register)
       /*0000000
         1 TOV1 Flag interrupt enable(타이머 오버플로우 인터럽트)
       */

    ICR1   = 799;     // 비교기(TCNT최대 증가치) Period for 16MHz crystal (클럭 16MHz) 
                      // (삼각파의 주파수를 10kHz로 줘야함)
    sei();             // Enable global interrupts.

    DDRB = 0b01100000; // Set outputs. pwm 11,12 pin
    pinMode(13,OUTPUT);
}

void loop(){; }

ISR(TIMER1_OVF_vect){
    static int num =0 ;
    static char trig;
    // change duty-cycle every period.
    OCR1A = lookUp1[num];//OC1A
    OCR1B = lookUp2[num];//OC1B
     if(++num >= 20){
      num=0;
     }
}
