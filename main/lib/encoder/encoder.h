#ifndef _ENCODER_
#define _ENCODER_

#include <stdint.h>

enum enc_event_en {
 ENC_NONE           = 0,
 ENC_LEFT           = 1,
 ENC_FAST_LEFT      = 2, //TODO
 ENC_RIGHT          = 4,
 ENC_FAST_RIGHT     = 8, //TODO
 ENC_HOLD           = 16,
 ENC_LONG_HOLD      = 32, //TODO
 ENC_CLICK          = 64,
 ENC_DOUBLE_CLICK   = 128 //TODO
};

typedef void (*enc_event)(uint8_t t);

void enc_init(int delay, int gpio_sw, int gpio_a, int gpio_b);
void enc_register_event(const enc_event e);
void enc_unregister_event();

void enc_loop();

#endif //_ENCODER_