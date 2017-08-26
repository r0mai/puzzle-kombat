
#ifndef PS_COMBINE_AFFECTOR_H_
#define PS_COMBINE_AFFECTOR_H_

namespace r0 { namespace ps {

//Only for AdvancePolicy
template<class A1, class A2>
struct combine_affector {

    typedef A1 affector1_type;
    typedef A2 affector2_type;

    combine_affector() {}
    combine_affector(const affector1_type& a1, const affector2_type& a2) : affector1(a1), affector2(a2) {}

    template<class P>
    bool operator()(P& particle, float elpased_time) {
        return affector1(particle, elpased_time) && affector2(particle, elpased_time);
    }

    affector1_type affector1;
    affector2_type affector2;
};

}} //namespace r0::ps

#endif //PS_COMBINE_AFFECTOR_H_