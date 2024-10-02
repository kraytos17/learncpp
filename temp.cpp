#include <array>
#include <iostream>

void printLength(const std::array<int, 5>& arr)
{
    constexpr int length{std::size(arr)}; // weird conversion error
    std::cout << "length: " << length << '\n';
    [[maybe_unused]] constexpr int narrowing = 5UL; // unsigned long -> int but constexpr so no narrowing warning
    [[maybe_unused]] auto x = 5UL;
}

int main()
{
    std::array arr{9, 7, 5, 3, 1};
    constexpr int length{std::size(arr)}; // works just fine
    std::cout << "length: " << length << '\n';
    printLength(arr);

    return 0;
}
