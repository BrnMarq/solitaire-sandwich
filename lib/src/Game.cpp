#include<iostream>
#include<map>
#include<numeric>

#include <algorithm>

#include <Game.hpp>
#include <Settings.hpp>

typedef std::function<bool(Card)> CardFilter;
typedef std::pair<CardDeck, CardDeck> DeckPair;
// Settings
CardFilter filter(Suit suit) { return [&](Card card) { return card.get_suit() == suit; }; };
CardFilter filter(Color color) { return [&](Card card) { return get_card_color(card) == color; }; };
std::unordered_map<Suit, Color> SUIT_COLORS = {
    {Suit::Clubs, Color::Black},
    {Suit::Spades, Color::Black},
    {Suit::Hearts, Color::Red},
    {Suit::Diamonds, Color::Red}
};
std::list<std::variant<Suit, Color>> SANDWICH_PRIORITIES = {
    Suit::Spades,
    Suit::Hearts,
    Suit::Clubs,
    Suit::Diamonds,
    Color::Red,
    Color::Black,
};
int HAND_SIZE = 8;
int SANDWICH_SIZE = 3;

// Helpers
bool are_different_suits(Card first, Card second) { return first.get_suit() != second.get_suit(); }
bool are_different_colors(Card first, Card second) { return get_card_color(first) != get_card_color(second); }
std::vector<int> init_pointer_register() {
    std::vector<int> pointer_register;
    for (int i = 0; i < SANDWICH_SIZE - 1; ++i) {
        pointer_register.push_back(SANDWICH_SIZE - 2 - i);
    }
    return pointer_register;
}
DeckPair remove_sandwich(CardDeck sandwich, CardDeck hand) {
    hand.remove_if([&](const Card& card){
        return std::find(sandwich.begin(), sandwich.end(), card)!= sandwich.end();
    });
    return std::make_pair(sandwich, hand);
}
int update_pointer_register(std::vector<int>& pointer_register, int pointer_number) {
    int position = pointer_number - 1;
    int next_number = pointer_register[position] + 1;
    ++pointer_register[position];
    for (int i = position - 1; i >= 0; --i) {
        pointer_register[i] = pointer_register[i + 1] + 1;
    }
    return next_number;
}
int get_same_amount(CardDeck deck1, CardDeck deck2) {
    int same_amount = 0;
    auto it1 = deck1.end();
    auto it2 = deck2.end();
    do {
        --it1;
        --it2;
        if (*it1 != *it2) return same_amount;
        ++same_amount;
    }
    while(it1 != deck1.begin() && it2 != deck2.begin());
    return same_amount;
}
CardDeck copy_last_n(CardDeck deck, int n) {
    CardDeck copy = CardDeck::create_empty_deck();
    auto it = deck.end();
    while (n > 0) {
        --it;
        copy.push_front(*it);
        --n;
    }
    return copy;
}
int clamp(int n, int min, int max) {
    int m = abs(n);
    if (n < min) return clamp(max - m, min, max);
    if (n > max) return clamp(m - max - 1, min, max);
    return n;
}
int get_difference(int val1, int val2) { return clamp(val1 - val2, 0, 13); }
bool check_sandwich(const CardDeck& cards) {
    std::list<int> card_values;
    std::transform(cards.begin(), cards.end(), std::back_inserter(card_values), get_card_value);
    for (int i = 0; i < SANDWICH_SIZE; i++) {
        std::list<int> differences;
        std::adjacent_difference(card_values.begin(), card_values.end(), std::back_inserter(differences), get_difference);
        differences.pop_front();
        if (std::adjacent_find(differences.begin(), differences.end(), std::not_equal_to<>()) == differences.end()) {
            return true;
        }
        int card = card_values.front();
        card_values.pop_front();
        card_values.push_back(card);
    }
    return false;
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

DeckPair create_hand(CardDeck deck) noexcept
{
    return draw_cards(deck, HAND_SIZE);
}

DeckPair draw_cards(CardDeck deck, size_t n) noexcept
{
    CardDeck hand = CardDeck::create_empty_deck();
    for (int i = 0; i < n; i++) {
        Card last = deck.front();
        hand.push_back(last);
        deck.pop_front();
    }
    return std::make_pair(hand, deck);
}

DeckPair find_sandwich(CardDeck hand) noexcept
{
    hand.sort([](Card card, Card card2) { return get_card_value(card) < get_card_value(card2);});
    if (hand.size() < SANDWICH_SIZE) return std::make_pair(CardDeck::create_empty_deck(), hand);

    auto card = hand.begin();
    CardDeck cards = CardDeck::create_empty_deck();
    CardDeck last_cards = copy_last_n(hand , SANDWICH_SIZE);
    std::vector<int> pointer_register = init_pointer_register();
    while (true) {
        if (cards.size() == SANDWICH_SIZE) {
            int same_amount = get_same_amount(cards, last_cards);
            if (check_sandwich(cards)) return remove_sandwich(cards, hand);
            if (same_amount == SANDWICH_SIZE) break;
            cards.erase(std::prev(cards.end(), same_amount + 1), cards.end());
            if (same_amount > 0) {
                int next_card = update_pointer_register(pointer_register, same_amount);
                card = std::next(hand.begin(), next_card);
            }
        }
        cards.push_back(*card);
        ++card;
    }
    return std::make_pair(CardDeck::create_empty_deck(), hand);
} 

DeckPair find_best_sandwich(CardDeck hand) noexcept
{
    for (const auto& filter_param : SANDWICH_PRIORITIES) {
        CardDeck filtered_hand;
        std::visit([&](auto&& param) {
            std::copy_if(hand.begin(), hand.end(), std::back_inserter(filtered_hand), filter(param));
        }, filter_param);
        DeckPair result = find_sandwich(filtered_hand);
        const auto& [sandwich, rest] = result;
        if (rest.size() != filtered_hand.size()) return remove_sandwich(sandwich, hand);
    }
    
    return find_sandwich(hand);
}

std::tuple<bool, size_t, CardDeck, CardDeck> play(CardDeck deck) noexcept
{
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}

std::tuple<bool, size_t, CardDeck, CardDeck> play_optimally(CardDeck deck) noexcept
{
    // Write your solution here
    return std::make_tuple(false, 0, CardDeck::create_empty_deck(), deck);
}