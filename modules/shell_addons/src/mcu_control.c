#include <mcu_control.h>


void mcu_reboot() {
    sys_reboot(SYS_REBOOT_COLD);
}

void mcu_reboot_to_bootsel() {
    reset_usb_boot(0, 0);
}