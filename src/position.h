
#ifndef POSITION_H_
#define POSITION_H_

#include <ostream>
#include <boost/operators.hpp>

namespace r0 {

template<class T>
struct basic_position :
    boost::arithmetic< basic_position<T>,
    boost::arithmetic< basic_position<T>, T,
    boost::equality_comparable< basic_position<T> > > >
{

    basic_position() : x(), y() {}
    basic_position(const T& x, const T& y) : x(x), y(y) {}

    bool operator==(const basic_position& rhs) {
        return x == rhs.x && y == rhs.y;
    }

    basic_position& operator+=(const basic_position& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    basic_position& operator-=(const basic_position& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    basic_position& operator*=(const basic_position& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    basic_position& operator/=(const basic_position& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    basic_position& operator+=(const T& rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }
    basic_position& operator-=(const T& rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }
    basic_position& operator*=(const T& rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    basic_position& operator/=(const T& rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    T x, y;
};

typedef basic_position<int> positioni;
typedef basic_position<float> positionf;

template<class T, class C, class CT>
std::basic_ostream<C, CT>& operator<<(std::basic_ostream<C, CT>& os, const basic_position<T>& p) {
    os << '(' << p.x << ", " <<  p.y << ')';
    return os;
}

} //namespace r0

#endif //POSITION_H_
