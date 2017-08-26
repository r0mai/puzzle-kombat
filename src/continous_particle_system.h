
#ifndef CONTINOUS_PARTICLE_SYSTEM_H_
#define CONTINOUS_PARTICLE_SYSTEM_H_

#include <boost/shared_ptr.hpp>

#include "continous_animation.h"

namespace r0 {

class continous_particle_system : public continous_animation {
public:

    virtual ~continous_particle_system();

protected:
    virtual void private_advance(float elpased_time);
    virtual void private_draw(sf::RenderTarget& target);

    float particles_per_sec;

    float x_pos;
    float y_pos;

    sf::Color color;
};

} //namespace r0

#endif