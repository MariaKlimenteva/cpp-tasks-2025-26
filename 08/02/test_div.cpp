#include "08.02.hpp"
#include <iostream>
#include <cassert>

int main() {
    Integer x = 10000;
    Integer y = 100;
    Integer result = x / y;
    std::cout << "10000 / 100 = " << result << std::endl;
    assert(result == 100);
    return 0;
}