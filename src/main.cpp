#include <stdexcept>
#include "game.hpp"


int main() {

    try {

        Game game;
        game.run();

    } catch (std::exception& e) {

        fprintf(stderr, "%s\n", e.what());

    }

}
