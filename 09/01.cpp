#include <iostream>
#include <source_location>
#include <string_view>

class Tracer {
public:
    explicit Tracer(std::source_location loc = std::source_location::current())
        : location(loc) {
        std::cout << "[ENTER] " << location.function_name() 
                  << " (" << location.file_name() << ":" << location.line() << ")" << std::endl;
    }

    ~Tracer() {
        std::cout << "[EXIT]  " << location.function_name() << std::endl;
    }

    Tracer(const Tracer&) = delete;
    Tracer& operator=(const Tracer&) = delete;

private:
    std::source_location location;
};

#ifndef NDEBUG
#define trace() Tracer _tracer_instance_{std::source_location::current()}
#else
#define trace() ((void)0)
#endif

void function_b() {
    trace();
}

void function_a() {
    trace();
    function_b();
}

int main() {
    trace();
    function_a();
    return 0;
}

//  g++ -std=c++23 01.cpp -o task1