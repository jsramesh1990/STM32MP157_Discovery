# BITWISE OPERATIONS

## What are Bitwise Operations?

Bitwise operations work directly on the binary representation of numbers at the bit level. They are essential for embedded programming, register manipulation, and performance-critical code.

## Bitwise Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| `&` | AND | `5 & 3` | `1` |
| `\|` | OR | `5 \| 3` | `7` |
| `^` | XOR | `5 ^ 3` | `6` |
| `~` | NOT | `~5` | `-6` |
| `<<` | Left Shift | `5 << 1` | `10` |
| `>>` | Right Shift | `5 >> 1` | `2` |

## Truth Tables

### AND (&)
| A | B | A & B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

### OR (|)
| A | B | A \| B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

### XOR (^)
| A | B | A ^ B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

### NOT (~)
| A | ~A |
|---|---|
| 0 | 1 |
| 1 | 0 |

## Common Bit Operations

| Operation | Formula | Example (8-bit) |
|-----------|---------|-----------------|
| Set bit n | `reg \|= (1 << n)` | `reg \|= (1 << 3)` → set bit 3 |
| Clear bit n | `reg &= ~(1 << n)` | `reg &= ~(1 << 3)` → clear bit 3 |
| Toggle bit n | `reg ^= (1 << n)` | `reg ^= (1 << 3)` → toggle bit 3 |
| Check bit n | `if(reg & (1 << n))` | `if(reg & (1 << 3))` → is bit 3 set? |
| Set multiple bits | `reg \|= (mask)` | `reg \|= (0x0F)` → set lower 4 bits |
| Clear multiple bits | `reg &= ~(mask)` | `reg &= ~(0x0F)` → clear lower 4 bits |

## Visual Examples

### Setting a Bit

Original: 0b10110010
Set bit 3: (1 << 3) = 0b00001000
OR operation: 0b10110010 | 0b00001000 = 0b10111010

1 0 1 1 0 0 1 0
OR 0 0 0 0 1 0 0 0
─────────────────
1 0 1 1 1 0 1 0
text


### Clearing a Bit

Original: 0b10111010
Clear bit 3: ~(1 << 3) = 0b11110111
AND operation: 0b10111010 & 0b11110111 = 0b10110010

1 0 1 1 1 0 1 0
AND 1 1 1 1 0 1 1 1
─────────────────
1 0 1 1 0 0 1 0
text


### Toggling a Bit

Original: 0b10110010
Toggle bit 3: (1 << 3) = 0b00001000
XOR operation: 0b10110010 ^ 0b00001000 = 0b10111010

1 0 1 1 0 0 1 0
XOR 0 0 0 0 1 0 0 0
─────────────────
1 0 1 1 1 0 1 0
text


## Shift Operations

### Left Shift (<<)

5 << 1 = 10

5 in binary: 0b00000101
Shift left 1: 0b00001010 = 10

Each left shift multiplies by 2
text


### Right Shift (>>)

5 >> 1 = 2

5 in binary: 0b00000101
Shift right 1: 0b00000010 = 2

Each right shift divides by 2 (integer division)
text


## Bit Masking Examples

```c
// Extract lower 4 bits
uint8_t value = 0xAB;        // 0b10101011
uint8_t lower = value & 0x0F; // 0b00001011 = 11

// Extract upper 4 bits
uint8_t upper = (value >> 4) & 0x0F; // 0b00001010 = 10

// Combine two values
uint8_t high = 0xA;   // 0b1010
uint8_t low = 0xB;    // 0b1011
uint8_t combined = (high << 4) | low; // 0b10101011 = 0xAB

Common Use Cases in Embedded
Use Case	Bit Operation
Set GPIO pin high	GPIO_PORT |= (1 << PIN)
Set GPIO pin low	GPIO_PORT &= ~(1 << PIN)
Toggle LED	LED_PORT ^= (1 << LED_PIN)
Read button state	if(BUTTON_PORT & (1 << BUTTON_PIN))
Configure timer prescaler	TIMER_REG = (TIMER_REG & ~0x07) | prescaler
Bit Fields in Structures
c

// Bit field (packed)
struct {
    uint8_t enable : 1;    // bit 0
    uint8_t mode : 2;      // bits 1-2
    uint8_t speed : 3;     // bits 3-5
    uint8_t reserved : 2;  // bits 6-7
} config;

Common Bit Tricks
Trick	Code	Explanation
Is power of 2	(x & (x-1)) == 0	Only one bit set
Count set bits	while(x) { count++; x &= (x-1); }	Brian Kernighan's method
Swap without temp	a ^= b; b ^= a; a ^= b;	XOR swap
Check even/odd	(x & 1) == 0	Check LSB
Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 01-c-language/bitwise/bitwise.c -o bitwise
./bitwise

Key Takeaways

    Bitwise operations work at bit level

    AND (&) clears bits, OR (|) sets bits, XOR (^) toggles bits

    Shift operators multiply/divide by powers of 2

    Essential for embedded register manipulation

    Much faster than arithmetic operations
