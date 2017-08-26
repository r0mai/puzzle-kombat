
#ifndef PS_POINT_INIT_POLICY
#define PS_POINT_INIT_POLICY

#include "position.h"

namespace r0 { namespace ps {

template<class Particle>
struct point_init_policy {

    typedef Particle particle_type;
    
    void operator()(particle_type& p) {} //Does nothing
};

}} //namespace r0::p

#endif //PS_POINT_INIT_POLICY