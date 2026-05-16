#ifndef MCU_CONTROL_H
#define MCU_CONTROL_H

#include "pico/bootrom.h"
#include <zephyr/sys/reboot.h>


void mcu_reboot();
void mcu_reboot_to_bootsel();

#endif