
#ifndef PS_RANDOM_RECTANGLE_POSITION_INIT_POLICY_H_
#define PS_RANDOM_RECTANGLE_POSITION_INIT_POLICY_H_

#include "position.h"
#include "random.h"

namespace r0 { namespace ps {

template<class Particle>
class random_rectangle_position_init_policy {
public:
    typedef Particle particle_type;
    
    random_rectangle_position_init_policy() {}
    random_rectangle_position_init_policy(float width, float height) : x_distribution(0.f, width), y_distribution(0.f, height) {}

    void operator()(particle_type& p) {
        const positionf offset_pos(x_distribution(get_rng()), y_distribution(get_rng()));
        p.position += offset_pos;
    }    

    float get_width() const { return x_distribution.max(); }
    float get_height() const { return y_distribution.max(); }

    void set_width(float w) { x_distribution = boost::uniform_real<float>(0.f, w); }
    void set_height(float h) { y_distribution = boost::uniform_real<float>(0.f, h); }
    void set_size(float w, float h) { set_width(w); set_height(h); }

private:
    boost::uniform_real<float> x_distribution;
    boost::uniform_real<float> y_distribution;
};

}} //namespace r0::p

#endif //PS_RANDOM_RECTANGLE_POSITION_INIT_POLICY_H_