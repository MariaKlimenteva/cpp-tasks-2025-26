#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

size_t collatz_length(unsigned long long n, vector<size_t>& cache) {
    if (n == 1) return 1;
    
    if (n < cache.size() && cache[n] != 0) {
        return cache[n];
    }
    
    size_t length;
    if (n % 2 == 0) {
        length = 1 + collatz_length(n / 2, cache);
    } else {
        length = 1 + collatz_length(3 * n + 1, cache);
    }
    
    if (n < cache.size()) {
        cache[n] = length;
    }
    
    return length;
}

int main() {
    const unsigned long long MAX_START = 100;
    vector<size_t> cache(MAX_START * 100, 0);
    
    size_t max_length = 0;
    unsigned long long max_start = 1;
    
    for (unsigned long long start = 1; start <= MAX_START; ++start) {
        size_t length = collatz_length(start, cache);
        
        if (length > max_length) {
            max_length = length;
            max_start = start;
        }
    }
    
    cout << "Start value: " << max_start << "\n";
    cout << "Length: " << max_length << "\n";
    
    return 0;
}
// g++ -Wall -Wextra -o collatz 08.cpp
// ./collatz