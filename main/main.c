#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"
#include "lv_pic_scheme/Main_Screen.h"
#include <stdio.h>
#include "driver/gpio.h"
#include "bsp_board.h"
//#include "./lib/encoder/encoder.h"




//#define CONFIG_RE_GET_PERIOD (10) // ms, Period get key + rot enc state
//#define CONFIG_LOG_MAXIMUM_LEVEL (3)


//static const char *TAG = "main";

static void rotary_encoder_gpio_init(void)
{
   // ESP_LOGI(TAG, "Example configured to rotary encoder GPIO!");
    gpio_reset_pin(GPIO_ROT_ENC_SW);
    gpio_reset_pin(GPIO_ROT_ENC_A);
    gpio_reset_pin(GPIO_ROT_ENC_B);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_ROT_ENC_SW, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_ROT_ENC_A, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_ROT_ENC_B, GPIO_MODE_INPUT);
}







static void lv_tick_task(void *arg)
{

    while(1) 
    {
        vTaskDelay((10) / portTICK_PERIOD_MS);
        lv_task_handler();        
    }
}




void app_main()
{
    /* LVGL init */
    lv_init();            
    lv_port_disp_init();
    main_screen();
    //lv_example_chart_2();
    lv_port_tick_init();
    rotary_encoder_gpio_init();


    xTaskCreate(lv_tick_task, "lv_tick_task", 4096, NULL, 1, NULL);
   // xTaskCreate(lv_example_chart_2, "lv_example_chart_2", 4096, NULL, 2, NULL);
    

}
