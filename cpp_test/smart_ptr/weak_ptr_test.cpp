#include <iostream>
#include <memory>

int main() {
    // Creating a shared_ptr and initializing it with a dynamically allocated integer
    std::shared_ptr<int> ptr1(new int(42));

    // Creating a weak_ptr from the shared_ptr
    std::weak_ptr<int> ptr2 = ptr1;

    // Using the shared_ptr
    std::cout << "ptr1 value: " << *ptr1 << std::endl;
    
    // Check if ptr2 is still pointing to a valid object
    if (auto lockedPtr = ptr2.lock()) {
        std::cout << "ptr2 value: " << *lockedPtr << std::endl;
    } else {
        std::cout << "ptr2 is expired" << std::endl;
    }

    // Resetting ptr1, decrementing reference count
    ptr1.reset();

    // Using ptr2 after ptr1 reset
    // Check if ptr2 is still pointing to a valid object
    if (auto lockedPtr = ptr2.lock()) {
        std::cout << "ptr2 value after ptr1 reset: " << *lockedPtr << std::endl;
    } else {
        std::cout << "ptr2 is expired" << std::endl;
    }

    return 0;
}
