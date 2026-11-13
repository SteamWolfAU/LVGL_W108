#ifndef W108_DASH_H
#define W108_DASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

/**
 * @brief Initializes all static and dynamic graphical components of the W108 dashboard.
 * 
 * This function handles creating the horizontal ribbed background, rendering the static
 * gauge faces, establishing coordinate-aligned gauge pods, setting up warning overlays,
 * and initializing the central diagnostic window and shift light bar.
 */
void w108_custom_graphics_init(void);

/**
 * @brief Updates all dashboard dials, warning lights, and diagnostic readouts with new data.
 * 
 * This function translates raw engine and vehicle parameters into physical needle sweeps
 * and warning light illumination states on your display.
 * 
 * @param speed_mph         Current vehicle speed in Miles Per Hour (MPH) (0.0 to 160.0).
 * @param water_temp_f      Engine coolant temperature in Fahrenheit (°F) (100.0 to 250.0).
 * @param fuel_percent      Fuel tank level percentage (0.0 to 100.0).
 * @param oil_psi           Engine oil pressure in PSI (0.0 to 45.0).
 * @param rpm               Engine speed in Revolutions Per Minute (RPM) used for shift light calculations.
 * @param is_mil            Check Engine Light state: 1 to illuminate, 0 to dim.
 * @param is_brake          Brake Warning Light state: 1 to illuminate, 0 to dim.
 * @param is_alt_fault      Alternator/Generator Fault state: 1 to illuminate, 0 to dim.
 * @param diagnostic_msg    Pointer to a character string printed on the central diagnostic screen.
 */
void update_dashboard_data(float speed_mph, float water_temp_f, float fuel_percent, float oil_psi, 
                           int rpm, int is_mil, int is_brake, int is_alt_fault, const char* diagnostic_msg);

#ifdef __cplusplus
}
#endif

#endif /* W108_DASH_H */
