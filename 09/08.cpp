#include <iostream>
#include <new>
#include <cstdlib>

class Entity {
public:
    static void* operator new(std::size_t size) {
        std::cout << "Custom new for size " << size << std::endl;
        return std::malloc(size);
    }

    static void operator delete(void* ptr) noexcept {
        std::cout << "Custom delete" << std::endl;
        std::free(ptr);
    }

    static void* operator new[](std::size_t size) {
        std::cout << "Custom new[] for size " << size << std::endl;
        return std::malloc(size);
    }

    static void operator delete[](void* ptr) noexcept {
        std::cout << "Custom delete[]" << std::endl;
        std::free(ptr);
    }

    static void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
        std::cout << "Custom nothrow new" << std::endl;
        return std::malloc(size);
    }

    static void operator delete(void* ptr, const std::nothrow_t&) noexcept {
        std::cout << "Custom nothrow delete" << std::endl;
        std::free(ptr);
    }

    static void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
        std::cout << "Custom nothrow new[]" << std::endl;
        return std::malloc(size);
    }

    static void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
        std::cout << "Custom nothrow delete[]" << std::endl;
        std::free(ptr);
    }
};

class Client : public Entity {
public:
    using Entity::operator new;
    using Entity::operator delete;
    using Entity::operator new[];
    using Entity::operator delete[];
};

int main() {
    std::cout << "--- Single object ---" << std::endl;
    Client* c = new Client();
    delete c;

    std::cout << "\n--- Array ---" << std::endl;
    Client* arr = new Client[3];
    delete[] arr;

    std::cout << "\n--- Nothrow ---" << std::endl;
    Client* nt = new (std::nothrow) Client();
    operator delete(nt, std::nothrow);

    return 0;
}