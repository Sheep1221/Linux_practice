#include <iostream>
#include <memory>

int main() {
    // Creating a shared_ptr and initializing it with a dynamically allocated integer
    std::shared_ptr<int> ptr1(new int(42));

    // Creating another shared_ptr that shares ownership
    std::shared_ptr<int> ptr2 = ptr1;

    // Using the shared_ptrs
    std::cout << "ptr1 value: " << *ptr1 << std::endl;
    std::cout << "ptr2 value: " << *ptr2 << std::endl;

    // Resetting ptr1, decrementing reference count
    ptr1.reset();

    // Using ptr2 after ptr1 reset
    std::cout << "ptr2 value after ptr1 reset: " << *ptr2 << std::endl;

    // Resetting ptr2, deallocate object as no more shared_ptr is referencing it
    ptr2.reset();

    return 0;
}
