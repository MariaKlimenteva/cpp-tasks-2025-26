#include <cmath>
#include <iostream>
#include <limits>

int main() {
    const double epsilon = std::numeric_limits<double>::epsilon();
    double a, b, c;
    
    std::cin >> a >> b >> c;
    
    if (std::abs(a) < epsilon) {
        if (std::abs(b) < epsilon) {
            if (std::abs(c) < epsilon) {
                std::cout << "any number\n";
            } else {
                std::cout << "no roots\n";
            }
        } else {
            double root = -c / b;
            std::cout << root << '\n';
        }
    } else {
        double discriminant = b * b - 4 * a * c;
        
        if (std::abs(discriminant) < epsilon) {
            double root = -b / (2 * a);
            std::cout << root << '\n';
        } else if (discriminant > 0) {
            double sqrt_d = std::sqrt(discriminant);
            double root1 = (-b - sqrt_d) / (2 * a);
            double root2 = (-b + sqrt_d) / (2 * a);
            std::cout << root1 << ' ' << root2 << '\n';
        } else {
            std::cout << "no roots\n";
        }
    }
    
    return 0;
}
// g++ -Wall -Wextra -o quadratic 02.cpp
// echo "1 -3 2" | ./quadratic