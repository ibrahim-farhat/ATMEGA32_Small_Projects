# C small project

Using ATMEGA32 I implemented this application.

Specifications:
1- 9 Vocal Commands that MCU can handle.
2- Ability to manage servo motor with two angles.
(Commands: Open the door – Close the door).
3- Ability to manage DC motor with 3 modes (Max Power – Map its power with LDR output voltage - Off).
(Commands: Open the fan – Control the fan speed – Close the fan).
4- Ability to manage LEDs with 3 modes (Mas Power – Map its power with Ultrasonic output distance – Off).
(Commands: Turn on light – Control light intensity – Turn off light).
5- Ability to send an alarm with the buzzer for a while.
(Command: Send Alarm).
6- CLCD: Displays LDR output voltage or Ultrasonic output distance when LDR or Ultrasonic are turned on.

Features: 
1- All the system modules can work parallel at the same time.
i.e. MCU maps ultrasonic reading to the motor speed, maps LDR reading with light intensity and sends pulses to the buzzer, all these operations take place at the same time.
2- USART receive the command with asynchronous function which allowed me to prevent any polling in my system.

I used: 
1- Some microcontroller peripherals such as: Timers – ADC – USART.
2- HW components such as: ultrasonic – LDR – Buzzer.
3- HC-05 Bluetooth module to deal with USART.
4- RoboBoy android application which allowed me to use google voice assistant.
 
I’d like to explain how timers peripheral work:
Timer 0: controls (light intensity – servo motor angle – DC motor speed) with CTC mode.
Timer 1: serves ultrasonic with its input capture unit.
Timer 2: makes the tone on the buzzer using fast PWM mode and also using compare match interrupt event.
 
And I don’t forget to thank Eng. Amgad Samir with his great support.