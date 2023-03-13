/*
 * StartupCheck.c
 *
 *  Created on: 13.03.2023
 *      Author: manni4
 */
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/unique_id.h"
//#include "pico/platform.h"
#include "hardware/exception.h"
#include "hardware/watchdog.h"

#include"StartupCheck.h"

#include "reset_fix_mem.h"



void dumpBoardID(void)
{

    pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

    printf("Unique identifier:");
    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++i)
    {
        printf(" %02x", board_id.id[i]);
    }
    printf("\n");
}


static void goodby(void)
{
    watchdog_reboot(0, 0, 2000);
}


exception_handler_t oldNmiException;
exception_handler_t oldHardfaultException;
exception_handler_t oldSvcallException;
exception_handler_t oldPendsvException;
exception_handler_t oldSystickException;

// TODO: getting crash parameter
static void myNmiException(void)
{
    sprintf( reset_buffer, "NMI\n");
    goodby();
}
static void myHardfaultException(void)
{
    sprintf( reset_buffer, "Hardfault\n");
    goodby();
}
static void mySvcallException(void)
{
    sprintf( reset_buffer, "Svcall\n");
    goodby();
}
static void myPendsvException(void)
{
    sprintf( reset_buffer, "Pendsv\n");
    goodby();
}
// TODO: really patch this
static void mySystickException(void)
{
    sprintf( reset_buffer, "Systick\n");
    goodby();
}

void set_exceptions(void)
{
    oldNmiException = exception_set_exclusive_handler(NMI_EXCEPTION, myNmiException);
    oldHardfaultException = exception_set_exclusive_handler(HARDFAULT_EXCEPTION, myHardfaultException);
    oldSvcallException = exception_set_exclusive_handler(SVCALL_EXCEPTION, mySvcallException);
    oldPendsvException = exception_set_exclusive_handler(PENDSV_EXCEPTION, myPendsvException);
    // TODO: really do this
    oldSystickException = exception_set_exclusive_handler(SYSTICK_EXCEPTION, mySystickException);
}
void checkWatchdog(void)
{
    printf("watchdog_caused_reboot : %i\n", watchdog_caused_reboot());
    printf("watchdog_enable_caused_reboot : %i\n",
            watchdog_enable_caused_reboot());

}

void startup_check(void)
{
    resetfix_counter++;
    printf("----------------StartupCheck %i\n", resetfix_counter);

    sprintf( reset_buffer, "ResetFixCounter : %i\n", resetfix_counter);

    dumpBoardID();
    printf(" rp2040_chip_version : %i\n", rp2040_chip_version());
    printf(" rp2040_rom_version : %i\n", rp2040_rom_version());
    printf(" __get_current_exception : %i\n", __get_current_exception());
    checkWatchdog();
    set_exceptions();
}

