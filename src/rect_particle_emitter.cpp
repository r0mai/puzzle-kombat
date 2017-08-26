
#include "rect_particle_emitter.h"

#include "random.h"

namespace r0 {

rect_particle_emitter::rect_particle_emitter() {}

rect_particle_emitter::rect_particle_emitter(float x, float y, float w, float h) : particle_emitter(x, y), width(w), height(h) {}

rect_particle_emitter::rect_particle_emitter(const positionf& p, float w, float h) : particle_emitter(p), width(w), height(h) {}

rect_particle_emitter::~rect_particle_emitter() {}

float rect_particle_emitter::get_width() const {
    return width;
}

float rect_particle_emitter::get_height() const {
    return height;
}

void rect_particle_emitter::set_width(float w) {
    width = w;
}

void rect_particle_emitter::set_height(float h) {
    height = h;
}

positionf rect_particle_emitter::get_new_particle_position() {
    boost::uniform_real<float> rng_x(pos.x, pos.x+width);
    boost::uniform_real<float> rng_y(pos.y, pos.y+height);

    rng_engine_type& rng = get_rng();
    
    return positionf( rng_x(rng), rng_y(rng) );
}

} //namespace r0