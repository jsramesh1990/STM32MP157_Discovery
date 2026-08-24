# POINTER ARITHMETIC

## What is Pointer Arithmetic?

Pointer arithmetic allows you to perform mathematical operations on pointers. When you add or subtract from a pointer, it moves by the size of the data type it points to, not by bytes.

## Syntax

| Operation | Syntax | Description |
|-----------|--------|-------------|
| Increment | `ptr++` | Move to next element |
| Decrement | `ptr--` | Move to previous element |
| Addition | `ptr + n` | Move n elements forward |
| Subtraction | `ptr - n` | Move n elements backward |
| Difference | `ptr1 - ptr2` | Number of elements between two pointers |

## Basic Points

1. **Type Size Matters**: `ptr++` moves by `sizeof(type)` bytes
2. **Array Name = Pointer**: Array name points to first element
3. **No Multiplication/Division**: `ptr * 2` is NOT allowed
4. **Pointers Must Point to Same Array**: When subtracting two pointers
5. **Valid Range**: Don't go outside array bounds

## How Pointer Arithmetic Works

Data Type: int (4 bytes on most systems)

int arr[5] = {10, 20, 30, 40, 50};
int *ptr = arr;

Memory Layout:

Address: 1000 1004 1008 1012 1016
┌────┐ ┌────┐ ┌────┐ ┌────┐ ┌────┐
Value: │ 10 │ │ 20 │ │ 30 │ │ 40 │ │ 50 │
└────┘ └────┘ └────┘ └────┘ └────┘
↑
ptr = 1000

ptr++ → ptr = 1004 (moves 4 bytes)
ptr += 2 → ptr = 1012 (moves 8 bytes)
text


## Example

```c
int arr[5] = {10, 20, 30, 40, 50};
int *ptr = arr;

printf("%d", *ptr);     // Output: 10
ptr++;
printf("%d", *ptr);     // Output: 20
ptr += 2;
printf("%d", *ptr);     // Output: 40

Rules Table
Pointer Type	ptr++ moves	Example
char*	1 byte	ptr+1 → next character
int*	4 bytes	ptr+1 → next integer
float*	4 bytes	ptr+1 → next float
double*	8 bytes	ptr+1 → next double
struct*	size of struct	ptr+1 → next struct
Common Mistakes
Wrong	Correct
ptr + 1 on void*	Cast first or use char*
ptr * 2	ptr + 2
ptr1 - ptr2 from different arrays	Only same array
ptr = 1000 (direct address)	ptr = &variable
Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
gcc 01-c-language/pointers/pointer_arithmetic.c -o pointer_arithmetic
./pointer_arithmetic

Output Explanation
text

Array: 10 20 30 40 50
*ptr = 10        → Points to first element
After ptr++ = 20 → Moves to second element
After ptr+=2 = 40 → Moves to fourth element
Difference = 4   → Number of elements between first and last

Key Takeaway

Pointer arithmetic + array name = natural array traversal

    arr[i] is same as *(arr + i)

    ptr++ automatically accounts for data type size
