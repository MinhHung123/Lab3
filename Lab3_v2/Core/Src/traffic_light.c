#include "display7SEG.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "input_reading.h"

enum TrafficState {
    INIT,
    AUTO_RED_GRN,
    AUTO_RED_YEL,
    AUTO_GRN_RED,
    AUTO_YEL_RED,
    RED_CONFIG,
	YEL_CONFIG,
	GRN_CONFIG
};

static enum TrafficState status = INIT;
int counter1 = 0, counter2 = 0;
int red = 7000, grn = 5000, yel = 2000;
int tmp_red = 7000, tmp_grn = 5000, tmp_yel = 2000;
int configue = 0;

void fsm_traffic_run(){
	switch (status){
	case INIT:
		setTimer(0, 1000);
		setTimer(1, grn);
		counter1 = red/1000;
		counter2 = grn/1000;
		updateLedBuffer(counter1, counter2);
		status = AUTO_RED_GRN;
		break;
	case AUTO_RED_GRN:
		turn_on_red_grn();
		if(isTimerExperied(0)){
			counter1--;
			counter2--;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
		}
		if(is_button_pressed(0)){
			HAL_GPIO_WritePin(LED_RED_SGN_GPIO_Port, LED_RED_SGN_Pin, 1);
			start_config();
			status = RED_CONFIG;
		}
		if(isTimerExperied(1)){
			counter1 = yel/1000;
			counter2 = yel/1000;
			setTimer(0, 1000);
			setTimer(1, yel);
			updateLedBuffer(counter1, counter2);
			status = AUTO_RED_YEL;
		}
		break;
	case AUTO_RED_YEL:
		turn_on_red_yel();
		if(isTimerExperied(0)){
			counter1--;
			counter2--;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
		}
		if(is_button_pressed(0)){
			HAL_GPIO_WritePin(LED_RED_SGN_GPIO_Port, LED_RED_SGN_Pin, 0);
			start_config();
			status = RED_CONFIG;
		}
		if(isTimerExperied(1)){
			counter1 = grn/1000;
			counter2 = red/1000;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
			setTimer(1, grn);
			updateLedBuffer(counter1, counter2);
			status = AUTO_GRN_RED;
		}
		break;
	case AUTO_GRN_RED:
		turn_on_grn_red();
		if(isTimerExperied(0)){
			counter1--;
			counter2--;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
		}
		if(isTimerExperied(1)){
			counter1 = yel/1000;
			counter2 = yel/1000;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
			setTimer(1, yel);
			updateLedBuffer(counter1, counter2);
			status = AUTO_YEL_RED;
		}
		if(is_button_pressed(0)){
			HAL_GPIO_WritePin(LED_RED_SGN_GPIO_Port, LED_RED_SGN_Pin, 0);
			start_config();
			status = RED_CONFIG;
		}
		break;
	case AUTO_YEL_RED:
		turn_on_yel_red();
		if(isTimerExperied(0)){
			counter1--;
			counter2--;
			updateLedBuffer(counter1, counter2);
			setTimer(0, 1000);
		}
		if(isTimerExperied(1)){
			status = INIT;
		}
		if(is_button_pressed(0)){
			HAL_GPIO_WritePin(LED_RED_SGN_GPIO_Port, LED_RED_SGN_Pin, 1);
			start_config();
			status = RED_CONFIG;
		}
		break;
	case RED_CONFIG:
		turn_red_blinky();
		show_config_val();
		if(is_button_pressed(0)) status = YEL_CONFIG;
		if(is_button_pressed(2)){
			configue = 0;
			red = tmp_red; grn = tmp_grn; yel = tmp_yel;
			ensure_red_time();
			status = INIT;
		}
		break;
	case YEL_CONFIG:
		turn_yel_blinky();
		show_config_val();
		if(is_button_pressed(0)) status = GRN_CONFIG;
		if(is_button_pressed(2)) {
			configue = 0;
			red = tmp_red; grn = tmp_grn; yel = tmp_yel;
			ensure_yel_time();
			status = INIT;
		}
		break;
	case GRN_CONFIG:
		turn_grn_blinky();
		show_config_val();
		if(is_button_pressed(0)) {
			ensure_grn_time();
			ensure_red_time();
			ensure_yel_time();
			status = INIT;
		}
		if(is_button_pressed(2)){
			configue = 0;
			red = tmp_red; grn = tmp_grn; yel = tmp_yel;
			ensure_grn_time();
			status = INIT;
		}
		break;
	default:
		break;
	}
}

void show_config_val(void){
	int v = 0;
	switch (status){
	case RED_CONFIG:
		v = tmp_red / 1000;
		break;
	case YEL_CONFIG:
		v = tmp_yel / 1000;
		break;
	case GRN_CONFIG:
		v = tmp_grn / 1000;
		break;
	default:
		break;
	}
	updateLedBuffer(v, v);
}

static void start_config(void){
	if(!configue){
		tmp_red = red;
		tmp_grn = grn;
		tmp_yel = yel;
		configue = 1;
	}
	setTimer(2, 500);
}

void short_press_increase(void){
	switch (status){
	case RED_CONFIG:
		tmp_red += 1000; if (tmp_red > 99000) tmp_red = 1000;
		show_config_val();
		break;
	case YEL_CONFIG:
		tmp_yel += 1000; if (tmp_yel > 99000) tmp_yel = 1000;
		show_config_val();
		break;
	case GRN_CONFIG:
		tmp_grn += 1000; if (grn > 99000) tmp_grn = 1000;
		show_config_val();
		break;
	default:
		break;
	}
}

void turn_on_red_grn(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, RESET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);

	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, RESET);
}

void turn_on_red_yel(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, RESET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);

	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, RESET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
}

void turn_on_grn_red(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, RESET);

	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, RESET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
}

void turn_on_yel_red(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, RESET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);

	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, RESET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
}

void turn_off_all(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);

	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
}

void turn_red_blinky(){
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
	if(isTimerExperied(2)){
		HAL_GPIO_TogglePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin);
		HAL_GPIO_TogglePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin);
		setTimer(2, 500);
	}
}

void turn_yel_blinky(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin, SET);
	if(isTimerExperied(2)){
		HAL_GPIO_TogglePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin);
		HAL_GPIO_TogglePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin);
		setTimer(2, 500);
	}
}

void turn_grn_blinky(){
	HAL_GPIO_WritePin(RED_0_SGN_GPIO_Port, RED_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_0_SGN_GPIO_Port, YEL_0_SGN_Pin, SET);
	HAL_GPIO_WritePin(RED_1_SGN_GPIO_Port, RED_1_SGN_Pin, SET);
	HAL_GPIO_WritePin(YEL_1_SGN_GPIO_Port, YEL_1_SGN_Pin, SET);
	if(isTimerExperied(2)){
		HAL_GPIO_TogglePin(GRE_0_SGN_GPIO_Port, GRE_0_SGN_Pin);
		HAL_GPIO_TogglePin(GRE_1_SGN_GPIO_Port, GRE_1_SGN_Pin);
		setTimer(2, 500);
	}
}

void ensure_red_time(){
	if(grn < red){
		grn = red - yel;
	}
	else {
		red = 7000;
		yel = 2000;
		grn = 5000;
	}
}

void ensure_grn_time(){
	if(grn < red){
		grn = red - yel;
	}
	else {
		red = 7000;
		yel = 2000;
		grn = 5000;
	}
}

void ensure_yel_time(){
	if(yel < grn){
		yel = red - grn;
	}
	else {
		red = 7000;
		yel = 2000;
		grn = 5000;
	}
}
