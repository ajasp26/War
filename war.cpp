#include "war.h"
#include <iostream>
#include <algorithm>

// Constructor for War which initializes the game and deals cards to each player
War::War(std::default_random_engine &_gen) : gen(_gen), deck(_gen)
{
    // Deal cards alternatively to each player
    std::queue<Card *> *current = &handA;
    while (Card *card = deck.draw())
    {
        current->push(card);
        current = (current == &handA) ? &handB : &handA;
    }
}

std::pair<Card *, Card *> War::placeCards()
{
    // Retireve and remove the top card from each players hand
    Card *cardA = handA.front();
    handA.pop();
    Card *cardB = handB.front();
    handB.pop();

    // Place these cards into the middle pile
    middle.push_back(cardA);
    middle.push_back(cardB);

    return {cardA, cardB};
}

// Collect cards from middle and add to winners hand
void War::collectRound(std::queue<Card *> &winnerHand)
{
    std::shuffle(middle.begin(), middle.end(), gen);
    for (Card *card : middle)
    {
        winnerHand.push(card);
    }
    middle.clear();
}

// Check the win condition after each round
WinState War::checkForWin()
{
    if (handA.empty() && handB.empty())
    {
        std::cout << "Both players are out of cards. It's a tie!" << std::endl;
        return WinState::tie;
    }
    else if (handA.empty())
    {
        std::cout << "Player A is out of cards; player B wins." << std::endl;
        return WinState::winB;
    }
    else if (handB.empty())
    {
        std::cout << "Player B is out of cards; player A wins." << std::endl;
        return WinState::winA;
    }
    return WinState::ongoing;
}

// Update the state of the game based on outcome of a round
void War::updateState(bool cardsMatch)
{
    // War is triggered when cards match
    if (cardsMatch)
    {
        switch (playState)
        {
        case PlayState::normal:
            playState = PlayState::warDown;
            std::cout << "Cards have same value. War!" << std::endl;
            break;
        case PlayState::warDown:
            playState = PlayState::warUp;
            std::cout << "Players playing one card each, face down..." << std::endl;
            break;
        case PlayState::warUp:
            std::cout << "Cards have same value. War continues." << std::endl;
            break;
        }
    }
    else
    {
        playState = PlayState::normal;
    }
}

// Handle a sub-round of War with card comparisons and War scenarios
WinState War::subRound()
{

    // Check if players have enough cards to continue a war
    if (playState != PlayState::normal && (handA.size() < 2 || handB.size() < 2))
    {
        if (handA.size() < 2)
        {
            std::cout << "Player A does not have enough cards for war. Player B wins." << std::endl;
            return WinState::winB;
        }
        else
        {
            std::cout << "Player B does not have enough cards for war. Player A wins." << std::endl;
            return WinState::winA;
        }
    }

    auto [cardA, cardB] = placeCards();
    std::cout << "Player A plays " << cardA->toString() << std::endl;
    std::cout << "Player B plays " << cardB->toString() << std::endl;

    bool cardsMatch = (cardA->rank == cardB->rank);
    if (!cardsMatch)
    {
        std::queue<Card *> &winnerHand = (cardA->rank > cardB->rank) ? handA : handB;
        collectRound(winnerHand);
        std::cout << "Player " << ((cardA->rank > cardB->rank) ? "A" : "B") << " has the higher card and wins the round." << std::endl;
    }

    updateState(cardsMatch);
    return checkForWin();
}

// Conduct a round of War. May include sub-rounds which are
WinState War::playRound()
{
    WinState roundResult = WinState::ongoing;
    do
    {
        roundResult = subRound();
    } while (playState != PlayState::normal && roundResult == WinState::ongoing);

    std::cout << "(Player A has " << handA.size() << " cards; player B has " << handB.size() << " cards.)" << std::endl;
    return roundResult;
}
