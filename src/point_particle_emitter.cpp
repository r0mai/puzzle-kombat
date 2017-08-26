
#include "point_particle_emitter.h"

namespace r0 {

point_particle_emitter::point_particle_emitter() {}
point_particle_emitter::point_particle_emitter(float x, float y) : particle_emitter(x, y) {}
point_particle_emitter::point_particle_emitter(const positionf& p) : particle_emitter(p) {}

point_particle_emitter::~point_particle_emitter() {}

positionf point_particle_emitter::get_new_particle_position() {
    return pos;
}

} //namespace r0
