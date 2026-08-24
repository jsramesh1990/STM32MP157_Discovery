# LAMBDAS

## What are Lambdas?

Lambdas are anonymous functions that can capture variables from their surrounding scope. They are syntactic sugar for function objects.

## Lambda Syntax

capture -> return_type { body }
↑ ↑ ↑ ↑
│ │ │ │
Capture Parameters Return Function
clause type body
text


## Capture Methods

| Capture | Description | Example |
|---------|-------------|---------|
| `[]` | Capture nothing | `[](){ return 5; }` |
| `[=]` | Capture all by value | `[=](){ return x; }` |
| `[&]` | Capture all by reference | `[&](){ x++; }` |
| `[x]` | Capture x by value | `[x](){ return x; }` |
| `[&x]` | Capture x by reference | `[&x](){ x++; }` |
| `[=, &x]` | All by value, x by reference | `[=, &x](){ x++; }` |
| `[&, x]` | All by reference, x by value | `[&, x](){ return x; }` |

## Basic Examples

```cpp
// Simple lambda
auto greet = []() { 
    std::cout << "Hello"; 
};

// Lambda with parameters
auto add = [](int a, int b) { 
    return a + b; 
};

// Lambda with capture
int x = 10;
auto addX = [x](int a) { 
    return a + x;  // captures x by value
};

// Lambda with return type
auto divide = [](double a, double b) -> double {
    if(b == 0) return 0;
    return a / b;
};

Common Uses
Use Case	Example
STL algorithms	std::sort(v.begin(), v.end(), [](int a, int b){ return a < b; })
Callbacks	button.onClick([](){ std::cout << "Clicked"; })
Threads	std::thread t([](){ std::cout << "Thread"; })
Custom sorting	std::sort(people.begin(), people.end(), [](auto& a, auto& b){ return a.age < b.age; })
Run the Code
bash

cd Systems_Stack_C-CPP-Embedded
g++ -std=c++17 02-cpp-language/lambdas/lambdas.cpp -o lambdas
./lambdas

Key Takeaways

    Lambdas are function objects – compiler generates a class

    Capture by value – copies variable (use [=])

    Capture by reference – avoids copy (use [&])

    Generic lambdas – use auto parameters (C++14)

    Mutable lambdas – allow modification of captured values
