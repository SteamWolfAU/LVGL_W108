# LVGL W108 dashboard preview

This is a static LVGL 9 XML layout mockup of a classic W108/W109 instrument cluster. It uses sample telemetry values and PNG artwork; it does not exercise the C firmware or live CAN data.

## Load in the LVGL viewer/editor

Open the **repository root as the project folder** (the folder containing `project.xml` and `globals.xml`). The screen is in `screens/w108_screen.xml`; PNG paths in `globals.xml` are project-root-relative under `assets/`.

Expected project layout:

```text
project.xml
globals.xml
screens/w108_screen.xml
assets/*.png
```

If importing an archive, ZIP those files and preserve the `screens/` and `assets/` folder names. The target display is 1920 × 720, so use fit/zoom-to-screen if the preview viewport is smaller.

The PNGs are registered with `<data>` entries in `globals.xml` for viewer/editor conversion. If images still fail to load, check the viewer's import/asset panel for a missing-file or image-decoder error and confirm it imported the repository root rather than only the screen XML.

## Firmware status

`src/` contains early dashboard/CAN code, not a complete ESP-IDF project. Display initialization, ESP32-S3 LVGL port setup, and CAN receive integration remain separate work.
