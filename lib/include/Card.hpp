#pragma once

#include <Types.hpp>

class Card
{
public:
    static Card create_random_card(rng_t& rng, bool visible = true) noexcept;

    Card(Suit s, Rank r, bool is_visible = true) noexcept;

    Suit get_suit() const noexcept;

    Rank get_rank() const noexcept;

    bool is_visible() const noexcept;

    void flip() noexcept;

    bool operator == (const Card& card) const noexcept;

    bool operator != (const Card& card) const noexcept;

private:
    Suit suit;
    Rank rank;
    bool visible;
};

std::string to_string(const Card& card) noexcept;

struct CardHash
{
    size_t operator () (const Card& c) const noexcept;
};