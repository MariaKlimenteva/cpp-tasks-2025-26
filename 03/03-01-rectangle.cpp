#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Rectangle
{
    int left;
    int top;
    int right;
    int bottom;
};

long long calculate_intersection_area(const std::vector<Rectangle>& rectangles)
{
    if (rectangles.empty())
    {
        return 0;
    }

    Rectangle intersection_rect = rectangles[0];

    for (size_t i = 1; i < rectangles.size(); ++i)
    {
        intersection_rect.left = std::max(intersection_rect.left, rectangles[i].left);
        intersection_rect.top = std::max(intersection_rect.top, rectangles[i].top);
        intersection_rect.right = std::min(intersection_rect.right, rectangles[i].right);
        intersection_rect.bottom = std::min(intersection_rect.bottom, rectangles[i].bottom);
    }

    long long width = static_cast<long long>(intersection_rect.right) - intersection_rect.left;
    long long height = static_cast<long long>(intersection_rect.bottom) - intersection_rect.top;

    if (width > 0 && height > 0)
    {
        return width * height;
    }

    return 0;
}

Rectangle find_min_bounding_box(const std::vector<Rectangle>& rectangles)
{
    if (rectangles.empty())
    {
        return {0, 0, 0, 0};
    }

    int min_left = std::numeric_limits<int>::max();
    int min_top = std::numeric_limits<int>::max();
    int max_right = std::numeric_limits<int>::min();
    int max_bottom = std::numeric_limits<int>::min();

    for (const auto& rect : rectangles)
    {
        min_left = std::min(min_left, rect.left);
        min_top = std::min(min_top, rect.top);
        max_right = std::max(max_right, rect.right);
        max_bottom = std::max(max_bottom, rect.bottom);
    }

    return {min_left, min_top, max_right, max_bottom};
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect)
{
    os << "Rectangle(left=" << rect.left << ", top=" << rect.top
       << ", right=" << rect.right << ", bottom=" << rect.bottom << ")";
    return os;
}

int main()
{
    // Case 1: Стандартное пересечение
    std::vector<Rectangle> rects_case_1 = {
        {0, 0, 10, 10},
        {5, 5, 15, 15}
    };

    // Case 2: Отсутствие пересечения
    std::vector<Rectangle> rects_case_2 = {
        {0, 0, 5, 5},
        {10, 10, 15, 15}
    };
    
    // Case 3: Пересечение с частичным наложением (ранее некорректно названный)
    std::vector<Rectangle> rects_case_3 = {
        {0, 0, 10, 10},
        {5, 0, 15, 10}
    };

    // Case 4: Настоящее вырожденное пересечение (линия)
    std::vector<Rectangle> rects_case_4 = {
        {0, 0, 10, 10},
        {10, 0, 20, 10}
    };

    // Case 5: Множественное вложенное пересечение
    std::vector<Rectangle> rects_case_5 = {
        {0, 0, 20, 20},
        {5, 5, 15, 15},
        {8, 8, 12, 12}
    };

    std::cout << "Case 1: Normal Intersection" << std::endl;
    std::cout << "Intersection Area: " << calculate_intersection_area(rects_case_1) << std::endl;
    std::cout << "Minimum Bounding Box: " << find_min_bounding_box(rects_case_1) << std::endl << std::endl;

    std::cout << "Case 2: No Intersection" << std::endl;
    std::cout << "Intersection Area: " << calculate_intersection_area(rects_case_2) << std::endl;
    std::cout << "Minimum Bounding Box: " << find_min_bounding_box(rects_case_2) << std::endl << std::endl;
    
    std::cout << "Case 3: Overlapping Intersection" << std::endl;
    std::cout << "Intersection Area: " << calculate_intersection_area(rects_case_3) << std::endl;
    std::cout << "Minimum Bounding Box: " << find_min_bounding_box(rects_case_3) << std::endl << std::endl;

    std::cout << "Case 4: Degenerate Intersection (Line)" << std::endl;
    std::cout << "Intersection Area: " << calculate_intersection_area(rects_case_4) << std::endl;
    std::cout << "Minimum Bounding Box: " << find_min_bounding_box(rects_case_4) << std::endl << std::endl;
    
    std::cout << "Case 5: Multiple Nested Rectangles" << std::endl;
    std::cout << "Intersection Area: " << calculate_intersection_area(rects_case_5) << std::endl;
    std::cout << "Minimum Bounding Box: " << find_min_bounding_box(rects_case_5) << std::endl;

    return 0;
}

// g++ -std=c++17 -o rectangle_app 03-01-rectangle.cpp
// ./rectangle_app