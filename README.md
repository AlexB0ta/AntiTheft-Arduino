# Arduino Security System  :computer:

:zap:This Arduino project implements a comprehensive security system using various sensors and RFID technology. The system includes features such as motion detection, access control using RFID cards, and an audible alarm.

## Components Used :dvd:

- Arduino board
- MFRC522 RFID module
- TFT display
- FSR (Force-Sensitive Resistor)
- PIR (Passive Infrared) motion sensor
- Buzzer and LED for alarm
- Pushbutton for system arming

## Setup Instructions

1. Connect the hardware components according to the specified pin configurations in the code.
2. Upload the Arduino sketch (`security_system.ino`) to your Arduino board.
3. Ensure that all necessary libraries (SPI, MFRC522, TFT) are installed.
4. Power up the system and monitor the TFT display for system status.

## System Operation

- The system can be armed and disarmed using the pushbutton.
- Motion detection and RFID card reading are used for intrusion detection and access control.
- The TFT display provides visual feedback on the system's status and events.
- An audible alarm is triggered when unauthorized access or suspicious motion is detected.


Feel free to contribute, report issues, or suggest improvements!
