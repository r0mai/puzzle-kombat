
#include "digital_number.h"

#include <iostream>

namespace r0 {

digital_number::digital_number() {}

digital_number::digital_number(
		int digits,
		int number,
		float x,
		float y,
		float w,
		const sf::Color& active_color,
		const sf::Color& inactive_color )
: number(number), digit_count(digits), digit_scale_need_update(true), x_pos(x), y_pos(y), width(w), active_color(active_color), inactive_color(inactive_color),
piece(digit_count), standby_step(0)
{}

void digital_number::setposition(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void digital_number::setsize(float w) {
	width = w;
	digit_scale_need_update = true;
}

void digital_number::setactive_color(const sf::Color& acolor) {
    active_color = acolor;
}

void digital_number::setinactive_color(const sf::Color& incolor) {
    inactive_color = incolor;
}

void digital_number::redraw_digits() {

	for(int i = 0; i < digit_count; ++i) {

		boost::array<sf::Shape, 7> digit_pieces;

		for(unsigned j = 0; j < 7; ++j) {
			digit_pieces[j] = sf::Shape();
			digit_pieces[j].EnableOutline(false);
			digit_pieces[j].SetPosition(x_pos + i*(width + width/6.f), y_pos);
		}

		digit_pieces[0].AddPoint( width/12.f, 			 0.f );
		digit_pieces[0].AddPoint( width - width/12.f, 	 0.f );
		digit_pieces[0].AddPoint( width - 3.f*width/12.f, width / 6.f );
		digit_pieces[0].AddPoint( 3.f*width/12.f, 		 width / 6.f );

		digit_pieces[1].AddPoint( 0.f, 					 width / 12.f );
		digit_pieces[1].AddPoint( 0.f, 	 				 width - width / 12.f );
		digit_pieces[1].AddPoint( width/6.f,			 	 width - 3.f*width / 12.f);
		digit_pieces[1].AddPoint( width/6.f, 		 	 3.f*width / 12.f);

		digit_pieces[2].AddPoint( width, 				 width / 12.f );
		digit_pieces[2].AddPoint( width, 	 			 width - width / 12.f );
		digit_pieces[2].AddPoint( width - width/6.f,		 width - 3.f*width / 12.f);
		digit_pieces[2].AddPoint( width - width/6.f, 	 3.f*width / 12.f);

		digit_pieces[3].AddPoint( width / 12.f, 			 width );
		digit_pieces[3].AddPoint( width / 6.f, 	 		 width - width / 12.f );
		digit_pieces[3].AddPoint( width - width / 6.f,	 width - width / 12.f );
		digit_pieces[3].AddPoint( width - width / 12.f, 	 width);
		digit_pieces[3].AddPoint( width - width / 6.f, 	 width + width / 12.f );
		digit_pieces[3].AddPoint( width / 6.f,	 width + width / 12.f );

		digit_pieces[4].AddPoint( 0.f, 					 width + width / 12.f );
		digit_pieces[4].AddPoint( 0.f, 	 				 width + width - width / 12.f );
		digit_pieces[4].AddPoint( width/6.f,			 	 width + width - 3.f*width / 12.f);
		digit_pieces[4].AddPoint( width/6.f, 		 	 width + 3.f*width / 12.f);

		digit_pieces[5].AddPoint( width, 				 width + width / 12.f );
		digit_pieces[5].AddPoint( width, 	 			 width + width - width / 12.f );
		digit_pieces[5].AddPoint( width - width/6.f,		 width + width - 3.f*width / 12.f);
		digit_pieces[5].AddPoint( width - width/6.f, 	 width + 3.f*width / 12.f);

		digit_pieces[6].AddPoint( width/12.f, 			 2.f*width );
		digit_pieces[6].AddPoint( width - width/12.f, 	 2.f*width );
		digit_pieces[6].AddPoint( width - 3.f*width/12.f, 2.f*width - width / 6.f );
		digit_pieces[6].AddPoint( 3.f*width/12.f, 		 2.f*width - width / 6.f );

		piece[i] = digit_pieces;
	}
	digit_scale_need_update = false;
}

void digital_number::draw_number(sf::RenderTarget& target, int number) {
	if ( digit_scale_need_update ) {
		redraw_digits();
	}

	static const bool visible_digit_pieces[10][7] = {
			{true,  true,   true,   false,  true,   true,   true},
			{false, false,  true,   false,  false,  true,   false},
			{true,  false,  true,   true,   true,   false,  true},
			{true,  false,  true,   true,   false,  true,   true},
			{false, true,   true,   true,   false,  true,   false},
			{true,  true,   false,  true,   false,  true,   true},
			{true,  true,   false,  true,   true,   true,   true},
			{true,  false,  true,   false,  false,  true,   false},
			{true,  true,   true,   true,   true,   true,   true},
			{true,  true,   true,   true,   false,  true,   true},
	};

	std::vector<int> digits(digit_count);
	int tmpnumber = number;

	for( int i = digit_count-1; i >= 0; --i, tmpnumber /= 10 ) {
		digits[i] = tmpnumber%10;
	}



	bool have_drawn = false;
	for( int i = 0; i < digit_count; ++i ) {

		if( digits[i] == 0 && !have_drawn ) {
			for( int j = 0; j < 7; ++j ) {
				piece[i][j].SetColor(inactive_color);
				target.Draw(piece[i][j]);
			}
		} else {
			have_drawn = true;
			for( int j = 0; j < 7; ++j ) {
				if ( visible_digit_pieces[digits[i]][j] ) {
					piece[i][j].SetColor(active_color);
				} else {
					piece[i][j].SetColor(inactive_color);
				}
				target.Draw(piece[i][j]);
			}
		}
	}
}

void digital_number::draw_standby(sf::RenderTarget& target) {
    if ( digit_scale_need_update ) {
		redraw_digits();
	}

    for( int i = 0; i < digit_count; ++i ) {
        for( int j = 0; j < 7; ++j ) {
            piece[i][j].SetColor(inactive_color);
        }
    }
    
    if ( standby_step < digit_count ) {
        piece[standby_step][0].SetColor(active_color);
    } else if ( standby_step == digit_count ) {
        piece[digit_count-1][2].SetColor(active_color);
    } else if ( standby_step == digit_count+1 ) {
        piece[digit_count-1][5].SetColor(active_color);
    } else if ( standby_step == 2*digit_count+2 ) {
        piece[0][4].SetColor(active_color);
    } else if ( standby_step == 2*digit_count+3 ) {
        piece[0][1].SetColor(active_color);
    } else {
        piece[digit_count - (standby_step-(digit_count+1))][6].SetColor(active_color);
    }
    for( int i = 0; i < digit_count; ++i ) {
        for( int j = 0; j < 7; ++j ) {
            target.Draw(piece[i][j]);
        }
    }
}

void digital_number::next_standby_step() {
    ++standby_step;
    standby_step %= 2*digit_count+4;
}

} //namespace r0
