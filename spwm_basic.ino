/*
 * sPWMv2.c
 *
 * Created: 31/12/2014 3:44:43 PM
 *  Author: Kurt Hutten
 sPWM on the atMega328 for the arduino Uno, might be compatable with other atmel chips / arduino boards.
 Compare outputs A and B output to PORTB pins 1 and 2 which are pins 9 and 10 respectively on the Uno.
 Also useful to know the led on the Uno is pin 5 on PORTB.
 */ 
//https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
//http://artoa.hanbat.ac.kr/lecture_data/microprocessor/2014/%EC%A0%9C7%EC%9E%A5%20%ED%83%80%EC%9D%B4%EB%A8%B8%EC%99%80%20PWM%20(HBE-MCU-Multi%20AVR).pdf


#include <avr/io.h>
#include <avr/interrupt.h>

// Look up tables with 20 entries each, normalised to have max value of 80 which is the period of the PWM loaded into register ICR1.
int lookUp1[] = {8, 24, 40, 56, 80, 56, 40, 24, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//[9]=0
int lookUp2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 24, 40, 56, 80, 56, 40, 24, 8, 0};//[9]=0
/*
lookUp1[]={듀티 결정}
sizeof(lookUp1):주파수 결정
*/

void setup(){
    // Register initilisation, see datasheet for more detail.
    TCCR1A = 0b10100010; //(Timer/Counter Control Register)

       /*10 TCNT가 OCR1A와 일치해지면 1출력(COM1A1, COM1A0)
         10 (COM1B1, COM1B0)
         00
         10 WGM1 1:0 for waveform 15.
       */
    TCCR1B = 0b00011001;
       /*000
         11 WGM1 3:2 for waveform 15.
         001 prescale= 1.

         TCCR1A의 WGM1 1:0과  TCCR1B WGM1 3:2 합치면 1110(option = Fast PWM, TOP=ICR1 )
       */
    TIMSK1 = 0b00000001;//(Interrupt Mask Register)
       /*0000000
         1 TOV1 Flag interrupt enable(타이머 오버플로우 인터럽트)
       */

    ICR1   = 79;     // 비교기(TCNT최대 증가치) Period for 16MHz crystal (클럭 16MHz) 
                      //a switching frequency of 200KHz
                      //20 subdevisions per 10KHz sin wave cycle.
    sei();             // Enable global interrupts.
    DDRB = 0b00000110; // Set PB1 and PB2 as outputs. 핀설정9,10
    pinMode(13,OUTPUT);
}

void loop(){; /*Do nothing . . . . forever!*/}

ISR(TIMER1_OVF_vect){
    static int num;
    static char trig;
    // change duty-cycle every period.
    OCR1A = lookUp1[num];//TCNT 증가시 OCR1A와 같아지면 출력비교 인터럽트 발생.
    OCR1B = lookUp2[num];
    
    if(++num >= 20){ // Pre-increment num then check it's below 40. 없어도 될듯
       num = 0;       // Reset num.
       trig = trig^0b00000001;
       digitalWrite(13,trig); //13번 핀을 통한 HIGH, LOW 제어부분
     }
}
