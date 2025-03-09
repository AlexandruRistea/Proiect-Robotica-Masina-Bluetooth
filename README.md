# Remote Control Car

## Table of Contents
[1. Introduction](#introduction)\
[2. Overview](#overview)\
[3. Hardware Design](#hardware-design)\
[4. Software Design](#software-design)\
[5. Final Results](#final-results)\
[6. Journal](#journal)\
[7. Conclusion](#conclusion)\
[8. Source Code](#source-code)\
[9. Resources](#resources)



## Introduction
In an era of interconnected devices, integrating everyday technology with remote control systems provides innovative solutions for entertainment and practical applications. This project focuses on creating a remote-controlled car that bridges traditional toy car design with modern smartphone capabilities.

This compact vehicle is designed to be operated via a mobile app, offering a seamless and interactive user experience. By leveraging Bluetooth technology, users can navigate the car with precision and ease. The project emphasizes both hardware engineering and software development, providing a functional and engaging platform that showcases the potential of mobile-controlled systems.

## Overview
### Detailed Description of Hardware Functionality and Components Used:
1. **Microcontroller - Arduino Uno** ---- The Arduino Uno is a microcontroller board based on the ATmega328P. It features 14 digital input/output pins, 6 analog inputs, a 16 MHz quartz crystal, and USB connectivity. It is the core of the project, coordinating all inputs and outputs.
   
2.  **Shield driver motor stepper L293D** ---- Using an L293D motor driver IC with an Arduino is an excellent way to achieve precise DC motor control. The module allows the control of DC motors both forward and backward. It enables the Arduino to manage the high current and voltage requirements of the motors safely.The shield module supports 4 DC motors, 2 steppers or 2 servomotors.

3.  **4 TT Motors** ---- This is essentially a regular motor combined with a series of gears, all encased within a plastic shell. As the motor spins, the gears translate this spin to the wheels of our rover. The use of gears provides a crucial benefit - it increases torque, enabling the motor to move larger, heavier loads.

4.  **4 Mecanum Wheels** ---- A Mecanum wheel is an omnidirectional wheel design for a land-based vehicle to move in any direction. It consists of a series of rubberized external rollers set at a 45° angle to the wheel. Each wheel is independently-driven, and the direction of travel is dependent on the interaction between the directions each wheel is driven in relative to the others.

5.  **Breadboard** ---- A breadboard is a construction base used to build semi-permanent prototypes of electronic circuits.

6.  **ESP32 DEVKITV1** ---- The ESP32 module has integrated antenna and RF balun, power amplifier, power management module, filters and low noise amplifiers.
The board contains Wi-Fi, Bluetooth and a dual-core processor.

7.  **9V Battery** ---- The 9V battery supplies power to the L293D motor driver module, respectively to the Arduino

8.  **External Batterry** ---- An external battery that provides power to the ESP32 module

9.  **Wires** ---- Lots of wires that make the connections possible

10.  **Resistors** ---- Used for the transfer between the different power voltages of the Arduino and the ESP32

11.  **LEDs** ---- Used to show the different states and movements of the vehicle

12.  **Smartphone** ---- In this case an Android phone that is used to control the car

13.  *(Optional)* **Joystick** ---- A precaution in case the batteries of the car run out

## Hardware Design
| Component                           | Quantity | Description                                                                                 | Datasheet/Link                                                                 |
|-------------------------------------|----------|---------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------|
| Arduino Uno                         | 1        | Microcontroller based on ATmega328P. Coordinates inputs and outputs.                       | [Datasheet](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf) |
| Shield Driver Motor Stepper L293D   | 1        | Controls DC motors forward and backward. Supports DC motors, steppers, or servos.          | [Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)                          |
| TT Motors                           | 4        | DC motors controlled by the Arduino via the motor driver.                                  | [Datasheet](https://www.verical.com/datasheet/adafruit-brushless-dc-motors-3777-5912007.pdf) |
| Mecanum Wheels                      | 4        | Omnidirectional wheels with external rollers set at 45° for multidirectional movement.      | [Info](https://en.wikipedia.org/wiki/Mecanum_wheel)                              |
| Breadboard                          | 1        | Construction base for building semi-permanent electronic circuit prototypes.               | [Info](https://en.wikipedia.org/wiki/Breadboard)                                 |
| ESP32 DEVKITV1                      | 1        | Dual-core processor with Wi-Fi, Bluetooth, and power management.                          | [Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) |
| 9V Battery                          | 1        | Supplies power to the L293D motor driver and Arduino.                                      | N/A                                                                            |
| External Battery                    | 1        | Provides power to the ESP32 module.                                                       | N/A                                                                            |
| LEDs                                | 6        | Used to show the states back to the user.                                                 | N/A                                                                            |
| Wires                               | Multiple | Connect components in the circuit.                                                        | N/A                                                                            |
| Resistors                           | Multiple | Used for power transfer between Arduino and ESP32.                                         | N/A                                                                            |
| Joystick (Optional)                 | 1        | Provides directional input as a backup control method.                                     | [Datasheet](https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf) |


### Circuit Photos
![Poze_circuit1](https://github.com/user-attachments/assets/a921975f-0c9d-4b9c-a90b-a9d77d27bcd3)

![poza_circuit3](https://github.com/user-attachments/assets/36930972-e319-4a4e-9b71-135602be3f65)

![WhatsApp Image 2025-01-14 at 01 48 56_213627d3](https://github.com/user-attachments/assets/85b7a5d5-ac6f-4fb5-adc0-a8089e369811)


### Usage of the Shield:
| Component         | Pin Name      | Connection          |
|-------------------|---------------|---------------------|
|  L293D Shield     |       +       |      9V Battery     |
|                   |       -       |        GND          |
|                   |      PWR      |        PWR          |
|                   |      M3       |Motors 1 and 3(- & +)|
|                   |      M4       |Motors 2 and 4(- & +)|
|                   |      GND5     |    GND in ESP32     |
|                   |      A2       |    D19 in ESP32     |
|                   |      A3       |    D21 in ESP32     |
|                   |      A0       | right yellow light  |
|                   |      A1       | left yellow light   |
|                   |      A4       |    white lights     |
|                   |      A5       |     red lights      |

The Shield completely covers the Arduino and uses all it's pins, giving power to the Arduino as well through the PWR pin.

### Voltage Shifting
When connecting Arduino to the ESP32 there is a small problem: voltages are not compatible. Respectively, Arduino operates at 5V and ESP32 at 3.3V. I could leave it like this and connect them anyway, and while they still work, it is risking damaging the circuits.
The solution is using a logic level shifter to change the voltage and safely connect them. Or, if you forget to buy one (like me) you can make a logic level shifter at home. Like this:

![Schema_Comunicare_Arduino-Esp](https://github.com/user-attachments/assets/657700c0-e1d5-405c-b9c5-7abb14ae5b4c)

And after working through other technical difficulties, like not have the proper resistors and combining the ones I had, I got this result:

![Poza_circuit_rezistente](https://github.com/user-attachments/assets/e9b52a80-7fdc-46b6-b822-1f22520ad82b)


## Software Design
The software design is centered around efficient, reliable communication between the robot's hardware components and the user. The project is developed using PlatformIO on Visual Studio Code, and later Arduino IDE.
On the Smartphone we have downloaded an application called "Serial Bluetooth Terminal" from the Play Store and used it to connect via Bluetooth to the ESP32.
The coding software was made in C++.

### Libraries used:
1.   SoftwareSerial.h ---- used for communication between Arduino and ESP32
2.   AFMotor.h ---- library that helps make the motors work with the specific drivers that they need
3.   BluetoothSerial.h ---- used for communication between ESP32 and the smartphone

### Justification of Laboratory Functionalities
The implementation leverages laboratory components such as:

- **DC Motors with H-Bridge Driver**:
   - Provide forward/reverse control for robot movement, validated using oscilloscopes for signal integrity.
- **6 LEDs controlled through button presses**:
   - Used as headlight, signal lights and reverse lights to simulate a more realistic car.
- **Master-Slave communication**:
   - Used to communicate the information given to the ESP32(slave) from the smartphone towards the Arduino(master) for commands.

### Project Functionality:  
- **Input**:   
   - Smartphone through the app (button presses)
- **Processing**:
   - ESP32 takes the inputs from the smartphone without processing and feeds it to the Arduino
   - Arduino Uno acts as the control unit, processing the inputs from the ESP32 and coordinating outputs.  
- **Output Components**:  
   - DC Motors (Movement)  
   - LED Lights (State)
 
## Video Demo and Validation
I will put several pictures and videos that show the functionality of the car that will show:  
1. **Controlling**: Navigation using the smartphone.  
2. **Lightning**: Functionality of the headlights and brake lights.   

The video validates that all functionalities operate according to project specifications.

!!!VIDEO HERE!!!

## Optimization Details
### Areas of Optimization:
1. **Memory Usage**:  
   - Unused libraries and global variables were removed to free up SRAM.  
2. **Power Efficiency**:  
   - Optimized motor control to increase the power needed to move the car.  
3. **Debounce Logic**:  
   - Refined code to ensure button presses are detected and processed as fast as possible(with Bluetooth).
4. **Better batteries**:
   - Switched the original idea of using normal 1.5V batteries for more power.
5. **Balancing the weights on the car**:
   - Moved the components around and getting smaller components (yes that battery on top is the small one) for better balancing of the car.
  
  
### Outcome of Optimizations:
- Better response time from input to output.
- More power sent to the motors for better speed.
- Almost perfect balancing meaning all wheels move the same amount of distance, meaning the car works as intended
  
## Final Results
The project successfully achieves its objective:
- Seamless manual control via a smartphone application, providing precise and intuitive navigation.
- Functional lighting system, including headlights, brake lights, and signal lights, enhancing realism and user feedback.
- Reliable Bluetooth connectivity, ensuring smooth communication between the smartphone and the car.
- Fully calibrated and optimized system with efficient power consumption and robust performance.

## Conclusion
The project demonstrates a well-rounded implementation of embedded systems, showcasing innovation in design and effective use of hardware components.

- All features, including motor control, lighting, and Bluetooth communication, function as intended, validated through multiple test scenarios.
- The project is user-friendly, cost-effective, and serves as a practical example of integrating robotics and smartphone-based control systems.

# Journal:
There is a lot of room for improvement, of course, and the whole project should NOT be taken too seriously! It was fun to make, both the Hardware part and the coding, and it might have practical uses in the future.
A  good example of this is just the way that I started this project; just looking back at the initial plan and the way it turned out is just amazing. I can proudly say I completed all the goals I had in the begining and a lot more!

## This is the way I started the project:

This is a render of the idea I had for the project made in Blender.
The sizes of the components are not to scale, I made it just so we can have a rough idea of how it will look:

![Screenshot_20241209-010212_Word](https://github.com/user-attachments/assets/4ccc0243-d8dc-4d2d-a10a-a843d4fcf1e4)

Nothing complicated so far: a car that can drive forwards and backwards(and hopefully stir left and right), with headlight acting as such. Maybe more options added later

**Components:**

●Arduino Board

●Wheels

●Power Supply(4 AA Batteries)

●LEDs

●Wires

### Update Journal
I short-circuited the ESP32 while switching the 9V battery for a new one. I connected the new battery to the Arduino to test it, it worked, and then I started placing the ESP. If you look at the model, I placed the ESP over the battery (using non-conductive duct tape). Also I did take out the + cable from the battery to the Arduino, but left in the - one for easier assembling. So you can imagine, i accidentally touched the + cable on something on the ESP and now it turned into a little heater... I plan on finding another one quickly or, worst case, reassembly the joystick, even if it breaks the whole purpose of the project!

# Very Important Note:
The battery on top is just a temporary solution! Getting a smaller battery or finding another way of providing power to the esp32 is a way better solution, but this is the one that I had available at the time. I am not proud of it, but it works!

## Source-code
Codes for both the Arduino and the ESP32 are in another folder here! <3

## Resources
I used a lot of sites for videos and ideas, solving problems and finding components! These are a few that I kept regarding their impact on the project:

https://randomnerdtutorials.com/esp32-uart-communication-serial-arduino/

https://www.programmingboss.com/2021/04/esp32-arduino-serial-communication-with-code.html#gsc.tab=0

https://olddocs.zerynth.com/r2.6.2/official/board.zerynth.doit_esp32/docs/index.html
