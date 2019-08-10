 /*
 * Copyright (c) 2019, Piyush Itankar <pitankar@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
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