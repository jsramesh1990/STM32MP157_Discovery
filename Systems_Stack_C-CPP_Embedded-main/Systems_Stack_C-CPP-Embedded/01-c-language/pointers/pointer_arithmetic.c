#include <stdio.h>
#include <stdint.h>

int main() {
    // Array declaration
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Pointer to first element
    int *ptr = arr;
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    POINTER ARITHMETIC DEEP DIVE                 ║\n");
    printf("║              Understanding How Pointers Move in Memory          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    // ============================================================
    // SECTION 1: MEMORY LAYOUT VISUALIZATION
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 1: MEMORY LAYOUT OF ARRAY\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("Array values: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    printf("Memory Layout (assuming int = 4 bytes):\n");
    printf("┌─────────┬─────────┬─────────┬─────────┬─────────┐\n");
    printf("│ arr[0]  │ arr[1]  │ arr[2]  │ arr[3]  │ arr[4]  │\n");
    printf("├─────────┼─────────┼─────────┼─────────┼─────────┤\n");
    printf("│   10    │   20    │   30    │   40    │   50    │\n");
    printf("├─────────┼─────────┼─────────┼─────────┼─────────┤\n");
    
    // Print addresses
    printf("│ %p │ %p │ %p │ %p │ %p │\n", 
           &arr[0], &arr[1], &arr[2], &arr[3], &arr[4]);
    printf("└─────────┴─────────┴─────────┴─────────┴─────────┘\n\n");
    
    printf("Key Observation: Each int occupies %zu bytes\n", sizeof(int));
    printf("Addresses increase by %zu bytes between consecutive elements\n\n", sizeof(int));
    
    // ============================================================
    // SECTION 2: BASIC POINTER OPERATIONS
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 2: BASIC POINTER OPERATIONS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("Initial State:\n");
    printf("  ptr = arr (points to first element)\n");
    printf("  Address stored in ptr: %p\n", ptr);
    printf("  Value at that address (*ptr): %d\n\n", *ptr);
    
    // Pointer increment
    printf("▶ Operation 1: ptr++\n");
    printf("   Before: ptr = %p, *ptr = %d\n", ptr, *ptr);
    ptr++;
    printf("   After:  ptr = %p, *ptr = %d\n", ptr, *ptr);
    printf("   Explanation: ptr moved forward by %zu byte(s) (size of int)\n\n", sizeof(int));
    
    // Pointer addition
    printf("▶ Operation 2: ptr += 2\n");
    printf("   Before: ptr = %p, *ptr = %d\n", ptr, *ptr);
    ptr += 2;
    printf("   After:  ptr = %p, *ptr = %d\n", ptr, *ptr);
    printf("   Explanation: ptr moved forward by 2 × %zu = %zu bytes\n\n", 
           sizeof(int), 2 * sizeof(int));
    
    // Reset pointer for next demo
    ptr = arr;
    
    // ============================================================
    // SECTION 3: POINTER DIFFERENCE
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 3: POINTER DIFFERENCE (ptr1 - ptr2)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    int *start = &arr[0];
    int *end = &arr[4];
    
    printf("start = &arr[0] = %p\n", start);
    printf("end   = &arr[4] = %p\n", end);
    printf("\n");
    
    printf("Pointer Difference Formula:\n");
    printf("  end - start = (address_end - address_start) / sizeof(int)\n");
    printf("  = (%p - %p) / %zu\n", end, start, sizeof(int));
    printf("  = %ld / %zu = %ld\n", 
           (long)(end - start) * sizeof(int), sizeof(int), (long)(end - start));
    printf("\n");
    
    printf("Result: end - start = %ld (number of elements between them)\n\n", end - start);
    
    // ============================================================
    // SECTION 4: TRAVERSAL USING POINTER ARITHMETIC
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 4: TRAVERSING ARRAY USING POINTER ARITHMETIC\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("Using: *(ptr + i) is equivalent to arr[i]\n\n");
    
    ptr = arr;  // Reset to beginning
    printf("%-10s %-20s %-20s %-15s\n", "Index", "arr[i]", "*(ptr + i)", "Address");
    printf("─────────────────────────────────────────────────────────────────\n");
    
    for(int i = 0; i < 5; i++) {
        printf("%-10d %-20d %-20d %p\n", 
               i, arr[i], *(ptr + i), (ptr + i));
    }
    printf("\n");
    
    // ============================================================
    // SECTION 5: DIFFERENT DATA TYPES DEMONSTRATION
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 5: POINTER ARITHMETIC WITH DIFFERENT DATA TYPES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    // Char array
    char char_arr[] = {'A', 'B', 'C', 'D', 'E'};
    char *char_ptr = char_arr;
    
    printf("For char* (size = %zu byte):\n", sizeof(char));
    printf("  Before char_ptr++: address = %p, value = %c\n", char_ptr, *char_ptr);
    char_ptr++;
    printf("  After char_ptr++:  address = %p, value = %c\n", char_ptr, *char_ptr);
    printf("  Moved by %zu byte\n\n", sizeof(char));
    
    // Double array
    double double_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double *double_ptr = double_arr;
    
    printf("For double* (size = %zu bytes):\n", sizeof(double));
    printf("  Before double_ptr++: address = %p, value = %.1f\n", double_ptr, *double_ptr);
    double_ptr++;
    printf("  After double_ptr++:  address = %p, value = %.1f\n", double_ptr, *double_ptr);
    printf("  Moved by %zu bytes\n\n", sizeof(double));
    
    // ============================================================
    // SECTION 6: SIZE INFORMATION
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 6: SIZE INFORMATION & KEY RULES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("Data Type Sizes on This System:\n");
    printf("  sizeof(char)   = %2zu byte(s)\n", sizeof(char));
    printf("  sizeof(short)  = %2zu byte(s)\n", sizeof(short));
    printf("  sizeof(int)    = %2zu byte(s)\n", sizeof(int));
    printf("  sizeof(long)   = %2zu byte(s)\n", sizeof(long));
    printf("  sizeof(float)  = %2zu byte(s)\n", sizeof(float));
    printf("  sizeof(double) = %2zu byte(s)\n", sizeof(double));
    printf("  sizeof(int*)   = %2zu byte(s) (pointer itself)\n\n", sizeof(int*));
    
    printf("Pointer Arithmetic Rules:\n");
    printf("  ┌─────────────────────────────────────────────────────────────┐\n");
    printf("  │  ptr + n  → Moves forward by n × sizeof(*ptr) bytes        │\n");
    printf("  │  ptr - n  → Moves backward by n × sizeof(*ptr) bytes       │\n");
    printf("  │  ptr++    → Moves to next element                          │\n");
    printf("  │  ptr--    → Moves to previous element                      │\n");
    printf("  │  ptr2 - ptr1 → Number of elements between them            │\n");
    printf("  └─────────────────────────────────────────────────────────────┘\n\n");
    
    // ============================================================
    // SECTION 7: COMMON MISTAKES
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 7: COMMON MISTAKES TO AVOID\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("❌ WRONG:                                   ✓ CORRECT:\n");
    printf("─────────────────────────────────────────────────────────────────\n");
    printf("  int *ptr;                                 int arr[5];\n");
    printf("  ptr++;     // Wild pointer!               int *ptr = arr;\n");
    printf("                                            ptr++;     // Valid!\n");
    printf("\n");
    printf("  ptr = 0x1000;  // Direct assignment       ptr = &variable;\n");
    printf("\n");
    printf("  void *vp;                                 int *ptr;\n");
    printf("  vp++;         // Error!                   ptr++;     // Valid!\n");
    printf("\n");
    printf("  ptr1 - ptr2   // Different arrays         ptr1 - ptr2  // Same array\n");
    
    // ============================================================
    // SECTION 8: PRACTICAL EXAMPLE - REVERSE ARRAY
    // ============================================================
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  SECTION 8: PRACTICAL EXAMPLE - Reverse Array Using Pointers\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    int original[] = {1, 2, 3, 4, 5};
    int reversed[5];
    int *src = original;
    int *dst = reversed + 4;  // Point to last element
    
    printf("Original array: ");
    for(int i = 0; i < 5; i++) printf("%d ", original[i]);
    printf("\n");
    
    // Reverse using pointers
    for(int i = 0; i < 5; i++) {
        *dst = *src;
        src++;
        dst--;
    }
    
    printf("Reversed array: ");
    for(int i = 0; i < 5; i++) printf("%d ", reversed[i]);
    printf("\n\n");
    
    // ============================================================
    // SECTION 9: QUICK REFERENCE CARD
    // ============================================================
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  QUICK REFERENCE CARD\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│  OPERATION              MEANING                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│  int *ptr = arr;        Point to first element                  │\n");
    printf("│  ptr++;                 Move to next element                    │\n");
    printf("│  ptr--;                 Move to previous element                │\n");
    printf("│  ptr + n;               Move forward n elements                 │\n");
    printf("│  ptr - n;               Move backward n elements                │\n");
    printf("│  ptr2 - ptr1;           Number of elements between ptr1 and ptr2│\n");
    printf("│  *ptr;                  Value at current position               │\n");
    printf("│  *(ptr + i);            Value at index i (same as arr[i])       │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    
    // ============================================================
    // SECTION 10: SUMMARY
    // ============================================================
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  KEY TAKEAWAYS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("  1. Pointer arithmetic automatically accounts for data type size\n");
    printf("  2. arr[i] is equivalent to *(arr + i)\n");
    printf("  3. ptr++ moves by sizeof(*ptr) bytes, NOT 1 byte\n");
    printf("  4. Only subtract pointers pointing to the SAME array\n");
    printf("  5. Pointer difference returns number of elements, NOT bytes\n");
    printf("  6. void* cannot be used for pointer arithmetic (no size)\n");
    printf("  7. Always ensure pointers stay within array bounds\n");
    
    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("                     COMPLETE - Happy Coding!\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
