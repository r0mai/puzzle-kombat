
#include "animation_queue.h"

#include <algorithm>

namespace r0 {

animation_queue::animation_queue() {}

animation_queue::~animation_queue() {
    clear_waiting_queue();
}

void animation_queue::add(animation *a, float delay) {
    if ( delay <= 0.f ) {
        running_list.push_back(a);
    } else {
        waiting_queue.push_back( std::make_pair(delay, a) );
    }
}

unsigned animation_queue::get_waiting_queue_size() const {
    return waiting_queue.size();
}

unsigned animation_queue::get_running_list_size() const {
    return running_list.size();
}

void animation_queue::clear() {
    clear_waiting_queue();
    clear_running_list();
}

void animation_queue::clear_waiting_queue() {
    std::for_each(
        waiting_queue.begin(),
        waiting_queue.end(),
        [](const std::pair<float, animation*>& x) {
            delete x.second;
        }
    );
}

void animation_queue::clear_running_list() {
    running_list.clear();
}

bool animation_queue::isalive() const {
    return get_waiting_queue_size() != 0 || get_running_list_size() != 0;
}

void animation_queue::advance(float elpased_time) {

    std::for_each(running_list.begin(), running_list.end(), [elpased_time](animation& a) { a.advance(elpased_time); });
    running_list.erase(
        std::remove_if(running_list.begin(), running_list.end(), [](const animation& p) { return !p.isalive(); }),
        running_list.end()
    );    
    for( auto it = waiting_queue.begin(); it != waiting_queue.end(); ) {
        it->first -= elpased_time;
        if ( it->first <= 0.f ) { 
            it->second->advance(-it->first);
            running_list.push_back(it->second);
            waiting_queue.erase(it++);
        } else {
            ++it;
        }
    }
}

void animation_queue::draw(sf::RenderTarget& target) {
    std::for_each(running_list.begin(), running_list.end(), [&target](animation& a) { a.draw(target); });
}

} //namespace r0

