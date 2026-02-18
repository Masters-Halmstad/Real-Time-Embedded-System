/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include "led.h"
#include "rpi3.h"
#include "rpi-systimer.h"
#include "rpi-gpio.h"

int main()
{
    led_init();

    // blinking
    while (1)
    {
        led_toogle();
        RPI_WaitMicroSeconds(200000);
    }

    // toogle
    //  led_off();
    //  RPI_WaitMicroSeconds(100000);
    //  led_toogle();
}