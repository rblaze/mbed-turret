cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET mbed-turret)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(${MBED_PATH})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mbed-VL53L1X)

add_executable(${APP_TARGET}
    main.cpp
    Audio.cpp
    AudioGen.c
    Ranging.cpp
    Servo.cpp
    Targeting.cpp
)

target_link_libraries(${APP_TARGET}
    mbed-os
    mbed-events
    mbed-storage-littlefs
    mbed-storage-spif
    vl53l1x-driver
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
