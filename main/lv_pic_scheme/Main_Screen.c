#include <stdio.h>
#include <string.h>
#include "Main_Screen.h"
#include "lvgl.h"

 LV_FONT_DECLARE(bubble_big);
 LV_FONT_DECLARE(bubble_small);
 LV_FONT_DECLARE(drop);
 LV_FONT_DECLARE(marker);
 LV_FONT_DECLARE(pump_off);
 LV_FONT_DECLARE(pump_on);
 LV_FONT_DECLARE(scheme);
 LV_FONT_DECLARE(time);
 LV_FONT_DECLARE(valve);
 LV_FONT_DECLARE(valve_off);
 LV_FONT_DECLARE(Roboto_30);
 LV_FONT_DECLARE(ruler);

static lv_obj_t * list1;
static lv_obj_t *lbl_cnt;
static lv_obj_t *lbl_cnt1;
static lv_obj_t *lbl_cnt2;
static lv_obj_t *lbl_cnt3;
static uint32_t cnt = 0;

static void add_data(lv_timer_t*timer)
{
    cnt++;
    cnt = cnt % 100;
    lv_label_set_text_fmt(lbl_cnt, "%ld",cnt);
    lv_label_set_text_fmt(lbl_cnt1, "%ld",cnt/3);
    lv_label_set_text_fmt(lbl_cnt2, "%ld",cnt/2);
     lv_label_set_text_fmt(lbl_cnt3, "%ld",cnt/4);
}
static const lv_img_dsc_t* anim_imgs[2] = {    
    &pump_on,
    &pump_off,    
};


  

void main_screen(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style,lv_color_white());
   
    lv_obj_t * img = lv_img_create(lv_scr_act());
    lv_img_set_src(img,&scheme);
    lv_obj_set_pos(img, 200, 120);



 lv_obj_t * animimg0 = lv_animimg_create(lv_scr_act());
 lv_obj_set_pos(animimg0, 365, 195);
 lv_animimg_set_src(animimg0, (lv_img_dsc_t**) anim_imgs, 2);
 lv_animimg_set_duration(animimg0, 1000);
    lv_animimg_set_repeat_count(animimg0, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animimg0);

 lv_obj_t * animimg1 = lv_animimg_create(lv_scr_act());
 lv_obj_set_pos(animimg1, 365, 265);
 lv_animimg_set_src(animimg1, (lv_img_dsc_t**) anim_imgs, 2);
 lv_animimg_set_duration(animimg1, 2000);
    lv_animimg_set_repeat_count(animimg1, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animimg1);


    lv_obj_t * img3= lv_img_create(lv_scr_act());
    lv_img_set_src(img3,&bubble_small);
    lv_obj_set_pos(img3, 50, 148);

    lv_obj_t * img4= lv_img_create(lv_scr_act());
    lv_img_set_src(img4,&bubble_small);
    lv_obj_set_pos(img4, 50, 306);

    lv_obj_t * img5= lv_img_create(lv_scr_act());
    lv_img_set_src(img5,&bubble_small);
    lv_obj_set_pos(img5, 365, 306);

    lv_obj_t * img6= lv_img_create(lv_scr_act());
    lv_img_set_src(img6,&bubble_big);
    lv_obj_set_pos(img6, 365, 148);

    lv_obj_t * img7= lv_img_create(lv_scr_act());
    lv_img_set_src(img7,&valve);
    lv_obj_set_pos(img7, 65, 230);
    lv_obj_t * img8= lv_img_create(lv_scr_act());
    lv_img_set_src(img8,&valve);
    lv_obj_set_pos(img8, 65, 230);

    lv_obj_t * img9= lv_img_create(lv_scr_act());
    lv_img_set_src(img9,&ruler);
    lv_obj_set_pos(img9, 50, 380);







    lv_style_set_text_font(&style,&Roboto_30);
 
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "клапан");
    lv_obj_set_pos(label,65,200);
        lv_obj_t *label1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label1, "Отопление");
    lv_obj_set_pos(label1,200,80);

    lv_obj_add_style(lv_scr_act(), &style, 0);

    list1 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list1, 180, 300);
    lv_obj_set_pos(list1,600,100);
         /*Add buttons to the list*/
    lv_obj_t * btn;

    btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "GVS");
    //lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Heat");
    //lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "PODP");
   // lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "UV");
    //lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Pass");
   // lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
   lbl_cnt = lv_label_create(lv_scr_act());
   lbl_cnt1 = lv_label_create(lv_scr_act());
   lbl_cnt2 = lv_label_create(lv_scr_act());
   lbl_cnt3 = lv_label_create(lv_scr_act());
   lv_obj_set_pos(lbl_cnt,65,148);
   lv_obj_set_pos(lbl_cnt1,375,148);
   lv_obj_set_pos(lbl_cnt2,375,306);
   lv_obj_set_pos(lbl_cnt3,65,306);





    
      

lv_timer_create(add_data,500,NULL);
lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x1E2528), LV_PART_MAIN);
fflush(NULL);



}