# MEMORY MANAGEMENT IN C

## What is Memory Management?

Memory management refers to how a C program organizes and uses computer memory. Understanding memory layout is crucial for writing efficient and bug-free code.

## Memory Layout of a C Program

HIGH ADDRESS
┌─────────────────────────────────┐
│ STACK │
│ ┌─────────────────────────┐ │
│ │ Local variables │ │
│ │ Function parameters │ │
│ │ Return addresses │ │
│ │ Grows DOWNWARD │ │
│ └─────────────────────────┘ │
│ ↓ │
│ │
│ ↑ │
│ ┌─────────────────────────┐ │
│ │ HEAP │ │
│ │ Dynamic allocation │ │
│ │ malloc() / calloc() │ │
│ │ free() │ │
│ │ Grows UPWARD │ │
│ └─────────────────────────┘ │
├─────────────────────────────────┤
│ BSS │
│ Uninitialized global/static │
│ Automatically set to ZERO │
├─────────────────────────────────┤
│ DATA │
│ Initialized global/static │
│ Set at compile time │
├─────────────────────────────────┤
│ TEXT │
│ Program code (machine code) │
│ Read-only constants │
└─────────────────────────────────┘
LOW ADDRESS
text


## Memory Segments

| Segment | What it stores | Lifetime | Example |
|---------|---------------|----------|---------|
| **STACK** | Local variables, function calls | Function scope | `int x = 10;` |
| **HEAP** | Dynamically allocated memory | Until `free()` | `malloc(100)` |
| **DATA** | Initialized globals/statics | Program lifetime | `int g = 5;` |
| **BSS** | Uninitialized globals/statics (zeroed) | Program lifetime | `int g;` |
| **TEXT** | Code, constants | Program lifetime | `const char* s = "hi"` |

## Stack Memory

### Characteristics
- **Automatic** allocation/deallocation
- **Fast** access (just move stack pointer)
- **Limited** size (typically 1-8 MB)
- **LIFO** (Last In First Out) order

### What goes on Stack?
```c
void function(int param) {     // param on stack
    int local = 10;             // local variable on stack
    int arr[100];               // array on stack
    // DO NOT return &local      // dangerous!
}

Stack Frame
text

When function is called:
┌─────────────────────────┐ HIGH
│   Previous stack frame  │
├─────────────────────────┤
│   Return address        │
├─────────────────────────┤
│   Function parameters   │
├─────────────────────────┤
│   Local variables       │
├─────────────────────────┤
│   Saved registers       │
└─────────────────────────┘ LOW
    ↑
  Stack pointer

Heap Memory
Characteristics

    Manual allocation (malloc/free)

    Slower than stack

    Large size (up to RAM limit)

    Persistent until freed

Heap Functions
Function	Purpose	Example
malloc(n)	Allocate n bytes	int *p = malloc(4);
calloc(count, size)	Allocate and zero	calloc(10, sizeof(int))
realloc(ptr, new_size)	Resize allocation	realloc(p, 8)
free(ptr)	Deallocate memory	free(p)
Heap Allocation Example
c

int *ptr = malloc(sizeof(int));
if(ptr == NULL) {
    // Handle allocation failure
}
*ptr = 100;
// ... use ptr
free(ptr);
ptr = NULL;  // Prevent dangling pointer

Stack vs Heap Comparison
Feature	Stack	Heap
Allocation	Automatic	Manual (malloc/free)
Speed	Very fast	Slow
Size	Limited (MB)	Large (GB)
Lifetime	Function scope	Until freed
Memory fragmentation	No	Yes
Access	Direct	Through pointers
When to use	Small, fixed size	Large, dynamic size
Static Storage (DATA & BSS)
Characteristics

    Program lifetime (exists from start to end)

    Initialized once

    Thread-safe (in single thread)

Types
c

// DATA segment (initialized)
int global_init = 100;
static int static_init = 200;

// BSS segment (zero-initialized)
int global_uninit;
static int static_uninit;

void function() {
    static int count = 0;  // DATA (initialized only once)
    count++;
}

Common Memory Issues
Issue	Description	Example
Memory Leak	Forgetting to free heap memory	malloc() without free()
Dangling Pointer	Using freed memory	free(p); *p = 10;
Buffer Overflow	Writing beyond array bounds	arr[10] but size is 5
Stack Overflow	Too much stack usage	Recursion too deep
Double Free	Freeing same memory twice	free(p); free(p);
Use After Free	Accessing freed memory	free(p); printf("%d", *p);
Best Practices
DO ✓
c

// Always check malloc return
int *p = malloc(size);
if(p == NULL) {
    // Handle error
}

// Always free heap memory
free(p);
p = NULL;

// Use sizeof for portability
int *arr = malloc(10 * sizeof(int));

// Prefer stack for small arrays
int small_arr[100];

DON'T ✗
c

// Don't return stack addresses
int* bad_function() {
    int x = 10;
    return &x;  // Dangling pointer!
}

// Don't forget to free
int *p = malloc(100);
// ... use p
// Missing free() → memory leak

// Don't access out of bounds
int arr[5];
arr[10] = 100;  // Buffer overflow

Memory Layout Example
c

#include <stdio.h>
#include <stdlib.h>

int data = 10;           // DATA
int bss;                 // BSS

int main() {
    int stack = 20;      // STACK
    int *heap = malloc(sizeof(int));  // HEAP
    *heap = 30;
    
    printf("Data: %p\n", &data);
    printf("BSS:  %p\n", &bss);
    printf("Text: %p\n", main);
    printf("Stack:%p\n", &stack);
    printf("Heap: %p\n", heap);
    
    free(heap);
    return 0;
}

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 01-c-language/memory/memory.c -o memory
./memory

Key Takeaways

    Stack is fast but limited – use for local variables

    Heap is flexible but slower – use for dynamic/large data

    Always free heap memory – prevent memory leaks

    Never return stack addresses – they become invalid

    Check malloc return value – it can fail

    Set freed pointers to NULL – prevent dangling pointers
