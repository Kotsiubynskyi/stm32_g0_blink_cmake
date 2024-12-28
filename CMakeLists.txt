cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "STM32G0_toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(blink LANGUAGES C CXX ASM)

# Source files
add_executable(${PROJECT_NAME}
  src/main.cpp
  stm32_g0_hal/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal.c
  stm32_g0_hal/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_gpio.c
  stm32_g0_hal/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_cortex.c
  stm32_g0_hal/Drivers/CMSIS/Device/ST/STM32G0xx/Source/Templates/system_stm32g0xx.c
  stm32_g0_hal/Drivers/CMSIS/Device/ST/STM32G0xx/Source/Templates/gcc/startup_stm32g030xx.s
)

# Directories with headers
target_include_directories(${PROJECT_NAME} PRIVATE
  include
  stm32_g0_hal/Drivers/CMSIS/Include
  stm32_g0_hal/Drivers/STM32G0xx_HAL_Driver/Inc
  stm32_g0_hal/Drivers/CMSIS/Device/ST/STM32G0xx/Include
)

# Define compile options
target_compile_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m0
  -mthumb
  -Os
  -ffunction-sections # Place functions in separate sections
  -fdata-sections # Place data in separate sections
  -fno-exceptions # Disable exceptions for bare-metal code
)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m0
  -mthumb
  -Wl,--start-group
  -Wl,--end-group
  -static
)

# Define defines here
target_compile_definitions(${PROJECT_NAME} PRIVATE
  STM32G030xx # Define your G0 series MCU
)

# Convert .elf firmware to .bin after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)

# Print firmware Flash and RAM usage
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}
)

