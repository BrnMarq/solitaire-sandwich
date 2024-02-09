#include <algorithm>
#include <tuple>
#include <vector>

#include <TestUtilities.hpp>

std::ostream& operator << (std::ostream& out, Color color) noexcept
{
    out << to_string(color);
    return out;
}

std::ostream& operator << (std::ostream& out, Suit suit) noexcept
{
    out << to_string(suit);
    return out;
}

std::ostream& operator << (std::ostream& out, Rank rank) noexcept
{
    out << to_string(rank);
    return out;
}

std::ostream& operator << (std::ostream& out, const std::pair<CardDeck, CardDeck>& p) noexcept
{
    out << "(" << to_string(p.first) << ", " << to_string(p.second) << ")";
    return out;
}

std::ostream& operator << (std::ostream& out, const std::tuple<bool, size_t, CardDeck, CardDeck>& t) noexcept
{
    out << "(" << std::get<0>(t) << ", "
               << std::get<1>(t) << ", "
               << to_string(std::get<2>(t)) << ", "
               << to_string(std::get<3>(t)) << ")";
    return out;
}

bool equal(const CardDeck& cd1, const CardDeck& cd2) noexcept
{
    if (cd1.size() != cd2.size())
    {
        return false;
    }

    std::vector<Card> cv1{cd1.begin(), cd1.end()};
    std::vector<Card> cv2{cd2.begin(), cd2.end()};

    auto less_card = [] (const Card& c1, const Card& c2)
    {
        if (c1.get_suit() < c2.get_suit())
        {
            return true;
        }
        
        if (c1.get_suit() > c2.get_suit())
        {
            return false;
        }

        return c1.get_rank() < c2.get_rank();
    };

    std::sort(cv1.begin(), cv1.end(), less_card);
    std::sort(cv2.begin(), cv2.end(), less_card);

    for (size_t i = 0; i < cv1.size(); ++i)
    {
        if (cv1[i] != cv2[i])
        {
            return false;
        }
    }

    return true;
}

bool equal(const std::pair<CardDeck, CardDeck>& p1, const std::pair<CardDeck, CardDeck>& p2) noexcept
{
    return equal(p1.first, p2.first) && equal(p1.second, p2.second);
}

bool equal(const std::tuple<bool, size_t, CardDeck, CardDeck>& t1, const std::tuple<bool, size_t, CardDeck, CardDeck>& t2) noexcept
{
    return equal(std::get<0>(t1), std::get<0>(t2)) &&
           equal(std::get<1>(t1), std::get<1>(t2)) &&
           equal(std::get<2>(t1), std::get<2>(t2)) &&
           equal(std::get<3>(t1), std::get<3>(t2));
}