#include <stdint.h>

/* Section address defined in linker script */
extern uint32_t __etext[];
extern uint32_t __data_start__[];
extern uint32_t __data_end__[];
extern uint32_t __bss_start__[];
extern uint32_t __bss_end__[];
extern uint32_t __stack[];

extern int main(void);
void Default_Reset_Handler(void);
static void Default_Handler(void);

//*****************************************************************************
// Declaration of the default fault handlers
//*****************************************************************************

/* System exception vector handler */
void Reset_Handler(void)        __attribute__((weak, alias("Default_Reset_Handler")));
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Hander(void)     __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));


//*****************************************************************************
// Symbols defined in linker script
//*****************************************************************************

// Start address for the initialization values of the .data section.


//*****************************************************************************
// Function prototypes
//*****************************************************************************


/**
 * @brief Initialize .data section.
 *
 */
static void do_copy_data() {
    uint32_t *s, *d;
    for (s = __etext, d = __data_start__; d < __data_end__; *d++ = *s++) {
        ;
    }
}

/**
 * @brief Initialize .bss section.
 *
 */
static void do_clear_bss() {
    uint32_t *d;
    for (d = __bss_start__; d < __bss_end__; *d++ = 0) {
        ;
    }
}

//*****************************************************************************
// The minimal vector table for a Cortex M0+.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//*****************************************************************************
static void *const vector[] __attribute__((section(".isr_vector"))) = {
    // 0x00 is stack pointer
    __stack, // 0x00

    // 0x04 ~ 0x3C is Exception vector
    Reset_Handler,      // 0x04
    NMI_Handler,        // 0x08
    HardFault_Hander,   // 0x0C
    MemManage_Handler,  // 0x10
    BusFault_Handler,   // 0x14
    UsageFault_Handler, // 0x18
    0,                  // 0x1C
    0,                  // 0x20
    0,                  // 0x24
    0,                  // 0x28
    SVC_Handler,        // 0x2C
    DebugMon_Handler,   // 0x30
    0,                  // 0x34
    PendSV_Handler,     // 0x38
    SysTick_Handler,    // 0x3C
};

//*****************************************************************************
//! \brief This is the code that gets called when the processor first
//! starts execution following a reset event.
//!
//! \param None.
//!
//! Only the absolutely necessary set is performed, after which the
//! application supplied main() routine is called.
//!
//! \return None.
//*****************************************************************************
void Default_Reset_Handler(void) {

    /* call the application's entry point */
    (*(volatile uint32_t *)0xE000ED08) = (uint32_t)vector;    // VTOR address
    do_copy_data();
    do_clear_bss();
    main();
}


//*****************************************************************************
//! \brief This is the code that gets called when the processor receives an
//! unexpected interrupt.
//*****************************************************************************
static void Default_Handler(void) {
	for(;;);
}