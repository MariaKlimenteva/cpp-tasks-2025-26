#include <print>
#include <stdexcept>
#include <limits>
#include <string_view>

int log2_int(int value)
{
    if (value <= 0)
    {
        throw std::invalid_argument("Argument must be strictly positive");
    }

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

    unsigned int sign = (cast.u >> 31) & 1;
    unsigned int exp = (cast.u >> 23) & 0xFF;
    unsigned int mantissa = cast.u & 0x7FFFFF;

    if (exp == 255)
    {
        throw std::invalid_argument("Argument cannot be infinity or NaN");
    }

    if (sign == 1 || (exp == 0 && mantissa == 0))
    {
        throw std::invalid_argument("Argument must be strictly positive");
    }

    if (exp == 0)
    {
        int bit_index = -1;
        unsigned int temp_mantissa = mantissa;
        
        while (temp_mantissa > 0)
        {
            temp_mantissa >>= 1;
            ++bit_index;
        }
        
        return bit_index - 149;
    }
    
    return static_cast<int>(exp) - 127;
}

void EXPECT_EQ(std::string_view name, int actual, int expected)
{
    if (actual == expected) {
        std::print("[  OK  ] {}\n", name);
    } else {
        std::print("[ FAIL ] {} (Expected: {}, Actual: {})\n", name, expected, actual);
    }
}

template<typename Func>
void EXPECT_THROW(std::string_view name, Func f)
{
    try {
        f();
        std::print("[ FAIL ] {} (Expected exception, got none)\n", name);
    } catch (const std::invalid_argument&) {
        std::print("[  OK  ] {}\n", name);
    } catch (...) {
        std::print("[ FAIL ] {} (Thrown wrong exception type)\n", name);
    }
}

int main()
{
    std::print("--- Log2IntTest.ValidPositiveNumbers ---\n");
    EXPECT_EQ("log2_int(8)", log2_int(8), 3);
    EXPECT_EQ("log2_int(15)", log2_int(15), 3);
    EXPECT_EQ("log2_int(1024)", log2_int(1024), 10);
    EXPECT_EQ("log2_int(1)", log2_int(1), 0);

    std::print("\n--- Log2IntTest.ThrowsOnInvalidNumbers ---\n");
    EXPECT_THROW("log2_int(0)", []{ log2_int(0); });
    EXPECT_THROW("log2_int(-8)", []{ log2_int(-8); });

    std::print("\n--- Log2FloatTest.NormalizedNumbers ---\n");
    EXPECT_EQ("log2_float(8.0f)", log2_float(8.0f), 3);
    EXPECT_EQ("log2_float(15.0f)", log2_float(15.0f), 3);
    EXPECT_EQ("log2_float(1.0f)", log2_float(1.0f), 0);
    EXPECT_EQ("log2_float(1.001f)", log2_float(1.001f), 0);
    EXPECT_EQ("log2_float(0.999f)", log2_float(0.999f), -1);
    EXPECT_EQ("log2_float(0.5f)", log2_float(0.5f), -1);
    EXPECT_EQ("log2_float(0.125f)", log2_float(0.125f), -3);

    std::print("\n--- Log2FloatTest.DenormalizedNumbers ---\n");
    EXPECT_EQ("log2_float(denorm_min)", log2_float(std::numeric_limits<float>::denorm_min()), -149);
    EXPECT_EQ("log2_float(2.802597e-45f)", log2_float(2.802597e-45f), -148);

    std::print("\n--- Log2FloatTest.ThrowsOnInvalidNumbers ---\n");
    EXPECT_THROW("log2_float(0.0f)", []{ log2_float(0.0f); });
    EXPECT_THROW("log2_float(-0.0f)", []{ log2_float(-0.0f); });
    EXPECT_THROW("log2_float(-4.0f)", []{ log2_float(-4.0f); });

    std::print("\n--- Log2FloatTest.ThrowsOnInfinityAndNaN ---\n");
    EXPECT_THROW("log2_float(infinity)", []{ log2_float(std::numeric_limits<float>::infinity()); });
    EXPECT_THROW("log2_float(-infinity)", []{ log2_float(-std::numeric_limits<float>::infinity()); });
    EXPECT_THROW("log2_float(NaN)", []{ log2_float(std::numeric_limits<float>::quiet_NaN()); });

    return 0;
}
// g++ -std=c++23 03.cpp -o 03