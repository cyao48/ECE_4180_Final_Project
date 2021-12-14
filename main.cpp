#include "mbed.h"
#include "rtos.h"
#include "uLCD_4DGL.h"
#include "Motor.h"
#include "ultrasonic.h"
#include "Speaker.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
uLCD_4DGL uLCD(p28,p27,p30); // serial tx, serial rx, reset pin;
Serial pc(USBTX, USBRX);
Serial Blue(p13, p14);
Mutex uLCDMutex;
Mutex lcdModeMutex;
Mutex motorModeMutex;
Mutex speakerModeMutex;
int lcd_mode = 0;
int motor_mode = 0;
int speaker_mode = 0;
Motor right(p23, p15, p16); // pwm, fwd, rev, can brake 
Motor left(p22, p19, p20); // pwm, fwd, rev, can brake
bool stop = false;
Speaker speaker(p21);


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