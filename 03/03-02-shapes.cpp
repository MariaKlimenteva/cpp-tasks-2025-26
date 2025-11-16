#include <iostream>
#include <cmath>
#include <numbers>
#include <stdexcept>

class Triangle
{
public:
    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c)
    {
        if (m_a <= 0 || m_b <= 0 || m_c <= 0 || (m_a + m_b <= m_c) || (m_a + m_c <= m_b) || (m_b + m_c <= m_a))
        {
            throw std::invalid_argument("Invalid triangle sides");
        }
    }

    double perimeter() const
    {
        return m_a + m_b + m_c;
    }

    double area() const
    {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
    }

private:
    double m_a;
    double m_b;
    double m_c;
};

class Square
{
public:
    Square(double side) : m_side(side)
    {
        if (m_side <= 0)
        {
             throw std::invalid_argument("Invalid square side");
        }
    }

    double perimeter() const
    {
        return 4 * m_side;
    }

    double area() const
    {
        return m_side * m_side;
    }

private:
    double m_side;
};

class Circle
{
public:
    Circle(double radius) : m_radius(radius)
    {
        if (m_radius <= 0)
        {
            throw std::invalid_argument("Invalid circle radius");
        }
    }

    double perimeter() const
    {
        return 2 * std::numbers::pi * m_radius;
    }

    double area() const
    {
        return std::numbers::pi * m_radius * m_radius;
    }

private:
    double m_radius;
};

int main()
{
    try
    {
        Triangle t(3.0, 4.0, 5.0);
        Square s(4.0);
        Circle c(10.0);

        std::cout << "Triangle:" << std::endl;
        std::cout << "  Perimeter: " << t.perimeter() << std::endl;
        std::cout << "  Area: " << t.area() << std::endl;
        std::cout << std::endl;

        std::cout << "Square:" << std::endl;
        std::cout << "  Perimeter: " << s.perimeter() << std::endl;
        std::cout << "  Area: " << s.area() << std::endl;
        std::cout << std::endl;

        std::cout << "Circle:" << std::endl;
        std::cout << "  Perimeter (Circumference): " << c.perimeter() << std::endl;
        std::cout << "  Area: " << c.area() << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error creating shape: " << e.what() << std::endl;
    }
    
    return 0;
}

// g++ -std=c++20 -o out 03-02-shapes.cpp
// ./out