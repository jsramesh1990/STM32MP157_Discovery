/*
 * STM32MP157_M4.ld
 *
 * Linker script for STM32MP157 Cortex-M4 firmware.
 *
 * Project:
 *   Energy-Aware Industrial Sensor Node
 *
 * Target:
 *   STM32MP157 Cortex-M4
 *
 * NOTE:
 * The exact SRAM addresses/sizes must match the memory configuration
 * selected in your STM32MP157 device/BSP configuration.
 */

ENTRY(Reset_Handler)

/*
 * --------------------------------------------------------------------------
 * Stack / Heap configuration
 * --------------------------------------------------------------------------
 */

_Min_Heap_Size  = 0x00001000;     /* 4 KB  */
_Min_Stack_Size = 0x00002000;     /* 8 KB  */

/*
 * --------------------------------------------------------------------------
 * Memory Configuration
 * --------------------------------------------------------------------------
 *
 * STM32MP157 Cortex-M4 firmware normally executes from the MCU SRAM
 * assigned to the Cortex-M4.
 *
 * Verify these regions against the actual STM32MP157 memory configuration
 * used by your OpenAMP/remoteproc/device-tree setup.
 */

MEMORY
{
    /*
     * Cortex-M4 firmware code/data.
     */
    RAM (xrw) : ORIGIN = 0x10000000, LENGTH = 256K
}

/*
 * --------------------------------------------------------------------------
 * Sections
 * --------------------------------------------------------------------------
 */

SECTIONS
{
    /*
     * ----------------------------------------------------------------------
     * Interrupt Vector Table + Program Code
     * ----------------------------------------------------------------------
     */

    .isr_vector :
    {
        . = ALIGN(4);

        KEEP(*(.isr_vector))

        . = ALIGN(4);
    } > RAM

    .text :
    {
        . = ALIGN(4);

        *(.text)
        *(.text*)

        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);

        _etext = .;
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * Read-only data
     * ----------------------------------------------------------------------
     */

    .rodata :
    {
        . = ALIGN(4);

        *(.rodata)
        *(.rodata*)

        . = ALIGN(4);
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * ARM exception tables
     * ----------------------------------------------------------------------
     */

    .ARM :
    {
        . = ALIGN(4);

        __exidx_start = .;

        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)

        __exidx_end = .;

        . = ALIGN(4);
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * Initialization data
     * ----------------------------------------------------------------------
     */

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);

        _sdata = .;

        *(.data)
        *(.data*)

        . = ALIGN(4);

        _edata = .;
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * Uninitialized data
     * ----------------------------------------------------------------------
 */

    .bss :
    {
        . = ALIGN(4);

        _sbss = .;

        __bss_start__ = _sbss;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);

        _ebss = .;

        __bss_end__ = _ebss;
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * Heap
     * ----------------------------------------------------------------------
     */

    ._user_heap_stack :
    {
        . = ALIGN(8);

        PROVIDE(end = .);
        PROVIDE(_end = .);

        . = . + _Min_Heap_Size;

        . = . + _Min_Stack_Size;

        . = ALIGN(8);
    } > RAM

    /*
     * ----------------------------------------------------------------------
     * Remove unused standard-library sections
     * ----------------------------------------------------------------------
     */

    /DISCARD/ :
    {
        libc.a(*)
        libm.a(*)
        libgcc.a(*)
    }

    /*
     * ----------------------------------------------------------------------
     * ARM attributes
     * ----------------------------------------------------------------------
     */

    .ARM.attributes 0 :
    {
        *(.ARM.attributes)
    }
}
