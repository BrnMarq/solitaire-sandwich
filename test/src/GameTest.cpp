#include <TestUtilities.hpp>
#include <Game.hpp>

int main()
{
    std::cout << std::boolalpha;

    std::cout << "Card color tests\n";
    assert_equal(get_card_color(Card{Suit::Hearts, Rank::Ace}), Color::Red);
    assert_equal(get_card_color(Card{Suit::Clubs, Rank::Ace}), Color::Black);
    
    std::cout << "Card value tests\n";
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Ace}), 1);
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Six}), 6);
    assert_equal(get_card_value(Card{Suit::Clubs, Rank::Queen}), 12);

    std::cout << "Deck suit tests\n";
    assert_equal(are_all_same_suit(CardDeck::create_empty_deck()), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}}), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Clubs, Rank::Two}}), true);
    assert_equal(are_all_same_suit({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}}), false);

    std::cout << "Deck color tests\n";
    assert_equal(are_all_same_color(CardDeck::create_empty_deck()), true);
    assert_equal(are_all_same_color({Card{Suit::Clubs, Rank::Ace}}), true);
    assert_equal(are_all_same_color({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}}), true);
    assert_equal(are_all_same_color({Card{Suit::Clubs, Rank::Ace}, Card{Suit::Hearts, Rank::Ace}}), false);

    std::cout << "Create hand test\n";
    {
        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Spades, Rank::Four},
            Card{Suit::Spades, Rank::Five},
            Card{Suit::Spades, Rank::Six},
            Card{Suit::Spades, Rank::Seven},
            Card{Suit::Spades, Rank::Eight}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 8; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(create_hand(CardDeck::create_full_deck()), expected_pair);
    }

    std::cout << "Draw card test\n";
    {
        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Spades, Rank::Four}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 4; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 4), expected_pair);
    }
    {
        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Spades, Rank::Three}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 3; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 3), expected_pair);
    }
    {
        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Two}
        };

        CardDeck expected_deck = CardDeck::create_full_deck();
        for (size_t i = 0; i < 2; ++i)
        {
            expected_deck.pop_front();
        }

        auto expected_pair = std::make_pair(expected_hand, expected_deck);

        assert_equal(draw_cards(CardDeck::create_full_deck(), 2), expected_pair);
    }

    // std::cout << "Check sandwich tests\n";
    // {
    //     CardDeck sandwich{
    //         Card{Suit::Hearts, Rank::Eight},
    //         Card{Suit::Spades, Rank::Ace},
    //         Card{Suit::Clubs, Rank::Jack},
    //     };
    //     assert_equal(check_sandwich(sandwich), true);
    // }
    // {
    //     CardDeck sandwich{
    //         Card{Suit::Spades, Rank::King},
    //         Card{Suit::Hearts, Rank::Nine},
    //         Card{Suit::Spades, Rank::Nine},
    //     };
    //     assert_equal(check_sandwich(sandwich), false);
    // }
    // {
    //     CardDeck sandwich{
    //         Card{Suit::Hearts, Rank::King},
    //         Card{Suit::Clubs, Rank::Queen},
    //         Card{Suit::Diamonds, Rank::Eight},
    //     };
    //     assert_equal(check_sandwich(sandwich), false);
    // }

    std::cout << "Get same amount tests\n";
    {
        CardDeck first_deck{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
        };
        CardDeck second_deck{
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
        };
        assert_equal(get_same_amount(first_deck, second_deck), 2);
    }
    {
        CardDeck first_deck{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
        };
        CardDeck second_deck{
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
        };
        assert_equal(get_same_amount(first_deck, second_deck), 0);
    }
    {
        CardDeck first_deck{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
        };
        CardDeck second_deck{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
        };
        assert_equal(get_same_amount(first_deck, second_deck), 3);
    }

    std::cout << "Copy last n tests\n";
    {
        CardDeck original{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight},
        };

        CardDeck expected_copy{
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight},
        };

        assert_equal(to_string(copy_last_n(original, 3)), to_string(expected_copy));
    }
    {
        CardDeck original{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Diamonds, Rank::Eight}
        };

        CardDeck expected_copy{
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Diamonds, Rank::Eight}
        };

        assert_equal(to_string(copy_last_n(original, 3)), to_string(expected_copy));
    }

    std::cout << "Update pointer register tests\n";
    {
        std::vector<int> pointer_register = { 2, 1, 0 };
        std::vector<int> expected_pointer_register = { 3, 2, 0};

        update_pointer_register(pointer_register, 2);

        for (int i = 0; i < 3; ++i) {
            assert_equal(pointer_register[i], expected_pointer_register[i]);
        }
    }

    std::cout << "Find sandwich tests\n";
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight},
        };

        auto expected_pair = std::make_pair(CardDeck::create_empty_deck(), hand);

        assert_equal(find_sandwich(hand), expected_pair);
    }
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Ace},
            Card{Suit::Hearts, Rank::Two},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Spades, Rank::Four},
            Card{Suit::Hearts, Rank::Ten},
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Diamonds, Rank::Ten}
        };

        CardDeck expected_sandwich{
            Card{Suit::Hearts, Rank::Ten},
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Diamonds, Rank::Ten}
        };

        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Ace},
            Card{Suit::Hearts, Rank::Two},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Spades, Rank::Four},
        };

        auto expected_pair = std::make_pair(expected_sandwich, expected_hand);

        assert_equal(find_sandwich(hand), expected_pair);
    }
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight},
        };

        auto expected_pair = std::make_pair(CardDeck::create_empty_deck(), hand);

        assert_equal(find_sandwich(hand), expected_pair);
    }

    std::cout << "Find best sandwich tests\n";
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Clubs, Rank::King},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Diamonds, Rank::Eight}
        };

        CardDeck expected_sandwich{
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Clubs, Rank::King}
        };

        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Diamonds, Rank::Eight}
        };

        auto expected_pair = std::make_pair(expected_sandwich, expected_hand);

        assert_equal(find_best_sandwich(hand), expected_pair);
    }
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Spades, Rank::King},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Diamonds, Rank::Eight}
        };

        CardDeck expected_sandwich{
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Spades, Rank::King}
        };

        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight}
        };

        auto expected_pair = std::make_pair(expected_sandwich, expected_hand);

        assert_equal(find_best_sandwich(hand), expected_pair);
    }
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Diamonds, Rank::Eight}
        };

        CardDeck expected_sandwich{
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Spades, Rank::Ace}
        };

        CardDeck expected_hand{
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Diamonds, Rank::Eight}
        };

        auto expected_pair = std::make_pair(expected_sandwich, expected_hand);

        assert_equal(find_best_sandwich(hand), expected_pair);
    }
    {
        CardDeck hand{
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Diamonds, Rank::Eight},
        };

        auto expected_pair = std::make_pair(CardDeck::create_empty_deck(), hand);

        assert_equal(find_best_sandwich(hand), expected_pair);
    }

    std::cout << "Play test\n";
    {
        CardDeck deck{
            Card{Suit::Clubs, Rank::King},
            Card{Suit::Hearts, Rank::Ace},
            Card{Suit::Diamonds, Rank::Eight},
            Card{Suit::Diamonds, Rank::Five},
            Card{Suit::Hearts, Rank::Six},
            Card{Suit::Clubs, Rank::Nine},
            Card{Suit::Hearts, Rank::Five},
            Card{Suit::Diamonds, Rank::Two},
            Card{Suit::Clubs, Rank::Six},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Five},
            Card{Suit::Hearts, Rank::Two},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::Three},
            Card{Suit::Diamonds, Rank::King},
            Card{Suit::Clubs, Rank::Two},
            Card{Suit::Clubs, Rank::Four},
            Card{Suit::Spades, Rank::Five},
            Card{Suit::Spades, Rank::Jack},
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Four},
            Card{Suit::Spades, Rank::Eight},
            Card{Suit::Hearts, Rank::Ten},
            Card{Suit::Hearts, Rank::Queen},
            Card{Suit::Clubs, Rank::Seven},
            Card{Suit::Hearts, Rank::Four},
            Card{Suit::Diamonds, Rank::Ten},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Three},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Diamonds, Rank::Jack},
            Card{Suit::Diamonds, Rank::Six},
            Card{Suit::Diamonds, Rank::Seven},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Eight},
            Card{Suit::Spades, Rank::Six},
            Card{Suit::Diamonds, Rank::Three},
            Card{Suit::Hearts, Rank::Seven},
            Card{Suit::Diamonds, Rank::Queen},
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Jack},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Diamonds, Rank::Four},
            Card{Suit::Diamonds, Rank::Nine},
            Card{Suit::Spades, Rank::Ten},
            Card{Suit::Diamonds, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Spades, Rank::Seven}
        };

        CardDeck expected_hand{
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Four},
            Card{Suit::Spades, Rank::Five},
            Card{Suit::Spades, Rank::Eight}
        };

        CardDeck expected_deck{
            Card{Suit::Hearts, Rank::Ten},
            Card{Suit::Hearts, Rank::Queen},
            Card{Suit::Clubs, Rank::Seven},
            Card{Suit::Hearts, Rank::Four},
            Card{Suit::Diamonds, Rank::Ten},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Three},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Diamonds, Rank::Jack},
            Card{Suit::Diamonds, Rank::Six},
            Card{Suit::Diamonds, Rank::Seven},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Eight},
            Card{Suit::Spades, Rank::Six},
            Card{Suit::Diamonds, Rank::Three},
            Card{Suit::Hearts, Rank::Seven},
            Card{Suit::Diamonds, Rank::Queen},
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Jack},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Diamonds, Rank::Four},
            Card{Suit::Diamonds, Rank::Nine},
            Card{Suit::Spades, Rank::Ten},
            Card{Suit::Diamonds, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Spades, Rank::Seven}
        };

        auto expected_tuple = std::make_tuple(false, size_t(0), expected_hand, expected_deck);

        assert_equal(play(deck), expected_tuple);
    }

    std::cout << "Play optimally test\n";
    {
        CardDeck deck{
            Card{Suit::Clubs, Rank::King},
            Card{Suit::Hearts, Rank::Ace},
            Card{Suit::Diamonds, Rank::Eight},
            Card{Suit::Diamonds, Rank::Five},
            Card{Suit::Hearts, Rank::Six},
            Card{Suit::Clubs, Rank::Nine},
            Card{Suit::Hearts, Rank::Five},
            Card{Suit::Diamonds, Rank::Two},
            Card{Suit::Clubs, Rank::Six},
            Card{Suit::Hearts, Rank::Eight},
            Card{Suit::Clubs, Rank::Five},
            Card{Suit::Hearts, Rank::Two},
            Card{Suit::Spades, Rank::Queen},
            Card{Suit::Hearts, Rank::Three},
            Card{Suit::Diamonds, Rank::King},
            Card{Suit::Clubs, Rank::Two},
            Card{Suit::Clubs, Rank::Four},
            Card{Suit::Spades, Rank::Five},
            Card{Suit::Spades, Rank::Jack},
            Card{Suit::Spades, Rank::Ace},
            Card{Suit::Spades, Rank::Four},
            Card{Suit::Spades, Rank::Eight},
            Card{Suit::Hearts, Rank::Ten},
            Card{Suit::Hearts, Rank::Queen},
            Card{Suit::Clubs, Rank::Seven},
            Card{Suit::Hearts, Rank::Four},
            Card{Suit::Diamonds, Rank::Ten},
            Card{Suit::Clubs, Rank::Queen},
            Card{Suit::Hearts, Rank::King},
            Card{Suit::Clubs, Rank::Three},
            Card{Suit::Spades, Rank::Nine},
            Card{Suit::Hearts, Rank::Nine},
            Card{Suit::Diamonds, Rank::Jack},
            Card{Suit::Diamonds, Rank::Six},
            Card{Suit::Diamonds, Rank::Seven},
            Card{Suit::Clubs, Rank::Jack},
            Card{Suit::Clubs, Rank::Ace},
            Card{Suit::Clubs, Rank::Eight},
            Card{Suit::Spades, Rank::Six},
            Card{Suit::Diamonds, Rank::Three},
            Card{Suit::Hearts, Rank::Seven},
            Card{Suit::Diamonds, Rank::Queen},
            Card{Suit::Spades, Rank::King},
            Card{Suit::Hearts, Rank::Jack},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Diamonds, Rank::Four},
            Card{Suit::Diamonds, Rank::Nine},
            Card{Suit::Spades, Rank::Ten},
            Card{Suit::Diamonds, Rank::Ace},
            Card{Suit::Spades, Rank::Two},
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Spades, Rank::Seven}
        };

        CardDeck expected_hand{
            Card{Suit::Clubs, Rank::Ten},
            Card{Suit::Spades, Rank::Seven},
            Card{Suit::Diamonds, Rank::Ace},
            Card{Suit::Spades, Rank::Three},
            Card{Suit::Diamonds, Rank::Queen}
        };

        auto expected_tuple = std::make_tuple(true, size_t(5), expected_hand, CardDeck::create_empty_deck());

        assert_equal(play_optimally(deck), expected_tuple);
    }

    return EXIT_SUCCESS;
}