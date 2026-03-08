#include <print>

int log2_int(int value)
{
    unsigned int u = static_cast<unsigned int>(value);
    int log = -1;
    while (u > 0)
    {
        u >>= 1;
        ++log;
    }
    return log;
}

int log2_float(float value)
{
    union 
    {
        float f;
        unsigned int u;
    } cast;
    
    cast.f = value;

    unsigned int exp = (cast.u >> 23) & 0xFF;
    unsigned int mantissa = cast.u & 0x7FFFFF;

    if (exp == 255)
    {
        return -1; 
    }
    else if (exp == 0)
    {
        if (mantissa == 0) return -1; 
        
        int log = -126;
        while ((mantissa & 0x800000) == 0)
        {
            mantissa <<= 1;
            --log;
        }
        return log;
    }
    else
    {
        return static_cast<int>(exp) - 127;
    }
}

int main()
{
    std::print("log2_int(8) = {}\n", log2_int(8));
    std::print("log2_float(8.0f) = {}\n", log2_float(8.0f));
    std::print("log2_float(0.125f) = {}\n", log2_float(0.125f));
}
// g++ -std=c++23 03.cpp -o 03