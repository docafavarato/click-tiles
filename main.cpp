#include "Game.h"
#include <iostream>

int main() {
    // Init srandom
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game engine
    Game game;

    // Game loop
    while (game.running()) {

        // Update
        game.update();

        // Render
        game.render();

    }

    return 0;
}