#include <iostream>
#include <array>
#include <cstddef>
#include <memory>
#include <bit>

class Entity {
    struct Implementation {
        int x = 42;
        int y = 100;
    };

    alignas(std::max_align_t) std::array<std::byte, 16> storage;

public:
    Entity() {
        static_assert(sizeof(Implementation) <= sizeof(storage));
        static_assert(alignof(Implementation) <= alignof(std::max_align_t));
        new (storage.data()) Implementation();
    }

    ~Entity() {
        std::destroy_at(get());
    }

    Implementation* get() {
        auto ptr = std::bit_cast<Implementation*>(storage.data());
        return std::launder(ptr);
    }

    const Implementation* get() const {
        auto ptr = std::bit_cast<const Implementation*>(storage.data());
        return std::launder(ptr);
    }

    void print() const {
        const auto* impl = get();
        std::cout << "Implementation: x=" << impl->x << ", y=" << impl->y << std::endl;
    }
};

int main() {
    Entity e;
    e.print();
    return 0;
}