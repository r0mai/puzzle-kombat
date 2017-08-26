
#ifndef FIRE_ANIMATION_H_
#define FIRE_ANIMATION_H_

#include "continous_animation.h"

namespace r0 {

class fire_animation : public continous_animation {
public:
    virtual ~fire_animation();
protected:
    virtual void private_advance(float elpased_time);
    virtual void private_draw(sf::RenderTarget& target);
};

} //namespace r0

#endif