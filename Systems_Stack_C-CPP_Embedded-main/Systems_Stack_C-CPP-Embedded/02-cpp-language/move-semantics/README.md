# MOVE SEMANTICS

## What is Move Semantics?

Move semantics allows transferring ownership of resources from one object to another without copying. This makes code faster by avoiding deep copies.

## Lvalues vs Rvalues

| Type | Description | Example |
|------|-------------|---------|
| **Lvalue** | Has an address (can appear on left of =) | `int x = 5;` (x is lvalue) |
| **Rvalue** | Temporary, no address (appears on right) | `int x = 5;` (5 is rvalue) |

## Move vs Copy

COPY (expensive) MOVE (cheap)
┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐
│ Object1 │────→│ Object2 │ │ Object1 │ │ Object2 │
│ Data │ copy│ Data │ │ Data │────→│ Data │
└─────────┘ └─────────┘ └─────────┘ └─────────┘
↑ ↑ ↑ ↑
New memory New memory Transfer Take ownership
allocated allocated pointers (no copy)
text


## Syntax

| Operation | Code | Description |
|-----------|------|-------------|
| Rvalue reference | `T&&` | Reference to temporary |
| Move constructor | `T(T&& other)` | Steal resources from other |
| Move assignment | `T& operator=(T&& other)` | Steal resources |
| std::move() | `std::move(obj)` | Cast to rvalue |

## Move Constructor Example

```cpp
class Buffer {
    int* data;
public:
    // Move constructor
    Buffer(Buffer&& other) noexcept 
        : data(other.data) {
        other.data = nullptr;  // Leave other in valid state
    }
};

When Move Happens Automatically
cpp

std::vector<int> createVector() {
    std::vector<int> v{1,2,3,4,5};
    return v;  // Move automatically (RVO)
}

std::vector<int> v1 = createVector();  // Move
std::vector<int> v2 = std::move(v1);   // Explicit move

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
g++ -std=c++17 02-cpp-language/move-semantics/move_semantics.cpp -o move_semantics
./move_semantics

Key Takeaways

    Move transfers ownership – no copying of data

    std::move() casts to rvalue – enables move

    Move is faster – especially for large data

    Moved-from object is valid – but unspecified state

    Use noexcept for move operations
