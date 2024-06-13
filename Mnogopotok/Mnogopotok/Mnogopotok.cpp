#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        std::vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        std::vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }

private:
    void Merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            arr[k++] = left[i++];
        }
        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    std::vector<int> arr(10);

    std::cout << "Введите 10 целых чисел: ";
    for (int& num : arr) {
        std::cin >> num;
    }

    MergeSort sorter;
    std::thread mergeSortThread([&sorter, &arr]() { sorter.Sort(arr); });

    mergeSortThread.join();

    std::cout << "Отсортированный массив: ";
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
