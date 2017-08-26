
#ifndef PS_RANDOM_DIRECTION_INIT_POLICY_H_
#define PS_RANDOM_DIRECTION_INIT_POLICY_H_

#include "random.h"

namespace r0 { namespace ps {

template<class Particle>
class random_direction_init_policy {
public:

    typedef Particle particle_type;

    random_direction_init_policy() {}
    random_direction_init_policy(float x_min, float x_max, float y_min, float y_max)
        : x_distribution(x_min, x_max), y_distribution(y_min, y_max) {}

    void operator()(particle_type& p) {
        p.x_velocity = x_distribution(get_rng());
        p.y_velocity = y_distribution(get_rng());
    }  
    
    float get_x_min() const { return x_distribution.min(); }
    float get_x_max() const { return x_distribution.max(); }
    float get_y_min() const { return y_distribution.min(); }
    float get_y_max() const { return y_distribution.max(); }

private:
    boost::uniform_real<float> x_distribution;
    boost::uniform_real<float> y_distribution;
};

}} //namespace r0::ps

#endif //PS_RANDOM_DIRECTION_INIT_POLICY_H_