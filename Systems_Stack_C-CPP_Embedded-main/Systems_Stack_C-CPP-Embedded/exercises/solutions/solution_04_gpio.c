#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

// ============================================================
// SIMULATED HARDWARE REGISTERS
// ============================================================

// GPIOA registers
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR (*(volatile uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOA_ODR (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR (*(volatile uint32_t*)(GPIOA_BASE + 0x18))

// TIM2 registers
#define TIM2_BASE 0x40000000
#define TIM2_CR1 (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_CR2 (*(volatile uint32_t*)(TIM2_BASE + 0x04))
#define TIM2_DIER (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_EGR (*(volatile uint32_t*)(TIM2_BASE + 0x14))
#define TIM2_PSC (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile uint32_t*)(TIM2_BASE + 0x2C))
#define TIM2_CNT (*(volatile uint32_t*)(TIM2_BASE + 0x24))

// LED pin
#define LED_PIN 5

// Global flag for timer interrupt (simulated)
volatile bool timer_interrupt = false;
volatile int interrupt_count = 0;

// ============================================================
// SIMULATED TIMER INTERRUPT USING POSIX SIGNAL
// ============================================================

void timer_isr(int signum) {
    // Clear interrupt flag (simulate writing to SR)
    TIM2_SR &= ~0x0001;
    
    // Set flag for main loop
    timer_interrupt = true;
    interrupt_count++;
    
    // Toggle LED using BSRR (atomic)
    // Set bit: write 1 to bit position (0-15)
    // Clear bit: write 1 to bit position + 16
    static bool led_state = false;
    if(led_state) {
        GPIOA_BSRR = (1 << (LED_PIN + 16));  // Clear bit (LED OFF)
        led_state = false;
        printf("  [ISR] LED OFF\n");
    } else {
        GPIOA_BSRR = (1 << LED_PIN);         // Set bit (LED ON)
        led_state = true;
        printf("  [ISR] LED ON\n");
    }
}

void setup_timer_interrupt(void) {
    // Setup POSIX timer to simulate hardware interrupt
    struct sigaction sa;
    sa.sa_handler = timer_isr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);
    
    // Timer for 500ms interval
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000;   // 500ms
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000; // Repeat every 500ms
    setitimer(ITIMER_REAL, &timer, NULL);
}

// ============================================================
// HARDWARE INITIALIZATION
// ============================================================

void gpio_init(void) {
    // Configure PA5 as output
    // Clear MODER bits for pin 5 (bits 10-11)
    GPIOA_MODER &= ~(3 << (LED_PIN * 2));
    // Set to output mode (01)
    GPIOA_MODER |= (1 << (LED_PIN * 2));
    
    // Configure as push-pull (default)
    GPIOA_OTYPER &= ~(1 << LED_PIN);
    
    // Configure speed (high)
    GPIOA_OSPEEDR |= (2 << (LED_PIN * 2));
    
    // Initially LED OFF
    GPIOA_BSRR = (1 << (LED_PIN + 16));
    
    printf("GPIO initialized: PA%d as output, LED OFF\n", LED_PIN);
}

void timer_init(void) {
    // Enable timer clock (simulated)
    printf("Timer clock enabled\n");
    
    // Configure prescaler for 1ms tick
    // Assuming 72 MHz timer clock
    // 72 MHz / 72000 = 1 kHz (1ms)
    TIM2_PSC = 72000 - 1;
    
    // Configure auto-reload for 500ms period
    // 1 kHz * 500 = 500ms
    TIM2_ARR = 500 - 1;
    
    // Clear counter
    TIM2_CNT = 0;
    
    // Clear status register
    TIM2_SR = 0;
    
    // Enable update interrupt
    TIM2_DIER |= 0x0001;  // UIE = 1
    
    // Enable timer
    TIM2_CR1 |= 0x0001;   // CEN = 1
    
    printf("Timer initialized: PSC=%d, ARR=%d, period=500ms\n", 
           TIM2_PSC, TIM2_ARR);
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("   CHALLENGE 04: LED BLINK WITH TIMER   \n");
    printf("========================================\n\n");
    
    // Initialize hardware
    printf("--- INITIALIZATION ---\n");
    gpio_init();
    timer_init();
    
    // Setup simulated interrupt
    setup_timer_interrupt();
    
    printf("\n--- RUNNING (5 seconds) ---\n");
    printf("LED should blink every 500ms\n\n");
    
    // Main loop - empty! All work done in ISR
    // Just wait for 10 interrupts (5 seconds)
    int last_count = 0;
    while(interrupt_count < 10) {
        if(timer_interrupt) {
            timer_interrupt = false;
            // Main loop can do other work here
            // For demo, just tracking
            if(interrupt_count != last_count) {
                printf("  [MAIN] Interrupt #%d processed\n", interrupt_count);
                last_count = interrupt_count;
            }
        }
        // Simulate main program doing other tasks
        usleep(10000);  // 10ms
    }
    
    // Cleanup
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("\n--- SUMMARY ---\n");
    printf("Total interrupts: %d\n", interrupt_count);
    printf("LED blinked %d times\n", interrupt_count);
    
    printf("\n========================================\n");
    printf("              COMPLETE                  \n");
    printf("========================================\n\n");
    
    return 0;
}
