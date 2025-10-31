#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

void button_reading (void);
int is_button_pressed(unsigned char index) ;
int is_button_pressed_1s (unsigned char index) ;
void button_init();
int is_button_down(uint8_t index);
static void start_config(void);

# endif /* INC_INPUT_READING_H_ */
