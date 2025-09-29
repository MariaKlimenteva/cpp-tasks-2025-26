#include <iostream>
#include <cmath>
#include <vector>

int main() {
    std::vector<double> numbers;
    double value;
    
    while (std::cin >> value) {
        numbers.push_back(value);
    }
    
    if (numbers.empty()) {
        std::cout << "no numbers\n";
        return 0;
    }
    
    double min_val = numbers[0];
    double max_val = numbers[0];
    double sum = 0.0;
    
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
        sum += numbers[i];
    }
    
    double mean = sum / numbers.size();
    
    double variance = 0.0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        double diff = numbers[i] - mean;
        variance += diff * diff;
    }
    variance /= numbers.size();
    double std_dev = std::sqrt(variance);
    
    std::cout << "min: " << min_val << "\n";
    std::cout << "max: " << max_val << "\n";
    std::cout << "mean: " << mean << "\n";
    std::cout << "stddev: " << std_dev << "\n";
    
    return 0;
}

// g++ -Wall -Wextra -o stats_dynamic 07.cpp
// echo "1.5 2.3 4.7 3.2" | ./stats_dynamic