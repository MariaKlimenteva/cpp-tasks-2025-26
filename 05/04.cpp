#include <print>

template <typename T>
class Entity : public T
{
public:
    using T::T;
};

class StrategyA
{
public:
    void test() const 
    { 
        std::print("StrategyA::test execution\n"); 
    }
};

class StrategyB
{
public:
    void test() const 
    { 
        std::print("StrategyB::test execution\n"); 
    }
};

int main()
{
    Entity<StrategyA> entity_a;
    entity_a.test();

    Entity<StrategyB> entity_b;
    entity_b.test();
}
// g++ -std=c++23 04.cpp -o 04