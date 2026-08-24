#include <iostream>
#include <cstring>
#include <utility>

class String {
private:
    char* data;
    size_t len;
    
public:
    // Constructor
    String(const char* str = "") {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
        std::cout << "Constructor: \"" << data << "\"\n";
    }
    
    // Destructor
    ~String() {
        if(data) {
            std::cout << "Destructor: \"" << data << "\"\n";
            delete[] data;
        } else {
            std::cout << "Destructor: (moved-from, empty)\n";
        }
        data = nullptr;
        len = 0;
    }
    
    // Copy constructor (deep copy)
    String(const String& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
        std::cout << "Copy Constructor: \"" << data << "\"\n";
    }
    
    // Copy assignment (deep copy)
    String& operator=(const String& other) {
        if(this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
            std::cout << "Copy Assignment: \"" << data << "\"\n";
        }
        return *this;
    }
    
    // Move constructor (transfer ownership)
    String(String&& other) noexcept 
        : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
        std::cout << "Move Constructor: transferred \"" << data << "\"\n";
    }
    
    // Move assignment (transfer ownership)
    String& operator=(String&& other) noexcept {
        if(this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            other.data = nullptr;
            other.len = 0;
            std::cout << "Move Assignment: transferred \"" << data << "\"\n";
        }
        return *this;
    }
    
    const char* c_str() const { return data ? data : ""; }
    size_t length() const { return len; }
};

int main() {
    std::cout << "\n========================================\n";
    std::cout << "  CHALLENGE 03: MOVE SEMANTICS        \n";
    std::cout << "========================================\n\n";
    
    std::cout << "1. Creating s1:\n";
    String s1("Hello");
    
    std::cout << "\n2. Move constructor (s2 = std::move(s1)):\n";
    String s2 = std::move(s1);
    
    std::cout << "\n3. s1 is now empty (moved-from state):\n";
    std::cout << "   s1.c_str() = \"" << s1.c_str() << "\" (empty)\n";
    std::cout << "   s2.c_str() = \"" << s2.c_str() << "\"\n";
    
    std::cout << "\n4. Creating s3:\n";
    String s3("World");
    
    std::cout << "\n5. Move assignment (s3 = std::move(s2)):\n";
    s3 = std::move(s2);
    
    std::cout << "\n6. Final states:\n";
    std::cout << "   s1: \"" << s1.c_str() << "\" (moved-from)\n";
    std::cout << "   s2: \"" << s2.c_str() << "\" (moved-from)\n";
    std::cout << "   s3: \"" << s3.c_str() << "\"\n";
    
    std::cout << "\n7. Demonstrating copy (not move):\n";
    String s4 = s3;  // Copy constructor, not move
    
    std::cout << "\n8. Exiting scope - destructors will run:\n";
    
    std::cout << "\n========================================\n";
    std::cout << "              COMPLETE                  \n";
    std::cout << "========================================\n\n";
    
    return 0;
}
