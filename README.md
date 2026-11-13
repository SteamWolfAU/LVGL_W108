# LVGL W108 dashboard preview

This repository includes an XML mockup of a classic Mercedes W108/W109 instrument cluster. The preview is a **static design/layout test** with sample values; it does not exercise the C firmware, live data bindings, display drivers, or CAN hardware.

## Open in the LVGL viewer

Use the XML project files and PNG artwork together, preserving the directory layout:

```text
project.xml
globals.xml
w108_screen.xml
assets/
  w108_bg.png
  w108_clock_face.png
  w108_left_face.png
  w108_orange_needle.png
  w108_speedo_face.png
```

Open/import the project in [viewer.lvgl.io](https://viewer.lvgl.io/). If the viewer requests a project archive, ZIP the three root XML files and the `assets/` directory without flattening the paths. The screen uses LVGL 9 XML widget syntax; images are registered in `globals.xml` with paths relative to the project root.

The declared target is 1920 × 720. If the preview viewport is smaller, zoom or fit the canvas to view the complete cluster.

## Firmware status

`src/` contains an early C dashboard and CAN decoder, not a complete ESP-IDF project. It still needs an ESP32-S3 display/LVGL port, an ESP-IDF `app_main()` integration, and a real CAN receive path. The current XML mockup is independent from those firmware sources.
