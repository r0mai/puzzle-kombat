
#ifndef BACKGROUND_ANIMATION_H_
#define BACKGROUND_ANIMATION_H_

#include <SFML/Graphics.hpp>

#include "ps_particle_system.h"

namespace r0 {

class background_animation {
public:
	background_animation();
	void advance(float elpased_time);
	void draw(sf::RenderWindow& win);
private:
    typedef ps::combine_init_policy<
        ps::random_direction_init_policy<ps::particle>,
        ps::random_rectangle_position_init_policy<ps::particle>
    > particle_init_policy_type;

    typedef ps::gravity_affector<ps::particle> affector_type;

    ps::sfml_paricle_group<ps::particle, particle_init_policy_type, affector_type> particle_group;
};

} //namespace r0

#endif //BACKGROUND_ANIMATION_H_