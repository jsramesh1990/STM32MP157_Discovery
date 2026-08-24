#include <stdio.h>

// Solution using temporary variable
void swap_temp(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Solution using XOR (no temporary variable)
void swap_xor(int *a, int *b) {
    if(a != b) {  // Check for same address
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

// Solution using addition/subtraction
void swap_arith(int *a, int *b) {
    if(a != b) {
        *a = *a + *b;
        *b = *a - *b;
        *a = *a - *b;
    }
}

int main() {
    printf("\n========================================\n");
    printf("     CHALLENGE 01: POINTER SWAP        \n");
    printf("========================================\n\n");
    
    // Test with temporary variable method
    int x1 = 5, y1 = 10;
    printf("Method 1 (temporary):\n");
    printf("  Before: x=%d, y=%d\n", x1, y1);
    swap_temp(&x1, &y1);
    printf("  After:  x=%d, y=%d\n\n", x1, y1);
    
    // Test with XOR method
    int x2 = 5, y2 = 10;
    printf("Method 2 (XOR):\n");
    printf("  Before: x=%d, y=%d\n", x2, y2);
    swap_xor(&x2, &y2);
    printf("  After:  x=%d, y=%d\n\n", x2, y2);
    
    // Test with arithmetic method
    int x3 = 5, y3 = 10;
    printf("Method 3 (arithmetic):\n");
    printf("  Before: x=%d, y=%d\n", x3, y3);
    swap_arith(&x3, &y3);
    printf("  After:  x=%d, y=%d\n\n", x3, y3);
    
    // Test edge cases
    printf("Edge Cases:\n");
    
    int a = 0, b = 100;
    swap_temp(&a, &b);
    printf("  swap(0, 100) → (%d, %d)\n", a, b);
    
    int c = -5, d = 10;
    swap_temp(&c, &d);
    printf("  swap(-5, 10) → (%d, %d)\n", c, d);
    
    int e = 42, f = 42;
    swap_xor(&e, &f);
    printf("  swap(42, 42) → (%d, %d)\n", e, f);
    
    printf("\n========================================\n");
    printf("              COMPLETE                  \n");
    printf("========================================\n\n");
    
    return 0;
}
