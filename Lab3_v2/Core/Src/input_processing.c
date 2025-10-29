#include "main.h"
#include "input_reading.h"
#include "traffic_light.h"
#include "software_timer.h"

enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void) {
    switch (buttonState) {
        case BUTTON_RELEASED:
            if (is_button_pressed(1)) {
                buttonState = BUTTON_PRESSED;
                // INCREASE VALUE OF PORT A BY ONE UNIT
                short_press_increase();
            }
            break;
        case BUTTON_PRESSED:
            if (!is_button_down(1)) {
                buttonState = BUTTON_RELEASED;
            } else {
                if (is_button_pressed_1s(1)) {
                	setTimer(3, 500);
                    buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_down(1)) {
                buttonState = BUTTON_RELEASED;
            }
            // todo
            if(isTimerExperied(3)){
            	short_press_increase();
            	setTimer(3, 500);
            }
            break;
    }
}
