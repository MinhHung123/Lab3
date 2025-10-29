#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

void setTimer(int index, int duration);
void timer_run();
int isTimerExperied(int index);

#endif
