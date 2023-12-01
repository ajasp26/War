#include "war.h"
#include <iostream>
#include <random>
#include <chrono>

int main()
{
    // Use current epoch time to create a unique time seed.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto gen = std::default_random_engine{seed};

    // Create a War game instance with random number generator
    auto war = War{gen};

    auto ws = WinState::ongoing;
    int countRounds = 0;
    while (ws == WinState::ongoing)
    {
        ws = war.playRound();
        ++countRounds;
    }

    // Total number of rounds played once the game ends.
    std::cout << countRounds << " rounds total." << std::endl;

    return 0;
}