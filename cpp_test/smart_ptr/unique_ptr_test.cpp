#include <iostream>
#include <memory>

int main() {
    // Creating a shared_ptr and initializing it with a dynamically allocated integer
    std::unique_ptr<int> ptr1(new int (5));

    // Creating another shared_ptr that shares ownership
    //std::unique_ptr<int> ptr2 = ptr1;

    // Using the shared_ptrs
    std::cout << "ptr1 value: " << *ptr1 << std::endl;

    // Resetting ptr1, decrementing reference count
    ptr1.reset();

    return 0;
}
