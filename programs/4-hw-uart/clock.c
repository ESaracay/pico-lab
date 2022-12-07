#include "include/gpio.h"
#include "include/clock.h"

// Clock will run at 12 MHZ
// IMPORTANT: Sadly theres a bug here. Running from flash seems to freeze up the pico
void enable_clock() {
    // frequency_mhz * (1000 / 256);
     uint32_t delay = 47;
     // Step 1 is to setup delay
     PUT32(XOSC_STARTUP + SET_OFFSET, delay);
     // Step 2 enable XOSC
     PUT32(XOSC_CTRL + SET_OFFSET, 0xfab << 12);

     // Wait till ready
     while (!(GET32(XOSC_STATUS) >> 31));
     // Setup clk_ref so you can setup clock_sys
     PUT32(CLK_REF_CTRL, 0x2);
     PUT32(CLK_SYS_CTRL, 0x0);
     PUT32(FC0_REF_KHZ, 0x12000);
}

void delay_us(uint32_t delay) {
    uint64_t low = GET32(TIMER_READ_LOW);
    uint64_t high = GET32(TIMER_READ_HIGH); 
    uint64_t start_time = low | (high << 32);
    uint64_t cur_time = start_time;
    while (cur_time < start_time + delay) {
        low = GET32(TIMER_READ_LOW);
        high = GET32(TIMER_READ_HIGH); 
        cur_time = low | (high << 32);
    }
}

void delay_ms(uint32_t delay) {
    uint64_t delay_us = 1000 * delay;
    uint64_t low = GET32(TIMER_READ_LOW);
    uint64_t high = GET32(TIMER_READ_HIGH); 
    uint64_t start_time = low | (high << 32);
    uint64_t cur_time = start_time;
    while (cur_time < start_time + delay_us) {
        low = GET32(TIMER_READ_LOW);
        high = GET32(TIMER_READ_HIGH); 
        cur_time = low | (high << 32);
    }
}
