
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>

namespace r0 {

//An abstract base class for everything that moves without need for any control
class animation {
public:
    
    virtual ~animation() {}

    virtual void advance(float elpased_time) = 0;
    virtual bool isalive() const = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
};

} //namespace r0

#endif //ANIMATION_H_