#include <iostream>
#include <array>
#include <cstddef>
#include <memory>
#include <bit>
#include <utility>

class Entity {
public:
    struct Implementation {
        int x = 42;
        int y = 100;
        
        Implementation() = default;
        Implementation(int x, int y) : x(x), y(y) {}
    };

private:
    alignas(std::max_align_t) std::array<std::byte, sizeof(Implementation)> storage;

public:
    Entity() {
        static_assert(sizeof(Implementation) <= sizeof(storage));
        static_assert(alignof(Implementation) <= alignof(std::max_align_t));
        new (storage.data()) Implementation();
    }

    // Move constructor
    Entity(Entity&& other) noexcept {
        auto* other_impl = other.get();
        new (storage.data()) Implementation(std::move(*other_impl));
    }

    // Move assignment - demonstrates reuse of once-allocated memory
    Entity& operator=(Entity&& other) noexcept {
        if (this != &other) {
            std::destroy_at(get()); // Destroy current object
            auto* other_impl = other.get();
            // Reuse the same 'storage' to construct new implementation
            new (storage.data()) Implementation(std::move(*other_impl));
        }
        return *this;
    }

    // Explicitly delete copy operations as they are not implemented and would break the logic
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

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
};

/*
Обоснование накладных расходов и влияние на производительность оригинального паттерна Pimpl:
1. Динамическое выделение памяти: В классическом Pimpl объект реализации создается в куче (через new или std::unique_ptr). 
   Это влечет за собой накладные расходы на работу аллокатора и фрагментацию памяти.
2. Разыменование указателя (Indirection): Доступ к данным реализации требует перехода по указателю. 
   Это лишняя операция процессора и потенциальный cache miss, так как объект реализации 
   может находиться далеко в памяти от основного объекта.
3. Ограничение инлайнинга: Поскольку детали реализации скрыты в другом файле трансляции, компилятор не может 
   автоматически встраивать вызовы методов реализации в месте их вызова в клиентском коде.
4. Накладные расходы на владение: Использование std::unique_ptr добавляет небольшой оверхед на проверку 
   указателя на null и вызов деструктора через таблицу виртуальных функций (если деструктор виртуальный).

Fast Pimpl решает первые две проблемы, размещая реализацию прямо внутри буфера 
в стеке (или внутри основного объекта), сохраняя при этом преимущество скрытия деталей реализации от ABI.
*/

int main() {
    Entity e1;
    std::cout << "Non-const get: x=" << e1.get()->x << ", y=" << e1.get()->y << std::endl;
    
    const Entity e2;
    std::cout << "Const get: x=" << e2.get()->x << ", y=" << e2.get()->y << std::endl;
    
    Entity e3 = std::move(e1);
    std::cout << "After move construct, e3: x=" << e3.get()->x << std::endl;

    Entity e4;
    e4 = std::move(e3);
    std::cout << "After move assignment, e4: x=" << e4.get()->x << std::endl;

    return 0;
}
