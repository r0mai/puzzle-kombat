
#ifndef POINT_PARTICLE_EMITTER_H_
#define POINT_PARTICLE_EMITTER_H_

#include "particle_emitter.h"

namespace r0 {

class point_particle_emitter : public particle_emitter {
public:
    point_particle_emitter();
    point_particle_emitter(float x, float y);
    point_particle_emitter(const positionf& p);

    virtual ~point_particle_emitter();
    
    virtual positionf get_new_particle_position();
};

}

#endif //POINT_PARTICLE_EMITTER_H_