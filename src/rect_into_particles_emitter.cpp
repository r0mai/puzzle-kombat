
#include "rect_into_particles_emitter.h"

namespace r0 {

rect_into_particles_emitter::rect_into_particles_emitter() : x_break_count(0), y_break_count(0), current_x(0), current_y(0) {}

rect_into_particles_emitter::rect_into_particles_emitter(float x, float y, float w, float h, int x_bc, int y_bc, const sf::Color& col)
    : rect_particle_emitter(x, y, w, h), x_break_count(x_bc), y_break_count(y_bc), current_x(0), current_y(0), color(col) {}

rect_into_particles_emitter::rect_into_particles_emitter(const positionf& p, float w, float h, int x_bc, int y_bc, const sf::Color& col)
    : rect_particle_emitter(p, w, h), x_break_count(x_bc), y_break_count(y_bc), current_x(0), current_y(0), color(col) {}

rect_into_particles_emitter::~rect_into_particles_emitter() {}

int rect_into_particles_emitter::get_x_break_count() const {
    return x_break_count;
}

int rect_into_particles_emitter::get_y_break_count() const {
    return y_break_count;
}

void rect_into_particles_emitter::set_x_break_count(int x_bc) {
    x_break_count = x_bc;
}

void rect_into_particles_emitter::set_y_break_count(int y_bc) {
    y_break_count = y_bc;
}

positionf rect_into_particles_emitter::get_new_particle_position() {
    if ( current_x >= x_break_count ) {
        current_x = 0;
    }
    if ( current_y >= y_break_count ) {
        current_y = 0;
    }

    positionf result( pos.x + current_x * (width/x_break_count), pos.y + current_y * (height/y_break_count) );

    ++current_x;
    ++current_y;

    return result;
}

void rect_into_particles_emitter::reset() {
    current_x = 0;
    current_y = 0;
}

} //namespace r0