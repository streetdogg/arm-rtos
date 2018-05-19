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

unsigned long int total_tasks = 0;
tcb_ thread_pool[THREAD_POOL_SIZE];
tcb_ *execution_queue;

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
void set_pensv_priority_to_low() {

    //  Set the Priority of the PendSV interrupt to minimum
    *(unsigned long int volatile *) 0xE000ED20 |= (0xFFU << 16);
}

/*
 * Set the PendSV interrupt
 */
void set_pendsv() {
    // Set the 28th Bit to trigger PendSV interrupt
    *(unsigned long int volatile *)0xE000ED04 = (1U << 28);
}

void setup_systick() {
    *(unsigned long int volatile *)0xE000E010 = 0U;
    *(unsigned long int volatile *)0xE000E014 = 15999U;
    *(unsigned long int volatile *)0xE000E018 = 0U;
    *(unsigned long int volatile *)0xE000ED20 = ((*(unsigned long int volatile *)0xE000ED20) & 0x00FFFFFF) | 0x40000000;

    *(unsigned long int volatile *)0xE000E010 |= 0x07U;
}


void pendsv_handler() {
    // TODO
}

/*
 * Initializes the System Correctly
 */
void system_init() {
    __asm("CPSID I");
    // TODO: set_pensv_priority_to_low();
    setup_systick();
    __asm("CPSIE I");
}

void add_to_execution_queue(tcb_ *tcb) {
    tcb->next = execution_queue;
    execution_queue = tcb;
}

void create_thread(function task) {
    unsigned long int *sp;
    tcb_ *tcb = &thread_pool[total_tasks];  // Get the Next free TCB

    sp   = (unsigned long int *)((unsigned long int*)&(tcb->stack[TASK_STACK_SIZE]));

    *(--sp) = (1U << 24);  // Set thumb bit of XPSR
    *(--sp) = (unsigned long int)task;  // PC points to the task

    for (int i=0; i <= 13; i++)
        *(--sp) = 0xDEADBEEFU;

    // Get the stack pointer for current task
    tcb->sp = sp;

    add_to_execution_queue(tcb);
}