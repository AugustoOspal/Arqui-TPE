#include <timeLib.h>
#include <interrupts.h>

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

uint64_t ms_elapsed() {
	return (ticks * 1000) / 18;
}

/*
	TODO: Antes lo habia puesto contando los tick y no funcionaba
	bien en el userland, pero si en el kernel. Parece que es
	porque no le cedia control
*/
void sleep(uint64_t milliseconds) {
	uint64_t target_ticks = (milliseconds * 18) / 1000;
	uint64_t start_ticks = ticks;


	// Habilito los interrupts
	_sti();
	while ((ticks - start_ticks) < target_ticks);
	// Deshabilito los interrupts


	// TODO: Si dejaba esto no me andaba el teclado
	// _cli();
}

// void getDateTime(dateTime *dt) {
// 		dt->sec = getSysSeconds();
// 		dt->min = getSysMinutes();
// 		dt->hour = getSysHours();
// 		dt->day = getSysDayOfMonth();
// 		dt->month = getSysMonth();
// 		dt->year = getSysYear();
// }