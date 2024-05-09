# spwm_arduino
---
아두이노를 통한 인터버 spwm제어 시도


아래 github소스를 통해 얻음.


[https://github.com/Irev-Dev/Arduino-Atmel-sPWM](https://github.com/Irev-Dev/Arduino-Atmel-sPWM)

---
[atmega 328 데이터시트](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)
---
[atmega 2560 데이터시트]https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf
---


## Phase and Frequency Correct PWM Mode, Timing Diagram
![image](https://github.com/ziguin0925/spwm_arduino/assets/117524772/f4ae4194-86db-4096-99ee-628029b68f6a)

![image](https://github.com/ziguin0925/spwm_arduino/assets/117524772/e812a52d-42d3-4f3b-b9bd-aa2b2ecfc63c)







## FAST_PWM
---
![image](https://github.com/ziguin0925/spwm_arduino/assets/117524772/4129dc38-bc3a-44e1-b85c-55aa3375f0d8)

### PWM_frequency = clock_speed /(Prescaller_value * (1 + TOP_Value))

