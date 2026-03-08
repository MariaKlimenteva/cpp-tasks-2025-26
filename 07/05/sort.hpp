#pragma once

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template <typename T>
void order(std::vector<T> &vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j - 1] > vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

template <typename T>
std::size_t partition(std::vector<T> &vector, std::size_t left,
                      std::size_t right) {
  if (left >= right) return left;
  auto mid = std::midpoint(left, right - 1);
  auto last = right - 1;

  if (vector[mid] < vector[left])
    std::swap(vector[left], vector[mid]);
  if (vector[last] < vector[left])
    std::swap(vector[left], vector[last]);
  if (vector[last] < vector[mid])
    std::swap(vector[mid], vector[last]);

  auto pivot = vector[mid];
  auto i = left;
  auto j = right - 1;

  while (i <= j) {
    while (vector[i] < pivot) {
      i++;
    }
    while (vector[j] > pivot) {
      j--;
    }
    if (i <= j) {
      std::swap(vector[i], vector[j]);
      i++;
      if (j > 0) j--;
    }
  }
  return i;
}

template <typename T>
void split(std::vector<T> &vector, std::size_t left, std::size_t right,
           size_t threshold) {
  if (right > left) {
    if ((right - left) > threshold) {
      auto p = partition(vector, left, right);
      if (left < p - 1) {
        split(vector, left, p - 1, threshold);
      }
      if (p < right) {
        split(vector, p, right, threshold);
      }
    } else {
      order(vector, left, right);
    }
  }
}

template <typename T> void sort(std::vector<T> &vector, size_t threshold = 16) {
  if (vector.empty())
    return;
  split(vector, 0, std::size(vector), threshold);
}