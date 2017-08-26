
#ifndef PS_PARTICLE_H_
#define PS_PARTICLE_H_

#include <SFML/Graphics.hpp>

#include <boost/scoped_ptr.hpp>

#include "position.h"

namespace r0 { namespace ps {

//Takes care of object's destructoin
class particle {
public:
    particle(const positionf& pos = positionf(), sf::Drawable *obj = 0);

    positionf position;
    float x_velocity; //Are these zeroed out by default?
    float y_velocity;

    sf::Drawable *get_object();
    void set_object(sf::Drawable *obj);

private:
    boost::scoped_ptr<sf::Drawable> object;
};

inline
particle::particle(const positionf& p, sf::Drawable *obj) : position(p), object(obj) {}

inline
sf::Drawable *particle::get_object() {
    return object.get();
}

inline
void particle::set_object(sf::Drawable *obj) {
    object.reset(obj);
}

}} //namespace r0::ps

#endif