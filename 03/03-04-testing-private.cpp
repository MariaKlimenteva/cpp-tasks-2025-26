#include <iostream>

class Entity;

class Attorney_for_Tester_v1
{
private:
    friend class Tester_v1;
    static void call_test_v1(Entity& e);
};

class Attorney_for_Tester_v2
{
private:
    friend class Tester_v2;
    static void call_test_v2(Entity& e);
};

class Entity
{
public:
    Entity(int val1, double val2) : private_data_1(val1), private_data_2(val2) {}

private:
    friend class Attorney_for_Tester_v1;
    friend class Attorney_for_Tester_v2;

    void test_v1()
    {
        std::cout << "Executing Entity::test_v1(). Accessing private_data_1: "
                  << this->private_data_1 << std::endl;
    }

    void test_v2()
    {
        std::cout << "Executing Entity::test_v2(). Accessing private_data_2: "
                  << this->private_data_2 << std::endl;
    }

    int private_data_1;
    double private_data_2;
};


void Attorney_for_Tester_v1::call_test_v1(Entity& e)
{
    e.test_v1();
}

void Attorney_for_Tester_v2::call_test_v2(Entity& e)
{
    e.test_v2();
}

class Tester_v1
{
public:
    void run(Entity& entity)
    {
        std::cout << "Tester_v1 is running..." << std::endl;
        Attorney_for_Tester_v1::call_test_v1(entity);
    }
};

class Tester_v2
{
public:
    void run(Entity& entity)
    {
        std::cout << "Tester_v2 is running..." << std::endl;
        Attorney_for_Tester_v2::call_test_v2(entity);
    }
};

int main()
{
    Entity my_entity(42, 3.14);

    Tester_v1 tester1;
    Tester_v2 tester2;

    std::cout << "--- Running Test Suite ---" << std::endl;
    tester1.run(my_entity);
    tester2.run(my_entity);
    std::cout << "--- Test Suite Finished ---" << std::endl;

    // 'Entity::test_v1' is private
    // my_entity.test_v1();

    // 'Attorney_for_Tester_v1::call_test_v1' is private
    // Attorney_for_Tester_v1::call_test_v1(my_entity);

    // 'Attorney_for_Tester_2::call_test_v2' is private,
    // и Tester_v1 не является его другом.
    // Attorney_for_Tester_v2::call_test_v2(my_entity);

    return 0;
}
// g++ -std=c++17 -o out 03-04-testing-private.cpp
// ./out