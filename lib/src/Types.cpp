#include <type_traits>

#include <Types.hpp>

std::string to_string(Color color) noexcept
{
    switch (color)
    {
        case Color::Red: return "Red";
        case Color::Black: return "Black";
        default: return "";
    }
}

Suit& operator ++ (Suit& suit)
{
    if (suit == Suit::End)
    {
        throw std::overflow_error{"suit cannot be incremented"};
    }

    using base_type = std::underlying_type<Suit>::type;
    suit = static_cast<Suit>(static_cast<base_type>(suit) + 1);
    return suit;
}

Suit operator ++ (Suit& suit, int)
{
    Suit result = suit;
    ++suit;
    return suit;
}

Suit& operator -- (Suit& suit)
{
    if (suit == Suit::REnd)
    {
        throw std::underflow_error{"suit cannot be decremented"};
    }

    using base_type = std::underlying_type<Suit>::type;
    suit = static_cast<Suit>(static_cast<base_type>(suit) - 1);
    return suit;
}

Suit operator -- (Suit& suit, int)
{
    Suit result = suit;
    --suit;
    return suit;
}

std::string to_string(Suit suit) noexcept
{
    switch (suit)
    {
        case Suit::Spades: return "Spades";
        case Suit::Hearts: return "Hearts";
        case Suit::Clubs: return "Clubs";
        case Suit::Diamonds: return "Diamonds";
        default: return "";
    }
}

Rank& operator ++ (Rank& rank)
{
    if (rank == Rank::End)
    {
        throw std::underflow_error{"rank cannot be incremented"};
    }

    using base_type = std::underlying_type<Rank>::type;
    rank = static_cast<Rank>(static_cast<base_type>(rank) + 1);
    return rank;
}

Rank operator ++ (Rank& rank, int)
{
    Rank result = rank;
    ++rank;
    return result;
}

Rank& operator -- (Rank& rank)
{
    if (rank == Rank::REnd)
    {
        throw std::underflow_error{"rank cannot be decremented"};
    }

    using base_type = std::underlying_type<Rank>::type;
    rank = static_cast<Rank>(static_cast<base_type>(rank) - 1);
    return rank;
}

Rank operator -- (Rank& rank, int)
{
    Rank result = rank;
    --rank;
    return result;
}

std::string to_string(Rank rank) noexcept
{
    switch (rank)
    {
        case Rank::Ace: return "Ace";
        case Rank::Two: return "Two";
        case Rank::Three: return "Three";
        case Rank::Four: return "Four";
        case Rank::Five: return "Five";
        case Rank::Six: return "Six";
        case Rank::Seven: return "Seven";
        case Rank::Eight: return "Eight";
        case Rank::Nine: return "Nine";
        case Rank::Ten: return "Ten";
        case Rank::Jack: return "Jack";
        case Rank::Queen: return "Queen";
        case Rank::King: return "King";
        default: return "";
    }
}