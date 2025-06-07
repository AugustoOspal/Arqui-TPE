#include <time.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

// void getDateTime(dateTime *dt) {
// 	dt->sec = getSysSeconds();
// 	dt->min = getSysMinutes();
// 	dt->hour = getSysHours();
// 	dt->day = getSysDayOfMonth();
// 	dt->month = getSysMonth();
// 	dt->year = getSysYear();
// }