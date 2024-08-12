#include "TIMER_DEAKIN.h"
#include <Arduino.h>
#include <stdint.h>
#include <wiring_private.h>

// Check if the timer number is valid
bool TIMER_DEAKIN::isTimerValid(uint8_t timer_num) {
    return (timer_num == 3);  // Only TC3 is valid here.
}

// Get base address of the timer
uint32_t TIMER_DEAKIN::getTimerBaseAddress(uint8_t timer_num) {
    if (!isTimerValid(timer_num)) return 0;
    return (uint32_t) &TC3->COUNT16;  // Base address for TC3
}

// Configure timer registers
void TIMER_DEAKIN::configureTimerRegisters(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms) {
    if (!isTimerValid(timer_num)) return;
    TcCount16* TC = (TcCount16*) getTimerBaseAddress(timer_num);

    // Set the timer's control and status registers to 0
    TC->CTRLA.reg = 0;
    TC->CTRLBSET.reg = 0;

    // Set timer mode to 16-bit
    TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;

    // Set the resolution by setting the prescaler
    uint16_t prescaler = (uint16_t)(resolution_0_1ms * 48 - 1);
    TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1 + prescaler;

    // Set the starting and ending count values
    TC->COUNT.reg = start_value;
    TC->CC[0].reg = end_value;

    // Enable the timer
    TC->CTRLA.reg |= TC_CTRLA_ENABLE;
}

// Configure timer
bool TIMER_DEAKIN::config_timer(uint8_t timer_num, uint16_t start_value, uint16_t end_value, float resolution_0_1ms) {
    if (!isTimerValid(timer_num)) return false;
    configureTimerRegisters(timer_num, start_value, end_value, resolution_0_1ms);
    return true;
}

// Get the counter value for TC3
uint16_t TIMER_DEAKIN::getTC3_count() {
    return TC3->COUNT16.COUNT.reg;
}

// Wait for a specified period in 0.1ms units
void TIMER_DEAKIN::wait(float period_0_1ms) {
    TcCount16* TC = (TcCount16*) TC3;
    uint32_t start_count = TC->COUNT.reg;
    Serial.print("Waiting for ");
    Serial.print(period_0_1ms * 0.1);
    Serial.println(" milliseconds.");
    while ((TC->COUNT.reg - start_count) < (period_0_1ms * 48)) {
        // Optionally add a small delay to avoid blocking the CPU
        delay(1);
    }
    Serial.println("Wait complete.");
}
