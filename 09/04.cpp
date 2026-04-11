#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <std::random_access_iterator It>
void iterator_sort(It begin, It end) {
    if (begin == end) return;

    auto size = std::distance(begin, end);

    for (auto i = 0; i < size - 1; ++i) {
        for (auto j = begin; j != std::prev(end, i + 1); std::advance(j, 1)) {
            auto next_it = std::next(j);
            if (*next_it < *j) {
                std::iter_swap(j, next_it);
            }
        }
    }
}

int main() {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    std::cout << "Before: ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    iterator_sort(data.begin(), data.end());

    std::cout << "After:  ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
// g++ -std=c++23 04.cpp -o 4