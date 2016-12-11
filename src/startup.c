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

#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 256

extern int main();

void ResetIntHandler(){
    extern uint32_t _etext, _data, _edata, _bss, _ebss;
    uint32_t *src = &_etext, *dst = &_data;
    while(dst < &_edata) *(dst++) = *(src++);
    for(dst = &_bss; dst < &_ebss; dst++) *dst = 0;

    main();

    while(1);
}

void DefaultIntHandler(){
    while(1);
}

static uint32_t stack[STACK_SIZE];
__attribute__ ((section(".isr_vector"))) void (*const vectors[])() =
{
    (void (*)())((uint32_t)stack + sizeof(stack)),
    ResetIntHandler,                        // The reset handler
    DefaultIntHandler,                      // The NMI handler
    DefaultIntHandler,                      // The hard fault handler
    DefaultIntHandler,                      // The MPU fault handler
    DefaultIntHandler,                      // The bus fault handler
    DefaultIntHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultIntHandler,                      // SVCall handler
    DefaultIntHandler,                      // Debug monitor handler
    0,                                      // Reserved
    DefaultIntHandler,                      // The PendSV handler
    DefaultIntHandler,                      // The SysTick handler
    DefaultIntHandler,                      // GPIO Port A
    DefaultIntHandler,                      // GPIO Port B
    DefaultIntHandler,                      // GPIO Port C
    DefaultIntHandler,                      // GPIO Port D
    DefaultIntHandler,                      // GPIO Port E
    DefaultIntHandler,                    	// UART0 Rx and Tx
    DefaultIntHandler,                      // UART1 Rx and Tx
    DefaultIntHandler,                      // SSI0 Rx and Tx
    DefaultIntHandler,                      // I2C0 Master and Slave
    DefaultIntHandler,                      // PWM Fault
    DefaultIntHandler,                      // PWM Generator 0
    DefaultIntHandler,                      // PWM Generator 1
    DefaultIntHandler,                      // PWM Generator 2
    DefaultIntHandler,                      // Quadrature Encoder 0
    DefaultIntHandler,                      // ADC Sequence 0
    DefaultIntHandler,                      // ADC Sequence 1
    DefaultIntHandler,                      // ADC Sequence 2
    DefaultIntHandler,                      // ADC Sequence 3
    DefaultIntHandler,                      // Watchdog timer
    DefaultIntHandler,                      // Timer 0 subtimer A
    DefaultIntHandler,                      // Timer 0 subtimer B
    DefaultIntHandler,                      // Timer 1 subtimer A
    DefaultIntHandler,                      // Timer 1 subtimer B
    DefaultIntHandler,                      // Timer 2 subtimer A
    DefaultIntHandler,                      // Timer 2 subtimer B
    DefaultIntHandler,                      // Analog Comparator 0
    DefaultIntHandler,                      // Analog Comparator 1
    DefaultIntHandler,                      // Analog Comparator 2
    DefaultIntHandler,                      // System Control (PLL, OSC, BO)
    DefaultIntHandler,                      // FLASH Control
    DefaultIntHandler,                      // GPIO Port F
    DefaultIntHandler,                      // GPIO Port G
    DefaultIntHandler,                      // GPIO Port H
    DefaultIntHandler,                      // UART2 Rx and Tx
    DefaultIntHandler,                      // SSI1 Rx and Tx
    DefaultIntHandler,                      // Timer 3 subtimer A
    DefaultIntHandler,                      // Timer 3 subtimer B
    DefaultIntHandler,                      // I2C1 Master and Slave
    DefaultIntHandler,                      // Quadrature Encoder 1
    DefaultIntHandler,                      // CAN0
    DefaultIntHandler,                      // CAN1
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultIntHandler,                      // Hibernate
    DefaultIntHandler,                      // USB0
    DefaultIntHandler,                      // PWM Generator 3
    DefaultIntHandler,                      // uDMA Software Transfer
    DefaultIntHandler,                      // uDMA Error
    DefaultIntHandler,                      // ADC1 Sequence 0
    DefaultIntHandler,                      // ADC1 Sequence 1
    DefaultIntHandler,                      // ADC1 Sequence 2
    DefaultIntHandler,                      // ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultIntHandler,                      // GPIO Port J
    DefaultIntHandler,                      // GPIO Port K
    DefaultIntHandler,                      // GPIO Port L
    DefaultIntHandler,                      // SSI2 Rx and Tx
    DefaultIntHandler,                      // SSI3 Rx and Tx
    DefaultIntHandler,                      // UART3 Rx and Tx
    DefaultIntHandler,                      // UART4 Rx and Tx
    DefaultIntHandler,                      // UART5 Rx and Tx
    DefaultIntHandler,                      // UART6 Rx and Tx
    DefaultIntHandler,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultIntHandler,                      // I2C2 Master and Slave
    DefaultIntHandler,                      // I2C3 Master and Slave
    DefaultIntHandler,                      // Timer 4 subtimer A
    DefaultIntHandler,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    DefaultIntHandler,                      // Timer 5 subtimer A
    DefaultIntHandler,                      // Timer 5 subtimer B
    DefaultIntHandler,                      // Wide Timer 0 subtimer A
    DefaultIntHandler,                      // Wide Timer 0 subtimer B
    DefaultIntHandler,                      // Wide Timer 1 subtimer A
    DefaultIntHandler,                      // Wide Timer 1 subtimer B
    DefaultIntHandler,                      // Wide Timer 2 subtimer A
    DefaultIntHandler,                      // Wide Timer 2 subtimer B
    DefaultIntHandler,                      // Wide Timer 3 subtimer A
    DefaultIntHandler,                      // Wide Timer 3 subtimer B
    DefaultIntHandler,                      // Wide Timer 4 subtimer A
    DefaultIntHandler,                      // Wide Timer 4 subtimer B
    DefaultIntHandler,                      // Wide Timer 5 subtimer A
    DefaultIntHandler,                      // Wide Timer 5 subtimer B
    DefaultIntHandler,                      // FPU
    DefaultIntHandler,                      // PECI 0
    DefaultIntHandler,                      // LPC 0
    DefaultIntHandler,                      // I2C4 Master and Slave
    DefaultIntHandler,                      // I2C5 Master and Slave
    DefaultIntHandler,                      // GPIO Port M
    DefaultIntHandler,                      // GPIO Port N
    DefaultIntHandler,                      // Quadrature Encoder 2
    DefaultIntHandler,                      // Fan 0
    0,                                      // Reserved
    DefaultIntHandler,                      // GPIO Port P (Summary or P0)
    DefaultIntHandler,                      // GPIO Port P1
    DefaultIntHandler,                      // GPIO Port P2
    DefaultIntHandler,                      // GPIO Port P3
    DefaultIntHandler,                      // GPIO Port P4
    DefaultIntHandler,                      // GPIO Port P5
    DefaultIntHandler,                      // GPIO Port P6
    DefaultIntHandler,                      // GPIO Port P7
    DefaultIntHandler,                      // GPIO Port Q (Summary or Q0)
    DefaultIntHandler,                      // GPIO Port Q1
    DefaultIntHandler,                      // GPIO Port Q2
    DefaultIntHandler,                      // GPIO Port Q3
    DefaultIntHandler,                      // GPIO Port Q4
    DefaultIntHandler,                      // GPIO Port Q5
    DefaultIntHandler,                      // GPIO Port Q6
    DefaultIntHandler,                      // GPIO Port Q7
    DefaultIntHandler,                      // GPIO Port R
    DefaultIntHandler,                      // GPIO Port S
    DefaultIntHandler,                      // PWM 1 Generator 0
    DefaultIntHandler,                      // PWM 1 Generator 1
    DefaultIntHandler,                      // PWM 1 Generator 2
    DefaultIntHandler,                      // PWM 1 Generator 3
    DefaultIntHandler                       // PWM 1 Fault
};

