
#ifndef RANDOM_H_
#define RANDOM_H_

#include <boost/random.hpp>
#include <boost/noncopyable.hpp>

namespace r0 {

typedef boost::rand48 rng_engine_type;

//Singleton
class rng_holder : boost::noncopyable {
public:
    static rng_engine_type& get();
private:
    static rng_engine_type rng;
};

template<class T>
void seed_rng(const T& s) {
    rng_holder::get().seed(s);
}

rng_engine_type& get_rng();


} //namespace r0

#endif //RANDOM_H_