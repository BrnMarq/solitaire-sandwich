#include <algorithm>
#include <random>
#include <unordered_set>
#include <vector>

#include <CardDeck.hpp>

CardDeck CardDeck::create_full_deck(bool visible) noexcept
{
    CardDeck result{};

    for (Suit suit = Suit::Spades; suit < Suit::End; ++suit)
    {
        for (Rank rank = Rank::Ace; rank < Rank::End; ++rank)
        {
            result.push_back(Card{suit, rank, visible});
        }
    }

    return result;
}

CardDeck CardDeck::create_empty_deck() noexcept
{
    return CardDeck{};
}

CardDeck CardDeck::create_random_deck(rng_t& rng, size_t n, bool visible) noexcept
{
    CardDeck result;

    while (n-- > 0)
    {
        result.push_back(Card::create_random_card(rng, visible));
    }

    return result;
}

CardDeck CardDeck::create_random_unique_deck(rng_t& rng, size_t expected_n, bool visible) noexcept
{
    expected_n = std::min<size_t>(52, expected_n);

    std::unordered_set<Card, CardHash> cs;

    while (expected_n-- > 0)
    {
        cs.insert(Card::create_random_card(rng, visible));
    }

    return CardDeck{cs.begin(), cs.end()};
}

void CardDeck::shuffle(rng_t& rng) noexcept
{
    std::vector<Card> cs;
    while (!Base::empty())
    {
        cs.push_back(Base::back());
        Base::pop_back();
    }

    std::shuffle(cs.begin(), cs.end(), rng);

    for (const Card& card: cs)
    {
        Base::push_back(card);
    }
}

std::string to_string(const CardDeck& deck) noexcept
{
    std::stringstream s;

    s << "[";

    auto it = deck.begin();
    
    if (it != deck.end())
    {
        s << to_string(*it);
        ++it;
    }

    for ( ; it != deck.end(); ++it)
    {
        s << ", " << to_string(*it);
    }

    s << "]";

    return s.str();
}