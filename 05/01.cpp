#include <iostream>
#include <string>
#include <utility>

class Person
{
public:
    std::string m_name;
    int m_age = 0;
    int m_grade = 0;

    void print_info() const
    {
        std::cout << "Name: " << m_name 
                  << ", Age: " << m_age 
                  << ", Grade: " << m_grade << std::endl;
    }
};

class Builder
{
public:
    Builder() : m_person(new Person()) {}

    Builder& name(std::string name)
    {
        if (m_person) m_person->m_name = std::move(name);
        return *this;
    }

    Builder& age(int age)
    {
        if (m_person) m_person->m_age = age;
        return *this;
    }

    Builder& grade(int grade)
    {
        if (m_person) m_person->m_grade = grade;
        return *this;
    }

    Person* get()
    {
        Person* result = m_person;
        m_person = nullptr; 
        return result;
    }

    ~Builder()
    {
        delete m_person;
    }

private:
    Person* m_person = nullptr;
};

int main()
{
    Builder builder;
    
    auto person = builder.name("Ivan").age(25).grade(10).get();

    if (person)
    {
        person->print_info();
        delete person;
    }
}

// g++ -std=c++23 01.cpp -o 01
// ./01