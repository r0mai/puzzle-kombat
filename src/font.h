
#ifndef FONT_H_
#define FONT_H_

#include <SFML\Graphics.hpp>

struct font_holder {

    static sf::Font font;

private:
    static sf::Font init_font();
};

#endif //FONT_H_