#include "software_timer.h"

#define TIMER_CYCLE 10
#define number_timer 4

int timer_flag[number_timer] = {0};
int timer_counter[number_timer] = {0};

void setTimer(int index, int duration){
	timer_counter[index] = duration/TIMER_CYCLE;
	timer_flag[index] = 0;
}

void timer_run(){
	for(int i=0; i<number_timer; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] == 0){
				timer_flag[i] = 1;
			}
		}
	}
}

int isTimerExperied(int index){
	if(timer_flag[index] == 1){
		timer_flag[index] = 0;
		return 1;
	}
	return 0;
}
