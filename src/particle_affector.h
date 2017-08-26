
#ifndef PARTICLE_AFFECTOR_H_
#define PARTICLE_AFFECTOR_H_

#include "particle.h"

namespace r0 {

class particle_affector {
public:
    virtual ~particle_affector() {}

    virtual void affect(particle& p) = 0;
};

} //namespace r0

#endif //PARTICLE_AFFECTOR_H_