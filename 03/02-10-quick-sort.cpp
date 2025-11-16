#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

void order(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i)
    {
        for (auto j = i; j > left; --j)
        {
            if (vector[j - 1] > vector[j])
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

std::size_t partition(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    std::size_t mid = left + (right - left) / 2;

    if (vector[mid] < vector[left])
    {
        std::swap(vector[mid], vector[left]);
    }
    if (vector[right] < vector[left])
    {
        std::swap(vector[right], vector[left]);
    }
    if (vector[mid] < vector[right])
    {
        std::swap(vector[mid], vector[right]);
    }

    int pivot = vector[right];
    auto i = left;
    auto j = right;

    while (true)
    {
        while (vector[i] < pivot)
        {
            i++;
        }

        while (vector[j] > pivot)
        {
            j--;
        }

        if (i >= j)
        {
            return j;
        }

        std::swap(vector[i++], vector[j--]);
    }
}

void hybrid_quick_sort(std::vector<int>& vector, std::size_t left, std::size_t right)
{
    if (left < right)
    {
        if (right - left + 1 > 16)
        {
            std::size_t p = partition(vector, left, right);
            hybrid_quick_sort(vector, left, p);
            hybrid_quick_sort(vector, p + 1, right);
        }
        else
        {
            order(vector, left, right + 1);
        }
    }
}

void sort(std::vector<int>& vector)
{
    if (!vector.empty())
    {
        hybrid_quick_sort(vector, 0, std::size(vector) - 1);
    }
}

int main()
{
    auto size = 1'000uz;

    std::vector<int> vector(size, 0);

    for (auto i = 0uz; i < size; ++i)
    {
        vector[i] = size - i;
    }

    sort(vector);

    assert(std::ranges::is_sorted(vector));
}

//g++ -std=c++20 -o sort_app 02-10-quick-sort.cpp
//./sort_app
/* Обоснование временной сложности:
Quicksort в общем случае имеет сложность O(n log n), тк на каждом шаге рекурсии 
массив делится примерно пополам.
Выбор опорного элемента как медианы из трех значительно повышает вероятность 
сбалансированного разделения и делает достижение худшего случая, имеющего сложность O(n²), 
маловероятным на практике.
Insertion Sort имеет временную сложность O(k²), где k — размер подмассива. 
В данном алгоритме она применяется, когда k ≤ 16.
Гибридная сортировка: Рекурсивное деление с помощью быстрой сортировки продолжается до тех пор, 
пока размер подмассива не станет меньше или равен константе C (в нашем случае C = 16). 
Глубина рекурсии до этого момента составляет O(log(n/C)). 
На каждом уровне рекурсии обрабатываются все n элементов, поэтому сложность этой фазы 
составляет O(n log(n/C)). Когда размеры подмассивов достигают C, их сортировка выполняется
с помощью сортировки вставками. Количество таких подмассивов составляет n/C. Сложность сортировки 
одного подмассива равна O(C²). 
Таким образом, общая сложность для всех малых подмассивов составляет (n/C) * O(C²) = O(nC).
Суммарная временная сложность гибридного алгоритма:
T(n) = O(n log(n/C) + nC)
тк С-константа то log(n/C) = log(n) - log(C), где log(C) — также константа. 
Следовательно, O(n log(n/C)) эквивалентно O(n log n). 
Аналогично, O(nC) эквивалентно O(n).
Итоговая сложность:
T(n) = O(n log n + n) = O(n log n)
Для небольших массивов гибридный алгоритм эффективнее быстрой сортировки.
*/