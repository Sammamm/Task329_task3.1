#include "GPIO_DEAKIN.h"
#include "TIMER_DEAKIN.h"

GPIO_DEAKIN gpio;
TIMER_DEAKIN timer;

void setup() {
    Serial.begin(9600);  // Initialize Serial Monitor
    gpio.Config_GPIO('A', 21, OUTPUT);  // Configure PA21 (D10) as output
    timer.config_timer(3, 0, 0xFFFF, 0.1);  // Configure TC3 timer with 16-bit mode and a resolution of 0.1ms
}

void loop() {
    gpio.Write_GPIO('A', 21, HIGH);  // Turn ON the LED
    Serial.println("LED ON");
    timer.wait(20000);  // Wait for 2 seconds (20000 * 0.1ms)
    
    gpio.Write_GPIO('A', 21, LOW);  // Turn OFF the LED
    Serial.println("LED OFF");
    timer.wait(20000);  // Wait for 2 seconds (20000 * 0.1ms)
}
