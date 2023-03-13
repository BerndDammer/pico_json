

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#include <time.h>
#include <stdlib.h>

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
    menu();

    doTheTest();

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
            case 'm':
                dump_memory();
                break;
            case ' ':
            case '0':
                doTheTest();
                //printf("free Memory %d\n" );
                break;
            default:
                menu();
                break;
            }
        }
    }
}

