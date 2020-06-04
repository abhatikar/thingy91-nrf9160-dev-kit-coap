cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/../nrf/cmake/boilerplate.cmake)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(telenor_mic_coap)

target_sources(app PRIVATE src/main.c)
zephyr_include_directories(src)
