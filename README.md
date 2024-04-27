# spwm_arduino
---
아두이노를 통한 인터버 spwm제어 시도


아래 github소스를 통해 얻음.


[https://github.com/Irev-Dev/Arduino-Atmel-sPWM](https://github.com/Irev-Dev/Arduino-Atmel-sPWM)


[atmega 328 데이터시트](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)


## FAST_PWM
---
![image](https://github.com/ziguin0925/spwm_arduino/assets/117524772/4129dc38-bc3a-44e1-b85c-55aa3375f0d8)

### PWM_frequency = clock_speed /(Prescaller_value * (1 + TOP_Value))

