#include "rational.hpp"

Rational::Rational(int n, int d) : m_num(n), m_den(d)
{
    simplify();
}

int Rational::numerator() const
{
    return m_num;
}

int Rational::denominator() const
{
    return m_den;
}

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
    return os << r.m_num << "/" << r.m_den;
}

void Rational::simplify()
{
    if (m_den < 0) { m_num = -m_num; m_den = -m_den; }
    int gcd = std::gcd(std::abs(m_num), m_den);
    m_num /= gcd;
    m_den /= gcd;
}