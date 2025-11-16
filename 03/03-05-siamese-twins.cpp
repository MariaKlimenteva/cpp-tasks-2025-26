#include <iostream>

class Entity_v1
{
public:
    virtual ~Entity_v1() = default;
    virtual void test()
    {
        std::cout << "Executing default implementation of Entity_v1::test()" << std::endl;
    }
};

class Entity_v2
{
public:
    virtual ~Entity_v2() = default;
    virtual void test()
    {
        std::cout << "Executing default implementation of Entity_v2::test()" << std::endl;
    }
};

class Adapter_v1 : public Entity_v1
{
public:
    virtual void test_v1() = 0;

    void test() override final
    {
        this->test_v1();
    }
};

class Adapter_v2 : public Entity_v2
{
public:
    virtual void test_v2() = 0;

    void test() override final
    {
        this->test_v2();
    }
};

class Client : public Adapter_v1, public Adapter_v2
{
public:
    void test_v1() override
    {
        std::cout << "Client's implementation for Entity_v1 logic." << std::endl;
    }

    void test_v2() override
    {
        std::cout << "Client's implementation for Entity_v2 logic." << std::endl;
    }
};

int main()
{
    Client client;

    Entity_v1* p1 = &client;
    Entity_v2* p2 = &client;

    std::cout << "Calling test() via Entity_v1 pointer:" << std::endl;
    p1->test();

    std::cout << "\nCalling test() via Entity_v2 pointer:" << std::endl;
    p2->test();

    return 0;
}

// g++ -std=c++17 -o out 03-05-siamese-twins.cpp
// ./out