
#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <boost/array.hpp>

#include <vector>

namespace r0 {

class resources {
public:
	static resources& getinstace();

	sf::Sprite get_normal_block_sprite(int color, float width,float height, float x_pos = 0.f, float y_pos = 0.f) const;
	sf::Sprite get_destroyer_block_sprite(int color, float width, float height, float x_pos = 0.f, float y_pos = 0.f) const;

	sf::Sprite get_image_as_sprite(int index, float width, float height, float x_pos = 0.f, float y_pos = 0.f) const;
    sf::Color get_color(int index) const;

    sf::Sound get_breaking_sound() const;

	static int getmax_color();
private:
	resources();
    //image
    static const int max_color = 5;
    boost::array<sf::Color, max_color> colors;
	std::vector<sf::Image> images;
    //audio
    sf::SoundBuffer break_sound_buf;
};

} //namespace r0

#endif //RESOURCES_H_
