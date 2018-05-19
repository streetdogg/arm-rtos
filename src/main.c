/*
 * Copyright (c) 2015, Martin Jaros <xjaros32@stud.feec.vutbr.cz>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

 /*
 * Copyright (c) 2017, Piyush Itankar <pitankar@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "system.h"

void thread1 () {
    for (int i=0; i<= 1000000; i++);
    GPIO_PORT_F->DATA[GPIO_PIN_1] = GPIO_PIN_1;

    for (int i=0; i<= 1000000; i++);
    GPIO_PORT_F->DATA[GPIO_PIN_1] = ~GPIO_PIN_1;
}

void thread2 () {
    for (int i=0; i<= 1000000; i++);
    GPIO_PORT_F->DATA[GPIO_PIN_2] = GPIO_PIN_2;

    for (int i=0; i<= 1000000; i++);
    GPIO_PORT_F->DATA[GPIO_PIN_2] = ~GPIO_PIN_2;
}

void setup_leds() {
  SYS_CTRL->RCGC2       |= CLK_PORT_F;
  GPIO_PORT_F->GPIODIR   = GPIO_PIN_2;
  GPIO_PORT_F->GPIODEN   = GPIO_PIN_2;
}

int main( void ){
  setup_leds();
  system_init();

//   create_thread(thread1);
//   create_thread(thread2);

  while(1)
    __asm("WFI");
}
