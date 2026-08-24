#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================
// GLOBAL VARIABLES (DATA and BSS segments)
// ============================================================

// DATA segment - initialized global
int global_initialized = 100;

// DATA segment - initialized static
static int static_initialized = 200;

// BSS segment - uninitialized global (will be 0)
int global_uninitialized;

// BSS segment - uninitialized static (will be 0)
static int static_uninitialized;

// ============================================================
// FUNCTION TO SHOW STACK BEHAVIOR
// ============================================================

void stack_demo(int parameter) {
    int local_var = 50;
    int local_array[5] = {1, 2, 3, 4, 5};
    
    printf("\n  Inside stack_demo function:\n");
    printf("    Parameter address: %p\n", &parameter);
    printf("    Local variable: %p\n", &local_var);
    printf("    Local array: %p\n", local_array);
}

// ============================================================
// RECURSION TO DEMO STACK GROWTH
// ============================================================

int recursion_count = 0;

void recursive_function(int depth) {
    int stack_var = depth;
    recursion_count++;
    
    printf("  Depth %d: stack_var at %p\n", depth, &stack_var);
    
    if(depth < 3) {
        recursive_function(depth + 1);
    }
}

// ============================================================
// DANGEROUS FUNCTION (returns stack address)
// ============================================================

int* dangerous_function() {
    int local = 999;
    return &local;  // DANGER! Returning address of stack variable
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("        MEMORY MANAGEMENT DEMO          \n");
    printf("========================================\n\n");
    
    // ============================================================
    // 1. MEMORY SEGMENTS (DATA, BSS, TEXT, STACK, HEAP)
    // ============================================================
    
    printf("--- MEMORY SEGMENTS ---\n");
    
    // DATA segment variables
    printf("\nDATA SEGMENT (initialized):\n");
    printf("  global_initialized at %p = %d\n", &global_initialized, global_initialized);
    printf("  static_initialized at %p = %d\n", &static_initialized, static_initialized);
    
    // BSS segment variables
    printf("\nBSS SEGMENT (zero-initialized):\n");
    printf("  global_uninitialized at %p = %d\n", &global_uninitialized, global_uninitialized);
    printf("  static_uninitialized at %p = %d\n", &static_uninitialized, static_uninitialized);
    
    // TEXT segment (code)
    printf("\nTEXT SEGMENT (code):\n");
    printf("  main() function at %p\n", main);
    printf("  stack_demo() at %p\n", stack_demo);
    
    // STACK variables
    printf("\nSTACK SEGMENT:\n");
    int stack_var1 = 10;
    int stack_var2 = 20;
    int stack_array[5] = {10, 20, 30, 40, 50};
    
    printf("  stack_var1 at %p = %d\n", &stack_var1, stack_var1);
    printf("  stack_var2 at %p = %d\n", &stack_var2, stack_var2);
    printf("  stack_array at %p\n", stack_array);
    
    // HEAP allocation
    printf("\nHEAP SEGMENT:\n");
    int *heap_var = (int*)malloc(sizeof(int));
    *heap_var = 500;
    
    int *heap_array = (int*)malloc(5 * sizeof(int));
    for(int i = 0; i < 5; i++) {
        heap_array[i] = (i + 1) * 100;
    }
    
    printf("  heap_var at %p = %d\n", heap_var, *heap_var);
    printf("  heap_array at %p\n", heap_array);
    printf("  heap_array values: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", heap_array[i]);
    }
    printf("\n");
    
    // ============================================================
    // 2. STACK BEHAVIOR - Function calls
    // ============================================================
    
    printf("\n\n--- STACK BEHAVIOR ---\n");
    stack_demo(42);
    
    // ============================================================
    // 3. STACK GROWTH with recursion
    // ============================================================
    
    printf("\n--- STACK GROWTH (Recursion) ---\n");
    printf("Notice how addresses decrease (stack grows downward):\n");
    recursive_function(1);
    printf("  Total recursive calls: %d\n", recursion_count);
    
    // ============================================================
    // 4. DEMONSTRATE STACK VS HEAP LIFETIME
    // ============================================================
    
    printf("\n--- STACK vs HEAP LIFETIME ---\n");
    
    // Stack variable - dies when function returns
    printf("Stack variable (local): exists only in this function\n");
    
    // Heap variable - persists until freed
    int *persistent = (int*)malloc(sizeof(int));
    *persistent = 777;
    printf("Heap variable: value = %d at %p (persists until free)\n", 
           *persistent, persistent);
    
    // ============================================================
    // 5. DANGEROUS OPERATION (Returning stack address)
    // ============================================================
    
    printf("\n--- DANGEROUS OPERATION ---\n");
    int *danger = dangerous_function();
    printf("Dangerous: returned stack address %p (value may be corrupted!)\n", danger);
    printf("  Value at that address: %d (unpredictable!)\n", *danger);
    
    // ============================================================
    // 6. PROPER HEAP MANAGEMENT
    // ============================================================
    
    printf("\n--- PROPER HEAP MANAGEMENT ---\n");
    
    // Allocate
    int *proper = (int*)malloc(sizeof(int));
    if(proper == NULL) {
        printf("  Allocation failed!\n");
        return 1;
    }
    *proper = 888;
    printf("  Allocated at %p with value %d\n", proper, *proper);
    
    // Use
    printf("  Using the memory...\n");
    
    // Free
    free(proper);
    printf("  Freed the memory\n");
    
    // Set to NULL (prevent dangling pointer)
    proper = NULL;
    printf("  Set pointer to NULL\n");
    
    // ============================================================
    // 7. MEMORY ALLOCATION FUNCTIONS
    // ============================================================
    
    printf("\n--- MEMORY ALLOCATION FUNCTIONS ---\n");
    
    // malloc - allocates uninitialized memory
    int *m = (int*)malloc(3 * sizeof(int));
    printf("  malloc: %p (values are garbage)\n", m);
    
    // calloc - allocates and zeros memory
    int *c = (int*)calloc(3, sizeof(int));
    printf("  calloc: %p (values are zero)\n", c);
    printf("    c[0]=%d, c[1]=%d, c[2]=%d\n", c[0], c[1], c[2]);
    
    // realloc - resize existing allocation
    int *r = (int*)realloc(m, 5 * sizeof(int));
    if(r != NULL) {
        printf("  realloc: resized from 3 to 5 ints\n");
        m = r;
    }
    
    // Free all
    free(m);
    free(c);
    
    // ============================================================
    // 8. MEMORY LAYOUT SUMMARY (Address ordering)
    // ============================================================
    
    printf("\n--- MEMORY LAYOUT SUMMARY ---\n");
    printf("Addresses (typically from low to high):\n");
    printf("  TEXT (code):   %p\n", main);
    printf("  DATA (init):   %p\n", &global_initialized);
    printf("  BSS (uninit):  %p\n", &global_uninitialized);
    printf("  HEAP:          %p\n", heap_var);
    printf("  STACK:         %p\n", &stack_var1);
    
    // ============================================================
    // 9. STATIC VARIABLE DEMO
    // ============================================================
    
    printf("\n--- STATIC VARIABLE DEMO ---\n");
    
    // Static variable inside function (DATA segment)
    static int static_counter = 0;
    static_counter++;
    printf("  Static counter (in DATA segment): %d\n", static_counter);
    printf("  Static variable address: %p (same across calls)\n", &static_counter);
    
    // Call again to show it persists
    static_counter++;
    printf("  After increment: %d (value persists!)\n", static_counter);
    
    // ============================================================
    // 10. SIZEOF DEMO
    // ============================================================
    
    printf("\n--- SIZEOF INFORMATION ---\n");
    printf("  sizeof(char)   = %zu byte\n", sizeof(char));
    printf("  sizeof(int)    = %zu bytes\n", sizeof(int));
    printf("  sizeof(void*)  = %zu bytes (pointer size)\n", sizeof(void*));
    printf("  sizeof(int*)   = %zu bytes\n", sizeof(int*));
    
    // ============================================================
    // CLEANUP HEAP MEMORY
    // ============================================================
    
    free(heap_var);
    free(heap_array);
    free(proper);
    
    printf("\n========================================\n");
    printf("             COMPLETE                    \n");
    printf("========================================\n\n");
    
    return 0;
}
