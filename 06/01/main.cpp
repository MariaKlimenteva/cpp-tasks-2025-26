#include "rational.hpp"
#include <cassert>

int main()
{
    Rational r1(2, 4);
    Rational r2(1, 2);

    std::cout << "r1: " << r1 << "\n";
    std::cout << "r2: " << r2 << "\n";

    assert(r1 == r2);
    assert(r1.numerator() == 1);
}

/*
Сборка и запуск:
g++ -std=c++23 -c rational.cpp -o rational.o
g++ -std=c++23 -c main.cpp -o main.o
g++ rational.o main.o -o solution
./solution
*/