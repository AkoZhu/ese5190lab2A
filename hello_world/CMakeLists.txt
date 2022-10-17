cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
# include()
project(pio_example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(HELLO_PIO ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

if (TARGET tinyusb_device)
    add_executable(
            ws2812usb
                  
            )
    
    target_sources(ws2812usb PRIVATE ws2812usb.c ws2812.h ws2812.c )

    target_link_libraries(ws2812usb PRIVATE pico_stdlib hardware_pio)

    # pull in common dependencies
    # target_link_libraries(PRIVATE pico_stdlib hardware_pio hardware_dma)
        # enable usb output, disable uart output
    pico_enable_stdio_usb(ws2812usb 1)
    pico_enable_stdio_uart(ws2812usb 0)


    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(ws2812usb)

    # add url via pico_set_program_url
    example_auto_set_url(ws2812usb)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
