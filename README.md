# LVGL W108 dashboard preview

This is a static LVGL 9 XML layout mockup of a classic W108/W109 instrument cluster. It uses sample telemetry values and PNG artwork; it does not exercise the C firmware or live CAN data.

## Load in the LVGL viewer/editor

Open the **repository root as the project folder** (the folder containing `project.xml` and `globals.xml`). The project screen is `screens/w108_screen.xml`. The root-level `w108_screen.xml` is kept as a valid duplicate for viewers that open a selected XML file directly.

Expected project layout:

```text
project.xml
globals.xml
w108_screen.xml
screens/w108_screen.xml
assets/*.png
```

If importing an archive, ZIP the XML files and `assets/` directory, preserving folder names. The target display is 1920 × 720, so use fit/zoom-to-screen if the preview viewport is smaller. PNGs are registered as `<data>` in `globals.xml`, with paths relative to the project root.

## Firmware status

`src/` contains early dashboard/CAN code, not a complete ESP-IDF project. Display initialization, ESP32-S3 LVGL port setup, and CAN receive integration remain separate work.
