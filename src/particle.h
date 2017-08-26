
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include "animation.h"
#include "animation_queue.h"

namespace r0 {

class particle : public animation {
public:
    particle();
    particle(float x_velocity, float y_velocity, float x_acceleration, float y_acceleration, float life_time, const boost::shared_ptr<sf::Drawable>& object);

    virtual void advance(float elpased_time);

    virtual void draw(sf::RenderTarget& target);

    virtual bool isalive() const;

    //custom allocator
    static void *operator new(size_t size);
    static void operator delete(void *p, size_t size);

    //Pos in object    
    float x_velocity, y_velocity;
    float x_acceleration, y_acceleration;
    float life_time;    

    boost::shared_ptr<sf::Drawable> object;
};



/*
struct particle_generator {
    particle_generator();
    particle_generator(
        int particle_count,

        float x_pos_min,
        float x_pos_max,

        float y_pos_min,
        float y_pos_max,

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

        float min_birth_time,
        float max_birth_time);

    void generate(animation_queue& aq);

    int particle_count;

    float x_pos_min;
    float x_pos_max;

    float y_pos_min;
    float y_pos_max;

    float x_velocity_min;
    float x_velocity_max;
    float y_velocity_min;
    float y_velocity_max;

    float x_acceleration_min;
    float x_acceleration_max;
    float y_acceleration_min;
    float y_acceleration_max;

    float min_life_time;
    float max_life_time;

    float min_birth_time;
    float max_birth_time;
};
*/
} //namespace r0

#endif