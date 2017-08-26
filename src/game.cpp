
#include "game.h"

#include <iostream>
#include <cassert>

#include "rect_into_particles_emitter.h"
#include "random.h"
#include "font.h"

namespace r0 {

using std::cout;
using std::endl;

block::block() : sprite(), color(-1), destroyer(false) {}

block::block(const sf::Sprite& s, int c, bool isdestroyer) : sprite(s), color(c), destroyer(isdestroyer) {}

bool block::isempty() const {
	return color == -1;
}

bool block::isdestroyer() const {
	return destroyer;
}

block block::empty() {
	return block::block();
}

int block::get_block_type_count() {
	return resources::getmax_color();
}

game::game(sf::RenderWindow& win,
		float x,
		float y,
        unsigned long sync_seed) :
        state(GAME),
		window(win),
		well_x_pos(x),
		well_y_pos(y),
		well_width(8),
		well_height(16),
		block_size( win.GetWidth() / float(4*well_width) ),
		falling_speed(1.f*block_size),
		fast_falling_speed(10.f*block_size),
		freefalling_speed(12.f*block_size),
        sync_rng(sync_seed),
		well_content(well_width, well_height),
		fast_falling(false),
		punish_block_count(0),
		caution_str("CAUTION", font_holder::font, block_size),
		dignum_punishblock(2, 0, well_x_pos + 5.5f*block_size, well_y_pos - 2.2f*block_size, block_size, sf::Color(255, 0, 0), sf::Color(30, 30, 30))        

{
	caution_str.SetPosition( well_x_pos + block_size/2, well_y_pos - 2*block_size );
	reset_falling_block();
    init_enviroment();

    break_sound = resources::getinstace().get_breaking_sound();
}

int game::advance(float elpased_time) {

    assert(state == GAME);   

    int destroyed = -1;
    try {
        process_events(elpased_time);
        destroyed = move(elpased_time);
    } catch (const well_full&) {
        //Returns -1
    }
    if (particle_intensity > 0) {
        particle_sys.advance(elpased_time);
    }

	return destroyed;
}

bool game::advance_blow_up(float elpased_time) {
    assert(state == BLOW_UP);

    particle_sys.advance(elpased_time);
    return particle_sys.get_running_list_size() != 0 || particle_sys.get_waiting_queue_size() != 0;
}

//FIXME might make this into two functions
void game::draw() {
    assert(state == GAME);   

    //Draw enviroment (background shadow etc.)
    for(unsigned i = 0; i < enviroment.size(); ++i) {
        window.Draw(enviroment[i]);
    }


    //Draw fix blocks
    std::for_each(well_content.begin(), well_content.end(), [this](const block& b) {
        if (!b.isempty()) {
            window.Draw(b.sprite);
        }
    });    

    //Draw block freefalling
    std::for_each(blocks_freefalling.begin(), blocks_freefalling.end(), [this](const std::pair<int, block>& p) {
        window.Draw(p.second.sprite);
    });    

    //Draw user controlled blocks
    if (!falling_blockBL.isempty()) {
        window.Draw(falling_blockBL.sprite);
    }
    if (!falling_blockTR.isempty()) {
        window.Draw(falling_blockTR.sprite);
    }

    //Draw digital caution number
    dignum_punishblock.draw_number( window, punish_block_count );

    //Draw caution string
    if ( punish_block_count > 0 ) {
        caution_str.SetColor( sf::Color(255, 0, 0) );
    } else {
        caution_str.SetColor( sf::Color(30, 30, 30) );
    }
    window.Draw(caution_str);

    //Draw particles
    if (particle_intensity > 0) {
        particle_sys.draw(window);
    }


}

void game::draw_blow_up() {

    assert(state == BLOW_UP);   

    //Draw enviroment (background shadow etc.)
    for(unsigned i = 0; i < enviroment.size(); ++i) {
        window.Draw(enviroment[i]);
    }

    //Draw digital caution number
    dignum_punishblock.draw_number( window, punish_block_count );

    //Draw caution string
    if ( punish_block_count > 0 ) {
        caution_str.SetColor( sf::Color(255, 0, 0) );
    } else {
        caution_str.SetColor( sf::Color(30, 30, 30) );
    }
    window.Draw(caution_str);

    //Draw particles      
    particle_sys.draw(window);
}

void game::add_punish_blocks(int n) {
	punish_block_count += n;
}

void game::setparticle_intensity(int intensity) {
    if ( intensity <= 0 ) {
        particle_intensity = 0;
    } else {
        particle_intensity = intensity;
    }
}

void game::set_state(state_type new_state) {
    state = new_state;
    switch(state) {
    case BLOW_UP: {
            boost::uniform_real<float> unireal_rng1(-4.f*block_size, 4.f*block_size);
            boost::uniform_real<float> unireal_rng2(-4.f*block_size, -2.f*block_size);

            std::for_each(well_content.begin(), well_content.end(), [&](block& b) {
                if (!b.isempty()) {                
                    particle_sys.add(new particle(
                        unireal_rng1(get_rng()),
                        unireal_rng2(get_rng()),
                        0.f,
                        6.f*block_size,
                        3.f,
                        boost::shared_ptr<sf::Drawable>(new sf::Sprite(b.sprite))));
                    b = block::empty();
                }
            });
            break_sound.Play();
            break;
        }
    case GAME:
        break;
    default:
        break;
    }
}

int game::getblock_height_in_column(int column) const {
	for ( unsigned i = 0; i < well_content.height(); ++i  ) {
		if ( well_content(column, i).isempty() ) {
			return i;
		}
	}
	return well_content.height();
}

const matrix<block>& game::getwell_content() const {
    return well_content;
}

bool game::are_playerblocks_falling() const {
    return player_blocks_falling;
}

bool game::are_playerblocks_vertical() const {
    return falling_block_vertical;
}

const block& game::get_BLplayerblock() const {
    return falling_blockBL;
}

const block& game::get_TRplayerblock() const {
    return falling_blockTR;
}

int game::get_playerblock_column() const {
    return falling_block_column;
}

bool game::isfast_falling_enabled() const {
    return fast_falling;
}

void game::add_event_to_queue(event_type ev) {
	event_queue.push(ev);
}

void game::process_events(float elpased_time) {

	event_type ev;
	while (getevent(ev)) {

		switch(ev) {

        case MOVE_LEFT:
            move_playerblocks_left();
            break;
        case MOVE_RIGHT:
            move_playerblocks_right();
            break;
        case ROTATE:
            rotate_playerblocks();
            break;
        case FAST_DOWN_START:
            fast_falling = true;
            break;
        case FAST_DOWN_STOP:
            fast_falling = false;
            break;
        }
	}
}

int game::move(float elpased_time) { //OPTIMAZIATION

	bool destroy = false;

	if ( player_blocks_falling ) {

		float f_speed = fast_falling ? fast_falling_speed : falling_speed;

		if ( falling_block_vertical ) {
			if ( make_block_fall( falling_blockBL, falling_block_column, elpased_time, f_speed ) ) {
				int well_height_column = getblock_height_in_column( falling_block_column );
				falling_blockTR.sprite.SetPosition( falling_blockTR.sprite.GetPosition().x, well_y_pos + well_height * block_size - block_size * well_height_column - block_size );
				put_block_into_well(falling_block_column, well_height_column, falling_blockTR);
				falling_blockTR = block::empty();
				destroy = true;
			} else {
				make_block_fall( falling_blockTR, falling_block_column, elpased_time, f_speed );
			}
		} else { //!falling_block_vertical

			int left_well_height = getblock_height_in_column( falling_block_column );
			int right_well_height = getblock_height_in_column( falling_block_column+1 );
            
			if ( left_well_height == right_well_height ) {
				if ( make_block_fall( falling_blockBL, falling_block_column, elpased_time, f_speed ) ) {

					falling_blockTR.sprite.SetPosition( falling_blockTR.sprite.GetPosition().x, well_y_pos + well_height * block_size - block_size * right_well_height - block_size );
					put_block_into_well(falling_block_column+1, right_well_height, falling_blockTR);

					falling_blockTR = block::empty();
					destroy = true;
				} else {
					make_block_fall( falling_blockTR, falling_block_column, elpased_time, f_speed );
				}
			} else if ( left_well_height > right_well_height ) {
				if ( make_block_fall( falling_blockBL, falling_block_column, elpased_time, f_speed ) ) {
					blocks_freefalling.push_back( std::make_pair(falling_block_column+1, falling_blockTR) );
					falling_blockTR = block::empty();
					player_blocks_falling = false;
				} else {
					make_block_fall( falling_blockTR, falling_block_column+1, elpased_time, f_speed );
				}

			} else { /*left_well_height > right_well_height*/
				if ( make_block_fall( falling_blockTR, falling_block_column+1, elpased_time, f_speed ) ) {
					blocks_freefalling.push_back( std::make_pair(falling_block_column, falling_blockBL) );
					falling_blockBL = block::empty();
					player_blocks_falling = false;
				} else {
					make_block_fall( falling_blockBL, falling_block_column, elpased_time, f_speed );
				}
			}

		}

	} else {
		if (do_free_fall(elpased_time, freefalling_speed)) {
			destroy = true;
		}
	}

	if ( destroy ) {
		int destroyed = do_destroy();
		if (destroyed == 0) {

			if ( punish_block_count > 0 ) {
                put_punish_blocks_into_well();
			} else {
				reset_falling_block();
			}

		} else {
			player_blocks_falling = false;
			return destroyed;
		}
	}


	return 0;

}

bool game::getevent(event_type& ev) {
	if ( event_queue.empty() ) {
		return false;
	} else {
		ev = event_queue.front();
		event_queue.pop();
		return true;
	}
}

void game::move_playerblocks_right() {   

    if ( player_blocks_falling ) {      

        int column_in_way =
            falling_block_vertical ?
            falling_block_column+1 :
            falling_block_column+2;

        bool can_move = column_in_way < well_width;

        if ( can_move ) { //check if there is something else there
            int block_height_indestcol = getblock_height_in_column(column_in_way);
            if ( well_y_pos + block_size * (well_height-block_height_indestcol) > falling_blockBL.sprite.GetPosition().y + block_size ) {
                ++falling_block_column;
                falling_blockBL.sprite.Move(block_size, 0.f);
                falling_blockTR.sprite.Move(block_size, 0.f);
            }
        }
    }
}

void game::move_playerblocks_left() {


    if ( player_blocks_falling ) {

        int column_in_way = falling_block_column-1;

        bool can_move = column_in_way >= 0;
        if ( can_move ) { //check if there is something else there
            int block_height_indestcol = getblock_height_in_column(column_in_way);
            if ( well_y_pos + block_size * (well_height-block_height_indestcol) > falling_blockBL.sprite.GetPosition().y + block_size ) {
                --falling_block_column;
                falling_blockBL.sprite.Move(-1.f*block_size, 0.f);
                falling_blockTR.sprite.Move(-1.f*block_size, 0.f);
            }
        }
    }
}

void game::rotate_playerblocks() {
    if ( player_blocks_falling ) {
        if ( falling_block_vertical ) { 

            if ( falling_block_column+1 >= well_width || //at side
                well_y_pos + block_size * (well_height-getblock_height_in_column( falling_block_column+1))
                <= falling_blockBL.sprite.GetPosition().y + block_size ) { //middle obstacle
                //BUT don't have obstacles from both directions
                if ( falling_block_column != 0 &&
                    well_y_pos + block_size * (well_height-getblock_height_in_column( falling_block_column-1 ))
                    > falling_blockBL.sprite.GetPosition().y + block_size ) {

                    falling_blockTR.sprite.Move( 0, block_size );
                    falling_blockBL.sprite.Move( -1.f*block_size, 0 );
                    --falling_block_column;
                    falling_block_vertical = false;
                }
            } else {
                falling_blockTR.sprite.Move( block_size, block_size );
                falling_block_vertical = false;
            }
            
        } else {
            falling_blockBL.sprite.Move( 0, -1.f*block_size );
            falling_blockTR.sprite.Move( -1.f*block_size, 0 );
            std::swap(falling_blockBL, falling_blockTR);
            falling_block_vertical = true;
        }
    }
    return;

}

void game::reset_falling_block() {

    boost::variate_generator<boost::rand48&, boost::uniform_smallint<> > rand_gen( sync_rng, boost::uniform_smallint<>(1, block::get_block_type_count()-1) );             

    bool black = sync_rng() / static_cast<float>(sync_rng.max()) < 0.05f;

    if ( black ) {
        falling_blockTR = getblock_for_color(0, true, well_x_pos + (well_width/2) * block_size, well_y_pos);
    } else {
        falling_blockTR = getblock_for_color(rand_gen(), (sync_rng() / static_cast<float>(sync_rng.max()) < 0.2f), well_x_pos + (well_width/2) * block_size, well_y_pos);
    }
    black = sync_rng() / static_cast<float>(sync_rng.max()) < 0.05f;
    if ( black ) {
        falling_blockBL = getblock_for_color(0, true, well_x_pos + (well_width/2) * block_size, well_y_pos + block_size);
    } else {
        falling_blockBL = getblock_for_color(rand_gen(), (sync_rng() / static_cast<float>(sync_rng.max()) < 0.2f), well_x_pos + (well_width/2) * block_size, well_y_pos + block_size);
    }
    player_blocks_falling = true;
    falling_block_column = (well_width/2);
    falling_block_vertical = true;
}

bool game::make_block_fall(block& b, int column, float elpased_time, float speed) {
	float new_pos = b.sprite.GetPosition().y + elpased_time*speed;

	int well_height_in_column = getblock_height_in_column(column);
	float pixheight_in_column = well_y_pos + well_height * block_size - block_size * well_height_in_column;

	if ( new_pos >= pixheight_in_column-block_size ) {

		b.sprite.SetPosition( b.sprite.GetPosition().x, pixheight_in_column-block_size );
		put_block_into_well( column, well_height_in_column, b);
		b = block::empty();

		return true;
	} else {

		b.sprite.SetPosition( b.sprite.GetPosition().x, new_pos );
		return false;
	}
}

bool game::do_free_fall(float elpased_time, float speed) {
	
	bool res = true;

	for( auto it = blocks_freefalling.begin(); it != blocks_freefalling.end(); ) {
		if ( make_block_fall(it->second, it->first, elpased_time, speed) ) {
			blocks_freefalling.erase( it++ );
		} else {
			++it;
			res = false;
		}
	}
	return res;
}

void game::put_block_into_well( int x, int y, const block& b ) {
	if ( y >= well_height ) {
		throw well_full();
	}
	well_content(x, y) = b;
}

void game::put_punish_blocks_into_well() {
    std::vector<int> punish_block_height(well_width);
    std::vector<int> well_heights(well_width);
    for(int i = 0; i < well_width; ++i) {
        well_heights[i] = getblock_height_in_column(i);
    }

    boost::uniform_int<> block_rng(1, block::get_block_type_count()-1);

    while( punish_block_count > 0 ) {
        std::list<int> lowest_columns;
        int lowest = *std::min_element(well_heights.begin(), well_heights.end());
        for(int i = 0; i < well_width; ++i) {
            if ( well_heights[i] == lowest ) {
                lowest_columns.push_back(i);
            }
        } 

        if ( lowest_columns.size() < static_cast<unsigned>(punish_block_count) ) { //static_cast to silnet compiler warning
            for(std::list<int>::iterator it = lowest_columns.begin(); it != lowest_columns.end(); ++it) {
                 block b = getblock_for_color(
                     block_rng(get_rng()),
                     false,
                     well_x_pos + (*it) * block_size,
                     well_y_pos - punish_block_height[*it] * block_size);
                 blocks_freefalling.push_back(std::make_pair(*it, b));
                 ++punish_block_height[*it];
                 ++well_heights[*it];
            }
            punish_block_count -= lowest_columns.size();
        } else {
            for( ; punish_block_count > 0; --punish_block_count ) {

                const int col = boost::uniform_int<>(0, lowest_columns.size()-1)(get_rng());

                std::list<int>::iterator it = lowest_columns.begin();
                std::advance(it, col);

                block b = getblock_for_color(
                     block_rng(get_rng()),
                     false,
                     well_x_pos + (*it) * block_size,
                     well_y_pos - punish_block_height[*it] * block_size);

                blocks_freefalling.push_back(std::make_pair(*it, b));
                ++punish_block_height[*it];
                ++well_heights[*it];

                lowest_columns.erase(it);
            }
        }
    }
    punish_block_count = 0;
    player_blocks_falling = false;
}

int game::do_destroy() {

	int res = 0;

	for( int y = 0; y < well_height; ++y ) {
		for( int x = 0; x < well_width; ++x ) {
			if ( well_content(x, y).isdestroyer() ) {
				if ( well_content(x, y).color == 0 ) { //BLACK (0==BLACK)
					//remove all colors which are under the black piece,
					//if nothing is under it, remove all colors which are
					//over black, leave alone otherwise
					int color = -1;
					if ( y > 0 ) {
						color = well_content(x, y-1).color;
					} else if ( y < well_height-1 && !well_content(x, y+1).isempty() ) {
						color = well_content(x, y+1).color;
					}

                    if ( color == 0 ) { //Black fell onto black (0==BLACK)
                        res += remove_color(color);
                    } else if ( color != -1 ) {
						res += remove_color(color) + 1; //Remove all block from color 'color'
                        remove_block(x, y); //Remove the black itself
					}
				} else {
					//Only destroy the group if it has another block of the same color next to it
					std::vector<positioni> neighbours = get_neighbours(x, y);
					
					for( auto it = neighbours.begin(); it != neighbours.end(); ++it ) {
						if ( well_content(it->x, it->y).color ==  well_content(x, y).color ) {
							res += remove_group(positioni(x,y));
							break;
						}
					}
				}
			}
		}
	}
	if ( res > 0 ) {
		for( int x = 0; x < well_width; ++x ) {
			bool on_ground = true;
			for( int y = 0; y < well_height; ++y ) {
				if( on_ground ) {
					if ( well_content(x, y).isempty() ) {
						on_ground = false;
					}
				} else {
					if ( !well_content(x, y).isempty() ) {
						blocks_freefalling.push_back( std::make_pair(x, well_content(x, y)) );
                        well_content(x, y) = block::empty();
					}
				}
			}
		}
	}

	return res;
}

std::vector<positioni> game::get_neighbours( const positioni& p ) {
	std::vector<positioni> res;
	res.reserve(4);
	if ( p.x > 0 ) {
		res.push_back( positioni(p.x-1, p.y) );
	}
	if ( p.x < well_width-1 ) {
		res.push_back( positioni(p.x+1, p.y) );
	}
	if ( p.y > 0 ) {
		res.push_back( positioni(p.x, p.y-1) );
	}
	if ( p.y < well_height-1 ) {
		res.push_back( positioni(p.x, p.y+1) );
	}
	return res;
}

std::vector<positioni> game::get_neighbours( int x, int y ) {
	return get_neighbours( positioni(x,y) );
}

int game::remove_group( const positioni& p ) {

	const int color = well_content(p.x, p.y).color;
	int res = 0;

	std::list<positioni> to_check_queue;
	to_check_queue.push_back(p);
	++res;
    remove_block(p.x, p.y);

	while( !to_check_queue.empty() ) {
		std::vector<positioni> neighbours = get_neighbours(to_check_queue.front());
		to_check_queue.pop_front();
        		
		for( auto it = neighbours.begin(); it != neighbours.end(); ++it ) {
			if ( well_content(it->x, it->y).color == color ) {
				to_check_queue.push_back(*it);
				++res;
				remove_block(it->x, it->y);
			}
		}
	}
	return res;
}

int game::remove_color( int color ) {
	int res = 0;
	for(int y = 0; y < well_height; ++y) {
		for(int x= 0; x < well_width; ++x) {
			if ( well_content(x, y).color == color ) {
				++res;
				remove_block(x, y);
			}
		}
	}
	return res;
}

void game::remove_block( int x, int y ) {
    if (particle_intensity > 0) {

        const int x_break = particle_intensity;
        const int y_break = particle_intensity;
        const sf::Color color = resources::getinstace().get_color(well_content(x, y).color);

        rect_into_particles_emitter emitter(
            well_x_pos + x*block_size,
            well_y_pos + (well_height - y - 1)*block_size,
            block_size,
            block_size,
            x_break, y_break,
            color
        );
        
        particle_sys.generate_particles(
            x_break * y_break,
            emitter,
            -3.f*block_size, 3*block_size,
            -3.f*block_size, 3*block_size,
            0.f, 0.f,
            block_size, block_size,
            .5f, 1.f,
            block_size / x_break,
            block_size / y_break,
            color
        );
    }
    if ( break_sound.GetStatus() != sf::Sound::Playing ) {
        break_sound.Play();
    }
    well_content(x, y) = block::empty();
}

void game::init_enviroment() {    
    sf::Shape *well_background = new sf::Shape(sf::Shape::Rectangle(well_x_pos, well_y_pos, well_x_pos+well_width*block_size, well_y_pos+well_height*block_size, sf::Color(0, 0, 0, 200)));
    enviroment.push_back(well_background);
}

block game::getblock_for_color(int color, bool isdestroyer, float x_pos, float y_pos) {
	if ( isdestroyer ) {
		return block( resources::getinstace().get_destroyer_block_sprite(color, block_size, block_size, x_pos, y_pos), color, isdestroyer );
	} else {
		return block( resources::getinstace().get_normal_block_sprite(color, block_size, block_size, x_pos, y_pos), color, isdestroyer );
	}
}

} //namespace r0

