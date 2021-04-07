We will fill these in as they come up.


### Hints for 1-fake-pi

You can run things by hand to see better what is going on.

        % cd 1-fake-pi/tests
        % make

        # run one of the 0 tests by hand
        % ./0-put
        calling pi code
        TRACE:PUT32:20200000:1
        pi exited cleanly
        TRACE:1 calls to random

        # what is it doing?
        % cat 0-put.c
        #include "rpi.h"
        void notmain(void) {
            PUT32(0x20200000, 1);
        }
 

An easy way to get a difference is to call `fake_random` a different
number of times.  The `fake-pi` code will print out the number of calls
so check that first.

There are a couple reference outputs:

        % cat 1-fake-pi/tests/0-get.*ref
        TRACE:GET32:20200000:327b23c6
        TRACE:2 calls to random


If `ls` lists the output in the same order, you can run `cksum` on the
`cksum` of everything for a single way to compare everything:

        % make emitall
        % ls *.out
        0-get.out      1-blink.out	     1-gpio-set-on.out	    3-unix-gpio-test.out
        0-put-get.out  1-gpio-set-input.out  1-gpio-set-output.out  3-unix-test-put-get.out
        0-put.out      1-gpio-set-off.out    2-blink.out	    4-unix-test-gpio.out
        % cksum *.out | cksum
        289534801 379

