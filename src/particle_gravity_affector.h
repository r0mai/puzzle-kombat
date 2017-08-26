
#ifndef PARTICLE_GRAVITY_AFFECTOR_H_
#define PARTICLE_GRAVITY_AFFECTOR_H_

#include "particle_affector.h"

namespace r0 {

class gravity_particle_affector : public particle_affector {
public:
    gravity_particle_affector();
    gravity_particle_affector(float gravity);
    virtual ~gravity_particle_affector();

    virtual void affect(particle& p);

private:
    float gravity;
};

} //namespace r0

#endif //PARTICLE_GRAVITY_AFFECTOR_H_