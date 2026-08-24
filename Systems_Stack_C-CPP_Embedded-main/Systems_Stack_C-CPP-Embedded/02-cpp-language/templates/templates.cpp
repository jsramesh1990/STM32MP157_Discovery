#include <iostream>
#include <vector>
#include <string>

// ============================================================
// 1. FUNCTION TEMPLATES
// ============================================================

template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T add(T a, T b) {
    return a + b;
}

// Function template with multiple types
template<typename T1, typename T2>
auto multiply(T1 a, T2 b) -> decltype(a * b) {
    return a * b;
}

// ============================================================
// 2. CLASS TEMPLATES
// ============================================================

template<typename T>
class Box {
private:
    T content;
    
public:
    Box(const T& value) : content(value) {}
    
    void set(const T& value) { content = value; }
    T get() const { return content; }
    
    void display() const {
        std::cout << "Box contains: " << content << std::endl;
    }
};

// ============================================================
// 3. TEMPLATE SPECIALIZATION
// ============================================================

// Primary template
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        std::cout << "Generic: " << value << std::endl;
    }
};

// Full specialization for bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        std::cout << "Boolean: " << (value ? "true" : "false") << std::endl;
    }
};

// Partial specialization for pointers
template<typename T>
class Printer<T*> {
public:
    static void print(T* value) {
        std::cout << "Pointer: " << value;
        if(value) std::cout << " (value: " << *value << ")";
        std::cout << std::endl;
    }
};

// ============================================================
// 4. VARIADIC TEMPLATES
// ============================================================

// Base case - no arguments
void variadicPrint() {
    std::cout << std::endl;
}

// Recursive variadic template
template<typename T, typename... Args>
void variadicPrint(T first, Args... args) {
    std::cout << first << " ";
    variadicPrint(args...);
}

// Sum using variadic templates (C++17 fold expression)
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Fold expression
}

// ============================================================
// 5. TEMPLATE WITH DEFAULT PARAMETER
// ============================================================

template<typename T = int>
class DefaultContainer {
private:
    T value;
    
public:
    DefaultContainer(T v = T{}) : value(v) {}
    T get() const { return value; }
};

// ============================================================
// 6. NON-TYPE TEMPLATE PARAMETERS
// ============================================================

template<typename T, int Size>
class Array {
private:
    T data[Size];
    
public:
    int size() const { return Size; }
    
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
};

// ============================================================
// 7. TEMPLATE TEMPLATE PARAMETERS
// ============================================================

template<typename T, template<typename> class Container>
class Wrapper {
private:
    Container<T> container;
    
public:
    void add(const T& value) {
        container.push_back(value);
    }
    
    void display() {
        for(const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    std::cout << "\n========================================\n";
    std::cout << "          TEMPLATES DEMO               \n";
    std::cout << "========================================\n\n";
    
    // ============================================================
    // 1. FUNCTION TEMPLATES
    // ============================================================
    
    std::cout << "--- FUNCTION TEMPLATES ---\n\n";
    
    std::cout << "maximum(10, 20) = " << maximum(10, 20) << std::endl;
    std::cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << std::endl;
    std::cout << "maximum('A', 'Z') = " << maximum('A', 'Z') << std::endl;
    
    std::cout << "add(5, 3) = " << add(5, 3) << std::endl;
    std::cout << "add(2.5, 1.5) = " << add(2.5, 1.5) << std::endl;
    
    std::cout << "multiply(5, 3.14) = " << multiply(5, 3.14) << std::endl;
    
    // ============================================================
    // 2. CLASS TEMPLATES
    // ============================================================
    
    std::cout << "\n--- CLASS TEMPLATES ---\n\n";
    
    Box<int> intBox(42);
    Box<double> doubleBox(3.14159);
    Box<std::string> stringBox("Hello Templates");
    
    intBox.display();
    doubleBox.display();
    stringBox.display();
    
    // ============================================================
    // 3. TEMPLATE SPECIALIZATION
    // ============================================================
    
    std::cout << "\n--- TEMPLATE SPECIALIZATION ---\n\n";
    
    Printer<int>::print(100);
    Printer<double>::print(3.14);
    Printer<bool>::print(true);
    Printer<bool>::print(false);
    
    int x = 42;
    int* px = &x;
    Printer<int*>::print(px);
    
    // ============================================================
    // 4. VARIADIC TEMPLATES
    // ============================================================
    
    std::cout << "\n--- VARIADIC TEMPLATES ---\n\n";
    
    std::cout << "variadicPrint: ";
    variadicPrint(1, 2.5, "hello", 'c', 100);
    
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "sum(1.5, 2.5, 3.5) = " << sum(1.5, 2.5, 3.5) << std::endl;
    
    // ============================================================
    // 5. NON-TYPE TEMPLATE PARAMETERS
    // ============================================================
    
    std::cout << "\n--- NON-TYPE TEMPLATE PARAMETERS ---\n\n";
    
    Array<int, 5> intArray;
    for(int i = 0; i < intArray.size(); i++) {
        intArray[i] = (i + 1) * 10;
    }
    
    std::cout << "intArray size: " << intArray.size() << std::endl;
    std::cout << "intArray values: ";
    for(int i = 0; i < intArray.size(); i++) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;
    
    Array<std::string, 3> strArray;
    strArray[0] = "Hello";
    strArray[1] = "Template";
    strArray[2] = "World";
    
    std::cout << "strArray values: ";
    for(int i = 0; i < strArray.size(); i++) {
        std::cout << strArray[i] << " ";
    }
    std::cout << std::endl;
    
    // ============================================================
    // 6. DEFAULT TEMPLATE PARAMETER
    // ============================================================
    
    std::cout << "\n--- DEFAULT TEMPLATE PARAMETER ---\n\n";
    
    DefaultContainer<> defaultInt(100);
    DefaultContainer<std::string> defaultString("Default String");
    
    std::cout << "defaultInt: " << defaultInt.get() << std::endl;
    std::cout << "defaultString: " << defaultString.get() << std::endl;
    
    // ============================================================
    // 7. AUTO WITH TEMPLATES (C++17)
    // ============================================================
    
    std::cout << "\n--- AUTO with Templates (C++17) ---\n\n";
    
    auto autoMax = [](auto a, auto b) { return (a > b) ? a : b; };
    std::cout << "autoMax(10, 20) = " << autoMax(10, 20) << std::endl;
    std::cout << "autoMax(3.14, 2.71) = " << autoMax(3.14, 2.71) << std::endl;
    std::cout << "autoMax('A', 'Z') = " << autoMax('A', 'Z') << std::endl;
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    std::cout << "\n========================================\n";
    std::cout << "           KEY TAKEAWAYS                \n";
    std::cout << "========================================\n";
    std::cout << "1. Templates enable generic programming\n";
    std::cout << "2. Code is generated at compile time\n";
    std::cout << "3. Specialization for specific types\n";
    std::cout << "4. Variadic templates for variable args\n";
    std::cout << "5. Non-type parameters for compile-time values\n";
    std::cout << "========================================\n\n";
    
    return 0;
}
