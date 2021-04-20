// trivial test of putk: this is the easiest one, since the uart hardware
// is pretty tolerant of errors.
#include "rpi.h"
#include "sw-uart.h"

void notmain(void) {
    uart_init();
    enable_cache();

    // use pin 20 for tx, 21 for rx
    sw_uart_t u = sw_uart_mk(20,21, 115200);

    printk("%d: going to print 'hi'\n");
    sw_uart_put8(&u, 'h');
    sw_uart_put8(&u, 'i');
    sw_uart_put8(&u, '\n');

    delay_ms(1000);
    clean_reboot();
}
