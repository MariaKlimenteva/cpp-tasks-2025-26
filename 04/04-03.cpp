#include <vector>
#include <string>
#include <cassert>

template <typename Container, typename T>
void handle(Container& c, T val)
{
}

template <typename Container>
void handle(Container& c, int val)
{
    c.push_back(val);
}

template <typename Container, typename ... Args>
void insert_ints(Container& c, Args ... args)
{
    (handle(c, args), ...);
}

int main()
{
    std::vector<int> v;

    insert_ints(v, 1, 2.5, std::string("test"), 3, 4.0f, 5);

    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 3);
    assert(v[2] == 5);
}