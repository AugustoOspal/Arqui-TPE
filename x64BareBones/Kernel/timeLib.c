#include <timeLib.h>

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

void timer_wait(uint64_t ticks) {
	unsigned long end = ticks_elapsed() + ticks;
	while (ticks_elapsed() < end);
}

// void getDateTime(dateTime *dt) {
// 		dt->sec = getSysSeconds();
// 		dt->min = getSysMinutes();
// 		dt->hour = getSysHours();
// 		dt->day = getSysDayOfMonth();
// 		dt->month = getSysMonth();
// 		dt->year = getSysYear();
// }