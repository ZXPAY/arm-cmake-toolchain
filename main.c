#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "SEGGER_RTT.h"
#include "add.h"
#include "fpu.h"

extern uint32_t __etext[];
extern uint32_t __data_start__[];
extern uint32_t __data_end__[];
extern uint32_t __bss_start__[];
extern uint32_t __bss_end__[];
extern uint32_t __stack[];

int a = 100;

int main(void) {
    enable_fpu();

    SEGGER_RTT_printf(0, "__etext:         0x%p\n", __etext);
    SEGGER_RTT_printf(0, "__data_start__:  0x%p\n", __data_start__);
    SEGGER_RTT_printf(0, "__data_end__:    0x%p\n", __data_end__);
    SEGGER_RTT_printf(0, "__bss_start__:   0x%p\n", __bss_start__);
    SEGGER_RTT_printf(0, "__bss_end__:     0x%p\n", __bss_end__);
    SEGGER_RTT_printf(0, "__stack:         0x%p\n", __stack);
    
    SEGGER_RTT_printf(0, "Start main\n");
    SEGGER_RTT_printf(0, "a      :         0x%p\n", &a);
    
    char temp_str[50];
    memset(temp_str, 0, sizeof(temp_str));
    sprintf(temp_str, "Float value is %f\n", 3.144444);
    
    int i=0;
    while(temp_str[i] != '\0') {
        SEGGER_RTT_printf(0, "%c", temp_str[i]);
        i++;
    }
    
    SEGGER_RTT_printf(0, "Start \n");

    while(true) {
        __asm("nop");
    }

    return 0;
}

