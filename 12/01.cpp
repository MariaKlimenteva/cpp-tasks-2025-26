#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <print>

long double convert(const std::string& in) {
    std::stringstream ss(in);
    try { ss.imbue(std::locale("ru_RU.utf8")); } catch (...) {}
    long double units;
    ss >> std::get_money(units);
    if (ss.fail()) throw std::runtime_error("Parse error");
    return (units / 100.0) / 90.0;
}

std::string format(long double usd) {
    std::stringstream ss;
    try { ss.imbue(std::locale("en_US.utf8")); } catch (...) {}
    ss << std::showbase << std::put_money(usd * 100.0);
    return ss.str();
}

int main() {
    try {
        std::string tests[] = { "1000,00 ₽", "500,50 ₽", "90,00 ₽" };
        for (const auto& t : tests) {
            std::print("{} -> {}\n", t, format(convert(t)));
        }
    } catch (const std::exception& e) {
        std::print("Error: {}\n", e.what());
    }
    return 0;
}
