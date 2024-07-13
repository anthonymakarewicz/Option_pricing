#include <iostream>
#include <memory>

class Example {
public:
    Example() { std::cout << "Example created at address " << this << std::endl; }
    ~Example() { std::cout << "Example destroyed at address " << this << std::endl; }
    Example(Example&& other) noexcept { std::cout << "Example moved from address " << &other << " to address " << this << std::endl; }
};

int main() {
    auto ptr1 = std::make_shared<Example>();
    std::cout << "ptr1 address: " << ptr1.get() << std::endl;
    auto ptr2 = std::make_shared<Example>(std::move(*ptr1)); // Moves the Example object
    std::cout << "ptr2 address: " << ptr2.get() << std::endl;

    Example ex = std::move(*ptr2);

    auto ptr1 = Option::create("APPL", payoff, T);

    auto ptr2 = Option::copy(ptr1);

    // Check if ptr1's managed object is in a valid state
    if (ptr1 && ptr1.use_count() > 0) {
        std::cout << "ptr1 still manages an object with " << ptr1.use_count() << "\n";
    } else {
        std::cout << "ptr1's managed object is now empty (nullptr)\n";
    }

    if (ptr2 && ptr2.use_count() > 0) {
        std::cout << "ptr1 still manages an object with " << ptr2.use_count() << "\n";
    } else {
        std::cout << "ptr1's managed object is now empty (nullptr)\n";
    }

    auto ptr3 = std::move(ptr2);

    std::cout << "ptr2 address: " << ptr3.get() << std::endl;
    std::cout << "ptr2 address: " << ptr2.get() << std::endl;

    if (ptr3 && ptr3.use_count() > 0) {
        std::cout << "ptr1 still manages an object with " << ptr3.use_count() << "\n";
    } else {
        std::cout << "ptr1's managed object is now empty (nullptr)\n";
    }

    if (ptr2 && ptr2.use_count() > 0) {
        std::cout << "ptr1 still manages an object with " << ptr2.use_count() << "\n";
    } else {
        std::cout << "ptr1's managed object is now empty (nullptr)\n";
    }
    return 0;
}
