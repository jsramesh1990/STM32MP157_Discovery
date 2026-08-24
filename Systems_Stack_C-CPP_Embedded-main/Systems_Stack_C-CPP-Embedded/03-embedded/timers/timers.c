#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>

// ============================================================
// SIMULATED TIMER REGISTERS
// ============================================================

typedef struct {
    volatile uint32_t CR1;      // Control register 1 (offset 0x00)
    volatile uint32_t CR2;      // Control register 2 (offset 0x04)
    volatile uint32_t SMCR;     // Slave mode control (offset 0x08)
    volatile uint32_t DIER;     // DMA/Interrupt enable (offset 0x0C)
    volatile uint32_t SR;       // Status register (offset 0x10)
    volatile uint32_t EGR;      // Event generation (offset 0x14)
    volatile uint32_t CCMR1;    // Capture/compare mode 1 (offset 0x18)
    volatile uint32_t CCMR2;    // Capture/compare mode 2 (offset 0x1C)
    volatile uint32_t CCER;     // Capture/compare enable (offset 0x20)
    volatile uint32_t CNT;      // Counter (offset 0x24)
    volatile uint32_t PSC;      // Prescaler (offset 0x28)
    volatile uint32_t ARR;      // Auto-reload register (offset 0x2C)
    volatile uint32_t CCR1;     // Capture/compare 1 (offset 0x34)
    volatile uint32_t CCR2;     // Capture/compare 2 (offset 0x38)
    volatile uint32_t CCR3;     // Capture/compare 3 (offset 0x3C)
    volatile uint32_t CCR4;     // Capture/compare 4 (offset 0x40)
} TIM_TypeDef;

TIM_TypeDef* TIM2 = (TIM_TypeDef*)0x40000000;

// ============================================================
// SIMULATED TIMER INTERRUPTS
// ============================================================

volatile bool timer_overflow_flag = false;
volatile uint32_t overflow_count = 0;

void timer_simulation_interrupt(void) {
    timer_overflow_flag = true;
    overflow_count++;
    
    // Clear update flag
    TIM2->SR &= ~0x0001;
}

// ============================================================
// HELPER FUNCTIONS
// ============================================================

void delay_ms(int ms) {
    usleep(ms * 1000);
}

void setup_simulated_timer(void) {
    struct sigaction sa;
    sa.sa_handler = timer_simulation_interrupt;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);
    
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;  // 100ms
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;
    setitimer(ITIMER_REAL, &timer, NULL);
}

void stop_simulated_timer(void) {
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("           TIMERS DEMO                  \n");
    printf("========================================\n\n");
    
    uint32_t clock_freq = 72000000;  // 72 MHz (typical STM32)
    
    // ============================================================
    // 1. TIMER BASIC CONCEPTS
    // ============================================================
    
    printf("--- BASIC TIMER CONCEPTS ---\n\n");
    
    printf("Timer frequency calculation:\n");
    printf("  Timer Clock = APB Clock / (Prescaler + 1)\n");
    printf("  Timer Period = (Auto Reload + 1) / Timer Clock\n\n");
    
    printf("Example with 72 MHz clock:\n");
    uint32_t prescaler = 7200;
    uint32_t auto_reload = 10000;
    uint32_t timer_freq = clock_freq / prescaler;
    float period = (float)(auto_reload + 1) / timer_freq;
    
    printf("  Prescaler = %d\n", prescaler);
    printf("  Auto Reload = %d\n", auto_reload);
    printf("  Timer Frequency = %d Hz\n", timer_freq);
    printf("  Period = %.3f seconds\n\n", period);
    
    // ============================================================
    // 2. TIMER REGISTERS (SIMULATED)
    // ============================================================
    
    printf("--- TIMER REGISTERS (SIMULATED) ---\n\n");
    
    // Configure timer
    TIM2->PSC = prescaler - 1;
    TIM2->ARR = auto_reload - 1;
    TIM2->CR1 = 0x0001;  // Enable timer
    TIM2->SR = 0x0000;    // Clear status
    
    printf("TIM2 configured:\n");
    printf("  PSC = %d (Prescaler)\n", TIM2->PSC);
    printf("  ARR = %d (Auto Reload)\n", TIM2->ARR);
    printf("  CR1 = 0x%04X (Control)\n", TIM2->CR1);
    
    // ============================================================
    // 3. PRESCALER DEMONSTRATION
    // ============================================================
    
    printf("\n--- PRESCALER EFFECT ---\n\n");
    
    printf("Prescaler divides the input clock:\n");
    for(int psc = 1; psc <= 10000; psc *= 10) {
        uint32_t freq = clock_freq / psc;
        printf("  Prescaler = %5d → Timer Freq = %8d Hz\n", psc, freq);
    }
    
    // ============================================================
    // 4. AUTO RELOAD DEMONSTRATION
    // ============================================================
    
    printf("\n--- AUTO RELOAD EFFECT ---\n\n");
    
    prescaler = 7200;
    for(int arr = 100; arr <= 10000; arr *= 10) {
        uint32_t timer_freq_hz = clock_freq / prescaler;
        float period_sec = (float)(arr + 1) / timer_freq_hz;
        printf("  ARR = %5d → Period = %.3f seconds\n", arr, period_sec);
    }
    
    // ============================================================
    // 5. TIMER INTERRUPT DEMO
    // ============================================================
    
    printf("\n--- TIMER INTERRUPT (100ms) ---\n\n");
    
    // Clear simulated timer registers
    TIM2->SR = 0x0000;
    overflow_count = 0;
    
    // Setup simulated interrupt
    setup_simulated_timer();
    printf("Timer configured for 100ms interrupts\n");
    printf("Waiting for 5 timer interrupts...\n\n");
    
    // Wait for interrupts
    int last_count = 0;
    for(int i = 0; i < 5; i++) {
        while(!timer_overflow_flag) {
            delay_ms(10);
        }
        timer_overflow_flag = false;
        
        printf("  Timer interrupt! Count = %d\n", overflow_count);
        
        // Simulate TIM2->CNT counting
        TIM2->CNT = (TIM2->CNT + 100) % (auto_reload);
        printf("    Counter (CNT) = %d\n", TIM2->CNT);
    }
    
    stop_simulated_timer();
    
    // ============================================================
    // 6. PWM (Pulse Width Modulation)
    // ============================================================
    
    printf("\n--- PWM (Pulse Width Modulation) ---\n\n");
    
    // PWM settings
    uint32_t pwm_prescaler = 720;   // 72 MHz / 720 = 100 kHz
    uint32_t pwm_period = 1000;      // 100 kHz / 1000 = 100 Hz PWM
    
    TIM2->PSC = pwm_prescaler - 1;
    TIM2->ARR = pwm_period - 1;
    
    printf("PWM Configuration:\n");
    printf("  Timer Clock = %d MHz\n", clock_freq / 1000000);
    printf("  PWM Frequency = %d Hz\n", clock_freq / pwm_prescaler / pwm_period);
    printf("  Period (ARR) = %d\n", pwm_period);
    printf("\n");
    
    // Duty cycles
    printf("Duty Cycle Examples:\n");
    int duty_cycles[] = {0, 250, 500, 750, 1000};
    const char* names[] = {"0%", "25%", "50%", "75%", "100%"};
    
    for(int i = 0; i < 5; i++) {
        uint32_t ccr = duty_cycles[i];
        float duty = (float)ccr / pwm_period * 100;
        
        TIM2->CCR1 = ccr;
        
        printf("  CCR1 = %3d → Duty Cycle = %5.1f%%", ccr, duty);
        
        // Visual representation
        printf("  [");
        int bars = (ccr * 20) / pwm_period;
        for(int b = 0; b < 20; b++) {
            printf("%c", b < bars ? '#' : '.');
        }
        printf("]\n");
    }
    
    // ============================================================
    // 7. TIMER MODES
    // ============================================================
    
    printf("\n--- TIMER MODES ---\n\n");
    
    printf("Up-counting mode (default):\n");
    printf("  CNT: 0 → 1 → 2 → ... → ARR → 0 → 1...\n");
    TIM2->CR1 &= ~0x0010;  // DIR = 0 (up)
    printf("  DIR bit = 0\n\n");
    
    printf("Down-counting mode:\n");
    printf("  CNT: ARR → ARR-1 → ... → 0 → ARR...\n");
    TIM2->CR1 |= 0x0010;   // DIR = 1 (down)
    printf("  DIR bit = 1\n\n");
    
    printf("Center-aligned mode (up then down):\n");
    printf("  CNT: 0→1→...→ARR→ARR-1→...→0→1...\n");
    TIM2->CR1 |= 0x0060;   // CMS = 01 (center aligned)
    printf("  CMS bits = 01\n");
    
    // Reset to up-counting
    TIM2->CR1 &= ~0x0070;
    
    // ============================================================
    // 8. ONE-SHOT TIMER
    // ============================================================
    
    printf("\n--- ONE-SHOT TIMER (OPM mode) ---\n\n");
    
    printf("One Pulse Mode (OPM): Timer stops after one cycle\n");
    
    // Enable one-pulse mode
    TIM2->CR1 |= 0x0008;   // OPM = 1
    
    printf("  Timer enabled (CEN=1) → counts once → stops (CEN cleared)\n");
    printf("  Useful for generating precise single delays\n");
    
    // Disable one-pulse mode
    TIM2->CR1 &= ~0x0008;
    printf("  OPM bit = 0 (continuous mode)\n");
    
    // ============================================================
    // 9. INPUT CAPTURE
    // ============================================================
    
    printf("\n--- INPUT CAPTURE ---\n\n");
    
    printf("Input Capture measures external signal frequency:\n");
    printf("  1. Signal edge detected\n");
    printf("  2. Current counter value captured into CCR\n");
    printf("  3. Interrupt generated\n");
    printf("  4. Frequency = Timer Clock / (CCR2 - CCR1)\n\n");
    
    printf("Example: Measuring 1 kHz signal with 1 MHz timer:\n");
    uint32_t capture1 = 1000;
    uint32_t capture2 = 2000;
    uint32_t diff = capture2 - capture1;
    uint32_t freq = 1000000 / diff;
    printf("  Capture 1 = %d\n", capture1);
    printf("  Capture 2 = %d\n", capture2);
    printf("  Difference = %d timer ticks\n", diff);
    printf("  Measured frequency = %d Hz\n", freq);
    
    // ============================================================
    // 10. WATCHDOG TIMER (Independent)
    // ============================================================
    
    printf("\n--- WATCHDOG TIMER (IWDG) ---\n\n");
    
    printf("Watchdog Timer: Resets system if not 'fed' periodically\n");
    printf("\n");
    printf("  Configure: IWDG->KR = 0xCCCC  (enable)\n");
    printf("             IWDG->KR = 0x5555  (enable write)\n");
    printf("             IWDG->PR = prescaler\n");
    printf("             IWDG->RLR = reload\n");
    printf("             IWDG->KR = 0xAAAA  (refresh/feed)\n");
    printf("\n");
    printf("If feed not called within timeout → system reset\n");
    printf("Used for safety-critical applications\n");
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    printf("\n========================================\n");
    printf("           KEY TAKEAWAYS                \n");
    printf("========================================\n");
    printf("1. PSC (Prescaler): Divides input clock\n");
    printf("2. ARR (Auto Reload): Sets period\n");
    printf("3. CNT (Counter): Current value (0 to ARR)\n");
    printf("4. CCR (Capture/Compare): PWM duty cycle\n");
    printf("5. Update Event: When CNT reaches ARR\n");
    printf("6. PWM Frequency = Clock / (PSC+1) / (ARR+1)\n");
    printf("7. Use one-shot for single delays\n");
    printf("8. Watchdog for safety (must be fed)\n");
    printf("========================================\n\n");
    
    return 0;
}
