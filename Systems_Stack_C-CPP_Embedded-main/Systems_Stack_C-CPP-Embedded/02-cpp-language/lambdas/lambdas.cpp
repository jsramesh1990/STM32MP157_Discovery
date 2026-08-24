#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// ============================================================
// STRUCT FOR COMPARISON (to show lambda equivalence)
// ============================================================

struct CompareStruct {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    std::cout << "\n========================================\n";
    std::cout << "           LAMBDAS DEMO                 \n";
    std::cout << "========================================\n\n";
    
    // ============================================================
    // 1. BASIC LAMBDA SYNTAX
    // ============================================================
    
    std::cout << "--- BASIC LAMBDA SYNTAX ---\n\n";
    
    // Lambda with no parameters
    auto sayHello = []() {
        std::cout << "  Hello from lambda!\n";
    };
    sayHello();
    
    // Lambda with parameters
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "  add(5,3) = " << add(5, 3) << std::endl;
    
    // Lambda with return type specified
    auto divide = [](double a, double b) -> double {
        if(b == 0) return 0;
        return a / b;
    };
    std::cout << "  divide(10,3) = " << divide(10, 3) << std::endl;
    
    // Immediately invoked lambda
    int result = [](int x, int y) { return x * y; }(4, 5);
    std::cout << "  Immediately invoked: " << result << std::endl;
    
    // ============================================================
    // 2. CAPTURE CLAUSES
    // ============================================================
    
    std::cout << "\n--- CAPTURE CLAUSES ---\n\n";
    
    int x = 10;
    int y = 20;
    
    // Capture by value [=]
    auto captureByValue = [=]() {
        // x = 30;  // ERROR! cannot modify captured value
        return x + y;
    };
    std::cout << "  captureByValue: " << captureByValue() << std::endl;
    
    // Capture by reference [&]
    auto captureByRef = [&]() {
        x = 30;  // Can modify x
        y = 40;  // Can modify y
        return x + y;
    };
    std::cout << "  Before captureByRef: x=" << x << ", y=" << y << std::endl;
    std::cout << "  captureByRef: " << captureByRef() << std::endl;
    std::cout << "  After captureByRef: x=" << x << ", y=" << y << std::endl;
    
    // Reset values
    x = 10;
    y = 20;
    
    // Capture specific variables
    auto captureSpecific = [x, &y]() {
        // x++;  // ERROR! captured by value (const)
        y = 100;  // OK! captured by reference
        return x + y;
    };
    std::cout << "\n  Before captureSpecific: x=" << x << ", y=" << y << std::endl;
    std::cout << "  captureSpecific: " << captureSpecific() << std::endl;
    std::cout << "  After captureSpecific: x=" << x << ", y=" << y << std::endl;
    
    y = 20;  // Reset
    
    // ============================================================
    // 3. MUTABLE LAMBDA
    // ============================================================
    
    std::cout << "\n--- MUTABLE LAMBDA ---\n\n";
    
    int counter = 0;
    
    auto increment = [counter]() mutable {
        counter++;
        return counter;
    };
    
    std::cout << "  counter initially: " << counter << std::endl;
    std::cout << "  increment: " << increment() << std::endl;
    std::cout << "  increment: " << increment() << std::endl;
    std::cout << "  increment: " << increment() << std::endl;
    std::cout << "  counter after increments: " << counter 
              << " (original unchanged!)\n";
    
    // Lambda with mutable reference capture
    int count = 0;
    auto realIncrement = [&count]() {
        count++;
        return count;
    };
    
    std::cout << "\n  realIncrement: " << realIncrement() << std::endl;
    std::cout << "  realIncrement: " << realIncrement() << std::endl;
    std::cout << "  count after: " << count << std::endl;
    
    // ============================================================
    // 4. LAMBDAS WITH STL ALGORITHMS
    // ============================================================
    
    std::cout << "\n--- LAMBDAS with STL ALGORITHMS ---\n\n";
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "  Original vector: ";
    for(int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Sort with lambda
    std::sort(numbers.begin(), numbers.end(), 
              [](int a, int b) { return a < b; });
    
    std::cout << "  Sorted ascending: ";
    for(int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Sort descending
    std::sort(numbers.begin(), numbers.end(), 
              [](int a, int b) { return a > b; });
    
    std::cout << "  Sorted descending: ";
    for(int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Find even numbers
    auto isEven = [](int n) { return n % 2 == 0; };
    auto evenCount = std::count_if(numbers.begin(), numbers.end(), isEven);
    std::cout << "  Even numbers count: " << evenCount << std::endl;
    
    // Transform with lambda
    std::vector<int> squared(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squared.begin(),
                   [](int n) { return n * n; });
    
    std::cout << "  Squared values: ";
    for(int n : squared) std::cout << n << " ";
    std::cout << std::endl;
    
    // ============================================================
    // 5. CAPTURE WITH INITIALIZATION (C++14)
    // ============================================================
    
    std::cout << "\n--- CAPTURE WITH INITIALIZATION (C++14) ---\n\n";
    
    // Capture with initialization (move only types)
    auto uniquePtrLambda = [ptr = std::make_unique<int>(42)]() {
        return *ptr;
    };
    std::cout << "  Lambda owning unique_ptr: " << uniquePtrLambda() << std::endl;
    
    // Capture with computation
    auto computed = [value = 10 * 5]() {
        return value;
    };
    std::cout << "  Capture with computation: " << computed() << std::endl;
    
    // ============================================================
    // 6. GENERIC LAMBDAS (C++14)
    // ============================================================
    
    std::cout << "\n--- GENERIC LAMBDAS (C++14) ---\n\n";
    
    auto genericAdd = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "  genericAdd(5, 3) = " << genericAdd(5, 3) << std::endl;
    std::cout << "  genericAdd(2.5, 1.5) = " << genericAdd(2.5, 1.5) << std::endl;
    std::cout << "  genericAdd(std::string(\"Hello\"), std::string(\" World\")) = "
              << genericAdd(std::string("Hello"), std::string(" World")) << std::endl;
    
    // Generic lambda with auto parameters
    auto compare = [](const auto& a, const auto& b) {
        return a < b;
    };
    
    std::cout << "  compare(10, 20) = " << compare(10, 20) << std::endl;
    std::cout << "  compare(3.14, 2.71) = " << compare(3.14, 2.71) << std::endl;
    
    // ============================================================
    // 7. LAMBDA AS FUNCTION OBJECT (STD::FUNCTION)
    // ============================================================
    
    std::cout << "\n--- LAMBDA as std::function ---\n\n";
    
    std::function<int(int, int)> func;
    
    func = [](int a, int b) { return a + b; };
    std::cout << "  func as add: " << func(5, 3) << std::endl;
    
    func = [](int a, int b) { return a - b; };
    std::cout << "  func as subtract: " << func(5, 3) << std::endl;
    
    func = [](int a, int b) { return a * b; };
    std::cout << "  func as multiply: " << func(5, 3) << std::endl;
    
    // ============================================================
    // 8. LAMBDA WITH AUTO RETURN TYPE DEDUCTION
    // ============================================================
    
    std::cout << "\n--- AUTO RETURN TYPE DEDUCTION ---\n\n";
    
    auto getMultiplier = [](int factor) {
        return [factor](int x) { return x * factor; };
    };
    
    auto times2 = getMultiplier(2);
    auto times5 = getMultiplier(5);
    
    std::cout << "  times2(10) = " << times2(10) << std::endl;
    std::cout << "  times5(10) = " << times5(10) << std::endl;
    
    // ============================================================
    // 9. LAMBDA EQUIVALENT TO FUNCTOR
    // ============================================================
    
    std::cout << "\n--- LAMBDA vs FUNCTOR ---\n\n";
    
    // Lambda version
    auto lambdaLess = [](int a, int b) { return a < b; };
    
    // Functor version (what compiler generates)
    struct FunctorLess {
        bool operator()(int a, int b) const {
            return a < b;
        }
    };
    FunctorLess functorLess;
    
    std::vector<int> v1 = {3, 1, 4, 1, 5};
    std::vector<int> v2 = {3, 1, 4, 1, 5};
    
    std::sort(v1.begin(), v1.end(), lambdaLess);
    std::sort(v2.begin(), v2.end(), functorLess);
    
    std::cout << "  Lambda sort result: ";
    for(int n : v1) std::cout << n << " ";
    std::cout << std::endl;
    
    std::cout << "  Functor sort result: ";
    for(int n : v2) std::cout << n << " ";
    std::cout << std::endl;
    
    // ============================================================
    // 10. PRACTICAL EXAMPLE: CUSTOM SORTING
    // ============================================================
    
    std::cout << "\n--- PRACTICAL: Sorting with Custom Criteria ---\n\n";
    
    struct Person {
        std::string name;
        int age;
    };
    
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35},
        {"Diana", 28}
    };
    
    // Sort by age
    std::sort(people.begin(), people.end(),
              [](const Person& a, const Person& b) {
                  return a.age < b.age;
              });
    
    std::cout << "  People sorted by age:\n";
    for(const auto& p : people) {
        std::cout << "    " << p.name << " (" << p.age << ")\n";
    }
    
    // Sort by name length
    std::sort(people.begin(), people.end(),
              [](const Person& a, const Person& b) {
                  return a.name.length() < b.name.length();
              });
    
    std::cout << "\n  People sorted by name length:\n";
    for(const auto& p : people) {
        std::cout << "    " << p.name << " (" << p.name.length() << " chars)\n";
    }
    
    // ============================================================
    // SUMMARY
    // ============================================================
    
    std::cout << "\n========================================\n";
    std::cout << "           KEY TAKEAWAYS                \n";
    std::cout << "========================================\n";
    std::cout << "1. [=]  - capture all by value\n";
    std::cout << "2. [&]  - capture all by reference\n";
    std::cout << "3. [x]  - capture x by value\n";
    std::cout << "4. [&x] - capture x by reference\n";
    std::cout << "5. mutable - allows modification of captured values\n";
    std::cout << "6. Great with STL algorithms\n";
    std::cout << "========================================\n\n";
    
    return 0;
}
