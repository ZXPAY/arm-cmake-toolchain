cmake_minimum_required(VERSION 3.16)

project(hello_world)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(STARTUP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32f767zi/startup.c")
set(LINKER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32f767zi/gcc.ld")
set(LINKER_MAP_FLAGS "-Wl,-Map=${PROJECT_NAME}.map")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CPU_FLAGS -mthumb -mthumb-interwork -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv4-sp-d16)
set(DEBUG_FLAGS dwarf-2)
set(OPTIMIZATION_FLAGS O0)
set(CFLAGS
    ${CPU_FLAGS}
    -Wall
    -ffunction-sections
    -fdata-sections -fsigned-char
    -fmessage-length=0
    -fshort-enums
    -u __isr_vectors
    -fno-builtin -Wp,-MM,-MP,-MT,
    -fno-math-errno
    -fsingle-precision-constant
    -g${DEBUG_FLAGS}
    -${OPTIMIZATION_FLAGS}
    -fdiagnostics-color=always   # high light the warning or error
    )
set(LDFLAGS
    -T${LINKER_FILE}
    ${LINKER_MAP_FLAGS}
    -g${DEBUG_FLAGS}
    ${CPU_FLAGS}
    -lm
    -u __isr_vectors
    -fsingle-precision-constant
)

add_compile_options(${CFLAGS})
add_link_options(${LDFLAGS})

# Assembly file
FILE(GLOB ASMSRC src/*.s)
# C file
FILE(GLOB CSRC src/*.c segger_rtt/*.c)
# C++ file
FILE(GLOB CXXSRC src/*.cpp)

message(STATUS ${ASMSRC})
message(STATUS ${CSRC})
message(STATUS ${CXXSRC})
message(STATUS ${STARTUP_FILE})
message(STATUS ${LINKER_FILE})
message(STATUS ${CMAKE_OBJCOPY})

set_property(SOURCE ${ASMSRC} PROPERTY LANGUAGE C)
add_executable(${PROJECT_NAME} ${STARTUP_FILE} main.c ${CSRC} ${CXXSRC} ${ASMSRC})

# Generate the hex and bin file
add_custom_target(
    ${PROJECT_NAME}.hex ALL
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
add_custom_target(
    ${PROJECT_NAME}.bin ALL
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
add_custom_target(
    ${PROJECT_NAME}.lst ALL
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJDUMP} -h -S -C ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst)
add_custom_command(
    TARGET ${PROJECT_NAME}.lst
    COMMAND ${CMAKE_SIZE} -A ${PROJECT_NAME}.hex)
add_custom_command(
    TARGET ${PROJECT_NAME}.lst
    COMMAND ${CMAKE_SIZE} -A ${PROJECT_NAME}.elf)

# Include reference
target_include_directories(${PROJECT_NAME} PUBLIC 
    inc
    segger_rtt
    platform/stm32f767zi
    )



