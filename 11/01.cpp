#include <print>

class Wrapper;

using FunctionPtr = Wrapper (*)();

class Wrapper {
public:
    Wrapper(FunctionPtr p) : ptr(p) {}

    operator FunctionPtr() const {
        return ptr;
    }

private:
    FunctionPtr ptr;
};

Wrapper test() {
    std::println("Function test() is called!");
    return &test;
}

int main() {
    Wrapper function = test();
    (*function)();
    
    return 0;
}