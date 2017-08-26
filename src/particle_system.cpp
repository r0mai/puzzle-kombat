
#include "particle_system.h"

#include <algorithm>

#include "random.h"

namespace r0 {

particle_system::~particle_system() {}

void particle_system::generate_particles(
    int n,
    particle_emitter& emitter,
    float x_velocity_min,
    float x_velocity_max,
    float y_velocity_min,
    float y_velocity_max,
    float x_acceleration_min,
    float x_acceleration_max,
    float y_acceleration_min,
    float y_acceleration_max,
    float min_life_time,
    float max_life_time,
    float particle_width,
    float particle_height,
    const sf::Color& col) {

    for(int i = 0; i < n; ++i) {
        boost::shared_ptr<sf::Drawable> obj(new sf::Shape(sf::Shape::Rectangle(0, 0, particle_width, particle_height, col)));
        
        positionf parc_pos = emitter.get_new_particle_position();

        obj->SetPosition(
            parc_pos.x,
            parc_pos.y);

        add( new particle(
            boost::uniform_real<float>(x_velocity_min, x_velocity_max)(get_rng()),
            boost::uniform_real<float>(y_velocity_min, y_velocity_max)(get_rng()),
            boost::uniform_real<float>(x_acceleration_min, x_acceleration_max)(get_rng()),
            boost::uniform_real<float>(y_acceleration_min, y_acceleration_max)(get_rng()),
            boost::uniform_real<float>(min_life_time, max_life_time)(get_rng()),
            obj
        ));
    }
}
/*
void particle_system::generate_particles(
    int n,
    float x_pos,
    float y_pos,
    float x_velocity_min,
    float x_velocity_max,
    float y_velocity_min,
    float y_velocity_max,
    float x_acceleration_min,
    float x_acceleration_max,
    float y_acceleration_min,
    float y_acceleration_max,
    float min_life_time,
    float max_life_time,
    const sf::Color& col) {

        for(int i = 0; i < n; ++i) {
            boost::shared_ptr<sf::Drawable> obj(new sf::Shape(sf::Shape::Rectangle(0, 0, 2, 2, col)));

            obj->SetPosition(x_pos, y_pos);

            add( new particle(
                sf::Randomizer::Random(x_velocity_min, x_velocity_max),
                sf::Randomizer::Random(y_velocity_min, y_velocity_max),      
                sf::Randomizer::Random(x_acceleration_min, x_acceleration_max),
                sf::Randomizer::Random(y_acceleration_min, y_acceleration_max),
                sf::Randomizer::Random(min_life_time, max_life_time),
                obj
                ));
        }

}
*/
} //namespace r0
