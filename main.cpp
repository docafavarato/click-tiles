#include "Game.h"
#include "menu.h"
#include <iostream>

int main() {
    // Init srandom
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game engine
    Menu menu;

    // Game loop
    while (menu.running()) {

        // Update
        menu.update();

        // Render
        menu.render();

    }

    return 0;
}

