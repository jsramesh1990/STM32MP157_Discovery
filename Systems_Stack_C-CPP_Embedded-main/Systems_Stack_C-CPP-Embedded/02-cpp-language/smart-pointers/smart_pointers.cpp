#include <iostream>
#include <memory>
#include <vector>

// ============================================================
// CLASS TO TRACK CONSTRUCTOR/DESTRUCTOR
// ============================================================

class TestObject {
private:
    int id;
    static int count;
    
public:
    TestObject() : id(++count) {
        std::cout << "  TestObject " << id << " created\n";
    }
    
    ~TestObject() {
        std::cout << "  TestObject " << id << " destroyed\n";
    }
    
    int getId() const { return id; }
    void doSomething() const {
        std::cout << "  TestObject " << id << " is working\n";
    }
};

int TestObject::count = 0;

// ============================================================
// CLASS WITH CIRCULAR REFERENCE (to demonstrate weak_ptr)
// ============================================================

struct Node {
    int value;
    std::shared_ptr<Node> next;     // Strong reference
    std::weak_ptr<Node> weak_next;   // Weak reference (breaks cycle)
    
    Node(int v) : value(v) {
        std::cout << "  Node " << value << " created\n";
    }
    
    ~Node() {
        std::cout << "  Node " << value << " destroyed\n";
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    std::cout << "\n========================================\n";
    std::cout << "        SMART POINTERS DEMO            \n";
    std::cout << "========================================\n\n";
    
    // ============================================================
    // 1. UNIQUE_PTR
    // ============================================================
    
    std::cout << "--- UNIQUE_PTR (Exclusive Ownership) ---\n\n";
    
    // Create unique_ptr
    std::unique_ptr<TestObject> u1 = std::make_unique<TestObject>();
    u1->doSomething();
    
    std::cout << "u1 address: " << u1.get() << std::endl;
    
    // Cannot copy unique_ptr
    // std::unique_ptr<TestObject> u2 = u1;  // ERROR! Copy not allowed
    
    // Move unique_ptr (transfer ownership)
    std::unique_ptr<TestObject> u2 = std::move(u1);
    std::cout << "After move - u1: " << u1.get() << std::endl;
    std::cout << "After move - u2: " << u2.get() << std::endl;
    
    u2->doSomething();
    
    // Release (give up ownership without deleting)
    TestObject* raw = u2.release();
    std::cout << "After release - u2: " << u2.get() << std::endl;
    
    // Manually delete
    delete raw;
    
    // Reset (delete current and optionally point to new)
    std::unique_ptr<TestObject> u3 = std::make_unique<TestObject>();
    std::cout << "Before reset: " << u3.get() << std::endl;
    u3.reset();  // Deletes the object
    std::cout << "After reset: " << u3.get() << std::endl;
    
    // ============================================================
    // 2. SHARED_PTR
    // ============================================================
    
    std::cout << "\n--- SHARED_PTR (Shared Ownership) ---\n\n";
    
    // Create shared_ptr
    std::shared_ptr<TestObject> s1 = std::make_shared<TestObject>();
    std::cout << "s1 use count: " << s1.use_count() << std::endl;
    
    // Copy (shared ownership)
    std::shared_ptr<TestObject> s2 = s1;
    std::cout << "After copy - s1 use count: " << s1.use_count() << std::endl;
    std::cout << "After copy - s2 use count: " << s2.use_count() << std::endl;
    
    std::shared_ptr<TestObject> s3 = s1;
    std::cout << "After another copy - use count: " << s1.use_count() << std::endl;
    
    s2.reset();  // Release one reference
    std::cout << "After reset s2 - use count: " << s1.use_count() << std::endl;
    
    s1->doSomething();
    s3->doSomething();
    
    // ============================================================
    // 3. WEAK_PTR (Break circular references)
    // ============================================================
    
    std::cout << "\n--- WEAK_PTR (Breaking Cycles) ---\n\n";
    
    // Create shared_ptr
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);
    
    std::cout << "Initial use counts:\n";
    std::cout << "  node1: " << node1.use_count() << std::endl;
    std::cout << "  node2: " << node2.use_count() << std::endl;
    
    // Create strong reference cycle (BAD - memory leak)
    node1->next = node2;
    node2->next = node1;
    
    std::cout << "After strong cycle:\n";
    std::cout << "  node1: " << node1.use_count() << std::endl;
    std::cout << "  node2: " << node2.use_count() << std::endl;
    std::cout << "  Memory leak! (both use_count=2)\n";
    
    // Fix with weak_ptr
    std::shared_ptr<Node> node3 = std::make_shared<Node>(3);
    std::shared_ptr<Node> node4 = std::make_shared<Node>(4);
    
    node3->weak_next = node4;  // weak reference
    node4->weak_next = node3;  // weak reference
    
    std::cout << "\nAfter weak_ptr cycle:\n";
    std::cout << "  node3 use count: " << node3.use_count() << std::endl;
    std::cout << "  node4 use count: " << node4.use_count() << std::endl;
    
    // Lock weak_ptr to use
    if(auto sp = node3->weak_next.lock()) {
        std::cout << "  Weak_ptr locked successfully\n";
    }
    
    // ============================================================
    // 4. SMART POINTERS IN CONTAINERS
    // ============================================================
    
    std::cout << "\n--- SMART POINTERS in Containers ---\n\n";
    
    std::vector<std::unique_ptr<TestObject>> vec;
    
    for(int i = 0; i < 3; i++) {
        vec.push_back(std::make_unique<TestObject>());
    }
    
    std::cout << "Vector contains " << vec.size() << " objects\n";
    
    for(auto& ptr : vec) {
        ptr->doSomething();
    }
    
    // Vector automatically destroys unique_ptrs when cleared
    vec.clear();
    std::cout << "After clear, vector size: " << vec.size() << std::endl;
    
    // ============================================================
    // 5. CUSTOM DELETER
    // ============================================================
    
    std::cout << "\n--- Custom Deleter ---\n\n";
    
    auto customDeleter = [](TestObject* obj) {
        std::cout << "  Custom deleter called!\n";
        delete obj;
    };
    
    std::unique_ptr<TestObject, decltype(customDeleter)> custom(
        new TestObject(), customDeleter);
    
    custom->doSomething();
    // custom automatically deleted with custom deleter
    
    // ============================================================
    // 6. WHEN TO USE WHICH
    // ============================================================
    
    std::cout << "\n--- WHEN TO USE WHICH ---\n\n";
    
    std::cout << "unique_ptr:\n";
    std::cout << "  ✓ Single owner\n";
    std::cout << "  ✓ No copying needed\n";
    std::cout << "  ✓ Most common smart pointer\n";
    std::cout << "  ✓ Zero overhead over raw pointer\n\n";
    
    std::cout << "shared_ptr:\n";
    std::cout << "  ✓ Multiple owners\n";
    std::cout << "  ✓ Need to share ownership\n";
    std::cout << "  ✓ Reference counting overhead\n\n";
    
    std::cout << "weak_ptr:\n";
    std::cout << "  ✓ Break circular references\n";
    std::cout << "  ✓ Observer pattern\n";
    std::cout << "  ✓ Cache that can expire\n";
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    std::cout << "\n========================================\n";
    std::cout << "           KEY TAKEAWAYS                \n";
    std::cout << "========================================\n";
    std::cout << "1. Always use smart pointers over raw pointers\n";
    std::cout << "2. unique_ptr for exclusive ownership\n";
    std::cout << "3. shared_ptr for shared ownership\n";
    std::cout << "4. weak_ptr to break cycles\n";
    std::cout << "5. Use make_unique and make_shared\n";
    std::cout << "========================================\n\n";
    
    return 0;
}
