/**
 * WLED - ESP-IDF Entry Point
 * 
 * This file provides the app_main() entry point for ESP-IDF
 * and bridges to the Arduino-style setup()/loop() that WLED uses.
 */

#include "Arduino.h"
#include "wled.h"

extern "C" void app_main(void)
{
    // Initialize Arduino framework
    initArduino();
    
    // Run WLED setup
    WLED::instance().setup();
    
    // Main loop - runs forever
    for(;;) {
        WLED::instance().loop();
        // Small yield to prevent watchdog issues
        vTaskDelay(1);
    }
}

