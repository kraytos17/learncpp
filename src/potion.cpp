#include <array>
#include <iostream>
#include <limits>
#include <string_view>
#include "rand.hpp"

namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        max_potions,
    };

    using namespace std::string_view_literals;
    constexpr std::array<std::string_view, max_potions> names{"healing"sv, "mana"sv, "speed"sv, "invisibility"sv};
    constexpr std::array<Type, max_potions> types{healing, mana, speed, invisibility};
    constexpr std::array<int, max_potions> costs{20, 30, 12, 50};

    static_assert(std::size(types) == max_potions);
    static_assert(std::size(costs) == max_potions);
    static_assert(std::size(names) == max_potions);
} // namespace Potion

class Player {
private:
    static constexpr int s_minStartingGold{20};
    static constexpr int s_maxStartingGold{200};

    std::string m_name{};
    int m_gold{};
    std::array<int, Potion::max_potions> m_inventory{};

public:
    explicit Player(std::string_view name) : m_name{name}, m_gold{Random::get(s_minStartingGold, s_maxStartingGold)} {}

    int gold() const { return m_gold; }

    int inventory(Potion::Type x) { return m_inventory[x]; }

    bool buy(Potion::Type type) {
        if (m_gold < Potion::costs[type])
            return false;

        m_gold -= Potion::costs[type];
        ++m_inventory[type];
        return true;
    }
};

Potion::Type potionToBuy() {
    std::cout << "Enter the option of the potion you want to buy, or press 'q' to quit.\n";
    char input{};
    while (true) {
        std::cin >> input;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (!std::cin.eof() && std::cin.peek() != '\n') {
            std::cout << "Invalid input. Try again: \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (input == 'q')
            return Potion::Type::max_potions;

        int converted{input - 'a'};
        if (converted >= 0 && converted < Potion::max_potions)
            return static_cast<Potion::Type>(converted);

        std::cout << "Invalid input. Try again: \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printInventory(Player& player) {
    std::cout << "Your inventory contains: \n";

    for (auto p: Potion::types) {
        if (player.inventory(p) > 0)
            std::cout << player.inventory(p) << "x potion of " << Potion::names[p] << '\n';
    }

    std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
}

void shop(Player& player) {
    std::cout << "Here is our selection for today:\n";
    for (auto x: Potion::types)
        std::cout << static_cast<char>(x + 97) << ") " << Potion::names[x] << " costs " << Potion::costs[x] << '\n';

    Potion::Type potion{potionToBuy()};
    if (potion == Potion::Type::max_potions)
        return;

    bool success{player.buy(potion)};
    if (!success)
        std::cout << "Buy failed.\n";
    else
        std::cout << "You purchased a potion of " << Potion::names[potion] << ". You have " << player.gold()
                  << " gold left.\n";
}


int main() {
    std::cout << "Welcome to Roscoe's potion emporium!\nEnter you name: ";
    std::string name{};
    std::cin >> name;
    Player player{name};
    std::cout << "Hello, " << name << ", you have " << player.gold() << " gold.\n\n";
    shop(player);
    std::cout << '\n';
    printInventory(player);
    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
    return 0;
}
