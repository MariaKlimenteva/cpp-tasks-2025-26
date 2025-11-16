#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <numbers>
#include <stdexcept>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual const char* get_name() const = 0;
};

class Triangle : public Shape
{
public:
    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c)
    {
        if (m_a <= 0 || m_b <= 0 || m_c <= 0 || (m_a + m_b <= m_c) || (m_a + m_c <= m_b) || (m_b + m_c <= m_a))
        {
            throw std::invalid_argument("Invalid triangle sides");
        }
    }

    double perimeter() const override final
    {
        return m_a + m_b + m_c;
    }

    double area() const override final
    {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
    }

    const char* get_name() const override
    {
        return "Triangle";
    }

private:
    double m_a, m_b, m_c;
};

class Square final : public Shape
{
public:
    Square(double side) : m_side(side)
    {
        if (m_side <= 0)
        {
             throw std::invalid_argument("Invalid square side");
        }
    }

    double perimeter() const override
    {
        return 4 * m_side;
    }

    double area() const override
    {
        return m_side * m_side;
    }
    
    const char* get_name() const override
    {
        return "Square";
    }

private:
    double m_side;
};

class Circle final : public Shape
{
public:
    Circle(double radius) : m_radius(radius)
    {
        if (m_radius <= 0)
        {
            throw std::invalid_argument("Invalid circle radius");
        }
    }

    double perimeter() const override
    {
        return 2 * std::numbers::pi * m_radius;
    }

    double area() const override
    {
        return std::numbers::pi * m_radius * m_radius;
    }

    const char* get_name() const override
    {
        return "Circle";
    }
private:
    double m_radius;
};

int main()
{
    std::vector<Shape*> shapes;

    try
    {
        shapes.push_back(new Triangle(3.0, 4.0, 5.0));
        shapes.push_back(new Square(4.0));
        shapes.push_back(new Circle(10.0));
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error creating shape: " << e.what() << std::endl;
        for (Shape* shape : shapes)
        {
            delete shape;
        }
        return 1;
    }

    for (const Shape* shape : shapes)
    {
        std::cout << "Figure: " << shape->get_name() << std::endl;
        std::cout << "  Perimeter: " << shape->perimeter() << std::endl;
        std::cout << "  Area: " << shape->area() << std::endl;
        std::cout << std::endl;
    }

    for (Shape* shape : shapes)
    {
        delete shape;
    }
    shapes.clear();

    return 0;
}

// g++ -std=c++20 -o out 03-06-virtual-shapes.cpp
// ./out