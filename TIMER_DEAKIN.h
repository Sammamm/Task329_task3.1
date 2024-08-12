#ifndef TIMER_DEAKIN_H
#define TIMER_DEAKIN_H

#include <Arduino.h>
#include <stdint.h>
#include <wiring_private.h>

class TIMER_DEAKIN {
public:
    bool config_timer(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms);  // Configure timer
    uint16_t getTC3_count();  // Get the counter value for TC3
    void wait(float period_0_1ms);  // Wait for a specified period in 0.1ms units

private:
    void configureTimerRegisters(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms);  // Configure timer registers
    uint32_t getTimerBaseAddress(uint8_t timer_num);  // Get base address of the timer
    bool isTimerValid(uint8_t timer_num);  // Check if the timer number is valid
};

#endif
