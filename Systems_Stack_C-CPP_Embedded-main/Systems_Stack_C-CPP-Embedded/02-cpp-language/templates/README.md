# TEMPLATES

## What are Templates?

Templates allow writing generic code that works with any data type. The compiler generates actual code for each type used.

## Types of Templates

| Type | Syntax | Use Case |
|------|--------|----------|
| Function Template | `template<typename T>` | Generic functions |
| Class Template | `template<class T>` | Generic classes |
| Variadic Template | `template<typename... Args>` | Variable arguments |

## Function Template

```cpp
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Usage
int x = max(10, 20);        // T = int
double y = max(3.14, 2.71); // T = double

Class Template
cpp

template<typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() { return value; }
};

// Usage
Box<int> intBox(42);
Box<double> doubleBox(3.14);

Template Specialization
cpp

// Primary template
template<typename T>
void print(T value) {
    cout << value;
}

// Specialization for string
template<>
void print<string>(string value) {
    cout << "String: " << value;
}

Variadic Templates
cpp

// Base case
void print() {}

// Recursive case
template<typename T, typename... Args>
void print(T first, Args... args) {
    cout << first << " ";
    print(args...);
}

// Usage
print(1, 2.5, "hello", 'c');

Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
g++ -std=c++17 02-cpp-language/templates/templates.cpp -o templates
./templates

Key Takeaways

    Templates are compile-time – no runtime overhead

    Specialization for specific types – custom behavior

    Variadic templates for variable arguments

    SFINAE – Substitution Failure Is Not An Error

    Concepts (C++20) – better template constraints
