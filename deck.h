#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <random>

// Deck of playing cards
class Deck
{
private:
    std::vector<Card *> cards;
    std::default_random_engine &gen;

public:
    // Constructor for intializing a full deck of cards
    Deck(std::default_random_engine &_gen);

    // Destructor for cleaning up card objects
    ~Deck();

    // Shuffle cards
    void shuffle();

    Card *draw();
};

#endif // DECK_H
