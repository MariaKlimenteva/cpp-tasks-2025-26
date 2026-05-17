#include <optional>
#include <variant>
#include <utility>
#include <cmath>
#include <print>
#include <cassert>

using Solution = std::variant<double, std::pair<double, double>, std::monostate>;

std::optional<Solution> solve(double a, double b, double c) {
    if (std::abs(a) < 1e-9) {
        if (std::abs(b) < 1e-9) {
            return std::abs(c) < 1e-9 ? std::make_optional(std::monostate{}) : std::nullopt;
        }
        return -c / b;
    }

    double d = b * b - 4 * a * c;
    if (d < 0) return std::nullopt;
    if (std::abs(d) < 1e-9) return -b / (2 * a);

    double x1 = (-b - std::sqrt(d)) / (2 * a);
    double x2 = (-b + std::sqrt(d)) / (2 * a);
    return std::make_pair(std::min(x1, x2), std::max(x1, x2));
}

struct Visitor {
    void operator()(double x) const { std::print("One root: {}\n", x); }
    void operator()(std::pair<double, double> r) const { std::print("Two roots: {}, {}\n", r.first, r.second); }
    void operator()(std::monostate) const { std::print("Infinite roots\n"); }
};

void check(std::optional<Solution> res) {
    if (!res) std::print("No roots\n");
    else std::visit(Visitor{}, *res);
}

int main() {
    auto r1 = solve(1, -3, 2);
    assert((std::get<std::pair<double, double>>(*r1).first == 1.0));
    assert((std::get<std::pair<double, double>>(*r1).second == 2.0));

    auto r2 = solve(1, 2, 1);
    assert((std::get<double>(*r2) == -1.0));

    auto r3 = solve(1, 0, 1);
    assert(!r3.has_value());

    auto r4 = solve(0, 0, 0);
    assert(std::holds_alternative<std::monostate>(*r4));

    auto r5 = solve(0, 2, 4);
    assert(std::get<double>(*r5) == -2.0);

    check(r1);
    check(r2);
    check(r3);
    check(r4);
    check(r5);

    std::print("\nAll tests passed!\n");
    return 0;
}
