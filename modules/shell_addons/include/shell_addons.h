#ifndef SHELL_ADDONS_H
#define SHELL_ADDONS_H

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

#include <mcu_control.h>


static int cmd_reboot(const struct shell *sh, size_t argc, char **argv);
static int cmd_bootsel(const struct shell *sh, size_t argc, char **argv);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_system,
    SHELL_CMD(reboot, NULL, "Normal reboot", cmd_reboot),
    SHELL_CMD(bootsel, NULL, "Reboot to BOOTSEL mode", cmd_bootsel),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(system, &sub_system, "System commands", NULL);

#endif