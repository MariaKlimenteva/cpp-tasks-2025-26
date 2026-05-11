#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>

template <std::random_access_iterator It, typename Compare = std::less<>>
void iterator_sort(It begin, It end, Compare comp = Compare{}) {
    auto dist = std::distance(begin, end);
    if (dist <= 1) return;

    auto i = begin;
    auto j = std::prev(end);

    auto pivot = *std::next(begin, dist / 2);

    while (i <= j) {
        while (comp(*i, pivot)) ++i;
        while (comp(pivot, *j)) --j;

        if (i <= j) {
            std::iter_swap(i, j);
            ++i;
            --j;
        }
    }

    if (begin < j) iterator_sort(begin, std::next(j), comp);
    if (i < end) iterator_sort(i, end, comp);
}

template <typename T>
void print_data(const std::string& msg, const std::vector<T>& data) {
    std::cout << msg << ": ";
    for (const auto& x : data) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    // Test 1: Ints ascending
    std::vector<int> data1 = {5, 2, 9, 1, 5, 6};
    iterator_sort(data1.begin(), data1.end(), std::less<int>{});
    print_data("Ints (asc)", data1);

    // Test 2: Ints descending
    std::vector<int> data2 = {5, 2, 9, 1, 5, 6};
    iterator_sort(data2.begin(), data2.end(), [](int a, int b) { return a > b; });
    print_data("Ints (desc)", data2);

    // Test 3: Strings
    std::vector<std::string> data3 = {"banana", "apple", "cherry", "date", "elderberry"};
    iterator_sort(data3.begin(), data3.end());
    print_data("Strings (asc)", data3);

    // Test 4: Empty vector
    std::vector<int> data4 = {};
    iterator_sort(data4.begin(), data4.end());
    print_data("Empty", data4);

    // Test 5: Single element
    std::vector<int> data5 = {42};
    iterator_sort(data5.begin(), data5.end());
    print_data("Single element", data5);

    // Test 6: Already sorted
    std::vector<int> data6 = {1, 2, 3, 4, 5};
    iterator_sort(data6.begin(), data6.end());
    print_data("Already sorted", data6);

    // Test 7: Reverse sorted
    std::vector<int> data7 = {5, 4, 3, 2, 1};
    iterator_sort(data7.begin(), data7.end());
    print_data("Reverse sorted", data7);

    // Test 8: All identical
    std::vector<int> data8 = {7, 7, 7, 7, 7};
    iterator_sort(data8.begin(), data8.end());
    print_data("All identical", data8);

    return 0;
}
