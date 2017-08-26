#ifndef CONTINOUS_ANIMATION_H_
#define CONTINOUS_ANIMATION_H_

#include "animation.h"

namespace r0 {

class continous_animation : public animation {
public:

    virtual ~continous_animation();

    void start();
    //When stopped, isalive() returns false, draw doesn't do anything
    void stop();

    virtual bool isalive() const;
    virtual void advance(float elpased_time);
    virtual void draw(sf::RenderTarget& target);
protected:
    virtual void private_advance(float elpased_time) = 0;
    virtual void private_draw(sf::RenderTarget& target) = 0;
    
    bool running;
};

} //namespace r0

#endif //CONTINOUS_ANIMATION_H_