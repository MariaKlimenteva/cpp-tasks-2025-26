#include <cassert>
#include <cmath>
#include <compare>
#include <iostream>
#include <numeric>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class Exception : public std::exception {
public:
  Exception(char const *message) : m_message(message) {}

  char const *what() const noexcept override { return m_message; }

private:
  char const *m_message;
};

template <typename T> struct addable {
  friend T operator+(T lhs, const T &rhs) { return lhs += rhs; }
};

template <typename T> struct subtractable {
  friend T operator-(T lhs, const T &rhs) { return lhs -= rhs; }
};

template <typename T> struct multipliable {
  friend T operator*(T lhs, const T &rhs) { return lhs *= rhs; }
};

template <typename T> struct dividable {
  friend T operator/(T lhs, const T &rhs) { return lhs /= rhs; }
};

template <typename T> struct incrementable {
  friend T operator++(T &self, int) {
    T temp = self;
    ++self;
    return temp;
  }
};

template <typename T> struct decrementable {
  friend T operator--(T &self, int) {
    T temp = self;
    --self;
    return temp;
  }
};

template <typename T>
class Rational : public addable<Rational<T>>,
                 public subtractable<Rational<T>>,
                 public multipliable<Rational<T>>,
                 public dividable<Rational<T>>,
                 public incrementable<Rational<T>>,
                 public decrementable<Rational<T>> {
public:
  Rational(T num = 0, T den = 1) : m_num(num), m_den(den) {
    if (m_den == 0) {
      throw Exception("Denominator cannot be zero.");
    }
    reduce();
  }

  explicit operator double() const { return 1.0 * m_num / m_den; }

  auto &operator+=(Rational const &other) {
    auto lcm = std::lcm(m_den, other.m_den);
    m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
    m_den = lcm;
    reduce();
    return *this;
  }

  auto &operator-=(Rational const &other) {
    return *this += Rational(other.m_num * -1, other.m_den);
  }

  auto &operator*=(Rational const &other) {
    m_num *= other.m_num;
    m_den *= other.m_den;
    reduce();
    return *this;
  }

  auto &operator/=(Rational const &other) {
    if (other.m_num == 0) {
      throw Exception("Division by zero.");
    }
    return *this *= Rational(other.m_den, other.m_num);
  }

  auto &operator++() {
    *this += 1;
    return *this;
  }

  auto &operator--() {
    *this -= 1;
    return *this;
  }

  friend bool operator==(Rational const &lhs, Rational const &rhs) {
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
  }

  friend std::strong_ordering operator<=>(Rational const &lhs,
                                          Rational const &rhs) {
    return (lhs.m_num * rhs.m_den) <=> (rhs.m_num * lhs.m_den);
  }

  friend auto &operator>>(std::istream &stream, Rational &rational) {
    return (stream >> rational.m_num).ignore() >> rational.m_den;
  }

  friend auto &operator<<(std::ostream &stream, Rational const &rational) {
    return stream << rational.m_num << '/' << rational.m_den;
  }

private:
  void reduce() {
    if (m_den == 0) return;
    if (m_den < 0) {
      m_num = -m_num;
      m_den = -m_den;
    }
    auto gcd = std::gcd(m_num, m_den);
    m_num /= gcd;
    m_den /= gcd;
  }

  T m_num = 0;
  T m_den = 1;
};

void demo_rational_exception() {
  try {
    Rational<int> r(1, 0);
  } catch (std::exception const &e) {
    std::cerr << "rational_exception: " << e.what() << std::endl;
  }

  try {
    Rational<int> a(1, 1);
    Rational<int> b(0, 1);
    a /= b;
  } catch (std::exception const &e) {
    std::cerr << "rational_exception (division): " << e.what() << std::endl;
  }
}

void demo_bad_alloc() {
  try {
    std::vector<int> v(std::numeric_limits<std::size_t>::max());
  } catch (std::exception const &e) {
    std::cerr << "bad_alloc: " << e.what() << std::endl;
  }
}

void demo_bad_optional_access() {
  try {
    std::optional<int> o;
    o.value();
  } catch (std::exception const &e) {
    std::cerr << "bad_optional_access: " << e.what() << std::endl;
  }
}

void demo_bad_variant_access() {
  try {
    std::variant<int, double> v;
    v = 1;
    std::get<double>(v);
  } catch (std::exception const &e) {
    std::cerr << "bad_variant_access: " << e.what() << std::endl;
  }
}

void demo_length_error() {
  try {
    std::vector<int> v;
    v.resize(v.max_size() + 1);
  } catch (std::exception const &e) {
    std::cerr << "length_error: " << e.what() << std::endl;
  }
}

void demo_out_of_range() {
  try {
    std::vector<int> v;
    auto _ = v.at(0);
  } catch (std::exception const &e) {
    std::cerr << "out_of_range: " << e.what() << std::endl;
  }
}

int main() {
  demo_rational_exception();
  demo_bad_alloc();
  demo_bad_optional_access();
  demo_bad_variant_access();
  demo_length_error();
  demo_out_of_range();
}
// g++ -std=c++23 02.cpp -o 02