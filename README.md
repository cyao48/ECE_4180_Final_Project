# Interactive Mobile Robot - Bobert

**Team Members: Elizabeth Herrejon, Nishant Sharma, Changxuan Yao**

**Georgia Institute of Technology**

Presentation Slides: (Put link here)

![Picture](link)


## Table of Content
* [Project Idea](#project-idea)
* [Parts List](#parts-list)
* [Schematic and Connection Tables](#schematic-and-connection-tables)
* [Source Code](#source-code)
* [Future Direction](#future-direction)

## Project Idea
We were inspired by interactive robots like Cozmo and Vector to create an interactive mobile robot that can avoid obstacles and make cute faces and sounds. His name is Bobert.

(Click to view videos introducing Cozmo and Vector)

[![Cozmo](https://img.youtube.com/vi/DHY5kpGTsDE/0.jpg)](https://www.youtube.com/watch?v=DHY5kpGTsDE)
[![Vector](https://img.youtube.com/vi/Qy2Z2TWAt6A/0.jpg)](https://www.youtube.com/watch?v=Qy2Z2TWAt6A)


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
* Power Supply: AA batteries x4
* Shadow Chassis: https://www.sparkfun.com/products/13301
* Hobby Gearmotor x2: https://www.sparkfun.com/products/13302
* Rubber Wheels x2: https://www.sparkfun.com/products/13259
* Steren Kit para armar SmartBot (only the shell): https://www.steren.com.co/kit-para-armar-smartbot.html

## Schematic and Connection Tables

#### Device Setup
Pictures of fully assembled robot.
![](links)
All components are connected to and controlled by Mbed. We used external batteries to supply more power. Please see the schematic diagram and connection tables below to set up the robot.
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



