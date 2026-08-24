#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

// ============================================================
// SIMULATED HARDWARE REGISTERS
// ============================================================

typedef struct {
    volatile uint32_t SR;    // Status Register
    volatile uint32_t CR;    // Control Register
    volatile uint32_t CNT;   // Counter value
} TIM_TypeDef;

typedef struct {
    volatile uint32_t MODER;  // Mode Register
    volatile uint32_t ODR;    // Output Data Register
    volatile uint32_t IDR;    // Input Data Register
} GPIO_TypeDef;

// Simulated peripheral addresses
volatile TIM_TypeDef* TIM2 = (volatile TIM_TypeDef*)0x40000000;
volatile GPIO_TypeDef* GPIOA = (volatile GPIO_TypeDef*)0x40020000;

// ============================================================
// GLOBAL VARIABLES (shared between main and ISR)
// ============================================================

volatile bool timer_interrupt_flag = false;
volatile int interrupt_count = 0;

// ============================================================
// SIMULATED INTERRUPT HANDLER (using POSIX signal)
// ============================================================

void timer_isr(int signum) {
    // Clear interrupt flag
    TIM2->SR &= ~0x0001;  // Clear UIF (Update Interrupt Flag)
    
    // Set flag for main loop
    timer_interrupt_flag = true;
    interrupt_count++;
    
    // Simulate GPIO toggle
    GPIOA->ODR ^= (1 << 5);  // Toggle LED on PA5
    
    printf("\n  [ISR] Interrupt triggered! Count: %d\n", interrupt_count);
    printf("  [ISR] Toggled LED (ODR = 0x%08X)\n", GPIOA->ODR);
}

// ============================================================
// HELPER FUNCTIONS
// ============================================================

void delay_ms(int ms) {
    usleep(ms * 1000);
}

void setup_timer_interrupt(void) {
    // Setup POSIX timer (simulates hardware timer interrupt)
    struct sigaction sa;
    sa.sa_handler = timer_isr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);
    
    // Start timer (1 second interval)
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("  Timer interrupt configured (1 second interval)\n");
}

// ============================================================
// SIMULATED HARDWARE INITIALIZATION
// ============================================================

void hardware_init(void) {
    printf("\n--- HARDWARE INITIALIZATION ---\n");
    
    // Initialize GPIO
    GPIOA->MODER = 0x00000000;  // All inputs initially
    GPIOA->MODER |= (1 << (5*2));  // PA5 as output (01 in bits 10-11)
    GPIOA->ODR = 0x00000000;  // All low
    printf("  GPIOA initialized: PA5 as output\n");
    
    // Initialize Timer
    TIM2->CR = 0x00000001;  // Enable timer
    TIM2->SR = 0x00000000;  // Clear status
    TIM2->CNT = 0;
    printf("  TIM2 initialized: enabled\n");
    
    printf("  Hardware ready!\n");
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("        INTERRUPTS DEMO                 \n");
    printf("========================================\n\n");
    
    // ============================================================
    // 1. VECTOR TABLE DEMONSTRATION
    // ============================================================
    
    printf("--- VECTOR TABLE ---\n\n");
    
    // Simulating vector table as array of function pointers
    typedef void (*vector_entry_t)(void);
    
    vector_entry_t vector_table[] = {
        (vector_entry_t)0x20001000,  // Initial Stack Pointer
        (vector_entry_t)0x08000101,  // Reset Handler
        (vector_entry_t)0x08000102,  // NMI Handler
        (vector_entry_t)0x08000103,  // Hard Fault Handler
    };
    
    printf("Vector Table at address: %p\n", vector_table);
    printf("  Entry 0 (SP)    : %p\n", vector_table[0]);
    printf("  Entry 1 (Reset) : %p\n", vector_table[1]);
    printf("  Entry 2 (NMI)   : %p\n", vector_table[2]);
    printf("  Entry 3 (HardFault): %p\n", vector_table[3]);
    
    // ============================================================
    // 2. INTERRUPT PRIORITY
    // ============================================================
    
    printf("\n--- INTERRUPT PRIORITY ---\n\n");
    
    printf("Interrupt priorities (lower number = higher priority):\n");
    printf("  Priority 0: Highest (can preempt all)\n");
    printf("  Priority 1: High\n");
    printf("  Priority 2: Medium\n");
    printf("  Priority 3: Low\n");
    printf("  Priority 15: Lowest\n\n");
    
    printf("Nested Interrupt Example:\n");
    printf("  ISR priority 0 can preempt ISR priority 1\n");
    printf("  ISR priority 1 CANNOT preempt ISR priority 0\n");
    
    // ============================================================
    // 3. INITIALIZE HARDWARE
    // ============================================================
    
    hardware_init();
    
    // ============================================================
    // 4. ENABLE INTERRUPTS
    // ============================================================
    
    printf("\n--- ENABLING INTERRUPTS ---\n\n");
    
    // Enable interrupts (simulated)
    setup_timer_interrupt();
    printf("  Global interrupts enabled (__enable_irq())\n");
    printf("  TIM2 interrupt enabled (NVIC_EnableIRQ(TIM2_IRQn))\n");
    
    // ============================================================
    // 5. MAIN LOOP (interrupt-driven)
    // ============================================================
    
    printf("\n--- MAIN LOOP (Press Ctrl+C to exit) ---\n\n");
    
    int loop_count = 0;
    bool led_state = false;
    
    while(loop_count < 10) {  // Run for 10 seconds
        // Check if interrupt occurred
        if(timer_interrupt_flag) {
            timer_interrupt_flag = false;  // Clear flag
            
            printf("  [MAIN] Processing interrupt %d\n", interrupt_count);
            
            // Do non-critical work here (not in ISR)
            led_state = !led_state;
            printf("  [MAIN] LED state changed: %s\n", 
                   led_state ? "ON" : "OFF");
        }
        
        // Main program doing other work
        if(loop_count % 2 == 0) {
            printf("  [MAIN] Main program running... (loop %d)\n", loop_count);
        }
        
        loop_count++;
        delay_ms(1000);
    }
    
    // ============================================================
    // 6. DISABLE INTERRUPTS
    // ============================================================
    
    printf("\n--- DISABLING INTERRUPTS ---\n\n");
    
    // Disable timer
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("  Timer stopped\n");
    printf("  Timer interrupt disabled (NVIC_DisableIRQ())\n");
    printf("  Global interrupts: still enabled\n");
    
    // ============================================================
    // 7. INTERRUPT LATENCY
    // ============================================================
    
    printf("\n--- INTERRUPT LATENCY ---\n\n");
    
    printf("Interrupt latency factors:\n");
    printf("  1. CPU saves registers (12 cycles on ARM Cortex-M)\n");
    printf("  2. Vector table fetch (1-2 cycles)\n");
    printf("  3. ISR entry overhead (10-20 cycles)\n");
    printf("  4. Higher priority ISRs (can delay lower priority)\n");
    printf("  Typical latency: 30-50 CPU cycles\n");
    
    // ============================================================
    // 8. NESTED INTERRUPTS DEMO
    // ============================================================
    
    printf("\n--- NESTED INTERRUPTS ---\n\n");
    
    printf("When high priority interrupt occurs during low priority ISR:\n");
    printf("\n");
    printf("  Low Prio ISR: ┌─────────────┐\n");
    printf("                 │ Running     │\n");
    printf("  High Prio ISR: └────┐   ┌────┘\n");
    printf("                      │ISR│\n");
    printf("                      └───┘\n");
    printf("  Result: High priority preempts low priority\n");
    
    // ============================================================
    // 9. SHARED VOLATILE VARIABLE
    // ============================================================
    
    printf("\n--- SHARED VARIABLES (volatile) ---\n\n");
    
    printf("Variables shared between main() and ISR must be 'volatile':\n");
    printf("  volatile bool timer_interrupt_flag = %d\n", timer_interrupt_flag);
    printf("  volatile int interrupt_count = %d\n", interrupt_count);
    printf("\n");
    printf("Why volatile?\n");
    printf("  Prevents compiler optimization that might cache the value\n");
    printf("  Ensures always read from memory, not register cache\n");
    
    // ============================================================
    // 10. CRITICAL SECTION
    // ============================================================
    
    printf("\n--- CRITICAL SECTION ---\n\n");
    
    printf("Critical sections (disable interrupts briefly):\n");
    printf("\n");
    printf("  __disable_irq();        // Disable all interrupts\n");
    printf("  // Access shared resource\n");
    printf("  __enable_irq();         // Re-enable interrupts\n");
    printf("\n");
    printf("Used for atomic operations on shared data structures\n");
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    printf("\n========================================\n");
    printf("           KEY TAKEAWAYS                \n");
    printf("========================================\n");
    printf("1. ISRs must be SHORT and FAST\n");
    printf("2. Use volatile for shared variables\n");
    printf("3. Clear interrupt flags in ISR\n");
    printf("4. Lower priority number = higher priority\n");
    printf("5. Disable interrupts in critical sections\n");
    printf("6. Vector table at fixed address (0x00000000)\n");
    printf("========================================\n\n");
    
    return 0;
}
