#  Systems Stack: C, C++, Embedded

## *From Source Code to Silicon - A Complete Learning Repository*

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C](https://img.shields.io/badge/C-11+-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![Embedded](https://img.shields.io/badge/Embedded-ARM%2C%20AVR-red)](https://github.com/yourname/Systems_Stack_C-CPP-Embedded)
[![Makefile](https://img.shields.io/badge/Makefile-Supported-green)](https://www.gnu.org/software/make/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20WSL-blue)]()

---

##  About This Repository

This repository provides a **complete, hands-on learning experience** for systems programming covering:

| Layer | Topics |
|-------|--------|
| **C Language** | Pointers, Memory Management, Bitwise Operations, Preprocessor |
| **C++ Language** | Move Semantics, Smart Pointers, Templates, Lambdas |
| **Embedded Systems** | Interrupts, GPIO, Timers, Communication (UART/SPI/I2C) |
| **Exercises** | 4 Practical Challenges with Solutions |

Each topic includes:
- ✅ **Detailed README** with theory, syntax, diagrams
- ✅ **Working Code** ready to compile and run
- ✅ **Interactive Makefile** for easy navigation
- ✅ **Exercises** to test your understanding

---

##  Systems Stack - Visual Representation

```
┌─────────────────────────────────────────────────────────────────────┐
│                         APPLICATION LAYER                           │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   ┌─────────────────────────────────────────────────────────────┐   │
│   │                      C++ LANGUAGE                            │   │
│   │   Move Semantics │ Smart Pointers │ Templates │ Lambdas      │   │
│   └─────────────────────────────────────────────────────────────┘   │
│                                    │                                 │
│                                    ▼                                 │
│   ┌─────────────────────────────────────────────────────────────┐   │
│   │                       C LANGUAGE                            │   │
│   │   Pointers │ Memory │ Bitwise │ Preprocessor                │   │
│   └─────────────────────────────────────────────────────────────┘   │
│                                    │                                 │
│                                    ▼                                 │
│   ┌─────────────────────────────────────────────────────────────┐   │
│   │                    EMBEDDED BAREMETAL                        │   │
│   │   Interrupts │ GPIO │ Timers │ UART/SPI/I2C                 │   │
│   └─────────────────────────────────────────────────────────────┘   │
│                                    │                                 │
│                                    ▼                                 │
│   ┌─────────────────────────────────────────────────────────────┐   │
│   │                         HARDWARE                             │   │
│   │              ARM Cortex-M / AVR / RISC-V                     │   │
│   └─────────────────────────────────────────────────────────────┘   │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

---

##  Project Structure

```
Systems_Stack_C-CPP-Embedded/
│
├── README.md                          # This file
├── Makefile                           # Interactive menu system
├── LICENSE                            # MIT License
│
├── 01-c-language/
│   ├── pointers/
│   │   ├── README.md                  # Theory + diagrams + syntax
│   │   └── pointer_arithmetic.c       # Working code
│   ├── memory/
│   │   ├── README.md
│   │   └── memory.c
│   ├── bitwise/
│   │   ├── README.md
│   │   └── bitwise.c
│   └── preprocessor/
│       ├── README.md
│       └── preprocessor.c
│
├── 02-cpp-language/
│   ├── move-semantics/
│   │   ├── README.md
│   │   └── move_semantics.cpp
│   ├── smart-pointers/
│   │   ├── README.md
│   │   └── smart_pointers.cpp
│   ├── templates/
│   │   ├── README.md
│   │   └── templates.cpp
│   └── lambdas/
│       ├── README.md
│       └── lambdas.cpp
│
├── 03-embedded-baremetal/
│   ├── interrupts/
│   │   ├── README.md
│   │   └── interrupts.c
│   ├── gpio/
│   │   ├── README.md
│   │   └── gpio.c
│   ├── timers/
│   │   ├── README.md
│   │   └── timers.c
│   └── communication/
│       ├── README.md
│       └── communication.c
│
├── exercises/
│   ├── challenges/
│   │   └── README.md                  # Challenge descriptions
│   └── solutions/
│       ├── solution_01_pointers.c
│       ├── solution_02_bitwise.c
│       ├── solution_03_move_semantics.cpp
│       └── solution_04_gpio.c
│
└── bin/                               # Compiled binaries (auto-created)
```

---

##  Quick Start

### Prerequisites

| Tool | Version | Check Command |
|------|---------|---------------|
| GCC | 4.8+ | `gcc --version` |
| G++ | 4.8+ | `g++ --version` |
| Make | 3.8+ | `make --version` |

### Installation

```bash
# Clone the repository
git clone https://github.com/yourname/Systems_Stack_C-CPP-Embedded.git
cd Systems_Stack_C-CPP-Embedded

# Build everything
make all

# Start interactive menu
make menu
```

---

##  Interactive Menu Flow

```
                    ┌─────────────────────────────────────┐
                    │           MAIN MENU                  │
                    │  1. C Language                       │
                    │  2. C++ Language                     │
                    │  3. Embedded Baremetal               │
                    │  4. Exercises                        │
                    │  5. Clean                            │
                    │  0. Exit                             │
                    └─────────────────────────────────────┘
                                    │
            ┌───────────────────────┼───────────────────────┐
            │                       │                       │
            ▼                       ▼                       ▼
    ┌───────────────┐       ┌───────────────┐       ┌───────────────┐
    │  C LANGUAGE   │       │  C++ LANGUAGE │       │   EMBEDDED    │
    ├───────────────┤       ├───────────────┤       ├───────────────┤
    │ 1. Pointers   │       │ 1. Move       │       │ 1. Interrupts │
    │ 2. Memory     │       │ 2. Smart Ptr  │       │ 2. GPIO       │
    │ 3. Bitwise    │       │ 3. Templates  │       │ 3. Timers     │
    │ 4. Preprocessor│      │ 4. Lambdas    │       │ 4. Comm       │
    └───────────────┘       └───────────────┘       └───────────────┘
            │                       │                       │
            ▼                       ▼                       ▼
    ┌───────────────┐       ┌───────────────┐       ┌───────────────┐
    │  TOPIC MENU   │       │  TOPIC MENU   │       │  TOPIC MENU   │
    ├───────────────┤       ├───────────────┤       ├───────────────┤
    │ 1. Run Code   │       │ 1. Run Code   │       │ 1. Run Code   │
    │ 2. View README│       │ 2. View README│       │ 2. View README│
    │ 0. Back       │       │ 0. Back       │       │ 0. Back       │
    └───────────────┘       └───────────────┘       └───────────────┘
            │                       │                       │
            ▼                       ▼                       ▼
    ┌───────────────┐       ┌───────────────┐       ┌───────────────┐
    │    OUTPUT     │       │    OUTPUT     │       │    OUTPUT     │
    │  Code runs    │       │  Code runs    │       │  Code runs    │
    │  Shows:       │       │  Shows:       │       │  Shows:       │
    │  - Explanation│       │  - Explanation│       │  - Explanation│
    │  - Code       │       │  - Code       │       │  - Code       │
    │  - Result     │       │  - Result     │       │  - Result     │
    └───────────────┘       └───────────────┘       └───────────────┘
```

---

##  Complete Working Flow

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           USER INTERACTION FLOW                             │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│   START                                                                      │
│     │                                                                        │
│     ▼                                                                        │
│   ┌─────────────────┐                                                        │
│   │  make menu      │  ← User runs this command                              │
│   └────────┬────────┘                                                        │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                         MAIN MENU DISPLAYED                          │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │     SYSTEMS STACK: C, C++, EMBEDDED                                 │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │    1. C Language                                                     │   │
│   │    2. C++ Language                                                   │   │
│   │    3. Embedded Baremetal                                             │   │
│   │    4. Exercises                                                      │   │
│   │    5. Clean                                                          │   │
│   │    0. Exit                                                           │   │
│   └────────┬────────────────────────────────────────────────────────────┘   │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────┐                                                        │
│   │  User selects 1 │  ← C Language                                         │
│   └────────┬────────┘                                                        │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                         C MENU DISPLAYED                             │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │        C LANGUAGE                                                    │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │    1. Pointers                                                       │   │
│   │    2. Memory                                                         │   │
│   │    3. Bitwise                                                        │   │
│   │    4. Preprocessor                                                   │   │
│   │    0. Back                                                           │   │
│   └────────┬────────────────────────────────────────────────────────────┘   │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────┐                                                        │
│   │ User selects 1  │  ← Pointers                                           │
│   └────────┬────────┘                                                        │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                      POINTERS MENU DISPLAYED                         │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │        POINTERS - EXPLANATION                                        │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │    A pointer stores a memory address.                               │   │
│   │    *ptr - Get value at address                                      │   │
│   │    &var - Get address of variable                                   │   │
│   │    ptr++ - Move to next element                                     │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │    1. Run Code                                                       │   │
│   │    2. View README                                                    │   │
│   │    0. Back                                                           │   │
│   └────────┬────────────────────────────────────────────────────────────┘   │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────┐                                                        │
│   │ User selects 1  │  ← Run Code                                           │
│   └────────┬────────┘                                                        │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                      CODE EXECUTION                                  │   │
│   │  ═══════════════════════════════════════════                        │   │
│   │                                                                      │   │
│   │  1. Compiler (gcc) compiles the .c file                             │   │
│   │     ↓                                                               │   │
│   │  2. Binary created in bin/ directory                                │   │
│   │     ↓                                                               │   │
│   │  3. Binary executes                                                 │   │
│   │     ↓                                                               │   │
│   │  4. Output displayed on screen                                      │   │
│   │                                                                      │   │
│   │  OUTPUT:                                                             │   │
│   │  ========== POINTER ARITHMETIC DEMO ==========                      │   │
│   │  Array values: 10 20 30 40 50                                       │   │
│   │  *ptr = 10                                                          │   │
│   │  After ptr++: 20                                                    │   │
│   │  After ptr+=2: 40                                                   │   │
│   │  ========== COMPLETE ==========                                     │   │
│   │                                                                      │   │
│   └────────┬────────────────────────────────────────────────────────────┘   │
│            │                                                                 │
│            ▼                                                                 │
│   ┌─────────────────┐                                                        │
│   │  Press Enter    │  ← Returns to Pointers Menu                           │
│   └─────────────────┘                                                        │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

##  Topics Covered in Detail

### C Language

| Topic | README | Code | Key Concepts |
|-------|--------|------|--------------|
| **Pointers** | ✅ | ✅ | Pointer arithmetic, function pointers, double pointers, NULL pointers |
| **Memory** | ✅ | ✅ | Stack, heap, static storage, memory layout |
| **Bitwise** | ✅ | ✅ | AND/OR/XOR/NOT, shifts, bit manipulation, bit fields |
| **Preprocessor** | ✅ | ✅ | Macros, conditional compilation, X-macros |

### C++ Language

| Topic | README | Code | Key Concepts |
|-------|--------|------|--------------|
| **Move Semantics** | ✅ | ✅ | Lvalue/Rvalue, move constructor, std::move |
| **Smart Pointers** | ✅ | ✅ | unique_ptr, shared_ptr, weak_ptr |
| **Templates** | ✅ | ✅ | Function templates, class templates, specialization |
| **Lambdas** | ✅ | ✅ | Capture, mutable, generic lambdas |

### Embedded Baremetal

| Topic | README | Code | Key Concepts |
|-------|--------|------|--------------|
| **Interrupts** | ✅ | ✅ | Vector table, ISR, NVIC, priorities |
| **GPIO** | ✅ | ✅ | Registers (MODER, ODR, BSRR), push-pull, open-drain |
| **Timers** | ✅ | ✅ | Prescaler, auto-reload, PWM, watchdog |
| **Communication** | ✅ | ✅ | UART, SPI, I2C, baud rate, modes |

### Exercises

| Challenge | Topic | Solution | Difficulty |
|-----------|-------|----------|------------|
| #1: Pointer Swap | Pointers | ✅ | ⭐ Easy |
| #2: Count Set Bits | Bitwise | ✅ | ⭐⭐ Medium |
| #3: String Move | Move Semantics | ✅ | ⭐⭐ Medium |
| #4: LED Blink | Embedded | ✅ | ⭐⭐⭐ Hard |

---

##  Commands Reference

| Command | Description |
|---------|-------------|
| `make menu` | Start interactive menu |
| `make c_menu` | Go directly to C menu |
| `make cpp_menu` | Go directly to C++ menu |
| `make embedded_menu` | Go directly to Embedded menu |
| `make exercises_menu` | Go directly to Exercises |
| `make clean` | Remove all compiled binaries |
| `make all` | Build all examples |

### Direct Code Execution

```bash
# Run specific topics without menu
make run_ptr_arith      # Pointers demo
make run_memory         # Memory demo
make run_bitwise        # Bitwise demo
make run_move           # Move semantics demo
make run_smart          # Smart pointers demo
make run_interrupts     # Interrupts demo
make run_gpio           # GPIO demo

# Run challenges
make run_challenge1     # Pointers challenge
make run_challenge2     # Bitwise challenge
make run_challenge3     # Move semantics challenge
make run_challenge4     # GPIO challenge
```

---

##  Learning Path Recommendation

```
Week 1-2: C Language
    ├── Day 1-2: Pointers
    ├── Day 3-4: Memory Management
    ├── Day 5-6: Bitwise Operations
    └── Day 7: Preprocessor

Week 3-4: C++ Language
    ├── Day 1-2: Move Semantics
    ├── Day 3-4: Smart Pointers
    ├── Day 5: Templates
    └── Day 6-7: Lambdas

Week 5-6: Embedded Baremetal
    ├── Day 1-2: Interrupts
    ├── Day 3-4: GPIO
    ├── Day 5: Timers
    └── Day 6-7: Communication Protocols

Week 7: Exercises & Challenges
    ├── Complete all 4 challenges
    ├── Review solutions
    └── Build your own projects
```

---

##  Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

---

##  License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

##  Acknowledgments

- ARM Cortex-M Reference Manuals
- C++ Standard Committee Papers
- GNU Compiler Collection Documentation
- STM32 Reference Manuals

---

## ⭐ Star This Repository

If this repository helps you learn systems programming, please give it a star! ⭐

---

##  Repository Stats

```
═══════════════════════════════════════════════════════════════
   Topics: 4 Languages | 12 Modules | 4 Challenges
   Code: 12 C Files | 8 C++ Files | 2000+ Lines
   Documentation: 12 README Files | 200+ Pages Equivalent
═══════════════════════════════════════════════════════════════
```

---

**Happy Coding!** 
```
