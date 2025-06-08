#include <timeLib.h>

// dateTime* getTime() {
//      return sys_getTime(); 
// }

extern void sleepMilli(uint64_t milliseconds){
    sys_sleepMilli(milliseconds);
}