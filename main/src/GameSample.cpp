#include <Game.hpp>

int main()
{
    rd_t rd{};
    seed_t seed = rd();
    rng_t rng{seed};

    std::cout << "Seed: " << seed << std::endl;

    CardDeck initial_deck = CardDeck::create_full_deck();
    initial_deck.shuffle(rng);

    std::cout << "Initial deck: " << to_string(initial_deck) << std::endl;

    auto [hand, deck] = create_hand(initial_deck);

    std::cout << "Hand: " << to_string(hand) << std::endl;
    std::cout << "Deck: " << to_string(deck) << std::endl;

    {
        auto [sandwich, remaining_hand] = find_sandwich(hand);
        std::cout << "Found sandiwch: " << to_string(sandwich) << std::endl;
        std::cout << "Remaining hand: " << to_string(remaining_hand) << std::endl;
    }

    {
        auto [sandwich, remaining_hand] = find_best_sandwich(hand);
        std::cout << "Found best sandiwch: " << to_string(sandwich) << std::endl;
        std::cout << "Remaining hand: " << to_string(remaining_hand) << std::endl;
    }

    std::cout << std::boolalpha;

    {
        std::cout << "Playing normal game\n";
        auto [win, score, final_hand, final_deck] = play(deck);
        std::cout << "Win: " << win << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Final hand: " << to_string(final_hand) << std::endl;
        std::cout << "Final deck: " << to_string(final_deck) << std::endl;
    }

    {
        std::cout << "Playing optimal game\n";
        auto [win, score, final_hand, final_deck] = play_optimally(deck);
        std::cout << "Win: " << win << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Final hand: " << to_string(final_hand) << std::endl;
        std::cout << "Final deck: " << to_string(final_deck) << std::endl;
    }

    return EXIT_SUCCESS;
}