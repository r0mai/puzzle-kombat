
#ifndef PS_COMBINE_INIT_POLICY_H_
#define PS_COMBINE_INIT_POLICY_H_

namespace r0 { namespace ps {

template<class P1, class P2>
struct combine_init_policy {
    typedef P1 policy1_type;
    typedef P2 policy2_type;

    combine_init_policy() {}
    combine_init_policy(const policy1_type& p1, const policy2_type& p2) : policy1(p1), policy2(p2) {}

    template<class P>
    void operator()(P& p) {
        policy1(p);
        policy2(p);
    }

    policy1_type policy1;
    policy2_type policy2;
};

}} //namespace r0::p

#endif //PS_COMBINE_INIT_POLICY_H_