#include <print>

class Entity 
{
public:
    virtual ~Entity() = default;
    virtual void test() const = 0;
};

class Client : public virtual Entity 
{ 
public: 
    void test() const override 
    { 
        std::print("Client::test\n");
    } 
};

class Server : public virtual Entity 
{ 
public: 
    void test() const override 
    { 
        std::print("Server::test\n");
    } 
};

template <typename T>
class Decorator : public T, public virtual Entity
{
public:
    void test() const override
    { 
        std::print("Decorator::test : ");
        T::test();
    }
};

int main()
{
    Entity* entity = new Decorator<Client>;

    entity->test();

    delete entity;
}
// g++ -std=c++23 02.cpp -o 02