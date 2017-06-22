#include <stdexcept>
#include <game.hpp>
#include <error/snkexception.hpp>


int main() {

    try {

        snk::Game game;
        game.setTitle("Game");
        game.run();

    } catch (snk::SnakeException& e) {

        fprintf(stderr, "%s\n", e.what());

    }

}
