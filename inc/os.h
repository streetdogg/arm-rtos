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

#ifndef __OS_H__
#define __OS_H__

#include "os_config.h"
#include "mem_layout.h"

/*
 * This is a Prototype for the User threads.
 * The user thread to be spwaned as thread must be of the type 'void'
 * and take no arguments.
 */
typedef void (*function) ();

/*
 * Thread control block.
 * Includes a dedicated stack, stack_pointer and pointer to
 * the next thread in the schedule queue.
 * Each user thread gets it's own thread control block.
 */
typedef struct tcb__ {
    unsigned long int stack[TASK_STACK_SIZE];
    unsigned long int *sp;
    struct tcb__ *next;
} tcb_;

/*
 * Enables Interrupts and the CPU can attend to the interrupts.
 */
void enable_interrupts();

/*
 * Disables Interrupts and the CPU can not attend to the interrupts.
 */
void dissable_interrupts();

/*
 * Initializes the CPU.
 * Configures the System Clock and interrupts
 */
void system_init();

/*
 * The 'task' provided as argument will be converted into a thread and
 * put into the execution queue.
 */
void create_thread(function task);

#endif