#include <array>
#include <iostream>
#include <string_view>

namespace Animal {
    enum Type {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals,
    };

    struct Data {
        std::string_view name{};
        int numLegs{};
        std::string_view sound{};
    };

    constexpr std::array animals{
            Data{"chicken", 2, "cluck"},  Data{"dog", 4, "woof"},   Data{"cat", 4, "meow"},
            Data{"elephant", 4, "pawoo"}, Data{"duck", 2, "quack"}, Data{"snake", 0, "hiss"},
    };

    constexpr std::array types{chicken, dog, cat, elephant, duck, snake};

    static_assert(std::size(types) == max_animals);
    static_assert(std::size(animals) == max_animals);
} // namespace Animal

std::istream& operator>>(std::istream& in, Animal::Type& animal) {
    std::string ip{};
    std::getline(in >> std::ws, ip);

    for (std::size_t i{0}; i < Animal::types.size(); ++i) {
        if (ip == Animal::animals[i].name) {
            animal = static_cast<Animal::Type>(i);
            return in;
        }
    }

    in.setstate(std::ios::failbit);
    return in;
}

void printInfo(Animal::Type type) {
    const Animal::Data& animal{Animal::animals[type]};
    std::cout << "A " << animal.name << " has " << animal.numLegs << " legs and says " << animal.sound << ".\n";
}

int main() {
    std::cout << "Enter an animal: ";
    Animal::Type type{};
    std::cin >> type;

    if (!std::cin) {
        std::cin.clear();
        std::cout << "That animal couldn't be found.\n";
        type = Animal::max_animals;
    } else
        printInfo(type);

    std::cout << "\nHere is the data for the rest of the animals:\n";
    for (auto a: Animal::types) {
        if (a != type)
            printInfo(a);
    }

    return 0;
}
