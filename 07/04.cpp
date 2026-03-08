#include <vector>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>

template <typename T>
void quick_sort(std::vector<T>& arr)
{
    if (arr.size() < 2) return;
    
    auto const pivot = arr[arr.size() / 2];
    
    std::vector<T> less, greater;
    std::vector<T> equal;

    for (const auto& elem : arr)
    {
        if (elem < pivot) less.push_back(elem);
        else if (elem > pivot) greater.push_back(elem);
        else equal.push_back(elem);
    }

    quick_sort(less);
    quick_sort(greater);

    std::move(less.begin(), less.end(), arr.begin());
    std::move(equal.begin(), equal.end(), arr.begin() + less.size());
    std::move(greater.begin(), greater.end(), arr.begin() + less.size() + equal.size());
}

TEST(SortTest, EmptyVector)
{
    std::vector<int> v;
    quick_sort(v);
    EXPECT_TRUE(v.empty());
}

TEST(SortTest, SingleElement)
{
    std::vector<int> v = {42};
    quick_sort(v);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 42);
}

TEST(SortTest, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, ReverseSorted)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    quick_sort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[4], 5);
}

TEST(SortTest, Duplicates)
{
    std::vector<int> v = {3, 1, 2, 3, 1};
    quick_sort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v.size(), 5);
}

TEST(SortTest, LargeRandom)
{
    std::vector<int> v(1000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(1, 10000);
    std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

    quick_sort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// g++ -std=c++23 04.cpp -lgtest -lgtest_main -lpthread -o 04