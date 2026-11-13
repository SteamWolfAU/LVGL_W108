cmake_minimum_required(VERSION 3.15)
project(w108_lvgl_dash C)

set(CMAKE_C_STANDARD 11)

# LVGL setup (usually added as a git submodule)
# add_subdirectory(lvgl)

add_executable(w108_lvgl_dash
    src/main.c
    src/haltech_can.c
    src/w108_dash.c
    assets/w108_bg.c
    assets/w108_left_face.c
    assets/w108_speedo_face.c
    assets/w108_clock_face.c
    assets/w108_orange_needle.c
)

target_include_directories(w108_lvgl_dash PRIVATE src assets)
# target_link_libraries(w108_lvgl_dash PRIVATE lvgl)
