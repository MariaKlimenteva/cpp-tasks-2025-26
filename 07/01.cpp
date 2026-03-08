#include <optional>
#include <variant>
#include <utility>
#include <cmath>
#include <print>

using Solution = std::variant<double, std::pair<double, double>, std::monostate>;

std::optional<Solution> solve(double a, double b, double c)
{
    if (std::abs(a) < 1e-9)
    {
        if (std::abs(b) < 1e-9)
        {
            if (std::abs(c) < 1e-9)
            {
                return std::monostate{};
            }
            else
            {
                return std::nullopt;
            }
        }
        else
        {
            return -c / b;
        }
    }

    double d = b * b - 4 * a * c;

    if (d < 0)
    {
        return std::nullopt;
    }
    else if (d == 0)
    {
        return -b / (2 * a);
    }
    else
    {
        double x1 = (-b - std::sqrt(d)) / (2 * a);
        double x2 = (-b + std::sqrt(d)) / (2 * a);
        return std::make_pair(x1, x2);
    }
}

void print_solution(const std::optional<Solution>& result)
{
    if (!result.has_value())
    {
        std::print("No roots\n");
    }
    else
    {
        const auto& val = result.value();
        
        if (std::holds_alternative<double>(val))
        {
            std::print("One root: {}\n", std::get<double>(val));
        }
        else if (std::holds_alternative<std::pair<double, double>>(val))
        {
            auto roots = std::get<std::pair<double, double>>(val);
            std::print("Two roots: {}, {}\n", roots.first, roots.second);
        }
        else if (std::holds_alternative<std::monostate>(val))
        {
            std::print("Infinite roots\n");
        }
    }
}

int main()
{
    print_solution(solve(1, -3, 2));
    print_solution(solve(1, 2, 1));
    print_solution(solve(1, 0, 1)); 
    print_solution(solve(0, 0, 0));
    print_solution(solve(0, 0, 5)); 
    print_solution(solve(0, 2, 4)); 
}
// g++ -std=c++23 01.cpp -o 01