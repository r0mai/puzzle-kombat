
#ifndef ANIMATION_QUEUE_H_
#define ANIMATION_QUEUE_H_

#include <boost/ptr_container/ptr_list.hpp>
#include <list>
#include <utility>
#include <SFML/Graphics.hpp>

#include "animation.h"
#include "particle.h"

namespace r0 {

//animation_queue is also a child class of animation, so animation_queues can be added to animation_queues
class animation_queue : public animation {
public:
    animation_queue();
    virtual ~animation_queue();
    
    void add(animation *a, float delay = 0.f);

    unsigned get_waiting_queue_size() const;
    unsigned get_running_list_size() const;
    
    //clears waiting_queue and running_list
    void clear();

    void clear_waiting_queue();
    void clear_running_list();

    virtual void advance(float elpased_time);
    virtual bool isalive() const;
    virtual void draw(sf::RenderTarget& target);
private:
    std::list< std::pair<float, animation*> > waiting_queue;
    boost::ptr_list<animation> running_list;
};


} //namespace r0

#endif