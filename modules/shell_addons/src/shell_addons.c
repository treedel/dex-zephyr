#include <shell_addons.h>


static int cmd_reboot(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Rebooting");
    
    mcu_reboot();

    return 0;
}

static int cmd_bootsel(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Rebooting to bootsel mode");
    
    mcu_reboot_to_bootsel();

    return 0;
}