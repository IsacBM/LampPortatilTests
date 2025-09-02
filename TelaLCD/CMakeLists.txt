# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(TelaLCD C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

# Arquivos do projeto
add_executable(TelaLCD
    TelaLCD.c
    st7789_lcd_pio.c
)

# Gera o header a partir do PIO
pico_generate_pio_header(TelaLCD ${CMAKE_CURRENT_LIST_DIR}/st7789_lcd.pio)

# Nome e versão do programa
pico_set_program_name(TelaLCD "TelaLCD")
pico_set_program_version(TelaLCD "0.1")

# Saída serial
pico_enable_stdio_uart(TelaLCD 1)
pico_enable_stdio_usb(TelaLCD 1)

# Bibliotecas necessárias
target_link_libraries(TelaLCD
    pico_stdlib
    hardware_pio
    hardware_clocks
    hardware_dma
)

# Includes
target_include_directories(TelaLCD PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Saídas extras (UF2, ELF etc.)
pico_add_extra_outputs(TelaLCD)