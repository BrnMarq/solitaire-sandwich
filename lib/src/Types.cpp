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
        case Suit::Spades: return "♠";
        case Suit::Hearts: return "♥";
        case Suit::Clubs: return "♦";
        case Suit::Diamonds: return "♣";
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
        case Rank::Ace: return "1";
        case Rank::Two: return "2";
        case Rank::Three: return "3";
        case Rank::Four: return "4";
        case Rank::Five: return "5";
        case Rank::Six: return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine: return "9";
        case Rank::Ten: return "10";
        case Rank::Jack: return "11";
        case Rank::Queen: return "12";
        case Rank::King: return "13";
        default: return "";
    }
}