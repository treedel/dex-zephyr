cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

zephyr_library_sources(
    src/wifi.c
)

zephyr_library_include_directories(
    include
)