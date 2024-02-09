/**
 * @author: 
*/

#pragma once

#include <tuple>

#include <CardDeck.hpp>

// Warming problems

Color get_card_color(const Card& card) noexcept;

card_value_t get_card_value(const Card& card) noexcept;

// Intermediate problems

bool are_all_same_suit(const CardDeck& deck) noexcept;

bool are_all_same_color(const CardDeck& deck) noexcept;

std::pair<CardDeck, CardDeck> create_hand(CardDeck deck) noexcept;

std::pair<CardDeck, CardDeck> draw_cards(CardDeck deck, size_t n) noexcept;

// Advanced problem

std::pair<CardDeck, CardDeck> find_sandwich(CardDeck hand) noexcept;

// Challenging problem

std::pair<CardDeck, CardDeck> find_best_sandwich(CardDeck hand) noexcept;

// Play problems

std::tuple<bool, size_t, CardDeck, CardDeck> play(CardDeck deck) noexcept;

std::tuple<bool, size_t, CardDeck, CardDeck> play_optimally(CardDeck deck) noexcept;