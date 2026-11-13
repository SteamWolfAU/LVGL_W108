# Classic Mercedes W108/W109 LVGL Dashboard

A skeuomorphic instrument-cluster concept for an LVGL display. The XML project files and PNG artwork are arranged for visual testing in the LVGL web viewer; the C sources are a separate, incomplete embedded integration and are not currently a standalone ESP-IDF application.

## Preview in viewer.lvgl.io

Load the project using these files together, preserving their paths:

- `project.xml`
- `globals.xml`
- `w108_screen.xml`
- `assets/*.png`

The `globals.xml` image paths are relative to the repository root and include the `assets/` directory. Initial telemetry subjects are defined there so the dashboard has sample values in the preview.

The project targets a 1920 × 720, 32-bit display. If the viewer asks for a project archive, ZIP the listed XML files and the `assets/` directory without flattening the paths.

## Current limitations

- The C dashboard implementation is not yet a complete ESP32-S3/ESP-IDF application; display initialization, LVGL port/tick setup, and CAN receive integration still need to be provided by the target project.
- `project.xml` selects LVGL 9.5.0 for the XML preview. The older C image and UI sources include LVGL 8-era APIs; they must be brought onto the same LVGL version before compiling together.
- The `.c` files for the background and dial-face assets are not generated image descriptors. Use the PNG assets for the viewer, or regenerate LVGL-compatible C descriptors for the firmware build.

## Layout

- `src/`: dashboard C code and Haltech CAN frame decoder
- `assets/`: source PNG artwork and generated/placeholder C assets
- `project.xml`, `globals.xml`, `w108_screen.xml`: viewer project, constants/subjects/assets, and screen layout
