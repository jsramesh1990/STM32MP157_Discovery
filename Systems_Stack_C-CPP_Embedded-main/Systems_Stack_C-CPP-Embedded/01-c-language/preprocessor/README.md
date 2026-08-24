# PREPROCESSOR

## What is Preprocessor?

The preprocessor runs BEFORE compilation. It processes directives that start with `#` and prepares the code for the compiler.

## Preprocessor Directives

| Directive | Purpose | Example |
|-----------|---------|---------|
| `#include` | Insert file contents | `#include <stdio.h>` |
| `#define` | Create macro | `#define PI 3.14` |
| `#undef` | Remove macro | `#undef PI` |
| `#ifdef` | If macro defined | `#ifdef DEBUG` |
| `#ifndef` | If macro not defined | `#ifndef HEADER_H` |
| `#if` | Conditional compilation | `#if VALUE > 10` |
| `#else` | Alternative | `#else` |
| `#elif` | Else if | `#elif VALUE == 5` |
| `#endif` | End conditional | `#endif` |
| `#error` | Show error | `#error "Invalid"` |
| `#pragma` | Compiler specific | `#pragma once` |

## How Preprocessor Works

Source Code After Preprocessor
─────────────────────────────────────────────────────

#include <stdio.h> → (entire stdio.h content)

#define MAX 100 → (removed)

int arr[MAX]; → int arr[100];

#define SQUARE(x) ((x)*(x))

int y = SQUARE(5); → int y = ((5)*(5));

#ifdef DEBUG
printf("Debug"); → (if DEBUG defined, keep)
#endif (if not defined, remove)
text


## Macros Syntax

```c
// Object-like macro
#define NAME value

// Function-like macro
#define MACRO_NAME(parameters) (expression)

// Multi-line macro
#define MACRO do { \
    statement1; \
    statement2; \
} while(0)

Common Macros Examples
Macro	Code	After Expansion
Constant	#define PI 3.14159	PI → 3.14159
Expression	#define AREA(r) (PI*(r)*(r))	AREA(5) → (3.14159*(5)*(5))
Stringize	#define STR(x) #x	STR(test) → "test"
Concatenation	#define CONCAT(a,b) a##b	CONCAT(var,1) → var1
Conditional Compilation
c

#define VERSION 2

#if VERSION == 1
    printf("Version 1\n");
#elif VERSION == 2
    printf("Version 2\n");
#else
    printf("Unknown version\n");
#endif

Header Guards
c

#ifndef HEADER_FILE_H
#define HEADER_FILE_H

// Header content here

#endif

Predefined Macros
Macro	Description	Example Output
__FILE__	Current file name	"program.c"
__LINE__	Current line number	42
__DATE__	Compilation date	"Jan 1 2024"
__TIME__	Compilation time	"12:00:00"
__STDC__	ANSI C standard	1
X-Macros Technique
c

// Define data once
#define COLORS \
    X(RED, 1)   \
    X(GREEN, 2) \
    X(BLUE, 3)

// Create enum
#define X(name, val) name = val,
enum { COLORS };
#undef X

// Create string array
#define X(name, val) #name,
const char* color_names[] = { COLORS };
#undef X

Common Mistakes
Wrong	Correct
#define SQUARE(x) x*x	#define SQUARE(x) ((x)*(x))
#define MAX = 100	#define MAX 100
Missing #endif	Always close with #endif
Space after #define	No space: #define MACRO value
Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 01-c-language/preprocessor/preprocessor.c -o preprocessor
./preprocessor

# See preprocessor output
gcc -E 01-c-language/preprocessor/preprocessor.c

Key Takeaways

    Preprocessor runs before compilation

    Macros are text substitution (not functions)

    Always use parentheses in function-like macros

    Header guards prevent double inclusion

    X-macros keep data in one place
