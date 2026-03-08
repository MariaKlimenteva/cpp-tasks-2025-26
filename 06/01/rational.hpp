#pragma once

#include <iostream>
#include <compare>
#include <numeric>

class Rational
{
public:
    Rational(int n = 0, int d = 1);

    int numerator() const;
    int denominator() const;

    auto operator<=>(const Rational&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

private:
    int m_num;
    int m_den;

    void simplify();
};