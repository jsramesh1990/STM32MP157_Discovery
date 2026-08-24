# GPIO (General Purpose Input/Output)

## What is GPIO?

GPIO pins are programmable digital I/O lines on a microcontroller. They can be configured as input or output to read sensors or control LEDs, relays, etc.

## GPIO Pin Modes

| Mode | Description | Use Case |
|------|-------------|----------|
| **Input** | Read external signal | Button, sensor |
| **Output** | Drive external device | LED, motor |
| **Alternate Function** | Peripheral signal (UART, SPI) | Communication |
| **Analog** | ADC/DAC input/output | Analog reading |

## GPIO Registers (STM32 Style)

┌─────────────────────────────────────────────────────────────────┐
│ GPIO REGISTERS │
├─────────────────────────────────────────────────────────────────┤
│ │
│ MODER (Mode Register) - 2 bits per pin │
│ ┌────────────────────────────────────────────┐ │
│ │ 00: Input │ 01: Output │ 10: AF │ 11: Analog│ │
│ └────────────────────────────────────────────┘ │
│ │
│ OTYPER (Output Type) - 1 bit per pin │
│ ┌────────────────────────────────────────────┐ │
│ │ 0: Push-pull │ 1: Open-drain │ │
│ └────────────────────────────────────────────┘ │
│ │
│ OSPEEDR (Output Speed) - 2 bits per pin │
│ ┌────────────────────────────────────────────┐ │
│ │ 00: Low │ 01: Medium │ 10: High │ 11: Very High│ │
│ └────────────────────────────────────────────┘ │
│ │
│ PUPDR (Pull-up/Pull-down) - 2 bits per pin │
│ ┌────────────────────────────────────────────┐ │
│ │ 00: None │ 01: Pull-up │ 10: Pull-down │ 11: Reserved│ │
│ └────────────────────────────────────────────┘ │
│ │
│ IDR (Input Data Register) - Read pin state │
│ ODR (Output Data Register) - Write pin state │
│ BSRR (Bit Set/Reset Register) - Atomic set/reset │
│ │
└─────────────────────────────────────────────────────────────────┘
text


## GPIO Operations

### Configuring as Output
```c
// Set PA5 as output
GPIOA->MODER &= ~(3 << (5 * 2));  // Clear bits
GPIOA->MODER |= (1 << (5 * 2));   // Set to 01 (output)

// Set output type (push-pull)
GPIOA->OTYPER &= ~(1 << 5);

// Set speed
GPIOA->OSPEEDR |= (2 << (5 * 2));  // High speed

Writing to Output
c

// Set pin high (traditional)
GPIOA->ODR |= (1 << 5);

// Set pin high (atomic BSRR) - better
GPIOA->BSRR = (1 << 5);

// Set pin low (traditional)
GPIOA->ODR &= ~(1 << 5);

// Set pin low (atomic BSRR)
GPIOA->BSRR = (1 << (5 + 16));

// Toggle pin
GPIOA->ODR ^= (1 << 5);

Reading Input
c

// Configure as input with pull-up
GPIOA->MODER &= ~(3 << (5 * 2));  // 00 = input
GPIOA->PUPDR |= (1 << (5 * 2));   // 01 = pull-up

// Read pin
if(GPIOA->IDR & (1 << 5)) {
    // Pin is HIGH
} else {
    // Pin is LOW
}

Push-Pull vs Open-Drain
text

Push-Pull:                       Open-Drain:
┌─────────┐                      ┌─────────┐
│   VDD   │                      │   VDD   │
│    │    │                      │    │    │
│  ┌▼┐    │                      │   ┌─┐   │
│  │ │PMOS│                      │   │ │   │  External pull-up
│  └─┘    │                      │   └─┘   │      ┌─────┐
│    │    │                      │    │    │      │     │
├────┼────┤                      ├────┼────┤      │     │
│    │    │                      │   ┌▼┐   │      │ ┌─┐ │
│  ┌▼┐    │                      │   │ │NMOS│      │ │ │ │
│  │ │NMOS│                      │   └─┘   │      │ └─┘ │
│  └─┘    │                      │    │    │      │     │
│   GND   │                      │   GND   │      └─────┘
└─────────┘                      └─────────┘
Drives HIGH and LOW              Only drives LOW (requires pull-up)

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 03-embedded-baremetal/gpio/gpio.c -o gpio
./gpio

Key Takeaways

    MODER configures pin mode (input/output/AF/analog)

    ODR writes output, IDR reads input

    BSRR for atomic set/reset (no race conditions)

    Pull-up/pull-down for input (prevents floating)

    Push-pull drives both high/low, open-drain needs pull-up
