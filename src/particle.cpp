
#include "particle.h"

#include <iostream>
#include <new>
#include <boost/pool/singleton_pool.hpp>

namespace r0 {

particle::particle(float x_velocity, float y_velocity, float x_acceleration, float y_acceleration, float life_time, const boost::shared_ptr<sf::Drawable>& object)
    : x_velocity(x_velocity), y_velocity(y_velocity), x_acceleration(x_acceleration), y_acceleration(y_acceleration), life_time(life_time), object(object)
{}

void particle::advance(float elpased_time) {
    life_time -= elpased_time;

    x_velocity += x_acceleration*elpased_time;
    y_velocity += y_acceleration*elpased_time;

    object->Move(x_velocity*elpased_time, y_velocity*elpased_time);
}

void particle::draw(sf::RenderTarget& target) {
    target.Draw(*object);
}

bool particle::isalive() const {
    return life_time > 0.f;
}

void *particle::operator new(size_t size) {
    if (size != sizeof(particle))
        return ::operator new(size);

    typedef boost::singleton_pool<boost::pool_allocator_tag, sizeof(particle)> pool_t;

    while(true) {
        void *p = pool_t::malloc();
        if (p) {
            return p;
        }
        std::new_handler global_handler = std::set_new_handler(0);
        std::set_new_handler(global_handler);
        if (global_handler) 
            (*global_handler)();
        else
            throw std::bad_alloc();

    }

}

void particle::operator delete(void *p, size_t size) {
    if (p) {
        if (size != sizeof(particle))
            ::operator delete(p);
        else {
            typedef boost::singleton_pool<boost::pool_allocator_tag, sizeof(particle)> pool_t;   
            pool_t::free(p);
        }
    }
}
/*

particle_generator::particle_generator() :
    particle_count(0),
    x_pos_min(0.f),
    x_pos_max(0.f),
    y_pos_min(0.f),
    y_pos_max(0.f),
    x_velocity_min(0.f),
    x_velocity_max(0.f),
    y_velocity_min(0.f),
    y_velocity_max(0.f),
    x_acceleration_min(0.f),
    x_acceleration_max(0.f),
    y_acceleration_min(0.f),
    y_acceleration_max(0.f),
    min_life_time(0.f),
    max_life_time(0.f),
    min_birth_time(0.f),
    max_birth_time(0.f)
{}

particle_generator::particle_generator() :
    particle_count(0),
    x_pos_min(0.f),
    x_pos_max(0.f),
    y_pos_min(0.f),
    y_pos_max(0.f),
    x_velocity_min(0.f),
    x_velocity_max(0.f),
    y_velocity_min(0.f),
    y_velocity_max(0.f),
    x_acceleration_min(0.f),
    x_acceleration_max(0.f),
    y_acceleration_min(0.f),
    y_acceleration_max(0.f),
    min_life_time(0.f),
    max_life_time(0.f),
    min_birth_time(0.f),
    max_birth_time(0.f)
{}

particle_generator::particle_generator(
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
    float max_birth_time) {}

void particle_generator::generate(animation_queue& aq) {

}
*/
} //namespace r0