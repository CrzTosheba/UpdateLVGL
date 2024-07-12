#include "encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

//1000ms
#define HOLD_DELAY (1000)

static const char *TAG = "encoder";

enc_event _event = NULL;
char _isEvent = 0;

void enc_register_event(const enc_event e){
    _event = e;
    _isEvent = 1;
}

void enc_unregister_event(){
    _isEvent = 0;
}

// KEY position
typedef enum {
    KEY_POS_DOWN = 0,
    KEY_POS_UP = 1
} key_pos_st_t;

static int  _delay, _gpio_sw, _gpio_a, _gpio_b;


void enc_init(int delay, int gpio_sw, int gpio_a, int gpio_b){
    _delay = delay;
    _gpio_sw = gpio_sw;
    _gpio_a = gpio_a;
    _gpio_b = gpio_b;    
}

static uint8_t _key_val_prev = 1;
static uint32_t _hold = 0;

static uint8_t sw_avtomat(const uint8_t key_val_cur)
{
    uint8_t ret = ENC_NONE;
    uint8_t key_val_prev = _key_val_prev;
    _key_val_prev = key_val_cur;

    if(key_val_cur + key_val_prev == 2)
        return ret;

    int hticks = HOLD_DELAY / _delay;

    if(key_val_cur > key_val_prev){
        ret = ret | ENC_CLICK;
        if(_hold > hticks)
            ret = ret | ENC_LONG_HOLD;
        return ret;
    }

    ret = ret | ENC_HOLD;
    if(key_val_prev == KEY_POS_UP){
        _hold = 0;
    } 

    _hold ++;
    if(_hold % hticks == 0)
        ret = ret | ENC_LONG_HOLD;

    return ret;
}

static uint8_t _rotary_prev = 0;

static uint8_t rotary_avtomat(const uint8_t rotary_a, const uint8_t rotary_b)
{
    uint8_t ret = ENC_NONE; 
    uint8_t rotary_prev = _rotary_prev;
    uint8_t rotary_cur = (rotary_a << 1) | rotary_b;
    _rotary_prev = rotary_cur;

    if(rotary_a != rotary_b || rotary_cur == rotary_prev)
        return ret;
    
    if((rotary_prev & 0x1) == rotary_b)
        ret = ret | ENC_LEFT;
    else
        ret = ret | ENC_RIGHT; 

    return ret;
}


void enc_loop(){
    static uint8_t re_sw_state_cur = 0;
    static uint8_t re_a_state_cur = 0;
    static uint8_t re_b_state_cur = 0;

    while (1) {
        vTaskDelay(_delay / portTICK_PERIOD_MS);
        if(!_isEvent) 
            continue;

        uint8_t kp_sw = sw_avtomat(gpio_get_level(_gpio_sw));
        uint8_t kp_rot = rotary_avtomat(gpio_get_level(_gpio_a), gpio_get_level(_gpio_b));
        uint8_t full = kp_sw | kp_rot;

        //ESP_LOGI(TAG, "kp_sw = %d, kp_rot = %d", kp_sw,kp_rot);

        if(full && (full ^ ENC_HOLD))
            (*_event)(full);
    }
}
        






