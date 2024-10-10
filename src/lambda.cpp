#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <vector>
#include "rand.hpp"

std::vector<int> generateNumbers(int start, int count, int multiplier) {
    std::vector<int> numbers;
    numbers.reserve(count);
    for (int i = 0; i < count; ++i) {
        numbers.push_back((start + i) * (start + i) * multiplier);
    }

    return numbers;
}

int main() {
    int start, count;
    std::cout << "Start where? ";
    std::cin >> start;
    std::cout << "How many? ";
    std::cin >> count;

    int multiplier = Random::get(2, 4);
    auto numbers = generateNumbers(start, count, multiplier);
    std::cout << std::format(
        "I generated {} square numbers. Do you know what each number is after multiplying it by {}?\n", count,
        multiplier);

    while (!numbers.empty()) {
        int guess;
        std::cout << "> ";
        std::cin >> guess;

        if (auto it = std::find(numbers.begin(), numbers.end(), guess); it != numbers.end()) {
            numbers.erase(it);
            std::cout << std::format("Nice! {} number(s) left.\n", numbers.size());
        } else {
            auto closest = std::min_element(numbers.begin(), numbers.end(), [guess](int a, int b) {
                return std::abs(a - guess) < std::abs(b - guess);
            });

            std::cout << std::format("{} is wrong! Try {} next time.\n", guess, *closest);
            return 0;
        }
    }

    std::cout << "You found all numbers, good job!\n";
    return 0;
}
