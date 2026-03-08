#include <iostream>
#include <string>
#include <stdexcept>
#include <print>

enum class Status
{
    success,
    failure
};

class Person
{
public:
    Person(std::string name, int grade, int salary, int id)
        : m_name(std::move(name)), m_grade(grade), m_salary(salary), m_id(id)
    {}

    const std::string& name() const 
    { 
        if (m_name.empty()) throw std::runtime_error("Empty name");
        return m_name; 
    }

    int grade() const { return m_grade; }
    
    int salary() const { return m_salary; }
    
    int id() const { return m_id; }

private:
    std::string m_name;
    int m_grade;
    int m_salary;
    int m_id;
};

void save(Status status, int id)
{
    if (id < 0) throw std::runtime_error("Invalid ID");
    
    std::print("Saved ID: {} with Status: {}\n", id, (status == Status::success ? "Success" : "Failure"));
}

void test(Person const & person)
{
    try
    {
        std::cout << "test : " << person.name() << '\n';

        if (person.grade() == 10 || person.salary() > 1'000'000)
        {
            save(Status::success, person.id());
        }
        else
        {
            save(Status::failure, person.id());
        }
    }
    catch (const std::exception& e)
    {
        std::print(stderr, "Exception caught in test: {}\n", e.what());
    }
}

int main()
{
    Person p1("Ivan", 10, 500, 1);
    test(p1);

    Person p2("Petr", 5, 2'000'000, 2);
    test(p2);

    Person p3("Sidor", 5, 500, 3);
    test(p3);

    Person p4("", 10, 100, 4);
    test(p4);

    Person p5("Error", 10, 100, -1);
    test(p5);
}
// g++ -std=c++23 03.cpp -o 03