
#ifndef RECT_INTO_PARTICLES_EMITTER_H_
#define RECT_INTO_PARTICLES_EMITTER_H_

#include <SFML/Graphics.hpp>

#include "rect_particle_emitter.h"

namespace r0 {


class rect_into_particles_emitter : public rect_particle_emitter {
public:
    rect_into_particles_emitter();
    rect_into_particles_emitter(float x, float y, float w, float h, int x_break_count, int y_break_count, const sf::Color& col);
    rect_into_particles_emitter(const positionf& p, float w, float h, int x_break_count, int y_break_count, const sf::Color& col);
        
    virtual ~rect_into_particles_emitter();

    int get_x_break_count() const;
    int get_y_break_count() const;

    void set_x_break_count(int x_bc);
    void set_y_break_count(int y_bc);

    virtual positionf get_new_particle_position();

    void reset();
private:
    int x_break_count;
    int y_break_count;

    int current_x;
    int current_y;

    sf::Color color;
};

} //namespace r0

#endif //RECT_INTO_PARTICLES_EMITTER_H_