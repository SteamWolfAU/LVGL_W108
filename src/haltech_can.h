#ifndef HALTECH_CAN_H
#define HALTECH_CAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Standardized CAN Frame structure
 * Represents a raw packet received from the CAN network controller.
 */
typedef struct {
    uint32_t id;         /* 11-bit or 29-bit CAN Message Identifier */
    uint8_t  data[8];    /* 8-Byte Payload Data Buffer */
    uint8_t  dlc;        /* Data Length Code (Number of valid payload bytes, 0-8) */
} haltech_can_frame_t;

/**
 * @brief Vehicle Telemetry Data Structure
 * Stores decoded, unit-converted values ready to be drawn directly by the LVGL gauges.
 */
typedef struct {
    float    speed_mph;         /* Decoded Vehicle Speed in Miles Per Hour (MPH) */
    float    water_temp_f;      /* Coolant Temperature in Fahrenheit (°F) */
    float    fuel_percent;      /* Fuel Tank Level (0.0% to 100.0%) */
    float    oil_psi;           /* Engine Oil Pressure in PSI */
    uint16_t rpm;               /* Engine Revolutions Per Minute (RPM) */
    uint8_t  check_engine;      /* Active Malfunction Indicator Lamp (MIL) Flag (0 or 1) */
    uint8_t  brake_warning;     /* Active Brake System Warning LED Flag (0 or 1) */
    uint8_t  alternator_fault;  /* Active Alternator/Battery fault Flag (0 or 1) */
    char     diag_message[64];  /* Text output printed inside the center digital screen */
} haltech_vehicle_data_t;

/* Global reference containing the parsed current telemetry states */
extern haltech_vehicle_data_t vehicle_data;

/**
 * @brief Initializes the CAN-telemetry parsing buffers.
 */
void haltech_can_init(void);

/**
 * @brief Processes and decodes raw CAN-bus payloads.
 * @param frame Pointer to the raw CAN frame packet.
 */
void haltech_can_process_frame(const haltech_can_frame_t *frame);

#ifdef __cplusplus
}
#endif

#endif /* HALTECH_CAN_H */
