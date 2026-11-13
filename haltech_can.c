#include "haltech_can.h"
#include <string.h>
#include <stdio.h>

/* Global vehicle data instance */
haltech_vehicle_data_t vehicle_data;

/**
 * @brief Initializes the vehicle CAN data structure.
 */
void haltech_can_init(void) {
    memset(&vehicle_data, 0, sizeof(vehicle_data));
    vehicle_data.fuel_percent = 100.0f; // Start with full tank by default
}

/**
 * @brief Decodes raw incoming CAN frames from the Haltech Elite network.
 * @param frame Pointer to the raw received CAN frame structure.
 */
void haltech_can_process_frame(const haltech_can_frame_t *frame) {
    if (!frame) return;

    switch (frame->id) {
        case 0x3E0: // Channel: RPM and Speed
            /* RPM (Big Endian, 2 bytes, 1 RPM/bit resolution) */
            vehicle_data.rpm = (frame->data[0] << 8) | frame->data[1];
            
            /* Vehicle Speed (Big Endian, 2 bytes, 10th of km/h) */
            uint16_t raw_speed = (frame->data[2] << 8) | frame->data[3];
            /* Convert km/h to MPH (1 km/h = 0.621371 mph) */
            vehicle_data.speed_mph = (raw_speed / 10.0f) * 0.621371f; 
            break;

        case 0x3E1: // Channel: Coolant Temp and Oil Pressure
            /* Coolant Temp (1 byte raw Celsius value, typical offset is 0) */
            /* Convert Celsius to Fahrenheit (°F = °C * 1.8 + 32) */
            vehicle_data.water_temp_f = (frame->data[0] * 1.8f) + 32.0f;
            
            /* Oil Pressure (Big Endian, 2 bytes, units of kPa) */
            uint16_t raw_oil = (frame->data[1] << 8) | frame->data[2];
            /* Convert kPa to PSI (1 kPa = 0.145038 psi) */
            vehicle_data.oil_psi = (raw_oil / 10.0f) * 0.145038f;
            break;

        case 0x3E2: // Channel: Fuel Level & Diagnostics Flags
            /* Fuel Level (1 byte raw, 0% to 100%) */
            vehicle_data.fuel_percent = frame->data[0];
            
            /* Decode Status warning flags inside data byte 1 */
            vehicle_data.check_engine     = (frame->data[1] & 0x01); // Bit 0: Malfunction Indicator Lamp (MIL)
            vehicle_data.brake_warning    = (frame->data[1] & 0x02); // Bit 1: Handbrake/Brake warning lamp
            vehicle_data.alternator_fault = (frame->data[1] & 0x04); // Bit 2: Alternator charging fault
            break;

        default:
            break;
    }

    /* Compile a real-time console status string for your center square screen */
    snprintf(vehicle_data.diag_message, sizeof(vehicle_data.diag_message),
             "CAN STATUS: ACTIVE\nRPM: %u rpm\nOIL: %.1f psi", 
             vehicle_data.rpm, 
             vehicle_data.oil_psi);
}
