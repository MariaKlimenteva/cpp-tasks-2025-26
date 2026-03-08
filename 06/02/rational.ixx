module;

#include <compare>
#include <iostream>
#include <numeric>

export module rational;

export namespace math
{
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
}