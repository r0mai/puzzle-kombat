
#include "random.h"

namespace r0 {

rng_engine_type rng_holder::rng;

rng_engine_type& rng_holder::get() {
    return rng;
}

rng_engine_type& get_rng() {
    return rng_holder::get();
}

} //namespace r0