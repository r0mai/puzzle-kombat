
#ifndef DIGITAL_NUMBER_H_
#define DIGITAL_NUMBER_H_

#include "matrix.h"
#include <SFML/Graphics.hpp>
#include <boost/array.hpp>

namespace r0 {

class digital_number {
public:

	digital_number();
	digital_number(int digits, int number, float x, float y, float w, const sf::Color& active_color = sf::Color(255, 255, 255), const sf::Color& inactive_color = sf::Color(0, 0, 0) );

	void setposition(float x, float y);
	void setsize(float w);
    void setactive_color(const sf::Color& acolor);
    void setinactive_color(const sf::Color& incolor);

	void draw_number(sf::RenderTarget& target, int number);

    void draw_standby(sf::RenderTarget& target);
    void next_standby_step();
private:

    void redraw_digits();

	/*  __ 0
	 * |  |1,2
	 * |  |
	 *  -- 3
	 * |  |4,5
	 * |__|6
	 */
    

	int number;
	int digit_count;
	bool digit_scale_need_update; //on resize
	float x_pos, y_pos;
	float width; //height is implicit
	sf::Color active_color;
	sf::Color inactive_color;
    int standby_step;

    //One vector element for every digit
    std::vector< boost::array<sf::Shape, 7> > piece;
};

} //namespace r0

#endif /* DIGITAL_NUMBER_H_ */
