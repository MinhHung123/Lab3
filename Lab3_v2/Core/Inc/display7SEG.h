#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "main.h"
#include "software_timer.h"

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(int digit1, int digit2);
void unable_led_7SEG();

#endif /* INC_DISPLAY7SEG_H_ */
