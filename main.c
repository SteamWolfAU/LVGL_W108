#include "lvgl/lvgl.h"
#include "w108_dash.h"
#include "haltech_can.h"
#include <unistd.h>

/**
 * @brief Main execution entry point for the W108 Classic Digital Dashboard.
 * 
 * This file handles the initial setup of the LVGL graphics library, initializes
 * the Haltech Elite CAN telemetry data structures, renders the custom layout
 * using skeuomorphic image files, and runs the high-performance update loop.
 */
int main(void) {
    /* 1. Initialize the LVGL Graphics Library */
    lv_init();

    /* 2. Initialize the Haltech CAN-bus Telemetry Buffer */
    haltech_can_init();

    /* 3. Render the Classic Mercedes-Benz Dashboard UI Components */
    /* This sets up the circular pods, backgrounds, needles, warning lamps, and diagnostic window */
    w108_custom_graphics_init();

    /* 4. Core System Update Loop */
    while (1) {
        /* Periodically process LVGL tasks (rendering, timers, animations, input) */
        lv_timer_handler();
        
        /* 5ms sleep interval to prevent CPU starvation on embedded Linux / RTOS */
        usleep(5000); 

        /* 
         * Hardware Integration Step:
         * In your actual target hardware (e.g. ESP32, STM32, or Linux Framebuffer), 
         * your CAN peripheral interrupt/polling routine will feed raw CAN frames 
         * into our decoder:
         * 
         * haltech_can_frame_t rx_frame;
         * if (raw_can_receive_peripheral(&rx_frame)) {
         *     haltech_can_process_frame(&rx_frame);
         * }
         */

        /* 5. Dynamically Push Telemetry Data to the LVGL Gauge Objects */
        update_dashboard_data(
            vehicle_data.speed_mph,        /* Calculated vehicle speed (MPH) */
            vehicle_data.water_temp_f,     /* Coolant Temperature (°F) */
            vehicle_data.fuel_percent,     /* Fuel Level (0-100%) */
            vehicle_data.oil_psi,          /* Oil Pressure (PSI) */
            vehicle_data.rpm,              /* Engine RPM for Shift Light */
            vehicle_data.check_engine,     /* Check Engine LED Trigger (MIL) */
            vehicle_data.brake_warning,    /* Brake System LED Trigger */
            vehicle_data.alternator_fault, /* Alternator Charging LED Trigger */
            vehicle_data.diag_message      /* Terminal string printed to the central display */
        );
    }
    return 0;
}
