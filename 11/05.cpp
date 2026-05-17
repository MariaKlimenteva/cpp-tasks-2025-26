#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>
#include <iterator>
#include <random>

template <typename R, typename Out, typename Pred, typename Op>
auto transform_if(R&& range, Out out, Pred pred, Op op) {
    std::vector<std::ranges::range_value_t<R>> temp;
    std::ranges::copy_if(range, std::back_inserter(temp), pred);
    return std::ranges::transform(temp, out, op).out;
}

template <std::ranges::input_range R1, std::ranges::input_range R2>
double calculate_mae(R1&& r1, R2&& r2) {
    auto n = std::ranges::distance(r1);
    if (n == 0) return 0.0;
    return std::transform_reduce(std::ranges::begin(r1), std::ranges::end(r1),
                                 std::ranges::begin(r2), 0.0, std::plus<>(),
                                 [](auto a, auto b) { return std::abs(a - b); }) / n;
}

template <std::ranges::input_range R1, std::ranges::input_range R2>
double calculate_mse(R1&& r1, R2&& r2) {
    auto n = std::ranges::distance(r1);
    if (n == 0) return 0.0;
    return std::transform_reduce(std::ranges::begin(r1), std::ranges::end(r1),
                                 std::ranges::begin(r2), 0.0, std::plus<>(),
                                 [](auto a, auto b) { return (a - b) * (a - b); }) / n;
}

class Fibonacci : public std::ranges::view_interface<Fibonacci> {
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = uint64_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const uint64_t*;
        using reference = const uint64_t&;

        Iterator() = default;
        explicit Iterator(size_t index) : m_index(index) { update(); }

        reference operator*() const { return m_val; }
        pointer operator->() const { return &m_val; }

        Iterator& operator++() { ++m_index; update(); return *this; }
        Iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
        bool operator==(const Iterator& other) const { return m_index == other.m_index; }
        bool operator==(std::default_sentinel_t) const { return false; }

    private:
        size_t m_index = 0;
        uint64_t m_val = 0;
        void update() {
            if (m_index == 0) { m_val = 0; return; }
            if (m_index == 1) { m_val = 1; return; }
            uint64_t a = 0, b = 1;
            for (size_t i = 2; i <= m_index; ++i) {
                uint64_t next = a + b;
                a = b;
                b = next;
            }
            m_val = b;
        }
    };

public:
    Fibonacci() = default;
    auto begin() const { return Iterator(0); }
    auto end() const { return std::default_sentinel; }
};

int main() {
    // std::ranges algorithms
    std::vector<int> v = {1, 2, 3, 2, 1, 4, 5, 2};
    std::ranges::replace(v, 2, 20);
    std::ranges::fill(v, 7);

    std::vector<int> u = {1, 1, 2, 2, 3, 3, 4, 5, 5};
    auto [ub, ue] = std::ranges::unique(u);
    u.erase(ub, ue);

    std::vector<int> r = {1, 2, 3, 4, 5};
    std::ranges::rotate(r, r.begin() + 2);

    std::vector<int> s;
    std::ranges::sample(r, std::back_inserter(s), 2, std::mt19937{std::random_device{}()});

    // transform_if
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> res;
    transform_if(nums, std::back_inserter(res), [](int x){ return x % 2 == 0; }, [](int x){ return x * x; });
    assert(res.size() == 3 && res[0] == 4);

    // MAE/MSE
    std::vector<double> a = {1.0, 2.0, 3.0}, p = {1.1, 1.9, 3.2};
    assert(std::abs(calculate_mae(a, p) - 0.133333) < 1e-5);
    assert(std::abs(calculate_mse(a, p) - 0.02) < 1e-5);

    // views
    auto vec = std::views::iota(1, 11) | std::views::filter([](int x){ return x % 2 == 0; }) 
               | std::views::drop(1) | std::views::stride(2);
    // Result should be 4, 8
    
    std::vector<std::vector<int>> nested = {{1, 2}, {3, 4}};
    auto joined = nested | std::views::join;

    auto zipped = std::views::zip(a, p);

    // Fibonacci
    Fibonacci fib;
    auto first10 = fib | std::views::take(10);
    std::vector<uint64_t> fv;
    std::ranges::copy(first10, std::back_inserter(fv));
    assert(fv.size() == 10 && fv.back() == 34);

    std::cout << "11.05 passed\n";
    return 0;
}
