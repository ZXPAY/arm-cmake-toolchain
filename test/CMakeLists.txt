# Unit test file
FILE(GLOB TEST_SOURCE_FILE
    ${CMAKE_SOURCE_DIR}/test/*.c
)


foreach(file ${TEST_SOURCE_FILE})
    get_filename_component(barefile ${file} NAME_WE)
    message(STATUS testfile->${barefile})
    add_compile_options(${CFLAGS})
    add_executable(${barefile} ${file})
    target_link_options(${barefile} PRIVATE
        -T${LINKER_FILE}
        -g${DEBUG_FLAGS}
        ${CPU_FLAGS}
        -u __isr_vectors
        -fsingle-precision-constant
        -Wl,-Map=test/${barefile}.map
    )
    target_include_directories(${barefile} PUBLIC 
        ${ALGO_PATH}
        ${RTOS_INCLUDE}
    )
    
    target_link_libraries(${barefile}
        SRCS
        m
    )
    # Generate the hex and bin file
    add_custom_target(
        ${barefile}.hex ALL
        DEPENDS ${barefile}
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${barefile}.elf ${barefile}.hex)
    add_custom_target(
        ${barefile}.bin ALL
        DEPENDS ${barefile}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${barefile}.elf ${barefile}.bin)
    add_custom_target(
        ${barefile}.lst ALL
        DEPENDS ${barefile}
        COMMAND ${CMAKE_OBJDUMP} -h -S -C ${barefile}.elf > ${barefile}.lst)
    add_custom_command(
        TARGET ${barefile}.lst
        COMMAND ${CMAKE_SIZE} -A ${barefile}.hex)
    add_custom_command(
        TARGET ${barefile}.lst
        COMMAND ${CMAKE_SIZE} -A ${barefile}.elf)
endforeach()
