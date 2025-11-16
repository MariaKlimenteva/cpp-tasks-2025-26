#include <iostream>
#include <array>
#include <cstdint>
#include <sstream>
#include <string>
#include <compare>
#include <stdexcept>
#include <cassert>

class IPv4
{
public:
    IPv4() : m_data({0, 0, 0, 0}) {}

    IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4) : m_data({o1, o2, o3, o4}) {}

    explicit IPv4(const std::string& ip_str)
    {
        std::stringstream ss(ip_str);
        ss >> *this;
        if (ss.fail() || !ss.eof())
        {
            throw std::invalid_argument("Invalid IPv4 string format");
        }
    }

    IPv4& operator++()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (++m_data[i] != 0)
            {
                break;
            }
        }
        return *this;
    }

    IPv4 operator++(int)
    {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    IPv4& operator--()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (--m_data[i] != 255)
            {
                break;
            }
        }
        return *this;
    }

    IPv4 operator--(int)
    {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip)
    {
        std::stringstream ss;
        ss << static_cast<int>(ip.m_data[0]) << '.'
           << static_cast<int>(ip.m_data[1]) << '.'
           << static_cast<int>(ip.m_data[2]) << '.'
           << static_cast<int>(ip.m_data[3]);
        return os << ss.str();
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip)
    {
        int o1, o2, o3, o4;
        char d1, d2, d3;
        
        std::string line;
        if (std::getline(is, line))
        {
            std::stringstream ss(line);
            ss >> o1 >> d1 >> o2 >> d2 >> o3 >> d3 >> o4;

            if (ss.fail() || d1 != '.' || d2 != '.' || d3 != '.' || o1 < 0 || o1 > 255 || o2 < 0 || o2 > 255 || o3 < 0 || o3 > 255 || o4 < 0 || o4 > 255)
            {
                is.setstate(std::ios_base::failbit);
            }
            else
            {
                ip.m_data = {
                    static_cast<uint8_t>(o1), static_cast<uint8_t>(o2),
                    static_cast<uint8_t>(o3), static_cast<uint8_t>(o4)
                };
            }
        }
        else
        {
             is.setstate(std::ios_base::failbit);
        }
        
        return is;
    }

    friend auto operator<=>(const IPv4& lhs, const IPv4& rhs) = default;

private:
    std::array<std::uint8_t, 4> m_data;
};

int main()
{
    // --- Тестирование конструкторов и вывода ---
    IPv4 ip1;
    IPv4 ip2(192, 168, 1, 1);
    IPv4 ip3("10.0.0.255");
    std::cout << "ip1 (default): " << ip1 << std::endl;
    std::cout << "ip2 (from octets): " << ip2 << std::endl;
    std::cout << "ip3 (from string): " << ip3 << std::endl;
    assert(ip1 == IPv4(0, 0, 0, 0));
    assert(ip2 == IPv4("192.168.1.1"));
    assert(ip3 == IPv4(10, 0, 0, 255));
    std::cout << "--- Constructor and Output tests passed ---\n\n";
    
    // --- Тестирование инкремента ---
    ++ip3;
    std::cout << "ip3 after pre-increment: " << ip3 << std::endl;
    assert(ip3 == IPv4("10.0.1.0"));
    
    IPv4 ip_before_post_inc = ip3++;
    std::cout << "ip3 after post-increment: " << ip3 << std::endl;
    std::cout << "Value before post-increment: " << ip_before_post_inc << std::endl;
    assert(ip3 == IPv4("10.0.1.1"));
    assert(ip_before_post_inc == IPv4("10.0.1.0"));
    std::cout << "--- Increment tests passed ---\n\n";

    // --- Тестирование декремента ---
    --ip1;
    std::cout << "ip1 after pre-decrement: " << ip1 << std::endl;
    assert(ip1 == IPv4("255.255.255.255"));
    
    IPv4 ip_before_post_dec = ip1--;
    std::cout << "ip1 after post-decrement: " << ip1 << std::endl;
    std::cout << "Value before post-decrement: " << ip_before_post_dec << std::endl;
    assert(ip1 == IPv4("255.255.255.254"));
    assert(ip_before_post_dec == IPv4("255.255.255.255"));
    std::cout << "--- Decrement tests passed ---\n\n";

    // --- Тестирование сравнения ---
    assert(IPv4("192.168.0.1") < IPv4("192.168.1.0"));
    assert(IPv4("10.0.0.1") > IPv4("9.255.255.255"));
    assert(IPv4("127.0.0.1") == IPv4("127.0.0.1"));
    assert(IPv4("127.0.0.1") != IPv4("127.0.0.2"));
    std::cout << "--- Comparison tests passed ---\n\n";
    
    // --- Тестирование ввода ---
    IPv4 input_ip;
    std::stringstream ss("8.8.8.8");
    ss >> input_ip;
    std::cout << "IP from stringstream: " << input_ip << std::endl;
    assert(input_ip == IPv4(8, 8, 8, 8));
    std::cout << "--- Input test passed ---\n\n";
    
    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}

// g++ -std=c++20 -o out 03-09-ipv4.cpp
// ./out