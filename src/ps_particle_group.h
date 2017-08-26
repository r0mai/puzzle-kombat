
#ifndef PS_PARTICLE_GROUP_H_
#define PS_PARTICLE_GROUP_H_

#include <list>

#include <boost/pool/pool_alloc.hpp>

#include "position.h"

namespace r0 { namespace ps {

template<class Particle, class InitPolicy, class Affector>
class particle_group {
public:
    typedef Particle    particle_type;
    typedef InitPolicy  init_policy_type;
    typedef Affector    affector_type;

    particle_group();
    particle_group(const InitPolicy& init_pol, const Affector& affector);

    virtual ~particle_group();
    
    void emitt(unsigned n, const positionf& p);
    void advance(float elpased_time);

protected:
    std::list< particle_type, boost::pool_allocator<particle_type> > particles;

private:
    init_policy_type init_policy;
    affector_type affector;
};

template<class Particle, class InitPolicy, class Affector>
particle_group<Particle, InitPolicy, Affector>::particle_group() {}

template<class Particle, class InitPolicy, class Affector>
particle_group<Particle, InitPolicy, Affector>::particle_group(const InitPolicy& init_pol, const Affector& a)
    : init_policy(init_pol), affectoror(a)  {}

template<class Particle, class InitPolicy, class Affector>
particle_group<Particle, InitPolicy, Affector>::~particle_group() {}

template<class Particle, class InitPolicy, class Affector>
void particle_group<Particle, InitPolicy, Affector>::emitt(unsigned n, const positionf& p) {

    for(unsigned i = 0; i < n; ++i) {
        Particle pr(p);
        init_policy(pr);
        particles.push_back(pr);
    }

}

template<class Particle, class InitPolicy, class Affector>
void particle_group<Particle, InitPolicy, Affector>::advance(float elpased_time) {

    for(auto it = particles.begin(); it != particles.end(); ) {
        if (!affector(*it, elpased_time)) {
            particles.erase(it++);
        } else {
            ++it;
        }
    }

}

}} //namespace r0::ps

#endif //PS_PARTICLE_GROUP_H_