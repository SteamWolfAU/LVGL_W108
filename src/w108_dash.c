#include "w108_dash.h"
#include <stdio.h>

/* Style Palette (Classic VDO colors) */
#define COLOR_VINTAGE_BLACK lv_color_make(0x11, 0x11, 0x11)
#define COLOR_VINTAGE_WHITE lv_color_make(0xEB, 0xE7, 0xDF)
#define COLOR_CHROME        lv_color_make(0xD1, 0xD5, 0xDB)
#define COLOR_WARN_RED      lv_color_make(0xDF, 0x20, 0x20)
#define COLOR_WARN_ORANGE   lv_color_make(0xE6, 0x7E, 0x22)
#define COLOR_NEEDLE_ORANGE lv_color_make(0xFA, 0x78, 0x3E)

/* Declare the converted graphical assets */
LV_IMG_DECLARE(w108_bg);            /* 1920x720 master charcoal ribbed background */
LV_IMG_DECLARE(w108_left_face);     /* 500x500 multi-gauge overlay (Temp, Fuel, Oil) */
LV_IMG_DECLARE(w108_speedo_face);   /* 500x500 speedometer dial face overlay */
LV_IMG_DECLARE(w108_clock_face);    /* 200x200 VDO circular clock face overlay */
LV_IMG_DECLARE(w108_orange_needle);  /* Tapered skeuomorphic copper-orange needle */

/* Dynamic GUI Objects */
static lv_obj_t *img_speed_needle;
static lv_obj_t *img_temp_needle;
static lv_obj_t *img_fuel_needle;
static lv_obj_t *img_oil_needle;

static lv_obj_t *img_check_engine;
static lv_obj_t *img_brake_warn;
static lv_obj_t *img_gen_warn;

static lv_obj_t *lbl_odo;
static lv_obj_t *lbl_trip;

static lv_obj_t *can_status_box;
static lv_obj_t *can_log_label;
static lv_obj_t *shift_light;

/**
 * @brief Initialize all dashboard graphical components and static structures.
 */
void w108_custom_graphics_init(void) {
    lv_obj_t *screen = lv_scr_act();

    /* 1. Draw Master Ribbed Background */
    /* Placing this as a single hardware-accelerated image saves massive GPU draw call cycles */
    lv_obj_t *bg = lv_img_create(screen);
    lv_img_set_src(bg, &w108_bg);
    lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);

    /* 2. Left Pod (Temp, Fuel, Oil, & Warning indicators) */
    lv_obj_t *left_pod = lv_obj_create(screen);
    lv_obj_set_size(left_pod, 500, 500);
    lv_obj_align(left_pod, LV_ALIGN_LEFT_MID, 120, 0);
    lv_obj_set_style_bg_opa(left_pod, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(left_pod, 0, 0);
    lv_obj_clear_flag(left_pod, LV_OBJ_FLAG_SCROLLABLE);

    /* Add Left Gauge Dial face artwork */
    lv_obj_t *left_face = lv_img_create(left_pod);
    lv_img_set_src(left_face, &w108_left_face);
    lv_obj_align(left_face, LV_ALIGN_CENTER, 0, 0);

    /* Add left pod sweeping needles (All pivot from absolute center of pod) */
    img_temp_needle = lv_img_create(left_pod);
    lv_img_set_src(img_temp_needle, &w108_orange_needle);
    lv_img_set_pivot(img_temp_needle, 12, 180); /* Pivot point aligned to custom needle asset geometry */
    lv_obj_align(img_temp_needle, LV_ALIGN_CENTER, 0, 0);

    img_fuel_needle = lv_img_create(left_pod);
    lv_img_set_src(img_fuel_needle, &w108_orange_needle);
    lv_img_set_pivot(img_fuel_needle, 12, 180);
    lv_obj_align(img_fuel_needle, LV_A
