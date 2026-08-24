#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// ============================================================
// SIMULATED GPIO REGISTERS (STM32 Style)
// ============================================================

typedef struct {
    volatile uint32_t MODER;    // Mode register (offset 0x00)
    volatile uint32_t OTYPER;   // Output type register (offset 0x04)
    volatile uint32_t OSPEEDR;  // Output speed register (offset 0x08)
    volatile uint32_t PUPDR;    // Pull-up/pull-down register (offset 0x0C)
    volatile uint32_t IDR;      // Input data register (offset 0x10)
    volatile uint32_t ODR;      // Output data register (offset 0x14)
    volatile uint32_t BSRR;     // Bit set/reset register (offset 0x18)
    volatile uint32_t LCKR;     // Lock register (offset 0x1C)
    volatile uint32_t AFR[2];   // Alternate function registers (offset 0x20, 0x24)
} GPIO_TypeDef;

// Simulated GPIO ports
GPIO_TypeDef* GPIOA = (GPIO_TypeDef*)0x40020000;
GPIO_TypeDef* GPIOB = (GPIO_TypeDef*)0x40020400;
GPIO_TypeDef* GPIOC = (GPIO_TypeDef*)0x40020800;

// ============================================================
// HELPER FUNCTIONS
// ============================================================

void delay_ms(int ms) {
    usleep(ms * 1000);
}

void print_gpio_state(const char* port_name, GPIO_TypeDef* port, int pin) {
    printf("  %s Pin %d:\n", port_name, pin);
    printf("    MODER: 0x%08X\n", port->MODER);
    printf("    ODR:   0x%08X\n", port->ODR);
    printf("    IDR:   0x%08X\n", port->IDR);
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("           GPIO DEMO                    \n");
    printf("========================================\n\n");
    
    // ============================================================
    // 1. GPIO REGISTERS EXPLANATION
    // ============================================================
    
    printf("--- GPIO REGISTERS ---\n\n");
    
    printf("Each GPIO pin has configuration registers:\n");
    printf("  MODER    (2 bits)  : Mode (Input/Output/AF/Analog)\n");
    printf("  OTYPER   (1 bit)   : Output type (Push-pull/Open-drain)\n");
    printf("  OSPEEDR  (2 bits)  : Output speed\n");
    printf("  PUPDR    (2 bits)  : Pull-up/Pull-down\n");
    printf("  IDR      (32 bits) : Input data (read pin state)\n");
    printf("  ODR      (32 bits) : Output data (write pin state)\n");
    printf("  BSRR     (32 bits) : Bit set/reset (atomic)\n");
    
    // ============================================================
    // 2. MODE CONFIGURATION
    // ============================================================
    
    printf("\n--- CONFIGURING PIN MODE (MODER) ---\n\n");
    
    int pin = 5;
    
    printf("Configuring PA%d as OUTPUT:\n", pin);
    
    // Clear bits for pin (2 bits per pin)
    GPIOA->MODER &= ~(3 << (pin * 2));
    printf("  After clear: MODER = 0x%08X\n", GPIOA->MODER);
    
    // Set to output mode (01 binary)
    GPIOA->MODER |= (1 << (pin * 2));
    printf("  After set to output: MODER = 0x%08X\n\n", GPIOA->MODER);
    
    printf("Other modes:\n");
    printf("  00: Input\n");
    printf("  01: Output\n");
    printf("  10: Alternate Function\n");
    printf("  11: Analog\n");
    
    // ============================================================
    // 3. OUTPUT TYPE
    // ============================================================
    
    printf("\n--- OUTPUT TYPE (OTYPER) ---\n\n");
    
    // Push-pull (default)
    GPIOA->OTYPER &= ~(1 << pin);
    printf("PA%d configured as PUSH-PULL\n", pin);
    printf("  Can drive both HIGH and LOW\n");
    
    // Open-drain
    GPIOA->OTYPER |= (1 << pin);
    printf("PA%d configured as OPEN-DRAIN\n", pin);
    printf("  Can only drive LOW, needs external pull-up for HIGH\n");
    
    // Back to push-pull
    GPIOA->OTYPER &= ~(1 << pin);
    
    // ============================================================
    // 4. OUTPUT SPEED
    // ============================================================
    
    printf("\n--- OUTPUT SPEED (OSPEEDR) ---\n\n");
    
    // Clear speed bits
    GPIOA->OSPEEDR &= ~(3 << (pin * 2));
    
    // Set low speed
    GPIOA->OSPEEDR |= (0 << (pin * 2));
    printf("Low speed (2 MHz): Good for LEDs, buttons\n");
    
    // Set high speed
    GPIOA->OSPEEDR |= (2 << (pin * 2));
    printf("High speed (50 MHz): Good for high-speed signals\n");
    
    // ============================================================
    // 5. PULL-UP/PULL-DOWN
    // ============================================================
    
    printf("\n--- PULL-UP/PULL-DOWN (PUPDR) ---\n\n");
    
    // No pull
    GPIOA->PUPDR &= ~(3 << (pin * 2));
    printf("No pull: Floating input (might be unstable)\n");
    
    // Pull-up
    GPIOA->PUPDR |= (1 << (pin * 2));
    printf("Pull-up: Default HIGH when nothing connected\n");
    
    // Pull-down
    GPIOA->PUPDR |= (2 << (pin * 2));
    printf("Pull-down: Default LOW when nothing connected\n");
    
    // ============================================================
    // 6. WRITING OUTPUT (ODR vs BSRR)
    // ============================================================
    
    printf("\n--- WRITING OUTPUT (ODR vs BSRR) ---\n\n");
    
    // Reset to no pull
    GPIOA->PUPDR &= ~(3 << (pin * 2));
    
    printf("Method 1: Using ODR (not atomic)\n");
    GPIOA->ODR |= (1 << pin);   // Set high
    printf("  Set high: ODR = 0x%08X\n", GPIOA->ODR);
    GPIOA->ODR &= ~(1 << pin);   // Set low
    printf("  Set low:  ODR = 0x%08X\n\n", GPIOA->ODR);
    
    printf("Method 2: Using BSRR (atomic, preferred)\n");
    GPIOA->BSRR = (1 << pin);       // Set high (bits 0-15)
    printf("  Set high: BSRR=0x%08X, ODR=0x%08X\n", GPIOA->BSRR, GPIOA->ODR);
    GPIOA->BSRR = (1 << (pin + 16)); // Set low (bits 16-31)
    printf("  Set low:  BSRR=0x%08X, ODR=0x%08X\n", GPIOA->BSRR, GPIOA->ODR);
    
    // ============================================================
    // 7. TOGGLING LED
    // ============================================================
    
    printf("\n--- BLINKING LED (PA5) ---\n\n");
    
    // Configure PA5 as output
    GPIOA->MODER |= (1 << (pin * 2));
    GPIOA->OTYPER &= ~(1 << pin);  // Push-pull
    GPIOA->OSPEEDR |= (2 << (pin * 2));  // High speed
    
    printf("Blinking PA5 (LED) 5 times:\n");
    
    for(int i = 0; i < 5; i++) {
        // Set LED ON
        GPIOA->BSRR = (1 << pin);
        printf("  LED ON  (BSRR=0x%08X, ODR=0x%08X)\n", 
               GPIOA->BSRR, GPIOA->ODR);
        delay_ms(200);
        
        // Set LED OFF
        GPIOA->BSRR = (1 << (pin + 16));
        printf("  LED OFF (BSRR=0x%08X, ODR=0x%08X)\n", 
               GPIOA->BSRR, GPIOA->ODR);
        delay_ms(200);
    }
    
    // ============================================================
    // 8. READING INPUT (BUTTON)
    // ============================================================
    
    printf("\n--- READING BUTTON (PA0) ---\n\n");
    
    int button_pin = 0;
    
    // Configure PA0 as input with pull-up
    GPIOA->MODER &= ~(3 << (button_pin * 2));  // Input mode (00)
    GPIOA->PUPDR |= (1 << (button_pin * 2));   // Pull-up (01)
    
    printf("PA0 configured as INPUT with PULL-UP\n");
    printf("  When button NOT pressed: IDR bit = 1 (pulled high)\n");
    printf("  When button pressed:     IDR bit = 0 (connected to ground)\n\n");
    
    printf("Reading button state (simulated):\n");
    
    for(int i = 0; i < 5; i++) {
        // Simulate button state
        int button_pressed = (i % 2 == 0);
        
        if(button_pressed) {
            GPIOA->IDR = (1 << button_pin);  // Simulate high
            printf("  Read %d: BUTTON RELEASED (IDR bit = 1)\n", i+1);
        } else {
            GPIOA->IDR = 0;  // Simulate low
            printf("  Read %d: BUTTON PRESSED  (IDR bit = 0)\n", i+1);
        }
        delay_ms(500);
    }
    
    // ============================================================
    // 9. MULTIPLE PINS CONFIGURATION
    // ============================================================
    
    printf("\n--- CONFIGURING MULTIPLE PINS ---\n\n");
    
    // Configure pins 8,9,10,11 as outputs (LED bar)
    for(int p = 8; p <= 11; p++) {
        GPIOA->MODER |= (1 << (p * 2));  // Output mode
        GPIOA->ODR |= (1 << p);          // Initially high
        printf("  PA%d configured as output, initially HIGH\n", p);
    }
    
    // Turn off one by one
    printf("\nTurning off LEDs sequentially:\n");
    for(int p = 8; p <= 11; p++) {
        GPIOA->BSRR = (1 << (p + 16));
        printf("  PA%d OFF\n", p);
        delay_ms(300);
    }
    
    // ============================================================
    // 10. ALTERNATE FUNCTION
    // ============================================================
    
    printf("\n--- ALTERNATE FUNCTION (UART, SPI, I2C) ---\n\n");
    
    printf("Alternate Function Mode: Pin controlled by peripheral\n");
    printf("Example: USART TX on PA9, USART RX on PA10\n\n");
    
    // Configure PA9 as AF (UART TX)
    int af_pin = 9;
    GPIOA->MODER &= ~(3 << (af_pin * 2));
    GPIOA->MODER |= (2 << (af_pin * 2));  // 10 = Alternate Function
    GPIOA->AFR[1] &= ~(0xF << ((af_pin - 8) * 4));
    GPIOA->AFR[1] |= (7 << ((af_pin - 8) * 4));  // AF7 = USART1
    
    printf("PA%d configured as AF7 (USART1_TX)\n", af_pin);
    printf("  Now controlled by USART peripheral, not software\n");
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    printf("\n========================================\n");
    printf("           KEY TAKEAWAYS                \n");
    printf("========================================\n");
    printf("1. MODER: 00=input, 01=output, 10=AF, 11=analog\n");
    printf("2. ODR: Write output, IDR: Read input\n");
    printf("3. BSRR: Atomic set/reset (bits 0-15=set, 16-31=reset)\n");
    printf("4. PUPDR: 00=none, 01=pull-up, 10=pull-down\n");
    printf("5. OTYPER: 0=push-pull, 1=open-drain\n");
    printf("6. Always use BSRR for output to avoid race conditions\n");
    printf("========================================\n\n");
    
    return 0;
}
