#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

template <std::random_access_iterator It, typename Compare = std::less<>>
void iterator_sort(It begin, It end, Compare comp = Compare{}) {
    if (begin == end) return;
    auto size = std::distance(begin, end);
    for (auto i = 0; i < size - 1; ++i) {
        for (auto j = begin; j != std::prev(end, i + 1); std::advance(j, 1)) {
            auto next_it = std::next(j);
            if (comp(*next_it, *j)) {
                std::iter_swap(j, next_it);
            }
        }
    }
}

bool free_compare(int a, int b) {
    return a > b;
}

int main() {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    auto print_data = [&data](const std::string& msg) {
        std::cout << msg << ": ";
        for (int x : data) std::cout << x << " ";
        std::cout << "\n";
    };

    iterator_sort(data.begin(), data.end(), std::less<int>{});
    print_data("std::less");

    iterator_sort(data.begin(), data.end(), free_compare);
    print_data("Free function (desc)");

    iterator_sort(data.begin(), data.end(), [](int a, int b) { return a < b; });
    print_data("Lambda (asc)");

    return 0;
}