# Classic Mercedes W108/W109 LVGL Dashboard

A skeuomorphic classic car digital cluster interface powered by **LVGL v8** and dynamic **Haltech Elite CAN-bus** telemetry.

## File Structure
- `src/main.c`: Core entry loop and thread handling.
- `src/w108_dash.c / .h`: Graphical gauge layouts, placement coordinates, and dynamic needle mapping equations.
- `src/haltech_can.c / .h`: Dynamic CAN-bus packet decoder for RPM, Speed, Temperature, Oil Pressure, and OBD Diagnostic MIL status.
- `assets/`: Empty/mock placeholder C-arrays for images. Convert your high-res design files (`.png`) via [LVGL Image Converter](https://lvgl.io/tools/imageconverter) to overwrite these arrays.

## Integration & Compilation
1. Add this repository as a submodule or source folder into your primary MPU framework project (e.g. ESP32-S3, NXP i.MX RT, or Linux framebuffer).
2. Wire your CAN Transceiver (such as MCP2515 or internal MPU controller) to feed raw packets to `haltech_can_process_frame(...)`.
3. Overwrite the files in the `assets/` folder with those exported from the online converter.
