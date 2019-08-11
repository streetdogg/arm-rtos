 /****************************************************************************
* MInimal Real-time Operating System (MIROS)
* version 0.25 (matching lesson 25)
*
* This software is a teaching aid to illustrate the concepts underlying
* a Real-Time Operating System (RTOS). The main goal of the software is
* simplicity and clear presentation of the concepts, but without dealing
* with various corner cases, portability, or error handling. For these
* reasons, the software is generally NOT intended or recommended for use
* in commercial applications.
*
* Copyright (C) 2018 Miro Samek. All Rights Reserved.
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
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
* Contact Information:
* https://www.state-machine.com
****************************************************************************/
 
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
#include "os.h"

void thread1 () {
	while (1){
		for (int i=0; i<1000000; i++);
			GPIO_PORT_F->DATA[pin_1] = pin_1;

		for (int i=0; i<1000000; i++);
			GPIO_PORT_F->DATA[pin_1] = ~pin_1;
	}
}

void thread2 () {
	while (1) {
		for (int i=0; i<10000000; i++);
			GPIO_PORT_F->DATA[pin_2] = pin_2;

		for (int i=0; i<10000000; i++);
			GPIO_PORT_F->DATA[pin_2] = ~pin_2;
	}
}

void thread3 () {
	while (1) {
		for (int i=0; i<10000; i++);
			GPIO_PORT_F->DATA[pin_3] = pin_3;

		for (int i=0; i<10000; i++);
			GPIO_PORT_F->DATA[pin_3] = ~pin_3;
	}
}

void setup_leds() {
	SYS_CTRL->RCGC2       |= clk_port_F;
	GPIO_PORT_F->GPIODIR   = pin_3|pin_2|pin_1;
	GPIO_PORT_F->GPIODEN   = pin_3|pin_2|pin_1;
}

int main( void ){
	setup_leds();
	system_init();

	create_thread(thread1);
	create_thread(thread2);
	create_thread(thread3);

	while(1)
		__asm("WFI");
}