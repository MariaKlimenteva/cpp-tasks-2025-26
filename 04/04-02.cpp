#include <cassert>
#include <cmath>
#include <iostream>

double min_val(double x)
{
    return x;
}

template <typename... Args>
double min_val(double x, Args... args)
{
    double rest = min_val(args...);
    return x < rest ? x : rest;
}

double max_val(double x)
{
    return x;
}

template <typename... Args>
double max_val(double x, Args... args)
{
    double rest = max_val(args...);
    return x > rest ? x : rest;
}

template <typename... Args>
double sum_val(Args... args)
{
    return (args + ...);
}

template <typename... Args>
double mean_val(Args... args)
{
    return (args + ...) / static_cast<double>(sizeof...(args));
}

bool equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    assert(equal(min_val(10.0, 5.0, 2.0, 8.0), 2.0));
    assert(equal(min_val(5.0), 5.0));

    assert(equal(max_val(10.0, 5.0, 2.0, 8.0), 10.0));
    assert(equal(max_val(2.0), 2.0));

    assert(equal(sum_val(1.0, 2.0, 3.0), 6.0));
    assert(equal(sum_val(10.5, 2.5), 13.0));

    assert(equal(mean_val(1.0, 2.0, 3.0), 2.0));
    assert(equal(mean_val(4.0, 8.0), 6.0));
    assert(equal(mean_val(10.0, 20.0, 30.0, 40.0), 25.0));
    
    std::cout << "All assertions passed!" << std::endl;
}