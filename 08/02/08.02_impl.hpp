#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////

class Integer
{
	friend std::ostream & operator << (std::ostream & output, Integer const & integer);

	friend std::istream & operator >> (std::istream & input, Integer & integer);

//  ----------------------------------------------------------------------------------------

	friend bool operator < (Integer const & x, Integer const & y);

	friend bool operator > (Integer const & x, Integer const & y);

	friend bool operator <= (Integer const & x, Integer const & y);

	friend bool operator >= (Integer const & x, Integer const & y);

	friend bool operator == (Integer const & x, Integer const & y);

	friend bool operator != (Integer const & x, Integer const & y);

//  ----------------------------------------------------------------------------------------

	friend Integer operator + (Integer x, Integer const & y);

	friend Integer operator - (Integer x, Integer const & y);

	friend Integer operator * (Integer const & x, Integer const & y);

	friend Integer operator / (Integer const & x, Integer const & y);

	friend Integer operator % (Integer const & x, Integer const & y);

//  ----------------------------------------------------------------------------------------

	friend Integer & operator += (Integer & x, Integer const & y);

	friend Integer & operator -= (Integer & x, Integer const & y);

	friend Integer & operator *= (Integer & x, Integer const & y);

	friend Integer & operator /= (Integer & x, Integer const & y);

	friend Integer & operator %= (Integer & x, Integer const & y);

//  ----------------------------------------------------------------------------------------

	friend Integer operator - (Integer x);

	friend Integer operator + (Integer x);

//  ----------------------------------------------------------------------------------------

	friend Integer & operator ++ (Integer & x);

	friend Integer operator ++ (Integer & x, int);

	friend Integer & operator -- (Integer & x);

	friend Integer operator -- (Integer & x, int);

//  ----------------------------------------------------------------------------------------

	friend Integer abs(Integer const & x);

	friend Integer pow(Integer const & x, unsigned int y);

	friend Integer sqrt(Integer const & x);

	friend Integer multiply(Integer const & x, Integer const & y);

	friend Integer subtract(Integer const & x, Integer const & y);

public :

	Integer() = default;

	Integer(long long x);

	Integer(std::string const & x);

//  ----------------------------------------------------------------------------------------

	bool is_negative() const;

	bool is_positive() const;

	bool is_zero() const;

private :

	void m_normalize();

	void m_shift();

//  ----------------------------------------------------------------------------------------

private :

	static constexpr int s_base = 1000'000'000;

//  ----------------------------------------------------------------------------------------

private :

	std::vector < int > m_digits;

	bool m_is_negative = false;
};

////////////////////////////////////////////////////////////////////////////////////////////

Integer::Integer(long long x)
{
	if (x < 0)
	{
		m_is_negative = true;

		x = - x;
	}

	do
	{
		m_digits.push_back(x % s_base);

		x /= s_base;
	}
	while (x != 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer::Integer(std::string const & x)
{
	m_is_negative = (x.front() == '-');

//  ----------------------------------------------------------------------------------------

	auto first = (x.front() == '-' || x.front() == '+') ? 1 : 0;

//  ----------------------------------------------------------------------------------------

	for (auto i = static_cast < int > (x.length()); i > first; i -= 9)
	{
		auto digit = 0;

		auto begin = std::max(first, i - 9);

		for (auto j = begin; j < i; ++ j)
		{
			digit = digit * 10 + (x.at(j) - '0');
		}

		m_digits.push_back(digit);
	}

//  ----------------------------------------------------------------------------------------

	m_normalize();
}

////////////////////////////////////////////////////////////////////////////////////////////

bool Integer::is_negative() const { return m_is_negative; }

bool Integer::is_positive() const { return !m_is_negative; }

bool Integer::is_zero() const { return m_digits.empty() || (m_digits.size() == 1 && m_digits.front() == 0); }

////////////////////////////////////////////////////////////////////////////////////////////

void Integer::m_normalize()
{
	while (m_digits.size() > 1 && m_digits.back() == 0)
	{
		m_digits.pop_back();
	}

	if (m_digits.size() == 1 && m_digits.front() == 0)
	{
		m_is_negative = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void Integer::m_shift()
{
	if (m_digits.empty())
	{
		m_digits.push_back(0);
	}
	else
	{
		m_digits.insert(m_digits.begin(), 0);

		for (auto i = 0; i < m_digits.size() - 1; ++ i)
		{
			m_digits.at(i) += m_digits.at(i + 1) / s_base;

			m_digits.at(i + 1) %= s_base;
		}

		m_normalize();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & operator << (std::ostream & output, Integer const & integer)
{
	if (integer.is_zero()) return output << 0;

//  ----------------------------------------------------------------------------------------

	if (integer.m_is_negative) output << '-';

//  ----------------------------------------------------------------------------------------

	output << integer.m_digits.back();

	for (auto i = static_cast < int > (integer.m_digits.size()) - 2; i >= 0; -- i)
	{
		output.width(9);
		output.fill('0');

		output << integer.m_digits.at(i);
	}

	return output;
}

////////////////////////////////////////////////////////////////////////////////////////////

std::istream & operator >> (std::istream & input, Integer & integer)
{
	std::string s;

	input >> s;

	integer = Integer(s);

	return input;
}

////////////////////////////////////////////////////////////////////////////////////////////

bool operator < (Integer const & x, Integer const & y)
{
	if (x.m_is_negative != y.m_is_negative) return x.m_is_negative;

	if (x.m_is_negative) return y < - x;

//  ----------------------------------------------------------------------------------------

	if (x.m_digits.size() != y.m_digits.size())
	{
		return x.m_digits.size() < y.m_digits.size();
	}

	for (auto i = static_cast < int > (x.m_digits.size()) - 1; i >= 0; -- i)
	{
		if (x.m_digits.at(i) != y.m_digits.at(i))
		{
			return x.m_digits.at(i) < y.m_digits.at(i);
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////

bool operator > (Integer const & x, Integer const & y) { return y < x; }

bool operator <= (Integer const & x, Integer const & y) { return !(y < x); }

bool operator >= (Integer const & x, Integer const & y) { return !(x < y); }

bool operator == (Integer const & x, Integer const & y) { return !(x < y) && !(y < x); }

bool operator != (Integer const & x, Integer const & y) { return (x < y) || (y < x); }

////////////////////////////////////////////////////////////////////////////////////////////

Integer operator - (Integer x)
{
	x.m_is_negative = !x.m_is_negative;

	return x;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer operator + (Integer x) { return x; }

////////////////////////////////////////////////////////////////////////////////////////////

Integer & operator ++ (Integer & x) { return x += 1; }

Integer operator ++ (Integer & x, int) { auto old = x; ++ x; return old; }

Integer & operator -- (Integer & x) { return x -= 1; }

Integer operator -- (Integer & x, int) { auto old = x; -- x; return old; }

////////////////////////////////////////////////////////////////////////////////////////////

Integer operator + (Integer x, Integer const & y) { return x += y; }

Integer operator - (Integer x, Integer const & y) { return x -= y; }

Integer operator * (Integer const & x, Integer const & y) { return multiply(x, y); }

Integer operator / (Integer const & x, Integer const & y)
{
	if (y.is_zero()) throw;

//  ----------------------------------------------------------------------------------------

	auto result = Integer();

	auto current = Integer();

//  ----------------------------------------------------------------------------------------

	result.m_digits.resize(x.m_digits.size());

	for (auto i = static_cast < int > (x.m_digits.size()) - 1; i >= 0; -- i)
	{
		current.m_shift();

		current.m_digits.at(0) = x.m_digits.at(i);

		current.m_normalize();

		auto a = 0;
		auto b = Integer::s_base;

		while (a <= b)
		{
			auto m = (a + b) / 2;

			if (multiply(abs(y), m) > current)
			{
				b = m - 1;
			}
			else
			{
				a = m + 1;
			}
		}

		result.m_digits.at(i) = a - 1;

		current = subtract(current, multiply(abs(y), a - 1));
	}

	result.m_is_negative = x.m_is_negative != y.m_is_negative;

	result.m_normalize();

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer operator % (Integer const & x, Integer const & y) { return subtract(x, multiply(x / y, y)); }

////////////////////////////////////////////////////////////////////////////////////////////

Integer & operator += (Integer & x, Integer const & y)
{
	if (x.m_is_negative == y.m_is_negative)
	{
		auto carry = 0;

		for (auto i = 0; i < std::max(x.m_digits.size(), y.m_digits.size()) || carry; ++ i)
		{
			if (i == x.m_digits.size()) x.m_digits.push_back(0);

			x.m_digits.at(i) += carry + (i < y.m_digits.size() ? y.m_digits.at(i) : 0);

			carry = x.m_digits.at(i) >= Integer::s_base;

			if (carry) x.m_digits.at(i) -= Integer::s_base;
		}
	}
	else
	{
		x = subtract(x, - y);
	}

	return x;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer & operator -= (Integer & x, Integer const & y) { return x += - y; }

Integer & operator *= (Integer & x, Integer const & y) { return x = multiply(x, y); }

Integer & operator /= (Integer & x, Integer const & y) { return x = x / y; }

Integer & operator %= (Integer & x, Integer const & y) { return x = x % y; }

////////////////////////////////////////////////////////////////////////////////////////////

Integer abs(Integer const & x) { return x.is_negative() ? - x : x; }

////////////////////////////////////////////////////////////////////////////////////////////

Integer pow(Integer const & x, unsigned int y)
{
	auto result = Integer(1);

	for (auto i = 0u; i < y; ++ i)
	{
		result = multiply(result, x);
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer sqrt(Integer const & x)
{
	if (x.is_negative()) throw;

	if (x.is_zero()) return 0;

//  ----------------------------------------------------------------------------------------

	auto result = Integer(1);

	auto is_small = x.m_digits.size() < 3;

	for (auto i = 0; i < (is_small ? 4 : 2); ++ i)
	{
		for (auto j = (x.m_digits.size() - 1) / 2; j >= 0; -- j)
		{
			auto next = result;

			next.m_digits.at(j) ++;

			if (multiply(next, next) <= x) result = next;
		}
	}

	for (auto i = (x.m_digits.size() - 1) / 2; i >= 0; -- i)
	{
		for (auto j = 0; j < 9; ++ j)
		{
			auto next = result;

			auto power = Integer(1);

			for (auto k = 0; k < i; ++ k)
			{
				power = multiply(power, 10);
			}

			next += power;

			if (multiply(next, next) <= x) result = next;
		}
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer multiply(Integer const & x, Integer const & y)
{
	auto result = Integer();

	result.m_digits.resize(x.m_digits.size() + y.m_digits.size());

	for (auto i = 0; i < x.m_digits.size(); ++ i)
	{
		auto carry = 0;

		for (auto j = 0; j < y.m_digits.size() || carry; ++ j)
		{
			auto current = result.m_digits.at(i + j) +
				x.m_digits.at(i) * 1ll * (j < y.m_digits.size() ? y.m_digits.at(j) : 0) + carry;

			result.m_digits.at(i + j) = current % Integer::s_base;

			carry = current / Integer::s_base;
		}
	}

	result.m_is_negative = x.m_is_negative != y.m_is_negative;

	result.m_normalize();

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

Integer subtract(Integer const & x, Integer const & y)
{
	if (x.m_is_negative != y.m_is_negative) return x + (- y);

	if (abs(x) < abs(y)) return - (y - x);

//  ----------------------------------------------------------------------------------------

	auto result = x;

	auto carry = 0;

	for (auto i = 0; i < y.m_digits.size() || carry; ++ i)
	{
		result.m_digits.at(i) -= carry + (i < y.m_digits.size() ? y.m_digits.at(i) : 0);

		carry = result.m_digits.at(i) < 0;

		if (carry) result.m_digits.at(i) += Integer::s_base;
	}

	result.m_normalize();

	return result;
}
