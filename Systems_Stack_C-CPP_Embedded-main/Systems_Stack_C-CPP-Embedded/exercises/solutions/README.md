# Systems_Stack_C-CPP-Embedded - Exercises Module

## exercises/challenges/README.md

```markdown
# EXERCISES & CHALLENGES

## How to Use These Exercises

1. Read the challenge description
2. Try to solve it on your own
3. Check the solution in `../solutions/`
4. Run the solution to verify

## Challenge Index

| # | Challenge | Topic | Difficulty |
|---|-----------|-------|------------|
| 1 | Pointer Swap | Pointers | ⭐ Easy |
| 2 | Count Set Bits | Bitwise | ⭐⭐ Medium |
| 3 | String Move | Move Semantics | ⭐⭐ Medium |
| 4 | LED Blink with Timer | Embedded | ⭐⭐⭐ Hard |
```

---

## exercises/challenges/challenge_01_pointers.md

```markdown
# Challenge 01: Swap Two Numbers Using Pointers

## Difficulty: ⭐ Easy

## Problem Statement

Write a function that swaps the values of two integers using pointers. The function should not use any temporary variable.

## Function Signature

```c
void swap(int *a, int *b);
```

## Requirements

1. Function must use pointers (no global variables)
2. Must work for any integer values
3. No temporary variable allowed (bonus: use XOR swap)

## Example

```c
int x = 5, y = 10;
swap(&x, &y);
// After swap: x = 10, y = 5
```

## Test Cases

| Input (x, y) | Expected Output (x, y) |
|--------------|------------------------|
| (5, 10) | (10, 5) |
| (-5, 10) | (10, -5) |
| (0, 100) | (100, 0) |
| (42, 42) | (42, 42) |

## Starter Code

```c
#include <stdio.h>

void swap(int *a, int *b) {
    // Your code here
}

int main() {
    int x = 5, y = 10;
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After:  x=%d, y=%d\n", x, y);
    return 0;
}
```

## Hints

<details>
<summary>Click for hints</summary>

1. You need to dereference the pointers to access values
2. Store one value in a temporary variable (if using temp method)
3. For XOR swap: `*a ^= *b; *b ^= *a; *a ^= *b;`
</details>

## Solution

See: `../solutions/solution_01_pointers.c`
```

---

## exercises/challenges/challenge_02_bitwise.md

```markdown
# Challenge 02: Count Set Bits (Population Count)

## Difficulty: ⭐⭐ Medium

## Problem Statement

Write a function that counts the number of 1 bits (set bits) in a 32-bit unsigned integer. This is also known as the "population count" or "Hamming weight".

## Function Signature

```c
int count_set_bits(uint32_t num);
```

## Requirements

1. Must use bitwise operations only (no string conversion)
2. Must work for any 32-bit unsigned integer
3. Optimize for speed (optional)

## Example

```c
count_set_bits(0b1011)     // 3 (bits: 1+0+1+1 = 3)
count_set_bits(0x00000000) // 0
count_set_bits(0xFFFFFFFF) // 32
count_set_bits(0x55555555) // 16 (alternating bits)
```

## Test Cases

| Input (hex) | Binary (first 8 bits) | Expected |
|-------------|----------------------|----------|
| 0x00000000 | 00000000 | 0 |
| 0x00000001 | 00000001 | 1 |
| 0x00000003 | 00000011 | 2 |
| 0x00000007 | 00000111 | 3 |
| 0x0000000F | 00001111 | 4 |
| 0x000000FF | 11111111 | 8 |
| 0xFFFFFFFF | all ones | 32 |
| 0xAAAAAAAA | 10101010 | 16 |

## Starter Code

```c
#include <stdio.h>
#include <stdint.h>

int count_set_bits(uint32_t num) {
    // Your code here
}

int main() {
    uint32_t test = 0b1011;
    printf("count_set_bits(0b1011) = %d\n", count_set_bits(test));
    return 0;
}
```

## Approaches

| Method | Description | Best For |
|--------|-------------|----------|
| Loop & mask | Check each bit (32 iterations) | Simple |
| Brian Kernighan | Clear lowest set bit each time | Sparse bits |
| Lookup table | Precompute for 8-bit chunks | Fastest |
| Built-in | `__builtin_popcount()` | GCC/Clang |

## Hints

<details>
<summary>Click for hints</summary>

1. Brian Kernighan's method: `num &= (num - 1)` clears the lowest set bit
2. Each iteration removes one set bit
3. Loop until num becomes 0
</details>

## Solution

See: `../solutions/solution_02_bitwise.c`
```

---

## exercises/challenges/challenge_03_move_semantics.md

```markdown
# Challenge 03: Implement String Class with Move Semantics

## Difficulty: ⭐⭐ Medium

## Problem Statement

Implement a simple `String` class that manages dynamic memory. The class must have proper move constructor and move assignment operator.

## Class Requirements

| Method | Description |
|--------|-------------|
| Constructor | Allocate and copy C-string |
| Destructor | Free allocated memory |
| Copy constructor | Deep copy (allocate new memory) |
| Copy assignment | Deep copy with self-assignment check |
| Move constructor | Transfer ownership (no allocation) |
| Move assignment | Transfer ownership with cleanup |
| `c_str()` | Return const char* |
| `length()` | Return string length |

## Example Usage

```cpp
String s1("Hello");
String s2 = std::move(s1);  // Move constructor
String s3("World");
s3 = std::move(s2);          // Move assignment
```

## Expected Output

```
Constructor: "Hello"
Move Constructor: transferred "Hello"
Constructor: "World"  
Move Assignment: transferred "World"
Destructor: (moved-from, empty)
Destructor: "World"
Destructor: (moved-from, empty)
```

## Starter Code

```cpp
#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    size_t len;
    
public:
    // Constructor
    String(const char* str = "") {
        // Your code here
    }
    
    // Destructor
    ~String() {
        // Your code here
    }
    
    // Copy constructor
    String(const String& other) {
        // Your code here
    }
    
    // Copy assignment
    String& operator=(const String& other) {
        // Your code here
    }
    
    // Move constructor
    String(String&& other) noexcept {
        // Your code here
    }
    
    // Move assignment
    String& operator=(String&& other) noexcept {
        // Your code here
    }
    
    const char* c_str() const { return data; }
    size_t length() const { return len; }
};

int main() {
    String s1("Hello");
    String s2 = std::move(s1);
    std::cout << "s2: " << s2.c_str() << std::endl;
    return 0;
}
```

## Hints

<details>
<summary>Click for hints</summary>

1. In move constructor: steal `other.data`, set `other.data = nullptr`
2. In move assignment: delete current data, then steal
3. Always leave moved-from object in valid state (nullptr, len=0)
4. Use `noexcept` for move operations
</details>

## Solution

See: `../solutions/solution_03_move_semantics.cpp`
```

---

## exercises/challenges/challenge_04_gpio.md

```markdown
# Challenge 04: LED Blink with Timer Interrupt

## Difficulty: ⭐⭐⭐ Hard

## Problem Statement

Write a program that blinks an LED using a timer interrupt instead of delay loops. The LED should toggle every 500ms.

## Requirements

1. Configure GPIO pin as output for LED
2. Configure timer for 500ms period
3. Toggle LED inside timer interrupt handler
4. Main loop should be empty (just while(1))

## Simulated Registers

```c
// GPIO registers (simulated)
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR  (*(volatile uint32_t*)(GPIOA_BASE + 0x18))

// Timer registers (simulated)
#define TIM2_BASE 0x40000000
#define TIM2_CR1   (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_DIER  (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR    (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_PSC   (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR   (*(volatile uint32_t*)(TIM2_BASE + 0x2C))
```

## LED Pin

Use PA5 (pin 5 of GPIOA) for the LED.

## Configuration Steps

1. **GPIO Configuration**
   - Set PA5 to output mode (MODER bits 10-11 = 01)
   - Set to push-pull (OTYPER bit 5 = 0)

2. **Timer Configuration**
   - Set prescaler (PSC) for 1ms tick
   - Set auto-reload (ARR) for 500ms period
   - Enable update interrupt (DIER bit 0 = 1)
   - Enable timer (CR1 bit 0 = 1)

3. **ISR Implementation**
   - Clear interrupt flag (SR bit 0 = 0)
   - Toggle LED (BSRR bit 5 = 1 to set, bit 21 = 1 to clear)

## Example Timer Calculation

```c
// Assume timer clock = 72 MHz
// For 1ms tick: PSC = 72000 - 1 = 71999
// For 500ms period: ARR = 500 - 1 = 499

TIM2_PSC = 71999;   // 72 MHz / 72000 = 1 kHz (1ms)
TIM2_ARR = 499;     // 1 kHz / 500 = 2 Hz (500ms period)
```

## Starter Code

```c
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

// Register definitions
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR  (*(volatile uint32_t*)(GPIOA_BASE + 0x18))

#define TIM2_BASE 0x40000000
#define TIM2_CR1   (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_DIER  (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR    (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_PSC   (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR   (*(volatile uint32_t*)(TIM2_BASE + 0x2C))

// LED pin
#define LED_PIN 5

// Simulated interrupt flag
volatile bool timer_interrupt = false;

// Timer ISR (simulated)
void TIM2_IRQHandler(void) {
    // Your code here: clear flag, toggle LED
}

int main() {
    // 1. Configure GPIO
    
    // 2. Configure Timer
    
    // 3. Main loop (empty, just wait for interrupts)
    
    return 0;
}
```

## Hints

<details>
<summary>Click for hints</summary>

1. Configure GPIO MODER: clear then set bits 10-11 to 01
2. Timer PSC = 71999 for 1ms at 72 MHz
3. Timer ARR = 499 for 500ms period
4. In ISR: clear SR bit 0, toggle LED using BSRR
5. Use BSRR for atomic toggling: set bit = (1 << pin), clear bit = (1 << (pin+16))
</details>

## Expected Behavior

```
LED ON  (500ms)
LED OFF (500ms)
LED ON  (500ms)
LED OFF (500ms)
... continues indefinitely
```

## Solution

See: `../solutions/solution_04_gpio.c`
```

---

## exercises/solutions/solution_01_pointers.c

```c
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
```

---

## exercises/solutions/solution_02_bitwise.c

```c
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
```

---

## exercises/solutions/solution_03_move_semantics.cpp

```cpp
#include <iostream>
#include <cstring>
#include <utility>

class String {
private:
    char* data;
    size_t len;
    
public:
    // Constructor
    String(const char* str = "") {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
        std::cout << "Constructor: \"" << data << "\"\n";
    }
    
    // Destructor
    ~String() {
        if(data) {
            std::cout << "Destructor: \"" << data << "\"\n";
            delete[] data;
        } else {
            std::cout << "Destructor: (moved-from, empty)\n";
        }
        data = nullptr;
        len = 0;
    }
    
    // Copy constructor (deep copy)
    String(const String& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
        std::cout << "Copy Constructor: \"" << data << "\"\n";
    }
    
    // Copy assignment (deep copy)
    String& operator=(const String& other) {
        if(this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
            std::cout << "Copy Assignment: \"" << data << "\"\n";
        }
        return *this;
    }
    
    // Move constructor (transfer ownership)
    String(String&& other) noexcept 
        : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
        std::cout << "Move Constructor: transferred \"" << data << "\"\n";
    }
    
    // Move assignment (transfer ownership)
    String& operator=(String&& other) noexcept {
        if(this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            other.data = nullptr;
            other.len = 0;
            std::cout << "Move Assignment: transferred \"" << data << "\"\n";
        }
        return *this;
    }
    
    const char* c_str() const { return data ? data : ""; }
    size_t length() const { return len; }
};

int main() {
    std::cout << "\n========================================\n";
    std::cout << "  CHALLENGE 03: MOVE SEMANTICS        \n";
    std::cout << "========================================\n\n";
    
    std::cout << "1. Creating s1:\n";
    String s1("Hello");
    
    std::cout << "\n2. Move constructor (s2 = std::move(s1)):\n";
    String s2 = std::move(s1);
    
    std::cout << "\n3. s1 is now empty (moved-from state):\n";
    std::cout << "   s1.c_str() = \"" << s1.c_str() << "\" (empty)\n";
    std::cout << "   s2.c_str() = \"" << s2.c_str() << "\"\n";
    
    std::cout << "\n4. Creating s3:\n";
    String s3("World");
    
    std::cout << "\n5. Move assignment (s3 = std::move(s2)):\n";
    s3 = std::move(s2);
    
    std::cout << "\n6. Final states:\n";
    std::cout << "   s1: \"" << s1.c_str() << "\" (moved-from)\n";
    std::cout << "   s2: \"" << s2.c_str() << "\" (moved-from)\n";
    std::cout << "   s3: \"" << s3.c_str() << "\"\n";
    
    std::cout << "\n7. Demonstrating copy (not move):\n";
    String s4 = s3;  // Copy constructor, not move
    
    std::cout << "\n8. Exiting scope - destructors will run:\n";
    
    std::cout << "\n========================================\n";
    std::cout << "              COMPLETE                  \n";
    std::cout << "========================================\n\n";
    
    return 0;
}
```

---

## exercises/solutions/solution_04_gpio.c

```c
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

// ============================================================
// SIMULATED HARDWARE REGISTERS
// ============================================================

// GPIOA registers
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR (*(volatile uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOA_ODR (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR (*(volatile uint32_t*)(GPIOA_BASE + 0x18))

// TIM2 registers
#define TIM2_BASE 0x40000000
#define TIM2_CR1 (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_CR2 (*(volatile uint32_t*)(TIM2_BASE + 0x04))
#define TIM2_DIER (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_EGR (*(volatile uint32_t*)(TIM2_BASE + 0x14))
#define TIM2_PSC (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile uint32_t*)(TIM2_BASE + 0x2C))
#define TIM2_CNT (*(volatile uint32_t*)(TIM2_BASE + 0x24))

// LED pin
#define LED_PIN 5

// Global flag for timer interrupt (simulated)
volatile bool timer_interrupt = false;
volatile int interrupt_count = 0;

// ============================================================
// SIMULATED TIMER INTERRUPT USING POSIX SIGNAL
// ============================================================

void timer_isr(int signum) {
    // Clear interrupt flag (simulate writing to SR)
    TIM2_SR &= ~0x0001;
    
    // Set flag for main loop
    timer_interrupt = true;
    interrupt_count++;
    
    // Toggle LED using BSRR (atomic)
    // Set bit: write 1 to bit position (0-15)
    // Clear bit: write 1 to bit position + 16
    static bool led_state = false;
    if(led_state) {
        GPIOA_BSRR = (1 << (LED_PIN + 16));  // Clear bit (LED OFF)
        led_state = false;
        printf("  [ISR] LED OFF\n");
    } else {
        GPIOA_BSRR = (1 << LED_PIN);         // Set bit (LED ON)
        led_state = true;
        printf("  [ISR] LED ON\n");
    }
}

void setup_timer_interrupt(void) {
    // Setup POSIX timer to simulate hardware interrupt
    struct sigaction sa;
    sa.sa_handler = timer_isr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);
    
    // Timer for 500ms interval
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000;   // 500ms
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000; // Repeat every 500ms
    setitimer(ITIMER_REAL, &timer, NULL);
}

// ============================================================
// HARDWARE INITIALIZATION
// ============================================================

void gpio_init(void) {
    // Configure PA5 as output
    // Clear MODER bits for pin 5 (bits 10-11)
    GPIOA_MODER &= ~(3 << (LED_PIN * 2));
    // Set to output mode (01)
    GPIOA_MODER |= (1 << (LED_PIN * 2));
    
    // Configure as push-pull (default)
    GPIOA_OTYPER &= ~(1 << LED_PIN);
    
    // Configure speed (high)
    GPIOA_OSPEEDR |= (2 << (LED_PIN * 2));
    
    // Initially LED OFF
    GPIOA_BSRR = (1 << (LED_PIN + 16));
    
    printf("GPIO initialized: PA%d as output, LED OFF\n", LED_PIN);
}

void timer_init(void) {
    // Enable timer clock (simulated)
    printf("Timer clock enabled\n");
    
    // Configure prescaler for 1ms tick
    // Assuming 72 MHz timer clock
    // 72 MHz / 72000 = 1 kHz (1ms)
    TIM2_PSC = 72000 - 1;
    
    // Configure auto-reload for 500ms period
    // 1 kHz * 500 = 500ms
    TIM2_ARR = 500 - 1;
    
    // Clear counter
    TIM2_CNT = 0;
    
    // Clear status register
    TIM2_SR = 0;
    
    // Enable update interrupt
    TIM2_DIER |= 0x0001;  // UIE = 1
    
    // Enable timer
    TIM2_CR1 |= 0x0001;   // CEN = 1
    
    printf("Timer initialized: PSC=%d, ARR=%d, period=500ms\n", 
           TIM2_PSC, TIM2_ARR);
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    printf("\n========================================\n");
    printf("   CHALLENGE 04: LED BLINK WITH TIMER   \n");
    printf("========================================\n\n");
    
    // Initialize hardware
    printf("--- INITIALIZATION ---\n");
    gpio_init();
    timer_init();
    
    // Setup simulated interrupt
    setup_timer_interrupt();
    
    printf("\n--- RUNNING (5 seconds) ---\n");
    printf("LED should blink every 500ms\n\n");
    
    // Main loop - empty! All work done in ISR
    // Just wait for 10 interrupts (5 seconds)
    int last_count = 0;
    while(interrupt_count < 10) {
        if(timer_interrupt) {
            timer_interrupt = false;
            // Main loop can do other work here
            // For demo, just tracking
            if(interrupt_count != last_count) {
                printf("  [MAIN] Interrupt #%d processed\n", interrupt_count);
                last_count = interrupt_count;
            }
        }
        // Simulate main program doing other tasks
        usleep(10000);  // 10ms
    }
    
    // Cleanup
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("\n--- SUMMARY ---\n");
    printf("Total interrupts: %d\n", interrupt_count);
    printf("LED blinked %d times\n", interrupt_count);
    
    printf("\n========================================\n");
    printf("              COMPLETE                  \n");
    printf("========================================\n\n");
    
    return 0;
}
```
