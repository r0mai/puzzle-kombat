
#ifndef PS_SFML_PARTICLE_GROUP_H_
#define PS_SFML_PARTICLE_GROUP_H_

#include "ps_particle_group.h"

#include <SFML/Graphics.hpp>

#include <algorithm>

namespace r0 { namespace ps {

template<class Particle, class InitPolicy, class Affector>
class sfml_paricle_group : public particle_group<Particle, InitPolicy, Affector> {
public:
    typedef typename particle_group<Particle, InitPolicy, Affector>::particle_type       particle_type;
    typedef typename particle_group<Particle, InitPolicy, Affector>::init_policy_type    init_policy_type;
    typedef typename particle_group<Particle, InitPolicy, Affector>::affector_type       affector_type;

    void draw(sf::RenderTarget& target);

};

template<class Particle, class InitPolicy, class Affector>
void sfml_paricle_group<Particle, InitPolicy, Affector>::draw(sf::RenderTarget& target) {
    std::for_each(particles.begin(), particles.end(), [&target](const particle_type& p) {
        target.Draw( *p.get_object() );
    });
}

}} //namespace r0::ps

#endif //PS_SFML_PARTICLE_GROUP_H_