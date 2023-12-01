#include "deck.h"
#include <algorithm>

// Intialize the deck of 52 playing cards
Deck::Deck(std::default_random_engine &_gen) : gen(_gen)
{
    static const std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    for (const auto &suit : suits)
    {
        for (int rank = 1; rank <= 13; ++rank)
        {
            cards.push_back(new Card(suit, rank));
        }
    }
    shuffle();
}

// Delete all allocated card objects in the deck.
Deck::~Deck()
{
    for (auto &card : cards)
    {
        delete card;
    }
}

// Random number generator to shuffle cards
void Deck::shuffle()
{
    std::shuffle(cards.begin(), cards.end(), gen);
}

// Draw a card from the top of the deck
Card *Deck::draw()
{
    if (cards.empty())
    {
        return nullptr;
    }
    Card *card = cards.back();
    cards.pop_back();
    return card;
}
