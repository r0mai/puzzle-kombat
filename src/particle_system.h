
#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

#include <list>

#include "particle.h"
#include "particle_emitter.h"
#include "animation_queue.h"

namespace r0 {

class particle_system : public animation_queue {
public:

    virtual ~particle_system();

    void addparticle(const particle& p);
    void generate_particles(
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
        const sf::Color& col);

    /*void generate_particles(
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
        const sf::Color& col);
    */
    //Inherited : virtual void advance(float elpased_time);
    //Inherited : virtual bool isalive() const; 
    //Inherited : virtual void draw(sf::RenderTarget& target);

};

} //namespace r0

#endif //PARTICLE_SYSTEM_H_
