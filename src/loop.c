//#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/watchdog.h"

#include "reset_fix_mem.h"



#include "loop.h"
#include "jsontest.h"
#include "memtool.h"

#include "pico/malloc.h"

#define CONSOLE_TIMEOUT 1000000


void menu(void)
{
    printf("------------------------------------\n");
    printf("press key to restart\n");
    printf("m memtool dump\n");
    printf("f show fix mem\n");
    printf("p cpp test\n");
    printf("w watchdog reboot after 3 sec\n");
    printf("space show menu\n");
    printf("------------------------------------\n");
}

void doTheTest(void)
{
    test();
}

void loop(void)
{
    int counter = 0;
    int c;

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);

        if (c == PICO_ERROR_TIMEOUT)
        {
            counter++;
        }
        else
        {
            switch (c)
            {
            case 'f':
                printf("resetfix_counter %i\n", resetfix_counter);
                puts("********************************************************\n");
                puts(reset_buffer);
                puts("********************************************************\n");
                break;
            case 'm':
                dump_memory();
                break;
            case 'w':
                puts(" ... 3 2 1 ... baem ....");
                watchdog_reboot( 0, 0, 3000); // don't like pointer NULL
                break;
            case 'p':
                doTheTest();
                break;
            case ' ':
            case '0':
            default:
                menu();
                break;
            }
        }
    }
}
//////////////////////////////
/// TODO: how to provocate non init ISR ... where does it go
