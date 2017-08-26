
#ifndef RECT_PARTICLE_EMITTER_H_
#define RECT_PARTICLE_EMITTER_H_

#include "particle_emitter.h"

namespace r0 {

class rect_particle_emitter : public particle_emitter {
public:
    rect_particle_emitter();
    rect_particle_emitter(float x, float y, float w, float h);
    rect_particle_emitter(const positionf& p, float w, float h);
        
    virtual ~rect_particle_emitter();

    float get_width() const;
    float get_height() const;

    void set_width(float w);
    void set_height(float h);

    virtual positionf get_new_particle_position();
protected:
    float width;
    float height;
};

} //namespace r0

#endif //RECT_PARTICLE_EMITTER_H_