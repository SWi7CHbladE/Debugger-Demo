#include <iostream>
#include <string>
#include <vector>

// 1. A global variable to test watchpoints
int global_counter = 0;

// 2. A struct to inspect complex data types
struct Point {
    int x;
    int y;
    const char* label;
};

// 3. A recursive function to demonstrate the call stack
long factorial(int n) {
    global_counter++; // This change can be caught by a watchpoint
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// 4. A function to demonstrate arrays and loops
int sum_array(int* arr, int size) {
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += arr[i]; // A good place for a conditional breakpoint
    }
    return total;
}

// 5. A function designed to cause a segmentation fault
void cause_crash() {
    Point* p_null = nullptr;
    std::cout << "About to dereference a null pointer..." << std::endl;
    p_null->x = 10; // This will cause a SEGFAULT
    std::cout << "This line will never be reached." << std::endl;
}

int main(int argc, char *argv[]) {
    // Basic variables for printing
    int a = 10;
    float b = 3.14f;
    const char* message = "Hello, GDB!";
    
    // Structs and dynamic memory
    Point p1 = {5, -2, "Point A"};
    Point* p2 = new Point{15, 20, "Point B"};

    // Arrays
    int numbers[] = {10, 20, 30, 40, 50};
    int total = sum_array(numbers, 5);
    std::cout << "Sum of numbers: " << total << std::endl;

    // Recursive call
    int fact_arg = 4;
    long fact_result = factorial(fact_arg);
    std::cout << "Factorial of " << fact_arg << " is " << fact_result << std::endl;
    std::cout << "Factorial function was called " << global_counter << " times." << std::endl;

    delete p2; // Clean up dynamic memory

    // Check for a command-line argument to trigger the crash
    if (argc > 1 && std::string(argv[1]) == "crash") {
        cause_crash();
    }

    std::cout << "Program finished successfully." << std::endl;
    return 0;
}
