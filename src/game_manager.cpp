
#include "game_manager.h"

#include <iostream>
#include <string>

#include "random.h"
#include "font.h"
#include "digital_number.h"

namespace r0 {

/*
 * Used program options 
 * <option name>=<default value>
 * 
 * resolution_width=640
 * resolution_height=480
 * particle_intensity=10
 */

int start_game(int argc, char **argv) {
    game_manager gm;
    return gm.run();
}



game_manager::game_manager(unsigned long rngseed) :
    options("config.cfg"),
    window(sf::VideoMode(options.get<unsigned>("resolution_width", 640), options.get<unsigned>("resolution_height", 480), 32), "Puzzle Combat"),
    game_left(window, window.GetWidth() / 8.f, 100.f, rngseed),
    game_right(window, 5 * window.GetWidth() / 8.f, 100.f, rngseed)
{    
    window.EnableKeyRepeat(false);
    
    seed_rng(rngseed ^ 0x123);

    const int particle_intensity = options.get<int>("particle_intensity", 10);
    game_left.setparticle_intensity(particle_intensity);
    game_right.setparticle_intensity(particle_intensity);
}

int game_manager::run() {
    digital_number frame_rate_dnumber(4, 0, 66.f, 10.f, 12.f, sf::Color(0, 255, 0), sf::Color(30, 30, 30));

    float frame_rate_timer = 0.f;
    int frame_count = 0;
    int frame_rate = 0;

    while(window.IsOpened()) {

        float elpased_time = window.GetFrameTime();

        sf::Event ev;
        while(window.GetEvent(ev)) {
            switch (ev.Type) {
            case sf::Event::KeyPressed:
                switch(ev.Key.Code) {
                case sf::Key::W: game_left.add_event_to_queue(r0::game::ROTATE); break;
                case sf::Key::S: game_left.add_event_to_queue(r0::game::FAST_DOWN_START); break;
                case sf::Key::A: game_left.add_event_to_queue(r0::game::MOVE_LEFT); break;
                case sf::Key::D: game_left.add_event_to_queue(r0::game::MOVE_RIGHT); break;

                case sf::Key::Up: game_right.add_event_to_queue(r0::game::ROTATE); break;
                case sf::Key::Down: game_right.add_event_to_queue(r0::game::FAST_DOWN_START); break;
                case sf::Key::Left: game_right.add_event_to_queue(r0::game::MOVE_LEFT); break;
                case sf::Key::Right: game_right.add_event_to_queue(r0::game::MOVE_RIGHT); break;

                case sf::Key::Escape:
                    window.Close();
                    break;
                default:
                    break;
                }
                break;     
            case sf::Event::KeyReleased:
                switch (ev.Key.Code) {
                case sf::Key::S: game_left.add_event_to_queue(r0::game::FAST_DOWN_STOP); break;
                case sf::Key::Down: game_right.add_event_to_queue(r0::game::FAST_DOWN_STOP); break;
                }
                break;
            default:
                break;
            }
        }
        background.advance(elpased_time);		
        background.draw(window);

        int destroyed_left = game_left.advance(elpased_time);
        int destroyed_right = game_right.advance(elpased_time);
        game_left.draw();
        game_right.draw();
        
        if ( destroyed_left < 0 ) {
            end_game(false);
            break;
        } else if ( destroyed_right < 0 ) {
            end_game(true);
            break;
        } else {
            game_left.add_punish_blocks(destroyed_right);
            game_right.add_punish_blocks(destroyed_left);
        }
        

#ifdef STANDBY_TIMER
        frame_rate_timer += elpased_time; 
        if ( frame_rate_timer >= 0.1f ) {
            frame_rate_dnumber.next_standby_step();
            frame_rate_timer = 0.f;
        }
        frame_rate_dnumber.draw_standby(window);
#else  
        frame_rate_timer += elpased_time;  
        ++frame_count;
        if ( frame_rate_timer >= 0.2f ) {

            frame_rate = frame_count*5;
            frame_rate_timer = 0.f;
            frame_count = 0;
        }

        sf::String fps_str("FPS:", font_holder::font, 23);
        fps_str.SetPosition( 10.f, 8.f );
        fps_str.SetColor( sf::Color(0, 255, 0) );
        window.Draw(fps_str);

        frame_rate_dnumber.draw_number( window, frame_rate );
#endif 
        window.Display();
    }
    return 0;

}

void game_manager::end_game(bool left_won) {
    using std::cout;
    using std::endl;
    

    game& lost_game = left_won ? game_right : game_left;
    game& won_game = left_won ? game_left : game_right;

    lost_game.set_state(game::BLOW_UP);

    bool run = true;

    while(window.IsOpened() && run) {

        float elpased_time = window.GetFrameTime();

        background.advance(elpased_time);		
        background.draw(window);

        run = lost_game.advance_blow_up(elpased_time);        

        lost_game.draw_blow_up();
        won_game.draw();

        window.Display();
    }

}

} //namespace r0