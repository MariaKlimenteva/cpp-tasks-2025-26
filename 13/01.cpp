#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cassert>

std::string to_hex(const std::vector<uint8_t>& data) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (auto b : data) {
        ss << std::setw(2) << static_cast<int>(b);
    }
    return ss.str();
}

std::vector<uint8_t> from_hex(const std::string& hex) {
    std::vector<uint8_t> data;
    for (size_t i = 0; i < hex.size(); i += 2) {
        auto c2i = [](char c) {
            if (c >= '0' && c <= '9') return c - '0';
            return c - 'a' + 10;
        };
        data.push_back((c2i(hex[i]) << 4) | c2i(hex[i + 1]));
    }
    return data;
}

int main() {
    std::vector<uint8_t> original = { 0x01, 0x02, 0x0a, 0xff, 0x10 };
    std::string hex = to_hex(original);
    assert(hex == "01020aff10");
    assert(from_hex(hex) == original);
    std::cout << hex << "\n";
    return 0;
}
