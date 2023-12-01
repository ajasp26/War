#ifndef WAR_H
#define WAR_H

#include "deck.h"
#include <queue>
#include <vector>
#include <utility>

enum class WinState
{
    winA,
    winB,
    tie,
    ongoing
};
enum class PlayState
{
    normal,
    warDown,
    warUp
};

class War
{
private:
    std::default_random_engine &gen;
    Deck deck;
    std::queue<Card *> handA, handB;
    std::vector<Card *> middle;
    PlayState playState;

    std::pair<Card *, Card *> placeCards();
    void collectRound(std::queue<Card *> &to);
    WinState checkForWin();
    void updateState(bool cardsMatch);
    WinState subRound();

public:
    // Intialize the War game
    War(std::default_random_engine &_gen);

    // Conduct a round of War
    WinState playRound();
};

#endif // WAR_H
