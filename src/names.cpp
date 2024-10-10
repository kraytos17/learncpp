#include <algorithm>
#include <iostream>

int main() {
    std::cout << "How many names would you like to enter? ";

    std::size_t len{};
    std::cin >> len;
    std::string* array{new std::string[len]{}};

    for (std::size_t i{0}; i < len; ++i) {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::string name{};
        std::cin >> name;
        array[i] = name;
    }

    std::sort(array, array + len);
    std::cout << "\nHere is your sorted list:\n";
    for (std::size_t i{0}; i < len; ++i) {
        std::cout << "Name #" << i + 1 << ": " << array[i] << '\n';
    }

    delete[] array;
    return 0;
}
