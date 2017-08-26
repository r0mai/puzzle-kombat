
#include "font.h"

sf::Font font_holder::font = font_holder::init_font();

sf::Font font_holder::init_font() {
	return sf::Font::GetDefaultFont();
}
