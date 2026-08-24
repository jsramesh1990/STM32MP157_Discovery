#include <stdio.h>

// ============================================================
// OBJECT-LIKE MACROS
// ============================================================

#define PI 3.14159
#define MAX_BUFFER 1024
#define PROGRAM_NAME "Preprocessor Demo"

// ============================================================
// FUNCTION-LIKE MACROS
// ============================================================

// WRONG way (no parentheses)
#define SQUARE_WRONG(x) x * x

// CORRECT way
#define SQUARE(x) ((x) * (x))

// Multi-parameter macro
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Multi-line macro
#define PRINT_RESULT(op, val) do { \
    printf("%s = %.2f\n", op, val); \
} while(0)

// ============================================================
// STRINGIZE AND CONCATENATION
// ============================================================

#define STR(x) #x
#define CONCAT(a, b) a##b

// ============================================================
// CONDITIONAL COMPILATION
// ============================================================

#define VERSION 2
#define DEBUG 1

// ============================================================
// X-MACROS (Advanced technique)
// ============================================================

#define WEEK_DAYS \
    X(MONDAY, 1)    \
    X(TUESDAY, 2)   \
    X(WEDNESDAY, 3) \
    X(THURSDAY, 4)  \
    X(FRIDAY, 5)    \
    X(SATURDAY, 6)  \
    X(SUNDAY, 7)

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("        PREPROCESSOR DEMO               \n");
    printf("========================================\n\n");
    
    // 1. Object-like macros
    printf("--- OBJECT-LIKE MACROS ---\n");
    printf("PI = %.5f\n", PI);
    printf("MAX_BUFFER = %d\n", MAX_BUFFER);
    printf("PROGRAM_NAME = %s\n\n", PROGRAM_NAME);
    
    // 2. Function-like macros
    printf("--- FUNCTION-LIKE MACROS ---\n");
    printf("SQUARE(5) = %d\n", SQUARE(5));
    printf("MAX(10, 20) = %d\n", MAX(10, 20));
    PRINT_RESULT("MAX(3.14, 2.71)", MAX(3.14, 2.71));
    printf("\n");
    
    // Demonstrate WRONG macro
    printf("--- WRONG MACRO DEMONSTRATION ---\n");
    printf("SQUARE_WRONG(2+3) = %d (WRONG!)\n", SQUARE_WRONG(2+3));
    printf("SQUARE(2+3) = %d (CORRECT)\n\n", SQUARE(2+3));
    
    // 3. Stringize and Concatenation
    printf("--- STRINGIZE & CONCATENATION ---\n");
    printf("STR(test) = %s\n", STR(test));
    int var1 = 100;
    int var2 = 200;
    printf("CONCAT(var,1) = %d\n", CONCAT(var,1));
    printf("CONCAT(var,2) = %d\n\n", CONCAT(var,2));
    
    // 4. Conditional compilation
    printf("--- CONDITIONAL COMPILATION ---\n");
    
    #if VERSION == 1
        printf("Running Version 1\n");
    #elif VERSION == 2
        printf("Running Version 2\n");
    #else
        printf("Running Unknown Version\n");
    #endif
    
    #ifdef DEBUG
        printf("DEBUG mode is ON\n");
    #else
        printf("DEBUG mode is OFF\n");
    #endif
    printf("\n");
    
    // 5. Predefined macros
    printf("--- PREDEFINED MACROS ---\n");
    printf("__FILE__ = %s\n", __FILE__);
    printf("__LINE__ = %d\n", __LINE__);
    printf("__DATE__ = %s\n", __DATE__);
    printf("__TIME__ = %s\n", __TIME__);
    printf("__STDC__ = %d\n\n", __STDC__);
    
    // 6. X-Macros (Advanced)
    printf("--- X-MACROS (WEEK DAYS) ---\n");
    
    // Create enum using X-macro
    #define X(name, val) name = val,
    enum { WEEK_DAYS };
    #undef X
    
    // Create string array using X-macro
    #define X(name, val) #name,
    const char* day_names[] = { WEEK_DAYS };
    #undef X
    
    // Print using both
    printf("Enum values and names:\n");
    printf("  MONDAY = %d, name = %s\n", MONDAY, day_names[0]);
    printf("  TUESDAY = %d, name = %s\n", TUESDAY, day_names[1]);
    printf("  WEDNESDAY = %d, name = %s\n", WEDNESDAY, day_names[2]);
    printf("  THURSDAY = %d, name = %s\n", THURSDAY, day_names[3]);
    printf("  FRIDAY = %d, name = %s\n", FRIDAY, day_names[4]);
    printf("  SATURDAY = %d, name = %s\n", SATURDAY, day_names[5]);
    printf("  SUNDAY = %d, name = %s\n", SUNDAY, day_names[6]);
    
    printf("\n========================================\n");
    printf("             COMPLETE                    \n");
    printf("========================================\n\n");
    
    return 0;
}
