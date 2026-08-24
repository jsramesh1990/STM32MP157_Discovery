#include <stdio.h>
#include <stdint.h>

// Method 1: Loop through all 32 bits
int count_set_bits_naive(uint32_t num) {
    int count = 0;
    for(int i = 0; i < 32; i++) {
        if(num & (1 << i)) {
            count++;
        }
    }
    return count;
}

// Method 2: Brian Kernighan's algorithm (best for sparse bits)
int count_set_bits_kernighan(uint32_t num) {
    int count = 0;
    while(num) {
        num &= (num - 1);  // Clear lowest set bit
        count++;
    }
    return count;
}

// Method 3: Lookup table (fastest, 256 entries)
int count_set_bits_table(uint32_t num) {
    static const uint8_t table[256] = {
        [0 ... 255] = 0  // Would need to initialize properly
    };
    // Actual implementation would have precomputed table
    // For demo, using Kernighan
    return count_set_bits_kernighan(num);
}

// Method 4: Built-in (GCC/Clang)
int count_set_bits_builtin(uint32_t num) {
    return __builtin_popcount(num);
}

int main() {
    printf("\n========================================\n");
    printf("     CHALLENGE 02: COUNT SET BITS      \n");
    printf("========================================\n\n");
    
    uint32_t test_values[] = {
        0x00000000,  // 0
        0x00000001,  // 1
        0x00000003,  // 2
        0x00000007,  // 3
        0x0000000F,  // 4
        0x000000FF,  // 8
        0xFFFFFFFF,  // 32
        0xAAAAAAAA,  // 16 (10101010...)
        0x55555555,  // 16 (01010101...)
        0b1011       // 3
    };
    
    printf("Testing various methods:\n\n");
    printf("%-12s %-12s %-12s %-12s\n", 
           "Value (hex)", "Naive", "Kernighan", "Built-in");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < sizeof(test_values)/sizeof(test_values[0]); i++) {
        uint32_t val = test_values[i];
        printf("0x%08X  %-12d %-12d %-12d\n",
               val,
               count_set_bits_naive(val),
               count_set_bits_kernighan(val),
               count_set_bits_builtin(val));
    }
    
    // Demonstration of Brian Kernighan algorithm
    printf("\n--- Brian Kernighan Algorithm Demo ---\n");
    uint32_t demo = 0b10110010;  // 0xB2 = 4 set bits
    printf("Starting with: 0x%02X (binary: ", demo);
    for(int i = 7; i >= 0; i--) {
        printf("%d", (demo >> i) & 1);
    }
    printf(")\n");
    
    uint32_t temp = demo;
    int step = 1;
    while(temp) {
        printf("  Step %d: 0x%02X", step, temp);
        temp &= (temp - 1);
        printf(" → 0x%02X (cleared lowest set bit)\n", temp);
        step++;
    }
    printf("  Total set bits = %d\n", step - 1);
    
    printf("\n========================================\n");
    printf("              COMPLETE                  \n");
    printf("========================================\n\n");
    
    return 0;
}
