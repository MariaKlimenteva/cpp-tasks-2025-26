#include <print>

class Entity_v1
{
private:
    int m_value = 10;

public:
    int get() const { return m_value; }
};

class Entity_v2
{
public:
    int m_value;
};

int main()
{
    Entity_v1 entity;

    Entity_v2& hack_v1 = reinterpret_cast<Entity_v2&>(entity);
    hack_v1.m_value = 42;

    int* hack_v2 = reinterpret_cast<int*>(&entity);
    *hack_v2 = 99;

    std::print("{}\n", entity.get());
}
// g++ -std=c++23 01.cpp -o 01