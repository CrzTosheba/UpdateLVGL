#include <stdio.h>
#include <string.h>
#include "base_obj.h"
#include "lvgl.h"



LV_FONT_DECLARE(yellow_tail_30);
LV_FONT_DECLARE(Roboto_30);


void base_obj(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x009900FF), LV_PART_MAIN);
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, 0);
    lv_style_set_text_font(&style, &Roboto_30); 
    lv_label_set_text(label, "Отопление");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
      
    lv_obj_align(label, LV_ALIGN_CENTER, 5, 100);

fflush(NULL);

}