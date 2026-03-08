import rational;
import <iostream>;
import <cassert>;

int main()
{
    math::Rational r1(2, 4);
    math::Rational r2(1, 2);

    std::cout << "r1: " << r1 << "\n";
    
    assert(r1 == r2);
}
/*
Сборка и запуск (GCC 14+):
g++ -std=c++23 -fmodules-ts -x c++-system-header iostream cassert
g++ -std=c++23 -fmodules-ts -c rational.ixx
g++ -std=c++23 -fmodules-ts -c rational.cpp
g++ -std=c++23 -fmodules-ts main.cpp rational.o -o solution
./solution
*/