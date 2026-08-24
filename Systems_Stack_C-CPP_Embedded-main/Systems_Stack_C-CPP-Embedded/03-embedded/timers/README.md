# TIMERS

## What are Timers?

Timers are hardware peripherals that count clock cycles. They can generate interrupts at precise intervals, measure input signals, generate PWM, etc.

## Timer Types

| Timer Type | Features | Use Case |
|------------|----------|----------|
| **SysTick** | 24-bit, simple | OS tick, delay |
| **General Purpose** | 16/32-bit, PWM, capture | LED dimming, frequency measurement |
| **Advanced** | Dead-time, complementary outputs | Motor control |
| **Watchdog** | Independent, reset on underflow | System recovery |
| **RTC** | Battery-backed | Real-time clock |

## Timer Block Diagram

┌─────────────────────────────────────────────────────────────────┐
│ TIMER BLOCK DIAGRAM │
├─────────────────────────────────────────────────────────────────┤
│ │
│ Clock Source │
│ ┌─────┐ │
│ │ PCLK│───┐ │
│ └─────┘ │ │
│ ↓ │
│ ┌─────────┐ ┌─────────┐ ┌─────────┐ │
│ │Prescaler│────▶│ Counter │────▶│ Auto │ │
│ │ (PSC) │ │ (CNT) │ │ Reload │ │
│ └─────────┘ └─────────┘ │ (ARR) │ │
│ │ └─────────┘ │
│ ↓ │ │
│ ┌─────────┐ │ │
│ │ Compare │◄──────────┘ │
│ │ (CCR) │ │
│ └─────────┘ │
│ │ │
│ ↓ │
│ ┌─────────┐ │
│ │ Output │ │
│ │ PWM │ │
│ └─────────┘ │
│ │
└─────────────────────────────────────────────────────────────────┘
text


## Timer Formulas

Timer Frequency = Clock Frequency / (Prescaler + 1)

Timeout Period = (Auto Reload + 1) / Timer Frequency

Example:
Clock = 72 MHz
Prescaler = 7200 - 1 → 72 MHz / 7200 = 10 kHz
Auto Reload = 10000 - 1 → 10 kHz / 10000 = 1 Hz (1 second)
text


## SysTick Timer (Simple)

```c
// Configure SysTick for 1ms interrupt
SysTick_Config(SystemCoreClock / 1000);

// SysTick ISR
void SysTick_Handler(void) {
    ms_ticks++;  // Increment every 1ms
}

// Delay function
void delay_ms(uint32_t ms) {
    uint32_t start = ms_ticks;
    while((ms_ticks - start) < ms);
}

Basic Timer Configuration
c

// Enable timer clock
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

// Set prescaler (72 MHz / 7200 = 10 kHz)
TIM2->PSC = 7200 - 1;

// Set auto reload (10 kHz / 10000 = 1 Hz)
TIM2->ARR = 10000 - 1;

// Enable update interrupt
TIM2->DIER |= TIM_DIER_UIE;

// Enable timer
TIM2->CR1 |= TIM_CR1_CEN;

PWM Configuration
c

// Configure channel 1 as PWM output
TIM2->CCMR1 |= (6 << 4);  // PWM mode 1
TIM2->CCER |= (1 << 0);    // Enable channel

// Set PWM frequency (72 MHz / 7200 / 1000 = 10 kHz)
TIM2->PSC = 7200 - 1;
TIM2->ARR = 1000 - 1;

// Set duty cycle (500/1000 = 50%)
TIM2->CCR1 = 500;

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 03-embedded-baremetal/timers/timers.c -o timers
./timers

Key Takeaways

    Prescaler divides clock – sets timer resolution

    Auto reload sets period – how long to count

    Counter counts up/down – from 0 to ARR then reset

    PWM duty cycle = CCR / ARR – controls output level

    Update interrupt on overflow – for periodic tasks
