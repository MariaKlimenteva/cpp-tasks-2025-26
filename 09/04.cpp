#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <std::random_access_iterator It>
void iterator_sort(It begin, It end) {
    if (std::distance(begin, end) <= 1) return;

    auto i = begin;
    auto j = std::prev(end);
    auto pivot = *std::next(begin, std::distance(begin, end) / 2);

    while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;

        if (i <= j) {
            std::iter_swap(i, j);
            ++i;
            --j;
        }
    }

    if (begin < j) iterator_sort(begin, std::next(j));
    if (i < end) iterator_sort(i, end);
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