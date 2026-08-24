# ============================================================
# SYSTEMS STACK: C, C++, EMBEDDED
# Complete Makefile with Exercises Integration
# ============================================================

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -O2
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

BIN_DIR = bin
$(shell mkdir -p $(BIN_DIR))

.PHONY: all clean

all: menu

# ============================================================
# MAIN MENU
# ============================================================

menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SYSTEMS STACK: C, C++, EMBEDDED"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. C Language"
	@echo "  2. C++ Language"
	@echo "  3. Embedded Baremetal"
	@echo "  4. Exercises"
	@echo "  5. Clean"
	@echo "  0. Exit"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) c_menu ;; \
		2) $(MAKE) cpp_menu ;; \
		3) $(MAKE) embedded_menu ;; \
		4) $(MAKE) exercises_menu ;; \
		5) $(MAKE) clean ;; \
		0) exit 0 ;; \
		*) $(MAKE) menu ;; \
	esac

# ============================================================
# C LANGUAGE MENU
# ============================================================

c_menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   C LANGUAGE"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Pointers"
	@echo "  2. Memory"
	@echo "  3. Bitwise"
	@echo "  4. Preprocessor"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) c_pointers ;; \
		2) $(MAKE) c_memory ;; \
		3) $(MAKE) c_bitwise ;; \
		4) $(MAKE) c_preprocessor ;; \
		0) $(MAKE) menu ;; \
	esac

# ------------------------------------------------------------
# C - POINTERS
# ------------------------------------------------------------

c_pointers:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   POINTERS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  A pointer stores a memory address."
	@echo ""
	@echo "  *ptr  - Get value at address"
	@echo "  &var  - Get address of variable"
	@echo "  ptr++ - Move to next element"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Pointer Arithmetic Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_ptr_arith ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   POINTERS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 01-c-language/pointers/README.md; \
			$(MAKE) c_pointers ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_ptr_arith:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   POINTER ARITHMETIC - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/ptr_arith 01-c-language/pointers/pointer_arithmetic.c && ./$(BIN_DIR)/ptr_arith
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) c_pointers

# ------------------------------------------------------------
# C - MEMORY
# ------------------------------------------------------------

c_memory:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MEMORY MANAGEMENT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Memory Layout: Stack, Heap, Data, BSS, Text"
	@echo ""
	@echo "  Stack - Local variables (fast, limited)"
	@echo "  Heap  - Dynamic allocation (malloc/free)"
	@echo "  Data  - Initialized globals/statics"
	@echo "  BSS   - Uninitialized globals/statics"
	@echo "  Text  - Code (read-only)"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Memory Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_memory ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   MEMORY - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 01-c-language/memory/README.md; \
			$(MAKE) c_memory ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_memory:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MEMORY MANAGEMENT - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/memory 01-c-language/memory/memory.c && ./$(BIN_DIR)/memory
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) c_memory

# ------------------------------------------------------------
# C - BITWISE
# ------------------------------------------------------------

c_bitwise:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   BITWISE OPERATIONS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  &  AND    - Clear bits"
	@echo "  |  OR     - Set bits"
	@echo "  ^  XOR    - Toggle bits"
	@echo "  ~  NOT    - Invert bits"
	@echo "  << LEFT   - Shift left (multiply by 2)"
	@echo "  >> RIGHT  - Shift right (divide by 2)"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Bitwise Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_bitwise ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   BITWISE - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 01-c-language/bitwise/README.md; \
			$(MAKE) c_bitwise ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_bitwise:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   BITWISE OPERATIONS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/bitwise 01-c-language/bitwise/bitwise.c && ./$(BIN_DIR)/bitwise
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) c_bitwise

# ------------------------------------------------------------
# C - PREPROCESSOR
# ------------------------------------------------------------

c_preprocessor:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   PREPROCESSOR"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Runs BEFORE compilation"
	@echo ""
	@echo "  #include  - File inclusion"
	@echo "  #define   - Macros"
	@echo "  #ifdef    - Conditional compilation"
	@echo "  #pragma   - Compiler directives"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Preprocessor Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_preprocessor ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   PREPROCESSOR - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 01-c-language/preprocessor/README.md; \
			$(MAKE) c_preprocessor ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_preprocessor:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   PREPROCESSOR - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/preprocessor 01-c-language/preprocessor/preprocessor.c && ./$(BIN_DIR)/preprocessor
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) c_preprocessor

# ============================================================
# C++ LANGUAGE MENU
# ============================================================

cpp_menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   C++ LANGUAGE"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Move Semantics"
	@echo "  2. Smart Pointers"
	@echo "  3. Templates"
	@echo "  4. Lambdas"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) cpp_move ;; \
		2) $(MAKE) cpp_smart ;; \
		3) $(MAKE) cpp_templates ;; \
		4) $(MAKE) cpp_lambdas ;; \
		0) $(MAKE) menu ;; \
	esac

# ------------------------------------------------------------
# C++ - MOVE SEMANTICS
# ------------------------------------------------------------

cpp_move:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MOVE SEMANTICS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Move transfers ownership (cheap)"
	@echo "  Copy duplicates data (expensive)"
	@echo ""
	@echo "  && - Rvalue reference"
	@echo "  std::move() - Convert to rvalue"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Move Semantics Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_move ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   MOVE SEMANTICS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 02-cpp-language/move-semantics/README.md; \
			$(MAKE) cpp_move ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_move:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MOVE SEMANTICS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/move 02-cpp-language/move-semantics/move_semantics.cpp && ./$(BIN_DIR)/move
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) cpp_move

# ------------------------------------------------------------
# C++ - SMART POINTERS
# ------------------------------------------------------------

cpp_smart:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SMART POINTERS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  unique_ptr  - Exclusive ownership (cannot copy)"
	@echo "  shared_ptr  - Shared ownership (reference counted)"
	@echo "  weak_ptr    - Non-owning observer (breaks cycles)"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Smart Pointers Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_smart ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   SMART POINTERS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 02-cpp-language/smart-pointers/README.md; \
			$(MAKE) cpp_smart ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_smart:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SMART POINTERS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/smart 02-cpp-language/smart-pointers/smart_pointers.cpp && ./$(BIN_DIR)/smart
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) cpp_smart

# ------------------------------------------------------------
# C++ - TEMPLATES
# ------------------------------------------------------------

cpp_templates:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TEMPLATES"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Code that works with ANY type"
	@echo ""
	@echo "  template<typename T>"
	@echo "  T max(T a, T b) { return (a>b)?a:b; }"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Templates Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_templates ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   TEMPLATES - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 02-cpp-language/templates/README.md; \
			$(MAKE) cpp_templates ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_templates:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TEMPLATES - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/templates 02-cpp-language/templates/templates.cpp && ./$(BIN_DIR)/templates
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) cpp_templates

# ------------------------------------------------------------
# C++ - LAMBDAS
# ------------------------------------------------------------

cpp_lambdas:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   LAMBDAS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  [capture](parameters) -> return_type { body }"
	@echo ""
	@echo "  auto add = [](int a, int b) { return a+b; }"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Lambdas Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_lambdas ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   LAMBDAS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 02-cpp-language/lambdas/README.md; \
			$(MAKE) cpp_lambdas ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_lambdas:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   LAMBDAS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/lambdas 02-cpp-language/lambdas/lambdas.cpp && ./$(BIN_DIR)/lambdas
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) cpp_lambdas

# ============================================================
# EMBEDDED BAREMETAL MENU
# ============================================================

embedded_menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   EMBEDDED BAREMETAL"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Interrupts"
	@echo "  2. GPIO"
	@echo "  3. Timers"
	@echo "  4. Communication"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) embedded_interrupts ;; \
		2) $(MAKE) embedded_gpio ;; \
		3) $(MAKE) embedded_timers ;; \
		4) $(MAKE) embedded_comms ;; \
		0) $(MAKE) menu ;; \
	esac

# ------------------------------------------------------------
# EMBEDDED - INTERRUPTS
# ------------------------------------------------------------

embedded_interrupts:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   INTERRUPTS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Hardware signals that pause CPU execution"
	@echo ""
	@echo "  • Vector Table - List of ISR addresses"
	@echo "  • ISR - Interrupt Service Routine"
	@echo "  • NVIC - Nested Vectored Interrupt Controller"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Interrupts Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_interrupts ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   INTERRUPTS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 03-embedded-baremetal/interrupts/README.md; \
			$(MAKE) embedded_interrupts ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_interrupts:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   INTERRUPTS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/interrupts 03-embedded-baremetal/interrupts/interrupts.c && ./$(BIN_DIR)/interrupts
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) embedded_interrupts

# ------------------------------------------------------------
# EMBEDDED - GPIO
# ------------------------------------------------------------

embedded_gpio:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   GPIO (General Purpose Input/Output)"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  Registers:"
	@echo "  • MODER  - Mode (Input/Output/Alternate/Analog)"
	@echo "  • ODR    - Output Data Register"
	@echo "  • IDR    - Input Data Register"
	@echo "  • BSRR   - Bit Set/Reset Register (atomic)"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run GPIO Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_gpio ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   GPIO - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 03-embedded-baremetal/gpio/README.md; \
			$(MAKE) embedded_gpio ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_gpio:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   GPIO - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/gpio 03-embedded-baremetal/gpio/gpio.c && ./$(BIN_DIR)/gpio
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) embedded_gpio

# ------------------------------------------------------------
# EMBEDDED - TIMERS
# ------------------------------------------------------------

embedded_timers:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TIMERS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  • SysTick   - System tick timer"
	@echo "  • General Purpose - PWM, Input Capture"
	@echo "  • Watchdog  - System reset if not fed"
	@echo "  • RTC       - Real Time Clock"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Timers Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_timers ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   TIMERS - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 03-embedded-baremetal/timers/README.md; \
			$(MAKE) embedded_timers ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_timers:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TIMERS - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/timers 03-embedded-baremetal/timers/timers.c && ./$(BIN_DIR)/timers
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) embedded_timers

# ------------------------------------------------------------
# EMBEDDED - COMMUNICATION
# ------------------------------------------------------------

embedded_comms:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   COMMUNICATION PROTOCOLS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  • UART - Asynchronous, point-to-point"
	@echo "  • SPI  - Synchronous, full-duplex, multiple slaves"
	@echo "  • I2C  - Two-wire, multi-master, multi-slave"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Communication Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_comms ;; \
		2) \
			clear; \
			echo "═══════════════════════════════════════════"; \
			echo "   COMMUNICATION - README (Press q to exit less)"; \
			echo "═══════════════════════════════════════════"; \
			echo ""; \
			less -R 03-embedded-baremetal/communication/README.md; \
			$(MAKE) embedded_comms ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_comms:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   COMMUNICATION - OUTPUT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/comms 03-embedded-baremetal/communication/communication.c && ./$(BIN_DIR)/comms
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) embedded_comms

# ============================================================
# EXERCISES MENU
# ============================================================

exercises_menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   EXERCISES & CHALLENGES"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Challenge 01: Pointers (Swap two numbers)"
	@echo "  2. Challenge 02: Bitwise (Count set bits)"
	@echo "  3. Challenge 03: Move Semantics (String class)"
	@echo "  4. Challenge 04: GPIO (LED blink with timer)"
	@echo "  5. View All Solutions"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_challenge1 ;; \
		2) $(MAKE) run_challenge2 ;; \
		3) $(MAKE) run_challenge3 ;; \
		4) $(MAKE) run_challenge4 ;; \
		5) $(MAKE) view_solutions ;; \
		0) $(MAKE) menu ;; \
	esac

# ------------------------------------------------------------
# CHALLENGE 1
# ------------------------------------------------------------

run_challenge1:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 01: POINTER SWAP"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Swap two numbers using pointers"
	@echo "File: exercises/solutions/solution_01_pointers.c"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge1 exercises/solutions/solution_01_pointers.c && ./$(BIN_DIR)/challenge1
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) exercises_menu

# ------------------------------------------------------------
# CHALLENGE 2
# ------------------------------------------------------------

run_challenge2:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 02: COUNT SET BITS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Count number of 1 bits using bitwise operations"
	@echo "File: exercises/solutions/solution_02_bitwise.c"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge2 exercises/solutions/solution_02_bitwise.c && ./$(BIN_DIR)/challenge2
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) exercises_menu

# ------------------------------------------------------------
# CHALLENGE 3
# ------------------------------------------------------------

run_challenge3:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 03: MOVE SEMANTICS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Implement String class with move semantics"
	@echo "File: exercises/solutions/solution_03_move_semantics.cpp"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/challenge3 exercises/solutions/solution_03_move_semantics.cpp && ./$(BIN_DIR)/challenge3
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) exercises_menu

# ------------------------------------------------------------
# CHALLENGE 4
# ------------------------------------------------------------

run_challenge4:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 04: LED BLINK WITH TIMER"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Blink LED using timer interrupt (no delay loops)"
	@echo "File: exercises/solutions/solution_04_gpio.c"
	@echo ""
	@echo "═══════════════════════════════════════════"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge4 exercises/solutions/solution_04_gpio.c && ./$(BIN_DIR)/challenge4
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) exercises_menu

# ------------------------------------------------------------
# VIEW SOLUTIONS
# ------------------------------------------------------------

view_solutions:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SOLUTIONS DIRECTORY"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Available solutions:"
	@echo "─────────────────────────────────────────────"
	@ls -la exercises/solutions/
	@echo ""
	@echo "─────────────────────────────────────────────"
	@echo ""
	@echo "To view a solution file:"
	@echo "  cat exercises/solutions/solution_01_pointers.c"
	@echo "  cat exercises/solutions/solution_02_bitwise.c"
	@echo "  cat exercises/solutions/solution_03_move_semantics.cpp"
	@echo "  cat exercises/solutions/solution_04_gpio.c"
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) exercises_menu

# ============================================================
# CLEAN
# ============================================================

clean:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CLEANING BINARIES"
	@echo "═══════════════════════════════════════════"
	@echo ""
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)
	@echo "  ✓ All binaries cleaned!"
	@echo ""
	@read -p "  Press Enter to continue..." dummy
	@$(MAKE) menu
