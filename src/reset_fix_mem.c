/*
 * reset_fix_mem.c
 *
 *  Created on: 13.03.2023
 *      Author: manni4
 */

#include "reset_fix_mem.h"

#include "pico/platform.h"

unsigned int __uninitialized_ram(resetfix_counter);

char __uninitialized_ram( reset_buffer ) [1024];

// TODO: how to use macros
/*
int c;
int *counter = &c;
//static __uninitialized_ram(int counter) [1];
*/
