# INTERRUPTS

## What are Interrupts?

Interrupts are hardware signals that pause the CPU's current execution to handle urgent events (like button press, timer expiry, data received).

## How Interrupts Work

Normal Execution Interrupt Occurs
─────────────────────────────────────────────────────────────

main() running ──┐
│
│ Hardware Signal
│ ↓
│ ┌─────────────────┐
│ │ Save CPU state │
│ │ Jump to ISR │
│ │ Execute ISR │
│ │ Restore state │
│ └─────────────────┘
│ ↓
main() continues ←┘
text


## Interrupt Flow Diagram

┌─────────────────────────────────────────────────────────────────┐
│ INTERRUPT FLOW │
├─────────────────────────────────────────────────────────────────┤
│ │
│ 1. HARDWARE EVENT │
│ ┌─────────┐ │
│ │ Button │──┐ │
│ │ Press │ │ │
│ └─────────┘ │ │
│ ↓ │
│ 2. INTERRUPT CONTROLLER (NVIC) │
│ ┌─────────────────────────┐ │
│ │ Check priority │ │
│ │ Set pending flag │ │
│ │ Signal CPU │ │
│ └─────────────────────────┘ │
│ ↓ │
│ 3. CPU RESPONDS │
│ ┌─────────────────────────┐ │
│ │ Save current registers │ │
│ │ Save program counter │ │
│ │ Disable interrupts │ │
│ │ Jump to Vector Table │ │
│ └─────────────────────────┘ │
│ ↓ │
│ 4. ISR EXECUTES │
│ ┌─────────────────────────┐ │
│ │ Clear interrupt flag │ │
│ │ Handle the event │ │
│ │ (keep it SHORT!) │ │
│ └─────────────────────────┘ │
│ ↓ │
│ 5. RETURN │
│ ┌─────────────────────────┐ │
│ │ Restore registers │ │
│ │ Resume main program │ │
│ └─────────────────────────┘ │
│ │
└─────────────────────────────────────────────────────────────────┘
text


## Vector Table

The vector table is an array of function pointers at a fixed memory address (usually 0x00000000).

Memory Address: Content:
┌─────────────────┐
│ 0x00000000 │ Initial Stack Pointer
├─────────────────┤
│ 0x00000004 │ Reset Handler ← Startup
├─────────────────┤
│ 0x00000008 │ NMI Handler
├─────────────────┤
│ 0x0000000C │ Hard Fault Handler
├─────────────────┤
│ 0x00000010 │ Mem Manage Handler
├─────────────────┤
│ ... │ ...
├─────────────────┤
│ 0x00000040 │ TIM2 Handler (IRQ #28)
├─────────────────┤
│ 0x00000044 │ TIM3 Handler
├─────────────────┤
│ ... │ ...
└─────────────────┘
text


## ISR (Interrupt Service Routine)

```c
// ISR naming depends on MCU vendor
// STM32: function name matches vector table

void TIM2_IRQHandler(void) {
    // Check if interrupt was from TIM2
    if(TIM2->SR & TIM_SR_UIF) {
        // Clear interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;
        
        // Handle interrupt (keep SHORT!)
        // Toggle LED, set flag, etc.
        GPIOA->ODR ^= (1 << 5);
    }
}

Interrupt Priority
text

Nested Interrupts:

High Priority ──────────────────────────────────►
(0 = highest)

Priority 0: ┌──┐
            │ISR│──────────────────┐
Priority 1:    └────┐         ┌────┘
                    │ISR│──────┘
Priority 2:         └────┐
                        │ISR│
                         └──┘

Higher priority preempts lower priority

Syntax
Operation	Code
Enable IRQ	NVIC_EnableIRQ(TIM2_IRQn)
Disable IRQ	NVIC_DisableIRQ(TIM2_IRQn)
Set Priority	NVIC_SetPriority(TIM2_IRQn, 2)
Global Enable	__enable_irq()
Global Disable	__disable_irq()
ISR Best Practices
DO ✓	DON'T ✗
Keep ISR short	Call printf() in ISR
Set volatile flags	Use malloc()/free()
Clear interrupt flag	Block/sleep
Use atomic operations	Complex calculations
Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 03-embedded-baremetal/interrupts/interrupts.c -o interrupts
./interrupts

Key Takeaways

    Interrupts pause main program – handle urgent events

    Vector table holds ISR addresses – fixed location

    ISRs must be short – only set flags, no heavy work

    Use volatile for shared variables – between ISR and main

    Priorities determine which interrupts preempt which
