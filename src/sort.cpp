#include <iostream>
#include <iterator>

// unoptimized sort
void unoptimized() {
    int array[]{6, 3, 2, 9, 7, 1, 5, 4, 8};
    constexpr int len = static_cast<int>(std::ssize(array));
    for (int i{0}; i < len - 1; ++i) {
        for (int j{0}; j < len - 1; ++j) {
            if (array[j] > array[j + 1])
                std::swap(array[j], array[j + 1]);
        }
    }

    for (int i{0}; i < len; ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';
}

// optimized sort
void optimized() {
    int array[]{6, 3, 2, 9, 7, 1, 5, 4, 8};
    constexpr int len = static_cast<int>(std::ssize(array));
    for (int i{0}; i < len - 1; ++i) {
        bool swapped{false};
        for (int j{0}; j < len - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            std::cout << "Early termination on iteration " << i + 1 << '\n';
            break;
        }
    }

    for (int i{0}; i < len; ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';
}

int main() {
    std::cout << "Unoptimized Bubble Sort : \n";
    unoptimized();
    std::cout << "Optimized Bubble Sort : \n";
    optimized();
    return 0;
}
