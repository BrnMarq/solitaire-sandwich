#pragma once

#include <CardDeck.hpp>

std::ostream& operator << (std::ostream& out, Color color) noexcept;

std::ostream& operator << (std::ostream& out, Suit suit) noexcept;

std::ostream& operator << (std::ostream& out, Rank rank) noexcept;

std::ostream& operator << (std::ostream& out, const std::pair<CardDeck, CardDeck>& p) noexcept;

std::ostream& operator << (std::ostream& out, const std::tuple<bool, size_t, CardDeck, CardDeck>& t) noexcept;

bool equal(const CardDeck& cd1, const CardDeck& cd2) noexcept;

bool equal(const std::pair<CardDeck, CardDeck>& p1, const std::pair<CardDeck, CardDeck>& p2) noexcept;

bool equal(const std::tuple<bool, size_t, CardDeck, CardDeck>& t1, const std::tuple<bool, card_value_t, CardDeck, CardDeck>& t2) noexcept;

template <typename T>
bool equal(const T& v1, const T& v2) noexcept
{
    return v1 == v2;
}

template <typename T>
void assert_equal(const T& current, const T& expected) noexcept
{
    if (!equal(current, expected))
    {
        std::cerr << "Test failed:\n";
        std::cerr << "Current: " << current << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        abort();
    }

    std::cout << "Test ok!\n";
}