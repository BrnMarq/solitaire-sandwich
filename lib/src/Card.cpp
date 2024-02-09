#include <functional>

#include <Card.hpp>

Card Card::create_random_card(rng_t& rng, bool visible) noexcept
{
    using suit_type = std::underlying_type<Rank>::type;

    std::uniform_int_distribution<suit_type> suit_dist{
        static_cast<suit_type>(Suit::Spades),
        static_cast<suit_type>(Suit::Diamonds)
    };

    using rank_type = std::underlying_type<Rank>::type;

    std::uniform_int_distribution<rank_type> rank_dist{
        static_cast<rank_type>(Rank::Ace),
        static_cast<rank_type>(Rank::King)
    };

    return Card{static_cast<Suit>(suit_dist(rng)), static_cast<Rank>(rank_dist(rng)), visible};
}

Card::Card(Suit s, Rank r, bool is_visible) noexcept
    : suit{s}, rank{r}, visible{is_visible}
{
    // Empty
}

Suit Card::get_suit() const noexcept
{
    return suit;
}

Rank Card::get_rank() const noexcept
{
    return rank;
}

bool Card::is_visible() const noexcept
{
    return visible;
}

void Card::flip() noexcept
{
    visible = !visible;
}

bool Card::operator == (const Card& card) const noexcept
{
    return suit == card.suit && rank == card.rank;
}

bool Card::operator != (const Card& card) const noexcept
{
    return suit != card.suit || rank != card.rank;
}

std::string to_string(const Card& card) noexcept
{
    std::stringstream s;
    s << "(" << ::to_string(card.get_suit()) << ", " << ::to_string(card.get_rank()) << ")";
    return s.str();
}

size_t CardHash::operator () (const Card& c) const noexcept
{
    size_t suit = static_cast<size_t>(c.get_suit());
    size_t rank = static_cast<size_t>(c.get_rank());

    size_t seed{0};
    seed ^= std::hash<size_t>{}(suit) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= std::hash<size_t>{}(rank) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}