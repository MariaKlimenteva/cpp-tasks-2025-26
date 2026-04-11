#include <iostream>
#include <boost/iterator/iterator_facade.hpp>

class FibIterator : public boost::iterator_facade<FibIterator, int const, boost::forward_traversal_tag> {
public:
    FibIterator() : a(0), b(1), count(-1) {}
    explicit FibIterator(int n) : a(0), b(1), count(n) {}

private:
    friend class boost::iterator_core_access;

    int a, b, count;

    void increment() {
        int next_first = a + b;
        int next_second = b + next_first;
        a = next_first;
        b = next_second;
        if (count != -1) --count;
    }

    bool equal(const FibIterator& other) const {
        return count == other.count;
    }

    const int& dereference() const {
        return b;
    }
};

int main() {
    FibIterator it(10), end;
    
    for (; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}