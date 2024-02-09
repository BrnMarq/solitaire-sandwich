#include <CardDeck.hpp>

int main()
{
    CardDeck empty_deck = CardDeck::create_empty_deck();
    std::cout << "Empty deck: " << to_string(empty_deck) << std::endl;

    CardDeck full_deck = CardDeck::create_full_deck();
    std::cout << "Full deck: " << to_string(full_deck) << std::endl;

    rd_t rd{};
    rng_t rng{rd()};

    CardDeck random_deck_10 = CardDeck::create_random_deck(rng, 10);
    std::cout << "Random deck (10 cards): " << to_string(random_deck_10) << std::endl;

    CardDeck random_unique_deck_10 = CardDeck::create_random_unique_deck(rng, 10);
    std::cout << "Random unique deck (expected 10 cards): " << to_string(random_unique_deck_10) << std::endl;

    return EXIT_SUCCESS;
}