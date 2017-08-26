
#include "resources.h"

namespace r0 {

resources& resources::getinstace() {
	static resources ims;
	return ims;
}

sf::Sprite resources::get_normal_block_sprite(int color, float width, float height, float x_pos, float y_pos) const {
	return get_image_as_sprite( color, width, height, x_pos, y_pos);
}

sf::Sprite resources::get_destroyer_block_sprite(int color, float width, float height, float x_pos, float y_pos) const {
	return get_image_as_sprite( getmax_color() + color, width, height, x_pos, y_pos);
}

sf::Sprite resources::get_image_as_sprite(int index, float width, float height, float x_pos, float y_pos) const {

	sf::Sprite s(images[index]);
	s.SetPosition(x_pos, y_pos);
	s.Resize( width, height );

	return s;
}

sf::Color resources::get_color(int index) const {
    return colors[index];
}

sf::Sound resources::get_breaking_sound() const {
    return sf::Sound(break_sound_buf);
}

int resources::getmax_color() {
	return max_color;
}

resources::resources() : images(2*getmax_color()) {

	const int image_size = 32;

    colors[0] = sf::Color(0, 0, 0);
    colors[1] = sf::Color(0, 255, 0);
    colors[2] = sf::Color(0, 0, 255);
    colors[3] = sf::Color(255, 255, 0);
    colors[4] = sf::Color(255, 0, 0);
    

	//nomral
	images[0] = sf::Image(image_size, image_size, colors[0]);
	images[1] = sf::Image(image_size, image_size, colors[1]);
	images[2] = sf::Image(image_size, image_size, colors[2]);
	images[3] = sf::Image(image_size, image_size, colors[3]);
	images[4] = sf::Image(image_size, image_size, colors[4]);

	//destroyer
	images[5] = sf::Image(image_size, image_size, colors[0]);
	images[6] = sf::Image(image_size, image_size, colors[1]);
	images[7] = sf::Image(image_size, image_size, colors[2]);
	images[8] = sf::Image(image_size, image_size, colors[3]);
	images[9] = sf::Image(image_size, image_size, colors[4]);

	for(int i = getmax_color(); i < 2*getmax_color(); ++i) {
		for(unsigned y = 0; y < image_size/2; ++y) {
			for(unsigned x = 0; x < image_size/2; ++x) {
				images[i].SetPixel(x+image_size/4, y+image_size/4, sf::Color(70, 70, 70));
			}
		}
	}

    break_sound_buf.LoadFromFile("break_sound.wav");

}

} //namespace r0
