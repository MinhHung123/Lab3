#include "main.h"
#include "traffic_light.h"

// We aim to work with more than one button
#define NO_OF_BUTTONS 3

// Timer interrupt duration is 10ms, so to pass 1 second,
// we need to jump to the interrupt service routine 100 times
#define DURATION_FOR_AUTO_INCREASING  100

#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

// The buffer that stores the final result after debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

// Two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];
static GPIO_PinState lastStable[NO_OF_BUTTONS];

// Flag for a button pressed more than 1 second
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint8_t pressed_flag[NO_OF_BUTTONS];
// Counter for automatically increasing the value
// after the button is pressed for more than 1 second
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

void button_init(){
	for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
		debounceButtonBuffer1[i] = debounceButtonBuffer2[i] = BUTTON_IS_RELEASED;
		buttonBuffer[i] = BUTTON_IS_RELEASED;
		lastStable[i] = BUTTON_IS_RELEASED;
		pressed_flag[i] = 0;
		counterForButtonPress1s[i] = 0;
		flagForButtonPress1s[i] = 0;
	}
}

void button_reading(void) {
    for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
    	debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        switch (i){
			case 0:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_0_GPIO_Port, BTN_0_Pin);
				break;
			case 1:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin);
				break;
			case 2:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin);
				break;
			default:
				break;
		}
        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i] && debounceButtonBuffer2[i] == debounceButtonBuffer3[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }
        if (lastStable[i] == BUTTON_IS_RELEASED && buttonBuffer[i] == BUTTON_IS_PRESSED) {
        	pressed_flag[i] = 1;
        }
        if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
            // If a button is pressed, we start counting
            if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                counterForButtonPress1s[i]++;
            } else {
                // The flag is turned on when 1 second has passed
                // since the button was pressed
                flagForButtonPress1s[i] = 1;
                // TODO: Handle long-press action
            }
        } else {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
        lastStable[i] = buttonBuffer[i];
    }
}


int is_button_pressed(uint8_t index) {
	if(index >= NO_OF_BUTTONS) return 0;
	if (pressed_flag[index]) {
		pressed_flag[index] = 0;
		return 1;
	}
	return 0;
}

int is_button_pressed_1s(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0;
	if(flagForButtonPress1s[index] == 1) return 1;
	return 0;
}

int is_button_down(uint8_t index){
    if(index >= NO_OF_BUTTONS) return 0;
    extern GPIO_PinState buttonBuffer[];
    return buttonBuffer[index] == BUTTON_IS_PRESSED;
}


