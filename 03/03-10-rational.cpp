#include <iostream>
#include <numeric>
#include <cmath>
#include <cassert>
#include <compare>
#include <sstream>

class Rational
{
public:
    Rational(long long num = 0, long long den = 1) : m_num(num), m_den(den)
    {
        reduce();
    }

    auto& operator+=(const Rational& other)
    {
        auto lcm = std::lcm(m_den, other.m_den);
        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;
        reduce();
        return *this;
    }

    auto& operator-=(const Rational& other)
    {
        return *this += Rational(other.m_num * -1, other.m_den);
    }

    auto& operator*=(const Rational& other)
    {
        m_num *= other.m_num;
        m_den *= other.m_den;
        reduce();
        return *this;
    }

    auto& operator/=(const Rational& other)
    {
        return *this *= Rational(other.m_den, other.m_num);
    }

    const auto operator++(int) { auto x = *this; *this += 1; return x; }
    const auto operator--(int) { auto x = *this; *this -= 1; return x; }
    auto& operator++() { *this += 1; return *this; }
    auto& operator--() { *this -= 1; return *this; }

    friend auto operator+(Rational lhs, const Rational& rhs) { return lhs += rhs; }
    friend auto operator-(Rational lhs, const Rational& rhs) { return lhs -= rhs; }
    friend auto operator*(Rational lhs, const Rational& rhs) { return lhs *= rhs; }
    friend auto operator/(Rational lhs, const Rational& rhs) { return lhs /= rhs; }
    
    friend std::ostream& operator<<(std::ostream& stream, const Rational& rational)
    {
        return stream << rational.m_num << '/' << rational.m_den;
    }
    
    friend std::istream& operator>>(std::istream& stream, Rational& rational)
    {
        long long num, den;
        char slash;
        if (stream >> num >> slash && slash == '/' && stream >> den) {
            rational.m_num = num;
            rational.m_den = den;
            rational.reduce();
        } else {
            stream.setstate(std::ios_base::failbit);
        }
        return stream;
    }

    friend std::strong_ordering operator<=>(const Rational& lhs, const Rational& rhs)
    {
        return (lhs.m_num * rhs.m_den) <=> (rhs.m_num * lhs.m_den);
    }

    friend bool operator==(const Rational& lhs, const Rational& rhs)
    {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

private:
    void reduce()
    {
        if (m_den == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        if (m_den < 0)
        {
            m_num = -m_num;
            m_den = -m_den;
        }
        auto common_divisor = std::gcd(m_num, m_den);
        m_num /= common_divisor;
        m_den /= common_divisor;
    }

    long long m_num;
    long long m_den;
};

int main()
{
    Rational r1(1, 2);
    Rational r2(3, 4);
    Rational r3(2, 4);

    std::cout << "r1 = " << r1 << std::endl; // 1/2
    std::cout << "r2 = " << r2 << std::endl; // 3/4
    std::cout << "r3 = " << r3 << std::endl; // 1/2 (after reduction)
    std::cout << std::endl;

    std::cout << "--- Testing spaceship operator (<=>) ---" << std::endl;
    assert((r1 <=> r2) < 0);
    std::cout << "r1 <=> r2 is less (correct)" << std::endl;
    assert((r2 <=> r1) > 0);
    std::cout << "r2 <=> r1 is greater (correct)" << std::endl;
    assert((r1 <=> r3) == 0);
    std::cout << "r1 <=> r3 is equal (correct)" << std::endl;
    std::cout << std::endl;

    std::cout << "--- Testing equality operator (==) ---" << std::endl;
    assert(r1 == r3);
    std::cout << "r1 == r3 is true (correct)" << std::endl;
    assert(!(r1 == r2));
    std::cout << "r1 == r2 is false (correct)" << std::endl;
    std::cout << std::endl;

    std::cout << "--- Testing compiler-synthesized operators ---" << std::endl;
    assert(r1 < r2);
    std::cout << "r1 < r2 is true (correct)" << std::endl;
    assert(r2 > r1);
    std::cout << "r2 > r1 is true (correct)" << std::endl;
    assert(r1 <= r3);
    std::cout << "r1 <= r3 is true (correct)" << std::endl;
    assert(r1 >= r3);
    std::cout << "r1 >= r3 is true (correct)" << std::endl;
    assert(r1 != r2);
    std::cout << "r1 != r2 is true (correct)" << std::endl;

    std::cout << "\nAll comparison tests passed successfully!" << std::endl;
    
    return 0;
}

// g++ -std=c++20 -o out 03-10-rational.cpp
// ./out