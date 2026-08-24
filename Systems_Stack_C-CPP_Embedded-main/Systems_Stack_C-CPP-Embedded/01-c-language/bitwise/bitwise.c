#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function to print binary representation
void print_binary(uint8_t num) {
    for(int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if(i == 4) printf(" ");
    }
}

int main() {
    printf("\n========================================\n");
    printf("        BITWISE OPERATIONS DEMO         \n");
    printf("========================================\n\n");
    
    // ============================================================
    // 1. BASIC BITWISE OPERATORS
    // ============================================================
    
    printf("--- BASIC OPERATORS ---\n");
    
    uint8_t a = 0b0101;  // 5
    uint8_t b = 0b0011;  // 3
    
    printf("a = %d (binary: ", a); print_binary(a); printf(")\n");
    printf("b = %d (binary: ", b); print_binary(b); printf(")\n\n");
    
    printf("a & b = %d  (binary: ", a & b); print_binary(a & b); printf(")  // AND\n");
    printf("a | b = %d  (binary: ", a | b); print_binary(a | b); printf(")  // OR\n");
    printf("a ^ b = %d  (binary: ", a ^ b); print_binary(a ^ b); printf(")  // XOR\n");
    printf("~a    = %d  (binary: ", ~a); print_binary(~a); printf(")  // NOT\n\n");
    
    // ============================================================
    // 2. SHIFT OPERATIONS
    // ============================================================
    
    printf("--- SHIFT OPERATIONS ---\n");
    
    uint8_t value = 5;  // 0b00000101
    printf("value = %d (binary: ", value); print_binary(value); printf(")\n\n");
    
    printf("value << 1 = %d (binary: ", value << 1); print_binary(value << 1); 
    printf(")  // Multiply by 2\n");
    
    printf("value << 2 = %d (binary: ", value << 2); print_binary(value << 2);
    printf(")  // Multiply by 4\n");
    
    printf("value >> 1 = %d (binary: ", value >> 1); print_binary(value >> 1);
    printf(")  // Divide by 2\n\n");
    
    // ============================================================
    // 3. BIT MANIPULATION (Set, Clear, Toggle, Check)
    // ============================================================
    
    printf("--- BIT MANIPULATION ---\n");
    
    uint8_t reg = 0b10110010;
    uint8_t bit_pos = 3;
    
    printf("Original register: "); print_binary(reg); printf(" (0x%02X)\n", reg);
    printf("Bit position to manipulate: %d\n\n", bit_pos);
    
    // Set bit
    reg |= (1 << bit_pos);
    printf("After SET bit %d:    ", bit_pos); print_binary(reg); 
    printf(" (0x%02X)\n", reg);
    
    // Clear bit
    reg &= ~(1 << bit_pos);
    printf("After CLEAR bit %d:  ", bit_pos); print_binary(reg); 
    printf(" (0x%02X)\n", reg);
    
    // Toggle bit
    reg ^= (1 << bit_pos);
    printf("After TOGGLE bit %d: ", bit_pos); print_binary(reg); 
    printf(" (0x%02X)\n", reg);
    
    // Check bit
    if(reg & (1 << bit_pos)) {
        printf("Bit %d is SET\n\n", bit_pos);
    } else {
        printf("Bit %d is CLEAR\n\n", bit_pos);
    }
    
    // ============================================================
    // 4. WORKING WITH MULTIPLE BITS
    // ============================================================
    
    printf("--- MULTIPLE BITS OPERATIONS ---\n");
    
    reg = 0b10110010;
    printf("Original: "); print_binary(reg); printf("\n");
    
    // Set multiple bits (bits 0,2,4)
    reg |= (1<<0) | (1<<2) | (1<<4);
    printf("Set bits 0,2,4: "); print_binary(reg); printf("\n");
    
    // Clear multiple bits (bits 1,3,5)
    reg &= ~((1<<1) | (1<<3) | (1<<5));
    printf("Clear bits 1,3,5: "); print_binary(reg); printf("\n\n");
    
    // ============================================================
    // 5. BIT MASKING EXAMPLES
    // ============================================================
    
    printf("--- BIT MASKING ---\n");
    
    uint8_t data = 0xAB;  // 0b10101011
    printf("Data: 0x%02X (", data); print_binary(data); printf(")\n");
    
    // Extract lower 4 bits
    uint8_t lower = data & 0x0F;
    printf("Lower 4 bits: 0x%01X (", lower); print_binary(lower); printf(")\n");
    
    // Extract upper 4 bits
    uint8_t upper = (data >> 4) & 0x0F;
    printf("Upper 4 bits: 0x%01X (", upper); print_binary(upper); printf(")\n");
    
    // Combine two values
    uint8_t high = 0xC;  // 0b1100
    uint8_t low = 0x9;   // 0b1001
    uint8_t combined = (high << 4) | low;
    printf("Combine 0x%01X and 0x%01X: 0x%02X (", high, low, combined);
    print_binary(combined); printf(")\n\n");
    
    // ============================================================
    // 6. BIT FIELDS IN STRUCTURES
    // ============================================================
    
    printf("--- BIT FIELDS ---\n");
    
    struct {
        uint8_t enable : 1;   // bit 0
        uint8_t mode : 2;     // bits 1-2
        uint8_t speed : 3;    // bits 3-5
        uint8_t reserved : 2; // bits 6-7
    } config;
    
    config.enable = 1;
    config.mode = 2;
    config.speed = 5;
    
    printf("Config structure:\n");
    printf("  enable = %d\n", config.enable);
    printf("  mode = %d\n", config.mode);
    printf("  speed = %d\n", config.speed);
    
    // View as raw uint8_t
    uint8_t* raw = (uint8_t*)&config;
    printf("  Raw value: 0x%02X (", *raw); print_binary(*raw); printf(")\n\n");
    
    // ============================================================
    // 7. BIT TRICKS
    // ============================================================
    
    printf("--- BIT TRICKS ---\n");
    
    // Check if number is power of 2
    uint8_t test = 16;
    if((test & (test - 1)) == 0) {
        printf("%d is power of 2\n", test);
    }
    
    // Count set bits (Brian Kernighan)
    uint8_t count_num = 0b10110110;
    uint8_t count = 0;
    uint8_t temp = count_num;
    while(temp) {
        count++;
        temp &= (temp - 1);
    }
    printf("Number of set bits in "); print_binary(count_num);
    printf(" = %d\n", count);
    
    // XOR swap (no temporary variable)
    int x = 10, y = 20;
    printf("\nXOR Swap: x=%d, y=%d\n", x, y);
    x ^= y;
    y ^= x;
    x ^= y;
    printf("After swap: x=%d, y=%d\n", x, y);
    
    // Check even/odd
    int num = 7;
    if(num & 1) {
        printf("\n%d is odd\n", num);
    } else {
        printf("\n%d is even\n", num);
    }
    
    // ============================================================
    // 8. EMBEDDED-STYLE REGISTER MANIPULATION
    // ============================================================
    
    printf("\n--- EMBEDDED REGISTER MANIPULATION ---\n");
    
    // Simulated GPIO registers
    uint32_t GPIOA_MODER = 0;
    uint32_t GPIOA_ODR = 0;
    uint32_t GPIOA_IDR = 0;
    
    #define PIN5 5
    #define PIN13 13
    
    // Configure PA5 as output (01 in MODER bits 10-11)
    GPIOA_MODER &= ~(3 << (PIN5 * 2));  // Clear bits
    GPIOA_MODER |= (1 << (PIN5 * 2));   // Set to output
    
    printf("GPIOA_MODER after config: 0x%08X\n", GPIOA_MODER);
    
    // Set PA5 high
    GPIOA_ODR |= (1 << PIN5);
    printf("GPIOA_ODR after SET PA5: 0x%08X\n", GPIOA_ODR);
    
    // Set PA5 low
    GPIOA_ODR &= ~(1 << PIN5);
    printf("GPIOA_ODR after CLEAR PA5: 0x%08X\n", GPIOA_ODR);
    
    // Toggle PA5
    GPIOA_ODR ^= (1 << PIN5);
    printf("GPIOA_ODR after TOGGLE PA5: 0x%08X\n", GPIOA_ODR);
    
    printf("\n========================================\n");
    printf("             COMPLETE                    \n");
    printf("========================================\n\n");
    
    return 0;
}
