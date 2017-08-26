
#include "particle_emitter.h"

namespace r0 {

particle_emitter::particle_emitter() {}

particle_emitter::particle_emitter(float x, float y) : pos(x, y) {}

particle_emitter::particle_emitter(const positionf& p) : pos(p) {}

particle_emitter::~particle_emitter() {}

void particle_emitter::set_x(float x) {
    pos.x = x;
}

void particle_emitter::set_y(float y) {
    pos.y = y;
}

void particle_emitter::set_position(float x, float y) {
    pos = positionf(x, y);
}

void particle_emitter::set_position(const positionf& p) {
    pos = p;
}

float particle_emitter::get_x() const {
    return pos.x;
}

float particle_emitter::get_y() const {
    return pos.y;
}

positionf particle_emitter::get_position() const {
    return pos;
}

} //namespace r0