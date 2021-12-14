# Interactive Mobile Robot - Bobert

**Team Members: Elizabeth Herrejon, Nishant Sharma, Changxuan Yao**

**Georgia Institute of Technology**

Presentation Slides: https://github.com/cyao48/ECE_4180_Final_Project/blob/main/presentation_slides.pptx

![Picture](https://github.com/cyao48/ECE_4180_Final_Project/blob/main/bobert.jpg)

Please **click** to view the videos of Bobert working below:

Teleoperated:

[![Teleoperated](https://img.youtube.com/vi/vme3hSqbSQM/0.jpg)](https://www.youtube.com/watch?v=vme3hSqbSQM)

Autonomous:

[![Autonomous](https://img.youtube.com/vi/ZKj0KyM5yLk/0.jpg)](https://www.youtube.com/watch?v=ZKj0KyM5yLk)


## Table of Content
* [Introduction](#introduction)
* [Parts List](#parts-list)
* [Schematic and Connection Tables](#schematic-and-connection-tables)
* [Source Code](#source-code)
* [Conclusion and Possible Improvements](#conclusion-and-possible-improvements)
* [References](#references)

## Introduction

*"Robotics is a powerful tool in education and it has gained a notable impact in the field of teaching computer science, engineering, math, physics and similar. As educational robotics laboratories stimulate many different abilities in students, such as problem solving and group working, it is possible to use robotics to promote soft skills as well."* - Rubinacci [1]

More and more interactive robot toys like Cozmo and Vector have been introduced into the market, and as the study mentioned above has stated, interacting with robots can inspire
and stimulate many different abilities in students. We were inspired by these interactive robot toys to build a basic interactive mobile robot named Bobert that has different expressions, plays different sounds, and is able to avoid obstacles.

(Click to view videos introducing Cozmo and Vector)

[![Cozmo](https://img.youtube.com/vi/DHY5kpGTsDE/0.jpg)](https://www.youtube.com/watch?v=DHY5kpGTsDE)
[![Vector](https://img.youtube.com/vi/Qy2Z2TWAt6A/0.jpg)](https://www.youtube.com/watch?v=Qy2Z2TWAt6A)


The robot takes in command from the Bluefruit LE Connect APP via Bluetooth, and has both an autonomous mode and teleoperated mode. To switch from teleoperated mode to autonomous mode, press number "1" on the APP. To switch from autonomous mode to teleoperated mode, press number "2" on the APP. At the start of the program, the mode is set to the teleoperated mode by default. In this mode, Bobert is able to drive forward, backward, and turn based on the D-Pad button presses. It is also able to change expressions based on the number button presses. If it senses an obstacle in the front, it will stop and cannot be commanded to move forward until the obstacle has been cleared.

In the autonomous mode, Bobert takes in distance information from the UltraSonic sensor. If anything is sensed to be within 400 mm, Bobert stops, turns, and continues to drive forward after avoiding the obstacle. His expression can still be changed via button presses.

Block Diagram:
![block diagram](https://github.com/cyao48/ECE_4180_Final_Project/blob/main/block_diagram.png)

## Parts List

* Mbed LPC1768, https://www.sparkfun.com/products/9564
* LCD Display: uLCD-144G2, https://www.sparkfun.com/products/11377
* Speaker: https://www.sparkfun.com/products/11089
* Adafruit Bluetooth Module: https://www.adafruit.com/product/2479
* Jumper Wires(M/M and M/F): https://www.sparkfun.com/products/124, https://www.sparkfun.com/products/11026, https://www.sparkfun.com/products/12794
* UltraSonic Sensor (HC-SR04): https://www.digikey.com/en/products/detail/osepp-electronics-ltd/HC-SR04/11198533
* H-Bridge (SparkFun Motor Driver): https://www.sparkfun.com/products/14450
* Mono Audio Ampt Breakout: https://www.sparkfun.com/products/11044
* Power Supply: 9V Battery: https://www.amazon.com/Duracell-Coppertop-Alkaline-Batteries-Count/dp/B000K2NW08
* Linear Voltage Regulator Board: https://www.digikey.com/en/products/detail/bud-industries/BBP-32701/8602382
* Shadow Chassis: https://www.sparkfun.com/products/13301
* Hobby Gearmotor x2: https://www.sparkfun.com/products/13302
* Rubber Wheels x2: https://www.sparkfun.com/products/13259
* Steren Kit para armar SmartBot (only the shell): https://www.steren.com.co/kit-para-armar-smartbot.html

## Schematic and Connection Tables

#### Device Setup
All components are connected to and controlled by Mbed. We used an external 9V battery (converted to 5V via the breaker) to supply more power. Please see the schematic diagram and connection tables below to set up the robot.

#### Schematic
![Schematic](https://github.com/cyao48/ECE_4180_Final_Project/blob/main/schematic.png)

#### Connection Tables

Mbed to Bluetooth

| Bluetooth   |     Mbed     |   Batteries  |
|-------------|--------------|--------------|
| GND         |  GND         |  GND         |
| Vin         |              |  5V          |
| RXI         |  p13         |              |
| TXO         |  p14         |              |
| CTS         |  GND         |  GND         |

Mbed to uLCD

|    uLCD     |     Mbed     |   Batteries  |
|-------------|--------------|--------------|
| 5V          |              |  5V          |
| TX          |  p27         |              |
| RX          |  p28         |              |
| Reset       |  p30         |              |
| GND         |  GND         |  GND         |

Mbed to H-Bridge to Motors

|  H-Bridge   |     Mbed     |   Batteries  |    Motors    |
|-------------|--------------|--------------|--------------|
| Vm          |              |  5V          |              |
| Vcc         |  Vout        |              |              |
| GND         |  GND         |  GND         |              |
| AO1         |              |              |Right motor + |
| AO2         |              |              |Right motor - |
| BO1         |              |              | Left motor + |
| BO2         |              |              | Left motor - |
| PWMA        |  p22         |              |              |
| AI1         |  p20         |              |              |
| AI2         |  p19         |              |              |
| STBY        |  Vout        |              |              |
| BI1         |  p24         |              |              |
| BI2         |  p25         |              |              |
| PWMB        |  p23         |              |              |
| GND         |  GND         |  GND         |              |

Mbed to UltraSonic Sensor

|UltraSonic Sensor|     Mbed     |   Batteries  |
|-----------------|--------------|--------------|
| Vcc             |              |  5V          |
| GND             |  GND         |  GND         |
| Trig            |  p6          |              |
| Echo            |  p7          |              |

Mbed to D-Amp to Speaker

|Class D Audio Amp|     Mbed     |   Speaker    |
|-----------------|--------------|--------------|
| pwr-            |  GND         |  GND         |
| pwr+            |  Vout        |              |
| in+             |  p18         |              |
| out+            |              |  +           |
| out-            |              |  -           |


## Source Code

main.ccp

```cpp
#include "mbed.h"
#include "rtos.h"
#include "uLCD_4DGL.h"
#include "wave_player.h"
#include "Motor.h"
#include "ultrasonic.h"
#include "Speaker.h"
// #include "rgbLED.h"

// SDFileSystem sd(p5, p6, p7, p8, "sd"); //SD card
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
uLCD_4DGL uLCD(p28,p27,p30); // serial tx, serial rx, reset pin;
Serial pc(USBTX, USBRX);
Serial Blue(p13, p14);
Mutex uLCDMutex;
Mutex lcdModeMutex;
// Mutex BlueMutex;
Mutex motorModeMutex;
Mutex speakerModeMutex;
int lcd_mode = 0;
int motor_mode = 0;
int speaker_mode = 0;
Motor left(p23, p24, p25); // pwm, fwd, rev, can brake 
Motor right(p22, p19, p20); // pwm, fwd, rev, can brake
bool stop = false;
Speaker speaker(p18); //was p21

void dist(int distance)
{
    //put code here to execute when the distance has changed
    //pc.printf("Distance %d mm\r\n", distance);
    
    if(distance < 400 && distance != 0){
        stop = true;
    }
    else{
        stop = false;
    }
    
}

ultrasonic mu(p6, p7, .1, 1, &dist);

void motor_thread(void const *argument) {
    mu.startUpdates();//start measuring the distance
    bool autonomous = false;
    int state = 0; // 0 - Stopped; 1 - Forward; 2 - Reversed; 3 - Left; 4 - Right;
    while(1)
    {
        motorModeMutex.lock();
        int motor_inner_mode = motor_mode;
        motor_mode = 0;
        motorModeMutex.unlock();
        if (motor_inner_mode == 1)
        {
            autonomous = true;
        }
        if (motor_inner_mode == 2)
        {
            autonomous = false;
        }
        if (autonomous)
        {
            state = 0;
            mu.checkDistance();
            left.speed(0.5);
            right.speed(0.5);
            if(stop)
            {
                left.speed(0);
                right.speed(0);
                Thread::wait(500);
                left.speed(-0.5);
                right.speed(0.5);
                Thread::wait(700);
            }
        }
        else
        {
            mu.checkDistance();
            if (state == 0)
            {
                left.speed(0);
                right.speed(0);
            }
            switch(motor_inner_mode)
            {
                case 5:
                    if (state != 0 && state != 1) // If reverse then stop
                    {
                        left.speed(0);
                        right.speed(0);
                        state = 0;
                    }
                    else
                    {
                        if (stop)
                        {
                            left.speed(0);
                            right.speed(0);
                            state = 0;
                        }
                        else
                        {
                            left.speed(0.5);
                            right.speed(0.5);
                            state = 1;
                        }
                    }
                    break;
                case 6:
                    if (state != 0 && state != 2) // If forward then stop
                    {
                        left.speed(0);
                        right.speed(0);
                        state = 0;
                    }
                    else
                    {
                        left.speed(-0.5);
                        right.speed(-0.5);
                        state = 2;                    
                    }    
                    break;
                case 7:
                    if (state != 0 && state != 3) // If right then stop
                    {
                        left.speed(0);
                        right.speed(0);
                        state = 0;
                    }
                    else
                    {
                        left.speed(0.5);
                        right.speed(-0.5);
                        state = 3;
                    }
                    break;
                case 8:
                    if (state != 0 && state != 4) // If left then stop
                    {
                        left.speed(0);
                        right.speed(0);
                        state = 0;
                    }
                    else
                    {
                        left.speed(-0.5);
                        right.speed(0.5);
                        state = 4;
                    }
                    break;
            }
            if (state == 1 && stop)
            {
                left.speed(0);
                right.speed(0);
                state = 0;
            }
        }
        Thread::wait(200);
    }
}


void speaker_thread(void const *argument) {
    while(true) {
        speakerModeMutex.lock();
        int speaker_inner_mode = speaker_mode;
        speaker_mode = 0;
        speakerModeMutex.unlock();
        switch(speaker_inner_mode) {
            case 1:
                speaker.PlayNote(200.0, 0.2, 0.1);
                speaker.PlayNote(1000.0, 0.2, 0.1);
                break;
            case 2:
                speaker.PlayNote(1000.0, 0.2, 0.1);
                speaker.PlayNote(200.0, 0.2, 0.1);
                break;
        }
        Thread::wait(1000);
    }
}

void lcd_image_thread(void const *argument) {  
    while(true) {
        lcdModeMutex.lock();
        int lcd_inner_mode = lcd_mode;
        // pc.printf("lcd_mode %d", lcd_inner_mode);
        lcdModeMutex.unlock();
        switch(lcd_inner_mode) {
            case 1:
                uLCDMutex.lock();
                // pc.printf("Entered");
                uLCD.media_init();
                uLCD.set_byte_address(0x0000, 0x0000);   // Annoyed
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 2:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0000, 0x8200);   // Annoyed2
                uLCD.display_image(0, 20);
                uLCDMutex.unlock(); 
                break;       
            case 3:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0001, 0x0400);   // Water
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 4:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0001, 0x8600);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 5:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0002, 0x0800);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 6:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0002, 0x8A00);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 7:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0003, 0x0C00);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 8:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0003, 0x8E00);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 9:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0004, 0x1000);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            case 10:
                uLCDMutex.lock();
                uLCD.media_init();
                uLCD.set_byte_address(0x0004, 0x9200);   // Thunder
                uLCD.display_image(0, 20);
                uLCDMutex.unlock();
                break;
            default:
                uLCDMutex.lock();
                uLCD.filled_rectangle(0, 0, 128, 128, BLACK);
                uLCDMutex.unlock();
                break;
        }
        Thread::wait(1000); // Wait for 0.5 seconds every iteration
    }
}

int main() {
    uLCDMutex.lock();
    uLCD.cls();
    uLCD.printf("Hello");
    uLCD.baudrate(3000000);
    uLCDMutex.unlock();
    Thread::wait(1000);
    int main_mode = 0;
    Thread t1(lcd_image_thread, NULL, osPriorityNormal, (DEFAULT_STACK_SIZE));
    Thread t2(motor_thread, NULL, osPriorityNormal, (DEFAULT_STACK_SIZE));
    Thread t3(speaker_thread, NULL, osPriorityNormal, (DEFAULT_STACK_SIZE));
    int bnum;
    int bhit;
    while (true) {
        uLCDMutex.lock();
        if (Blue.readable()) {
            if (Blue.getc()=='!') {
                if (Blue.getc()=='B') { //button data
                    bnum = Blue.getc(); //button number
                    bhit = Blue.getc();
                    if (bhit=='1') {
                        switch(bnum) {
                            case '1':
                                main_mode=1;
                                led4=1;
                                break;
                            case '2':
                                main_mode=2;
                                led3=1;
                                led4=0;
                                break;
                            case '3':
                                main_mode=3;
                                led3=1;
                                led4=1;
                                break;
                            case '4':
                                main_mode=4;
                                led2=1;
                                led3=0;
                                led4=0;
                                break;
                            case '5': // UP
                                main_mode=5;
                                led2=1;
                                led3=0;
                                led4=1;
                                break;
                            case '6': // DOWN
                                main_mode=6;
                                led2=1;
                                led3=1;
                                led4=0;
                                break;
                            case '7': // LEFT
                                main_mode=7;
                                led2=1;
                                led3=1;
                                led4=1;
                                break;
                            case '8': // RIGHT
                                main_mode=8;
                                led1=1;
                                led2=0;
                                led3=0;
                                led4=0;
                                break;
                        }
                        motorModeMutex.lock();
                        motor_mode = main_mode;
                        motorModeMutex.unlock();
                        lcdModeMutex.lock();
                        lcd_mode = main_mode;
                        lcdModeMutex.unlock();
                        speakerModeMutex.lock();
                        speaker_mode = main_mode;
                        speakerModeMutex.unlock();
                    }
                }
            }            
        }
        uLCDMutex.unlock();
        Thread::wait(500);
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 0;
    }
    /*
    while(1)
    {
        led1 = !led1;
        Thread::wait(1000);
        if (Blue.readable()){
            uLCD.putc(Blue.getc());
        }
    }
    */
}
```


## Conclusion and Possible Improvements

Bobert was inspired by various interactive robot toys, and is a basic interactive mobile robot that has different expressions, play different sounds, and is able to avoid obstacles. It has both an autonomous mode and a teleoperated mode. In both modes, there is an issue with not sensing obstacles from the sides and the back. Obstacles from the back are not as much of a problem, since Bobert only drives forward, but obstacles from the sides somtimes causes an issue when Bobert drives into walls at an angle. Since we only have one UltraSonic sensor on the robot, we can only detect obstacles from the front. Other than this, everything else works great.

Some of the improvements that we could make in the future include:

1. Add sensors to the sides and the back to be able to detect obstacles from all angles.
2. Add the ability to play wav sound files and/or video files.
3. Add more interactions with humans, such as hand-following, or response to hand waves.
4. Add cliff detection sensors.
5. Add a gyroscope to sense whether or not it has been picked up, and respond to it.

## References

[1] F. Rubinacci, M. Ponticorvo, R. Passariello, and O. Miglino, “Robotics for soft skills training,” ResearchGate, Dec-2017. [Online]. Available:           https://www.researchgate.net/publication/327036615_Robotics_for_soft_skills_training. [Accessed: 13-Dec-2021]. 

## Authors

* **Elizabeth Herrejon**   - eherrejon3@gatech.edu
* **Nishant Sharma**       - nsharma93@gatech.edu
* **Changxuan Yao**        - cyao48@gatech.edu
