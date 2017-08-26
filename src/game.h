
#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <vector>
#include <queue>
#include <utility>

#include <boost/random.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "resources.h"
#include "position.h"
#include "digital_number.h"
#include "particle_system.h"
#include "particle_system.h"

#define SAFE_MATRIX
#include "matrix.h"


namespace r0 {

struct block {

	block(); /*Constructs a default (empty) block (== block::empty())*/
	block(const sf::Sprite& s, int color, bool isdestroyer);

	sf::Sprite sprite;
	int color;
	bool destroyer;

	bool isempty() const;
	bool isdestroyer() const;
	static block empty();
	static int get_block_type_count();

};

class game {
public:
    
    //Custom event type for game
    enum event_type { MOVE_LEFT, MOVE_RIGHT, ROTATE, FAST_DOWN_START, FAST_DOWN_STOP };
    enum state_type { GAME, BLOW_UP };

	game(
		sf::RenderWindow& win,
		float well_x_pos,
		float well_y_pos,
        unsigned long sync_seed
	);

	/*
	 * Returns =<0 if it successes (num of destroyed block)
	 * Returns -1 on failure
	 */
	int advance(float elpased_time);
    /*
     * Returns false when there is nothing more to animate
     */
    bool advance_blow_up(float elpased_time);

	void draw();    
    void draw_blow_up();

	/*
	 * increments caution number (I should know from this)
	 */
	void add_punish_blocks(int n);
    
    /* 
     * Options
     */
    void setparticle_intensity(int intensity);
    
    /*
     * Effects (these may cause the object to lose it's state, and be unable to restore the game state after call)
     */
    void set_state(state_type new_state);

    /*For AI*/
	int getblock_height_in_column(int column) const;
    const matrix<block>& getwell_content() const;
    bool are_playerblocks_falling() const;
    bool are_playerblocks_vertical() const; //Returns true, if playerblocks are falling vertically
    const block& get_BLplayerblock() const;
    const block& get_TRplayerblock() const;
    int get_playerblock_column() const;
    bool isfast_falling_enabled() const;

	void add_event_to_queue(event_type ev);

private:

	void process_events(float elpased_time);
	int move(float elpased_time);
	bool getevent(event_type& ev);

    void move_playerblocks_right();
    void move_playerblocks_left();
    void rotate_playerblocks();

	void reset_falling_block();
	bool make_block_fall(block& b, int column, float elpased_time, float speed); //Returns true, when block hit ground
	bool do_free_fall(float elpased_time, float speed); //Returns true, when all blocks (var blocks_freefalling) fell
	void put_block_into_well( int x, int y, const block& b ); //throws game::well_full() if blocks are out of bound
    void put_punish_blocks_into_well();

	int do_destroy();
	std::vector<positioni> get_neighbours( const positioni& p );
	std::vector<positioni> get_neighbours( int x, int y );
	int remove_group( const positioni& p );
	int remove_color( int color );
    void remove_block( int x, int y ); //Removes the block, also adds effects

    void init_enviroment();

	block getblock_for_color(int color, bool isdestroyer, float x_pos, float y_pos);

	/**/
	class well_full {};

    state_type state;

	sf::RenderWindow& window;
	std::queue<event_type> event_queue;
    
	/*Private Constants*/
	float well_x_pos;
	float well_y_pos;
	int well_width;
	int well_height;
	float block_size; /*Width and Height*/
	float falling_speed;
	float fast_falling_speed;
	float freefalling_speed;

    /*Options*/
    int particle_intensity;

    boost::rand48 sync_rng; //ONLY used in resetblocks (so for player controlled falling pieces)    
    //Other random operations are done by the global get_rng() generator

	matrix<block> well_content;

	/*Falling blocks*/
	block falling_blockBL; //BOTTOM or LEFT block
	block falling_blockTR; //TOP or RIGHT block
	bool falling_block_vertical; //if false, then it's horizontal
	int falling_block_column; //if !fallin_block_vertical, then falling_block_column is the position of falling_blockTR,
	bool fast_falling; //true when DOWN is pressed

    //pair<column, block>
	std::list< std::pair<int, block> > blocks_freefalling;

	int punish_block_count;

    //true when user controlled blocks are falling
	bool player_blocks_falling;

    //Enviroment
	sf::String caution_str;
	digital_number dignum_punishblock;
    boost::ptr_vector<sf::Drawable> enviroment; //See init_enviroment()
    particle_system particle_sys;

    //Audio
    sf::Sound break_sound;

};

} //namespace r0

#endif /* GAME_H_ */
