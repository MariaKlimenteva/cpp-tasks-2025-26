#include <iostream>
#include <vector>
#include <string>

template <typename T>
void insertion_sort(std::vector<T>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void hybrid_sort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        if (right - left + 1 <= 16) {
            insertion_sort(arr, left, right);
        } else {
            int mid = left + (right - left) / 2;
            hybrid_sort(arr, left, mid);
            hybrid_sort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
}

template <typename T>
void print_vector(const std::vector<T>& arr) {
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> int_data = {12, 11, 13, 5, 6, 7, 34, 2, 0, -5};
    hybrid_sort(int_data, 0, int_data.size() - 1);
    print_vector(int_data);

    std::vector<double> double_data = {3.14, 1.41, 2.71, 0.5, 100.0, -1.5};
    hybrid_sort(double_data, 0, double_data.size() - 1);
    print_vector(double_data);

    std::vector<std::string> string_data = {"banana", "apple", "cherry", "date"};
    hybrid_sort(string_data, 0, string_data.size() - 1);
    print_vector(string_data);

    return 0;
}