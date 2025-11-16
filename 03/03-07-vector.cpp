#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <utility>

class Vector
{
public:
    Vector() = default;

    Vector(std::initializer_list<int> list)
        : m_size(list.size()), m_capacity(list.size())
    {
        m_array = m_capacity ? new int[m_capacity] : nullptr;
        std::ranges::copy(list, m_array);
    }

    Vector(const Vector& other)
        : m_size(other.m_size), m_capacity(other.m_capacity)
    {
        m_array = m_capacity ? new int[m_capacity] : nullptr;
        if (m_array)
        {
            std::copy(other.m_array, other.m_array + other.m_size, m_array);
        }
    }

    Vector(Vector&& other) noexcept
        : m_array(std::exchange(other.m_array, nullptr)),
          m_size(std::exchange(other.m_size, 0)),
          m_capacity(std::exchange(other.m_capacity, 0))
    {
    }

    ~Vector()
    {
        delete[] m_array;
    }

    Vector& operator=(Vector other)
    {
        swap(other);
        return *this;
    }

    void swap(Vector& other) noexcept
    {
        std::swap(m_array, other.m_array);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    std::size_t size() const
    {
        return m_size;
    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    void clear()
    {
        m_size = 0;
    }

    void push_back(int value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 8 : m_capacity * 2);
        }
        m_array[m_size] = value;
        m_size++;
    }

private:
    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= m_capacity)
        {
            return;
        }

        int* new_array = new int[new_capacity];
        for (std::size_t i = 0; i < m_size; ++i)
        {
            new_array[i] = m_array[i];
        }
        
        delete[] m_array;
        m_array = new_array;
        m_capacity = new_capacity;
    }

    int* m_array = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

void print_vector_stats(const Vector& v, const char* name)
{
    std::cout << "--- " << name << " ---" << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;
    std::cout << "Is empty: " << (v.empty() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
}

int main()
{
    Vector v;
    print_vector_stats(v, "Initial Vector");

    std::cout << "--- Pushing back 10 elements ---" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Pushing " << i << "..." << std::endl;
        v.push_back(i);
        std::cout << "Current size: " << v.size() << ", Current capacity: " << v.capacity() << std::endl;
    }

    print_vector_stats(v, "Vector after pushes");

    std::cout << "--- Clearing the vector ---" << std::endl;
    v.clear();
    print_vector_stats(v, "Vector after clear");

    Vector v2 = {100, 200, 300};
    print_vector_stats(v2, "Vector v2 from initializer list");
    
    return 0;
}

// g++ -std=c++20 -o out 03-07-vector.cpp
// ./out