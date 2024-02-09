#pragma once

#include <list>

#include <Card.hpp>

class CardDeck : public std::list<Card>
{
    using Base = std::list<Card>;
    using Base::Base;

public:
    static CardDeck create_full_deck(bool visible = true) noexcept;

    static CardDeck create_empty_deck() noexcept;

    static CardDeck create_random_deck(rng_t& rng, size_t n, bool visible = true) noexcept;

    static CardDeck create_random_unique_deck(rng_t& rng, size_t expected_n, bool visible = true) noexcept;

    void shuffle(rng_t& rng) noexcept;
};

std::string to_string(const CardDeck& deck) noexcept;