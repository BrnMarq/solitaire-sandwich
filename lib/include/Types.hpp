#pragma once

#include <iostream>
#include <optional>
#include <random>
#include <sstream>

using rd_t = std::random_device;
using rng_t = std::mt19937;
using seed_t = rd_t::result_type;
using optional_seed_t = std::optional<seed_t>;

enum class Color
{
    REnd,
    Red,
    Black,
    End
};

std::string to_string(Color color) noexcept;

enum class Suit
{
    REnd,
    Spades,
    Hearts,
    Clubs,
    Diamonds,
    End
};

Suit& operator ++ (Suit& suit);

Suit operator ++ (Suit& suit, int);

Suit& operator -- (Suit& suit);

Suit operator -- (Suit& suit, int);

std::string to_string(Suit suit) noexcept;

enum class Rank
{
    REnd,
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    End
};

// This an integral type, so you can perform arithmetic operations with any variable of this type
using card_value_t = std::underlying_type<Rank>::type;

Rank& operator ++ (Rank& rank);

Rank operator ++ (Rank& rank, int);

Rank& operator -- (Rank& rank);

Rank operator -- (Rank& rank, int);

std::string to_string(Rank rank) noexcept;