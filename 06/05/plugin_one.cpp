#include <iostream>
#include <boost/config.hpp> 

extern "C" BOOST_SYMBOL_EXPORT void test()
{
    std::cout << "Library ONE: test() called.\n";
}