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

#include "os.h"

tcb_ thread_pool[THREAD_POOL_SIZE];
tcb_ *execution_queue;
tcb_ *current_thread;
tcb_ *next_thread;

volatile unsigned long int total_tasks;
unsigned long int current_sp;
unsigned long int next_sp;
unsigned long int *sp;

#define MAIN_STACK_SIZE 256
#define NULL            ((void *) 0x00)

extern int  main();
extern void ResetIntHandler();
extern void pendsv_handler();
extern void systick_handler();
extern void DefaultIntHandler();


/*
 * Cortex M4 Vector Table.
 * The table lays out all the Interrupt handlers, Main processor
 * stack pointer and the associated stack.
 *
 * NOTE: change value of MAIN_STACK_SIZE to change the main stack size
 */
static unsigned long int stack[MAIN_STACK_SIZE];
__attribute__ ((section(".isr_vector"))) void (*const vectors[])() =
{
    (void (*)())((unsigned long int)stack + sizeof(stack)),
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
    pendsv_handler,                         // The PendSV handler
    systick_handler,                        // The SysTick handler
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

/*
 * Enables all interrupts
 */
void enable_interrupts() {
    // Enables all interrupts
    __asm("CPSIE I");
}

/*
 * Disables all interrupts
 */
void dissable_interrupts() {
    // Disables all interrupts
    __asm("CPSID I");
}

/*
 * Sets the priority of PenSV interrupt to the lowest
 * This is because the PendSV interrupt handler is used for job scheduling
 */
static void set_pensv_priority_to_low() {

    //  Set the Priority of the PendSV interrupt to minimum
    *(unsigned long int volatile *) 0xE000ED20 |= (0xFFU << 16);
}

/*
 * Set the PendSV interrupt
 */
static void set_pendsv() {
    // Set the 28th Bit to trigger PendSV interrupt
    *(unsigned long int volatile *)0xE000ED04 = (1U << 28);
}

/*
 * Configures the SysTick timer for periodic interrupts.
 */
void setup_systick_timer() {
    *(unsigned long int volatile *)0xE000E010 = 0U;
    *(unsigned long int volatile *)0xE000E014 = 15999U;
    *(unsigned long int volatile *)0xE000E018 = 0U;
    *(unsigned long int volatile *)0xE000ED20 = ((*(unsigned long int volatile *)0xE000ED20) & 0x00FFFFFF) | 0x40000000;

    *(unsigned long int volatile *)0xE000E010 |= 0x07U;
}

/*
 *
 */
void ResetIntHandler(){
    extern unsigned long int _etext, _data, _edata, _bss, _ebss;
    unsigned long int *src = &_etext, *dst = &_data;
    while(dst < &_edata) *(dst++) = *(src++);
    for(dst = &_bss; dst < &_ebss; dst++) *dst = 0;

    main();

    while(1);
}

void DefaultIntHandler(){
    while(1);
}

void pendsv_handler() {
    __asm("CPSID I");
	__asm("PUSH  {r4-r11}");


    if (current_thread == NULL) {
        current_thread = execution_queue;
		current_sp = (unsigned long int)(current_thread->sp);
        __asm("LDR R10, =current_sp");
        __asm("LDR SP,[R10,#0x00]");
		__asm("POP {R4-R11}");
        __asm("CPSIE I");
		return;
    }

    if (current_thread->next == NULL) {
        next_thread = execution_queue;
    } else {
        next_thread = current_thread->next;
		}

		current_sp = (unsigned long int)&current_thread->sp;
    __asm("LDR r10, =current_sp");
	__asm("LDR r11, [r10]");
    __asm("STR sp,[r11,#0x00]");

		next_sp = (unsigned long int)(next_thread->sp);
    __asm("LDR r10, =next_sp");
    __asm("LDR sp,[r10,#0x00]");
		current_thread = next_thread;

    __asm("POP {r4-r11}");
    __asm("CPSIE I");
}

void systick_handler() {
	set_pendsv();
}

/*
 * Initializes the System Correctly
 */
void system_init() {
    dissable_interrupts();
    set_pensv_priority_to_low();
    setup_systick_timer();
		total_tasks = 0;
    enable_interrupts();
}

void add_to_execution_queue(tcb_ *tcb) {
    tcb->next = execution_queue;
    execution_queue = tcb;
}

void create_thread(function task) {
		dissable_interrupts();

    unsigned long int *sp;
    tcb_ *tcb = &thread_pool[total_tasks];  // Get the Next free TCB

    sp   = (unsigned long int *)((unsigned long int*)&(tcb->stack[TASK_STACK_SIZE]));

	*(--sp) = (1U << 24);  // Set thumb bit of XPSR
    *(--sp) = (unsigned long int)task;  // PC points to the task

    for (int i=0; i <= 13; i++)
        *(--sp) = i;

		*sp =0xDEADBEEF;

    // Get the stack pointer for current task
    tcb->sp = sp;

    add_to_execution_queue(tcb);
		total_tasks ++;

	enable_interrupts();
}