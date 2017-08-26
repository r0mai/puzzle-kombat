
#ifndef PS_NULL_AFFECTOR_H_
#define PS_NULL_AFFECTOR_H_

namespace r0 { namespace ps {

//Does nothing affector
template<class Particle>
struct null_affector {

    typedef Particle particle_type;
    
    bool operator()(const particle_type&, float) { return true; }

};

}} //namespace r0::p

#endif //PS_NULL_AFFECTOR_H_