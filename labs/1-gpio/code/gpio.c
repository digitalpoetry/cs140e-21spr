/*
 * Implement the following routines to set GPIO pins to input or output,
 * and to read (input) and write (output) them.
 *
 * DO NOT USE loads and stores directly: only use GET32 and PUT32 
 * to read and write memory.  Use the minimal number of such calls.
 *
 * See rpi.h in this directory for the definitions.
 */
#include "rpi.h"

// see broadcomm documents for magic addresses.
#define GPIO_BASE 0x20200000
static const unsigned gpio_set0  = (GPIO_BASE + 0x1C);
static const unsigned gpio_clr0  = (GPIO_BASE + 0x28);
static const unsigned gpio_lev0  = (GPIO_BASE + 0x34);

void gpio_function_select(unsigned pin, unsigned function_code) {
    int total_registers = 6;
    int register_width = 4;
    int range_per_register = 10;
    int selection_width = 0x03;
    
    // Read current state
    uint32_t current_bits[total_registers];
    for (int i = 0; i < total_registers; i++) {
        current_bits[i] = GET32(GPIO_BASE + (i * register_width));
    }
    // Calculate new state
    int offset = (selection_width * (pin % range_per_register));
    uint32_t bit_mask = 0b111 << offset;
    uint32_t cleared_selection = current_bits[pin / range_per_register] & ~bit_mask;
    current_bits[pin / range_per_register] = cleared_selection | (function_code << offset);
    // Write new state
    for (int i = 0; i < total_registers; i++) {
        PUT32(GPIO_BASE + (i * register_width), current_bits[i]);
    }
}

//
// Part 1 implement gpio_set_on, gpio_set_off, gpio_set_output
//

// set <pin> to be an output pin.  
//
// note: fsel0, fsel1, fsel2 are contiguous in memory, so you 
// can (and should) use array calculations!
void gpio_set_output(unsigned pin) {    
    gpio_function_select(pin, 0b001);
}

// set GPIO <pin> on.
void gpio_set_on(unsigned pin) {
    // Writing 0 to GPSETn has no effect
    PUT32(gpio_set0, 1 << pin);
}

// set GPIO <pin> off
void gpio_set_off(unsigned pin) {
    // Writing 0 to GPCLRn has no effect
    PUT32(gpio_clr0, 1 << pin);
}

// set <pin> to <v> (v \in {0,1})
void gpio_write(unsigned pin, unsigned v) {
    if(v)
       gpio_set_on(pin);
    else
       gpio_set_off(pin);
}

//
// Part 2: implement gpio_set_input and gpio_read
//

// set <pin> to input.
void gpio_set_input(unsigned pin) {
    gpio_function_select(pin, 0b000);
}

// return the value of <pin>
int gpio_read(unsigned pin) {
    unsigned v = 0;

    // implement.
    return v;
}
