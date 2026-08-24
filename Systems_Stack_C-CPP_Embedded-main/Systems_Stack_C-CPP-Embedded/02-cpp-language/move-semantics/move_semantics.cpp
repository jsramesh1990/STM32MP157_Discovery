#include <iostream>
#include <vector>
#include <utility>
#include <cstring>

// ============================================================
// CLASS DEMONSTRATING COPY VS MOVE
// ============================================================

class MyBuffer {
private:
    char* data;
    size_t size;
    
public:
    // Constructor
    MyBuffer(size_t s) : size(s) {
        data = new char[size];
        std::cout << "  Constructor: allocated " << size << " bytes\n";
    }
    
    // Copy Constructor (expensive)
    MyBuffer(const MyBuffer& other) : size(other.size) {
        data = new char[size];
        std::memcpy(data, other.data, size);
        std::cout << "  Copy Constructor: copied " << size << " bytes\n";
    }
    
    // Move Constructor (cheap)
    MyBuffer(MyBuffer&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "  Move Constructor: transferred ownership\n";
    }
    
    // Copy Assignment
    MyBuffer& operator=(const MyBuffer& other) {
        if(this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size];
            std::memcpy(data, other.data, size);
            std::cout << "  Copy Assignment: copied " << size << " bytes\n";
        }
        return *this;
    }
    
    // Move Assignment
    MyBuffer& operator=(MyBuffer&& other) noexcept {
        if(this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "  Move Assignment: transferred ownership\n";
        }
        return *this;
    }
    
    // Destructor
    ~MyBuffer() {
        delete[] data;
        std::cout << "  Destructor: freed memory\n";
    }
    
    void fill(char c) {
        if(data) {
            std::memset(data, c, size);
        }
    }
};

// ============================================================
// FUNCTION RETURNING BY VALUE (MOVE HAPPENS)
// ============================================================

MyBuffer createBuffer() {
    MyBuffer temp(100);
    temp.fill('A');
    return temp;  // Move happens here (or RVO)
}

// ============================================================
// LVALUE AND RVALUE DEMONSTRATION
// ============================================================

void process(int& x) {
    std::cout << "  Lvalue reference: " << x << std::endl;
}

void process(int&& x) {
    std::cout << "  Rvalue reference: " << x << std::endl;
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    std::cout << "\n========================================\n";
    std::cout << "        MOVE SEMANTICS DEMO            \n";
    std::cout << "========================================\n\n";
    
    // ============================================================
    // 1. LVALUE VS RVALUE
    // ============================================================
    
    std::cout << "--- LVALUE vs RVALUE ---\n\n";
    
    int a = 42;           // a is lvalue
    process(a);           // Calls lvalue version
    process(100);         // Calls rvalue version (100 is temporary)
    process(std::move(a)); // Cast a to rvalue
    
    // ============================================================
    // 2. COPY VS MOVE CONSTRUCTOR
    // ============================================================
    
    std::cout << "\n--- COPY vs MOVE CONSTRUCTOR ---\n\n";
    
    std::cout << "Creating buffer1:\n";
    MyBuffer buffer1(50);
    buffer1.fill('X');
    
    std::cout << "\nCopy constructor (expensive):\n";
    MyBuffer buffer2 = buffer1;  // Copy
    
    std::cout << "\nMove constructor (cheap):\n";
    MyBuffer buffer3 = std::move(buffer1);  // Move
    
    // ============================================================
    // 3. COPY VS MOVE ASSIGNMENT
    // ============================================================
    
    std::cout << "\n--- COPY vs MOVE ASSIGNMENT ---\n\n";
    
    MyBuffer buffer4(30);
    MyBuffer buffer5(20);
    
    std::cout << "\nCopy assignment:\n";
    buffer4 = buffer5;
    
    std::cout << "\nMove assignment:\n";
    buffer4 = std::move(buffer5);
    
    // ============================================================
    // 4. MOVE WITH STL CONTAINERS
    // ============================================================
    
    std::cout << "\n--- MOVE with STL Containers ---\n\n";
    
    std::vector<std::string> source;
    source.push_back("Hello");
    source.push_back("World");
    source.push_back("Move");
    source.push_back("Semantics");
    
    std::cout << "Source vector size: " << source.size() << std::endl;
    
    // Move entire vector (no copying of strings)
    std::vector<std::string> destination = std::move(source);
    
    std::cout << "After move:\n";
    std::cout << "  Source size: " << source.size() << std::endl;
    std::cout << "  Destination size: " << destination.size() << std::endl;
    std::cout << "  Destination contents: ";
    for(const auto& s : destination) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    
    // ============================================================
    // 5. RETURN VALUE OPTIMIZATION (RVO)
    // ============================================================
    
    std::cout << "\n--- Return Value Optimization (RVO) ---\n\n";
    std::cout << "Creating buffer via factory function:\n";
    MyBuffer buffer6 = createBuffer();  // May use RVO or move
    
    // ============================================================
    // 6. WHEN TO USE std::move
    // ============================================================
    
    std::cout << "\n--- When to use std::move ---\n\n";
    
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2;
    
    // Wrong: moving from lvalue without std::move
    // vec2 = vec1;  // This would COPY
    
    // Correct: explicit move
    vec2 = std::move(vec1);
    
    std::cout << "  vec1 size after move: " << vec1.size() << std::endl;
    std::cout << "  vec2 size: " << vec2.size() << std::endl;
    
    // ============================================================
    // 7. PERFECT FORWARDING EXAMPLE
    // ============================================================
    
    std::cout << "\n--- Perfect Forwarding ---\n\n";
    
    auto wrapper = [](auto&& arg) {
        process(std::forward<decltype(arg)>(arg));
    };
    
    int x = 10;
    wrapper(x);      // Forwards as lvalue
    wrapper(20);     // Forwards as rvalue
    
    // ============================================================
    // 8. MOVED-FROM OBJECT STATE
    // ============================================================
    
    std::cout << "\n--- Moved-From Object State ---\n\n";
    
    MyBuffer original(10);
    original.fill('Z');
    
    MyBuffer moved = std::move(original);
    
    std::cout << "After move, original is in valid but unspecified state\n";
    std::cout << "It can be destroyed or assigned a new value\n";
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    std::cout << "\n========================================\n";
    std::cout << "           KEY TAKEAWAYS                \n";
    std::cout << "========================================\n";
    std::cout << "1. Move transfers ownership (no copy)\n";
    std::cout << "2. std::move() casts to rvalue\n";
    std::cout << "3. Move constructors should be noexcept\n";
    std::cout << "4. Use move for large objects\n";
    std::cout << "5. Moved-from objects are valid but empty\n";
    std::cout << "========================================\n\n";
    
    return 0;
}
