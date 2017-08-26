
#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <ctime>

#include <SFML/Graphics.hpp>

#include "game.h"
#include "background_animation.h"
#include "program_options.h"

namespace r0 {

int start_game(int argc, char **argv);

class game_manager {
public:
    game_manager(unsigned long rngseed = static_cast<unsigned long>(time(0)));
    int run();

private:    
    void end_game(bool left_won);

    program_options options;

    sf::RenderWindow window;

    background_animation background;

    game game_left;
    game game_right;
};

} //namespace r0

#endif