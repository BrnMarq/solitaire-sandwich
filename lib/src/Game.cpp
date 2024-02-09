#include<iostream>
#include<map>

#include <algorithm>

#include <Game.hpp>
#include <Settings.hpp>

std::map<Suit, Color> SUIT_COLORS = {
    {Suit::Clubs, Color::Black},
    {Suit::Spades, Color::Black},
    {Suit::Hearts, Color::Red},
    {Suit::Diamonds, Color::Red}
};
int HAND_SIZE = 8;
int SANDWICH_SIZE = 3;
bool are_different_suits(Card first, Card second) { return first.get_suit() != second.get_suit(); }
bool are_different_colors(Card first, Card second) { return get_card_color(first) != get_card_color(second); }
int clamp(int n, int min, int max) {
    int m = abs(n);
    if (n < min) return clamp(max - m, min, max);
    if (n > max) return clamp(m - max - 1, min, max);
    return n;
}

Color get_card_color(const Card& card) noexcept
{
    return SUIT_COLORS.find(card.get_suit())->second;
}

card_value_t get_card_value(const Card& card) noexcept
{
    return static_cast<std::underlying_type<Suit>::type>(card.get_rank());
}

bool are_all_same_suit(const CardDeck& deck) noexcept
{
    return std::adjacent_find(deck.begin(), deck.end(), are_different_suits) == deck.end();
}

bool are_all_same_color(const CardDeck& deck) noexcept
{
    return std::adjacent_find(deck.begin(), deck.end(), are_different_colors) == deck.end();
}

std::pair<CardDeck, CardDeck> create_hand(CardDeck deck) noexcept
{   
    return draw_cards(deck, HAND_SIZE);
}

std::pair<CardDeck, CardDeck> draw_cards(CardDeck deck, size_t n) noexcept
{
    CardDeck hand = CardDeck::create_empty_deck();
    for (int i = 0; i < n; i++) {
        Card last = deck.front();
        hand.push_back(last);
        deck.pop_front();
    }
    return std::make_pair(hand, deck);
}

std::pair<CardDeck, CardDeck> find_sandwich(CardDeck hand) noexcept
{
    if (hand.size() < SANDWICH_SIZE) return std::make_pair(CardDeck::create_empty_deck(), hand);
    hand.sort([](Card card, Card card2) { return get_card_value(card) < get_card_value(card2);});
    auto first_card_it = hand.begin();
    auto second_card_it = std::next(first_card_it);
    auto third_card_it = std::next(second_card_it);
    while (first_card_it != std::prev(hand.end(), 2)) {
        if (second_card_it == std::prev(hand.end())) {
            ++first_card_it;
            second_card_it = std::next(first_card_it);
            third_card_it = std::next(second_card_it);
            continue;
        }
        if(third_card_it == hand.end()) {
            ++second_card_it;
            third_card_it = std::next(second_card_it);
            continue;
        }
        std::vector<Card> cards = { *first_card_it, *second_card_it, *third_card_it };
        for (int i = 0; i < 3; ++i) {
            Card first_card = cards[i];
            Card second_card = cards[clamp(i + 1, 0, SANDWICH_SIZE - 1)];
            Card third_card = cards[clamp(i + 2, 0, SANDWICH_SIZE - 1)];
            if (get_card_value(third_card) - get_card_value(second_card) == get_card_value(second_card) - get_card_value(first_card)) {
                std::cout << to_string(first_card) << std::endl;
                std::cout << to_string(second_card) << std::endl;
                std::cout << to_string(third_card) << std::endl;
            }
        }
        ++third_card_it;
    }
    return std::make_pair(CardDeck::create_empty_deck(), hand);
}

std::pair<CardDeck, CardDeck> find_best_sandwich(CardDeck hand) noexcept
{
    // Write your solution here
    return std::make_pair(CardDeck::create_empty_deck(), hand);
}
std::tuple<bool, size_t, CardDeck, CardDeck> play(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}

std::tuple<bool, size_t, CardDeck, CardDeck> play_optimally(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}