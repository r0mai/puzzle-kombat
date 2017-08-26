#ifndef PARTICLE_EMITTER_H_
#define PARTICLE_EMITTER_H_

#include "position.h"

namespace r0 {

//Abstract base class for particle emitters
//All a class should do is to generate a point where a particle should emit, when get_new_particle_position() is called
class particle_emitter {
public:
    particle_emitter();
    particle_emitter(float x, float y);
    particle_emitter(const positionf& p);

    virtual ~particle_emitter();
    virtual positionf get_new_particle_position() = 0;

    void set_x(float x);
    void set_y(float y);
    void set_position(float x, float y);
    void set_position(const positionf& p);

    float get_x() const;
    float get_y() const;
    positionf get_position() const;

protected:
    positionf pos;
};

} //namespace r0

#endif //PARTICLE_EMITTER_H_