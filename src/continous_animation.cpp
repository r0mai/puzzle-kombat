
#include "continous_animation.h"

namespace r0 {
    
//LOT OF TODO
continous_animation::~continous_animation() {}

void continous_animation::start() {
    running = true;
}

void continous_animation::stop() {
    running = false;
}

bool continous_animation::isalive() const {
    return running;
}

void continous_animation::advance(float elpased_time) {
    if (running) {
        private_advance(elpased_time);
    }
}

void continous_animation::draw(sf::RenderTarget& target) {
    if (running) {
        private_draw(target);
    }
}

} //namespace r0