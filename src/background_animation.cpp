
#include "background_animation.h"

namespace r0 {

background_animation::background_animation() {}

void background_animation::advance(float elpased_time) {

}

void background_animation::draw(sf::RenderWindow& window) {
    sf::Shape r = sf::Shape::Rectangle(0.f, 0.f, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()), sf::Color(0, 70, 20)); 

	window.Clear(sf::Color(0, 70, 20));
}

} //namespace r0