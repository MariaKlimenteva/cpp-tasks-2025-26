#include <iostream>
#include <cmath>
#include <limits>

int main() {
    const int MAX_SIZE = 10000;
    double numbers[MAX_SIZE] = {};
    int count = 0;
    
    while (std::cin >> numbers[count]) {
        count++;
        if (count >= MAX_SIZE) {
            break;
        }
    }
    
    if (count == 0) {
        std::cout << "no numbers\n";
        return 0;
    }
    
    double min_val = numbers[0];
    double max_val = numbers[0];
    double sum = 0.0;
    
    for (int i = 0; i < count; ++i) {
        if (numbers[i] < min_val) {
            min_val = numbers[i];
        }
        if (numbers[i] > max_val) {
            max_val = numbers[i];
        }
        sum += numbers[i];
    }
    
    double mean = sum / count;
    
    double variance = 0.0;
    for (int i = 0; i < count; ++i) {
        double diff = numbers[i] - mean;
        variance += diff * diff;
    }
    variance /= count;
    double std_dev = std::sqrt(variance);
    
    std::cout << "min: " << min_val << "\n";
    std::cout << "max: " << max_val << "\n";
    std::cout << "mean: " << mean << "\n";
    std::cout << "stddev: " << std_dev << "\n";
    
    return 0;
}

// g++ -Wall -Wextra -o stats 06.cpp
// echo "1.5 2.3 4.7 3.2" | ./stats