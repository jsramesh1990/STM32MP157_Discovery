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
		2) cat 01-c-language/pointers/README.md | less ;; \
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
	@read -p "  Press Enter..." dummy
	@$(MAKE) c_pointers

c_memory:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MEMORY MANAGEMENT"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Memory Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_memory ;; \
		2) cat 01-c-language/memory/README.md | less ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_memory:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/memory 01-c-language/memory/memory.c && ./$(BIN_DIR)/memory
	@read -p "  Press Enter..." dummy
	@$(MAKE) c_memory

c_bitwise:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   BITWISE OPERATIONS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Bitwise Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_bitwise ;; \
		2) cat 01-c-language/bitwise/README.md | less ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_bitwise:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/bitwise 01-c-language/bitwise/bitwise.c && ./$(BIN_DIR)/bitwise
	@read -p "  Press Enter..." dummy
	@$(MAKE) c_bitwise

c_preprocessor:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   PREPROCESSOR"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Preprocessor Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_preprocessor ;; \
		2) cat 01-c-language/preprocessor/README.md | less ;; \
		0) $(MAKE) c_menu ;; \
	esac

run_preprocessor:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/preprocessor 01-c-language/preprocessor/preprocessor.c && ./$(BIN_DIR)/preprocessor
	@read -p "  Press Enter..." dummy
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

cpp_move:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   MOVE SEMANTICS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Move Semantics Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_move ;; \
		2) cat 02-cpp-language/move-semantics/README.md | less ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_move:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/move 02-cpp-language/move-semantics/move_semantics.cpp && ./$(BIN_DIR)/move
	@read -p "  Press Enter..." dummy
	@$(MAKE) cpp_move

cpp_smart:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SMART POINTERS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Smart Pointers Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_smart ;; \
		2) cat 02-cpp-language/smart-pointers/README.md | less ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_smart:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/smart 02-cpp-language/smart-pointers/smart_pointers.cpp && ./$(BIN_DIR)/smart
	@read -p "  Press Enter..." dummy
	@$(MAKE) cpp_smart

cpp_templates:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TEMPLATES"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Templates Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_templates ;; \
		2) cat 02-cpp-language/templates/README.md | less ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_templates:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/templates 02-cpp-language/templates/templates.cpp && ./$(BIN_DIR)/templates
	@read -p "  Press Enter..." dummy
	@$(MAKE) cpp_templates

cpp_lambdas:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   LAMBDAS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Lambdas Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_lambdas ;; \
		2) cat 02-cpp-language/lambdas/README.md | less ;; \
		0) $(MAKE) cpp_menu ;; \
	esac

run_lambdas:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/lambdas 02-cpp-language/lambdas/lambdas.cpp && ./$(BIN_DIR)/lambdas
	@read -p "  Press Enter..." dummy
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

embedded_interrupts:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   INTERRUPTS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Interrupts Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_interrupts ;; \
		2) cat 03-embedded-baremetal/interrupts/README.md | less ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_interrupts:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/interrupts 03-embedded-baremetal/interrupts/interrupts.c && ./$(BIN_DIR)/interrupts
	@read -p "  Press Enter..." dummy
	@$(MAKE) embedded_interrupts

embedded_gpio:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   GPIO"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run GPIO Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_gpio ;; \
		2) cat 03-embedded-baremetal/gpio/README.md | less ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_gpio:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/gpio 03-embedded-baremetal/gpio/gpio.c && ./$(BIN_DIR)/gpio
	@read -p "  Press Enter..." dummy
	@$(MAKE) embedded_gpio

embedded_timers:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   TIMERS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Timers Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_timers ;; \
		2) cat 03-embedded-baremetal/timers/README.md | less ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_timers:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/timers 03-embedded-baremetal/timers/timers.c && ./$(BIN_DIR)/timers
	@read -p "  Press Enter..." dummy
	@$(MAKE) embedded_timers

embedded_comms:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   COMMUNICATION"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Run Communication Demo"
	@echo "  2. View README"
	@echo "  0. Back"
	@echo ""
	@read -p "  Select: " opt; \
	case $$opt in \
		1) $(MAKE) run_comms ;; \
		2) cat 03-embedded-baremetal/communication/README.md | less ;; \
		0) $(MAKE) embedded_menu ;; \
	esac

run_comms:
	@clear
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/comms 03-embedded-baremetal/communication/communication.c && ./$(BIN_DIR)/comms
	@read -p "  Press Enter..." dummy
	@$(MAKE) embedded_comms

# ============================================================
# EXERCISES MENU (NEW)
# ============================================================

exercises_menu:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   EXERCISES & CHALLENGES"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "  1. Challenge 01: Pointers (Swap)"
	@echo "  2. Challenge 02: Bitwise (Count Set Bits)"
	@echo "  3. Challenge 03: Move Semantics (String Class)"
	@echo "  4. Challenge 04: GPIO (LED Blink with Timer)"
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

run_challenge1:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 01: POINTER SWAP"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Swap two numbers using pointers"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge1 exercises/solutions/solution_01_pointers.c && ./$(BIN_DIR)/challenge1
	@echo ""
	@echo "View the code: exercises/solutions/solution_01_pointers.c"
	@echo ""
	@read -p "  Press Enter..." dummy
	@$(MAKE) exercises_menu

run_challenge2:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 02: COUNT SET BITS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Count number of 1 bits using bitwise operations"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge2 exercises/solutions/solution_02_bitwise.c && ./$(BIN_DIR)/challenge2
	@echo ""
	@echo "View the code: exercises/solutions/solution_02_bitwise.c"
	@echo ""
	@read -p "  Press Enter..." dummy
	@$(MAKE) exercises_menu

run_challenge3:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 03: MOVE SEMANTICS"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Implement String class with move semantics"
	@echo ""
	@$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/challenge3 exercises/solutions/solution_03_move_semantics.cpp && ./$(BIN_DIR)/challenge3
	@echo ""
	@echo "View the code: exercises/solutions/solution_03_move_semantics.cpp"
	@echo ""
	@read -p "  Press Enter..." dummy
	@$(MAKE) exercises_menu

run_challenge4:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   CHALLENGE 04: LED BLINK WITH TIMER"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@echo "Problem: Blink LED using timer interrupt (no delay loops)"
	@echo ""
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/challenge4 exercises/solutions/solution_04_gpio.c && ./$(BIN_DIR)/challenge4
	@echo ""
	@echo "View the code: exercises/solutions/solution_04_gpio.c"
	@echo ""
	@read -p "  Press Enter..." dummy
	@$(MAKE) exercises_menu

view_solutions:
	@clear
	@echo "═══════════════════════════════════════════"
	@echo "   SOLUTIONS DIRECTORY"
	@echo "═══════════════════════════════════════════"
	@echo ""
	@ls -la exercises/solutions/
	@echo ""
	@echo "Solutions available:"
	@echo "  - solution_01_pointers.c"
	@echo "  - solution_02_bitwise.c"
	@echo "  - solution_03_move_semantics.cpp"
	@echo "  - solution_04_gpio.c"
	@echo ""
	@echo "View with: cat exercises/solutions/<filename>"
	@echo ""
	@read -p "  Press Enter..." dummy
	@$(MAKE) exercises_menu

# ============================================================
# CLEAN
# ============================================================

clean:
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)
	@echo "  Cleaned all binaries!"
	@sleep 1
	@$(MAKE) menu
