# SMART POINTERS

## What are Smart Pointers?

Smart pointers are C++ classes that automatically manage memory. They automatically delete the allocated object when no longer needed.

## Types of Smart Pointers

| Type | Ownership | Copyable | Use When |
|------|-----------|----------|----------|
| `unique_ptr` | Exclusive | No | Single owner |
| `shared_ptr` | Shared | Yes | Multiple owners |
| `weak_ptr` | Non-owning | Yes | Break circular references |

## Comparison

unique_ptr (exclusive) shared_ptr (shared)
┌─────┐ ┌─────┐
│ ptr1│─────→ Object │ ptr1│─┐
└─────┘ └─────┘ │
┌──┴──┐
Cannot copy │Object│
└──┬──┘
┌─────┐ ┌─────┐ │
│ ptr2│─────→ Object (move only) │ ptr2│─┘
└─────┘ └─────┘
text


## Syntax

| Operation | unique_ptr | shared_ptr |
|-----------|------------|------------|
| Create | `std::make_unique<T>()` | `std::make_shared<T>()` |
| Dereference | `*ptr` or `ptr->` | `*ptr` or `ptr->` |
| Check null | `if(ptr)` | `if(ptr)` |
| Release | `ptr.release()` | `ptr.reset()` |
| Get raw pointer | `ptr.get()` | `ptr.get()` |

## Basic Usage

```cpp
// unique_ptr - exclusive ownership
std::unique_ptr<int> u1 = std::make_unique<int>(42);
std::unique_ptr<int> u2 = std::move(u1);  // Move only

// shared_ptr - shared ownership
std::shared_ptr<int> s1 = std::make_shared<int>(100);
std::shared_ptr<int> s2 = s1;  // Copy OK, count=2

// weak_ptr - break cycles
std::weak_ptr<int> w = s1;
if(auto sp = w.lock()) {  // Get shared_ptr if still alive
    // Use sp
}

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
g++ -std=c++17 02-cpp-language/smart-pointers/smart_pointers.cpp -o smart_pointers
./smart_pointers

Key Takeaways

    Always prefer smart pointers over raw pointers

    unique_ptr for single ownership – cannot copy, only move

    shared_ptr for shared ownership – reference counted

    weak_ptr to break cycles – use with shared_ptr

    Use make_unique/make_shared – safer and faster
