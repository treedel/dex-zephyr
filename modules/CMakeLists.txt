cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Add all library paths here
add_subdirectory(wifi)
add_subdirectory(tcp)
add_subdirectory(shell_addons)
add_subdirectory(dex)