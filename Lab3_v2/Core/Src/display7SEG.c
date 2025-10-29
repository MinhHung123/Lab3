#include "display7SEG.h"
#include "software_timer.h"

uint8_t digit[10] = {0b1000000, 0b1111001, 0b0100100,
		             0b0110000, 0b0011001, 0b0010010,
					 0b0000010, 0b1111000, 0b0000000,
					 0b0010000};
int led_buffer[4] = {0, 0, 0, 0};

void display7SEG(int num){
	HAL_GPIO_WritePin(GPIOA, LED_A_SGN_Pin | LED_B_SGN_Pin | LED_C_SGN_Pin
			| LED_D_SGN_Pin | LED_E_SGN_Pin | LED_F_SGN_Pin
			| LED_G_SGN_Pin, SET);
	uint8_t number = digit[num];
	HAL_GPIO_WritePin(LED_A_SGN_GPIO_Port, LED_A_SGN_Pin, (number & (1<<0)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_B_SGN_GPIO_Port, LED_B_SGN_Pin, (number & (1<<1)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_C_SGN_GPIO_Port, LED_C_SGN_Pin, (number & (1<<2)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_D_SGN_GPIO_Port, LED_D_SGN_Pin, (number & (1<<3)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_E_SGN_GPIO_Port, LED_E_SGN_Pin, (number & (1<<4)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_F_SGN_GPIO_Port, LED_F_SGN_Pin, (number & (1<<5)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_SGN_GPIO_Port, LED_G_SGN_Pin, (number & (1<<6)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_DOT_SGN_GPIO_Port, LED_DOT_SGN_Pin, GPIO_PIN_RESET);
}

void unable_led_7SEG(){
	HAL_GPIO_WritePin(EN0_SGN_GPIO_Port, EN0_SGN_Pin, SET);
	HAL_GPIO_WritePin(EN1_SGN_GPIO_Port, EN1_SGN_Pin, SET);
	HAL_GPIO_WritePin(EN2_SGN_GPIO_Port, EN2_SGN_Pin, SET);
	HAL_GPIO_WritePin(EN3_SGN_GPIO_Port, EN3_SGN_Pin, SET);
}

void update7SEG(int index){
	unable_led_7SEG();
	switch (index){
	case 0:
		HAL_GPIO_WritePin(EN0_SGN_GPIO_Port, EN0_SGN_Pin, RESET);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		HAL_GPIO_WritePin(EN1_SGN_GPIO_Port, EN1_SGN_Pin, RESET);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		HAL_GPIO_WritePin(EN2_SGN_GPIO_Port, EN2_SGN_Pin, RESET);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		HAL_GPIO_WritePin(EN3_SGN_GPIO_Port, EN3_SGN_Pin, RESET);
		display7SEG(led_buffer[3]);
	default:
		break;
	}
}

void updateLedBuffer(int digit1, int digit2){
	int a = digit1%10;
	int b = digit1/10;
	int c = digit2%10;
	int d = digit2/10;
	led_buffer[0] = b;
	led_buffer[1] = a;
	led_buffer[2] = d;
	led_buffer[3] = c;
}


