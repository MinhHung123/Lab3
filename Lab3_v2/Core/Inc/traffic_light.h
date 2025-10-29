#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"

void fsm_traffic_run();

void turn_on_red_grn();
void turn_on_red_yel();
void turn_on_grn_red();
void turn_on_yel_red();

void turn_red_blinky();
void turn_yel_blinky();
void turn_grn_blinky();

void turn_off_all();

void red_config();
void yel_config();
void grn_config();

void short_press_increase(void);
void long_press_increase(void);
void show_config_val(void);

void ensure_red_time();
void ensure_grn_time();
void ensure_yel_time();

#endif
