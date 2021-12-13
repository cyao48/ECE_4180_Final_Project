# Interactive Mobile Robot

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
Pictures of fully assembled Bobert.
![](links)
All components are connected to and controlled by Mbed. We used external batteries to supply more power. Please see the schematic diagram and connection tables below to set up the robot.
#### Schematic
![](link)

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
// codes
```


## Future Direction



