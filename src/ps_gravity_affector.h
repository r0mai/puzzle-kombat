
#ifndef PS_GRAVITY_AFFECTOR_H_
#define PS_GRAVITY_AFFECTOR_H_

namespace r0 { namespace ps {

template<class Particle>
class gravity_affector { //Moves the particle
public:
    typedef Particle particle_type;
    
    gravity_affector() {}
    gravity_affector(float acceleration) : acceleration(acceleration) {}

    bool operator()(particle_type& p, float elpased_time) {
        //TODO
        return true;
    }
private:
    float acceleration;
};

}} //namespace r0::ps


#endif //PS_GRAVITY_AFFECTOR_H_