#include <algorithm>
#include <iostream>
#include <ranges>
#include <string_view>
#include "rand.hpp"

namespace WordList
{
    constexpr int randWordLength = 9;
    constexpr std::array<std::string_view, randWordLength> words{
        "mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};

    std::string_view getRandWord() { return words[Random::get<std::size_t>(0, words.size() - 1)]; }
} // namespace WordList

namespace Guesses
{
    constexpr int wrongGuesses{6};
}

class Session
{
private:
    std::string_view m_word{WordList::getRandWord()};
    std::array<bool, 26> m_letterGuessed{};
    int m_wrongGuessesLeft{Guesses::wrongGuesses};

    static constexpr std::size_t toIdx(char c) { return static_cast<std::size_t>(c - 'a'); }

public:
    [[nodiscard]] std::string_view getWord() const { return m_word; }

    [[nodiscard]] bool isLetterGuessed(char c) const { return m_letterGuessed[toIdx(c)]; }

    void setLetterGuessed(char c) { m_letterGuessed[toIdx(c)] = true; }

    [[nodiscard]] int wrongGuessesLeft() const { return m_wrongGuessesLeft; }

    void removeGuess() { --m_wrongGuessesLeft; }

    [[nodiscard]] bool isLetterInWord(char c) const
    {
        return std::ranges::any_of(m_word, [c](char l) { return l == c; });
    }

    [[nodiscard]] bool won() const
    {
        return std::ranges::all_of(m_word, [this](char l) { return isLetterGuessed(l); });
    }
};

void drawState(const Session& session)
{
    std::cout << "The word: ";
    for (const auto& c : session.getWord())
    {
        std::cout << (session.isLetterGuessed(c) ? c : '_');
    }

    std::cout << "   Wrong guesses: ";
    std::ranges::for_each(std::views::iota(0, session.wrongGuessesLeft()), [](int) { std::cout << '+'; });

    for (char c = 'a'; c <= 'z'; ++c)
    {
        if (session.isLetterGuessed(c) && !session.isLetterInWord(c))
            std::cout << c;
    }

    std::cout << '\n';
}

static char guessLetter(const Session& s)
{
    while (true)
    {
        std::cout << "Enter your next letter: ";
        char l{};
        std::cin >> l;

        if (!std::cin || l < 'a' || l > 'z')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That wasn't a valid input. Try again.\n";
            continue;
        }

        if (s.isLetterGuessed(l))
        {
            std::cout << "You have already guessed that. Please try again.\n";
            continue;
        }

        return l;
    }
}

void handleGuess(Session& s, char c)
{
    s.setLetterGuessed(c);
    if (s.isLetterInWord(c))
    {
        std::cout << "Yes, '" << c << "' is in the word!\n";
    }
    else
    {
        std::cout << "No, '" << c << "' is not in the word!\n";
        s.removeGuess();
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\nTo win: guess the word.  To lose: run out of pluses.\n";

    Session s{};
    while (s.wrongGuessesLeft() && !s.won())
    {
        drawState(s);
        const char c{guessLetter(s)};
        handleGuess(s, c);
    }

    drawState(s);
    if (!s.wrongGuessesLeft())
        std::cout << "You lost!  The word was: " << s.getWord() << '\n';
    else
        std::cout << "You won!\n";

    return 0;
}
