#include <geometry/points/Point3Df.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE or NEON are NOT available
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;

namespace Mind {
    Point3Df::Point3Df() {
        m_values = { 0.f, 0.f, 0.f } ;
    }

    Point3Df::Point3Df(
        const Scalar x,
        const Scalar y,
        const Scalar z
    ) {
        m_values = { x, y, z } ;
    }

    void Point3Df::translate(const Scalar x, const Scalar y, const Scalar z) {
        m_values[Point3Df::Axis::X] += x ;
        m_values[Point3Df::Axis::Y] += y ;
        m_values[Point3Df::Axis::Z] += z ;
    }

    void Point3Df::translate(const Point3Df& offset) {
        m_values[Point3Df::Axis::X] += offset.m_values[Point3Df::Axis::X] ;
        m_values[Point3Df::Axis::Y] += offset.m_values[Point3Df::Axis::Y] ;
        m_values[Point3Df::Axis::Z] += offset.m_values[Point3Df::Axis::Z] ;
    }

    Scalar Point3Df::dot(const Point3Df& other) const {
        return (
            (m_values[Point3Df::Axis::X] * other.m_values[Point3Df::Axis::X]) +
            (m_values[Point3Df::Axis::Y] * other.m_values[Point3Df::Axis::Y]) +
            (m_values[Point3Df::Axis::Z] * other.m_values[Point3Df::Axis::Z])
        ) ;
    }

    Point3Df Point3Df::cross(const Point3Df& other) const {
        return Point3Df(
            (m_values[Point3Df::Axis::Y] * other.m_values[Point3Df::Axis::Z] - m_values[Point3Df::Axis::Z] * other.m_values[Point3Df::Axis::Y]),
            (m_values[Point3Df::Axis::Z] * other.m_values[Point3Df::Axis::X] - m_values[Point3Df::Axis::X] * other.m_values[Point3Df::Axis::Z]),
            (m_values[Point3Df::Axis::X] * other.m_values[Point3Df::Axis::Y] - m_values[Point3Df::Axis::Y] * other.m_values[Point3Df::Axis::X])
        ) ;
    }

    void Point3Df::normalize() {
        Scalar lengthPoint = length() ;
        m_values[Point3Df::Axis::X] /= lengthPoint ;
        m_values[Point3Df::Axis::Y] /= lengthPoint ;
        m_values[Point3Df::Axis::Z] /= lengthPoint ;
    }

    Point3Df Point3Df::merge(const Point3Df& a, const Point3Df& b) {
        return Point3Df(
            (a.m_values[Point3Df::Axis::X] + b.m_values[Point3Df::Axis::X]) / 2.f,
            (a.m_values[Point3Df::Axis::Y] + b.m_values[Point3Df::Axis::Y]) / 2.f,
            (a.m_values[Point3Df::Axis::Z] + b.m_values[Point3Df::Axis::Z]) / 2.f
        ) ;
    }

    Point3Df Point3Df::mul(const Point3Df& p, const Point3Df& other) {
        return Point3Df(
            p.m_values[Point3Df::Axis::X] * other.m_values[Point3Df::Axis::X],
            p.m_values[Point3Df::Axis::Y] * other.m_values[Point3Df::Axis::Y],
            p.m_values[Point3Df::Axis::Z] * other.m_values[Point3Df::Axis::Z]
        ) ;
    }

    Scalar Point3Df::distanceX(const Point3Df& a, const Point3Df& b) {
        return a.m_values[Point3Df::Axis::X] - b.m_values[Point3Df::Axis::X] ;
    }

    Scalar Point3Df::distanceY(const Point3Df& a, const Point3Df& b) {
        return a.m_values[Point3Df::Axis::Y] - b.m_values[Point3Df::Axis::Y] ;
    }

    Scalar Point3Df::distanceZ(const Point3Df& a, const Point3Df& b) {
        return a.m_values[Point3Df::Axis::Z] - b.m_values[Point3Df::Axis::Z] ;
    }

    Scalar Point3Df::distance(const Point3Df& a, const Point3Df& b) {
        Scalar diffX, diffY, diffZ ;

        diffX = a.m_values[Point3Df::Axis::X] - b.m_values[Point3Df::Axis::X] ;
        diffY = a.m_values[Point3Df::Axis::Y] - b.m_values[Point3Df::Axis::Y] ;
        diffZ = a.m_values[Point3Df::Axis::Z] - b.m_values[Point3Df::Axis::Z] ;

        #ifdef USE_APPROXIMATION
            return (Scalar) FastMath::sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) ;
        #else
            return (Scalar) sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) ;
        #endif
    }

    Scalar Point3Df::length() {
        return (sqrt(this -> dot(*this))) ;
    }

    Scalar Point3Df::get(const Axis axis) const {
        return m_values[axis] ;
    }

    void Point3Df::set(const Axis axis, const Scalar value) {
        m_values[axis] = value ;
    }

    void Point3Df::set(const Scalar x, const Scalar y, const Scalar z) {
        m_values[Point3Df::Axis::X] = x ;
        m_values[Point3Df::Axis::Y] = y ;
        m_values[Point3Df::Axis::Z] = z ;
    }

    void Point3Df::set(const Point3Df& position) {
        m_values[Point3Df::Axis::X] = position.m_values[Point3Df::Axis::X] ;
        m_values[Point3Df::Axis::Y] = position.m_values[Point3Df::Axis::Y] ;
        m_values[Point3Df::Axis::Z] = position.m_values[Point3Df::Axis::Z] ;
    }

    std::array<float, 3> Point3Df::toArray() {
        return m_values ;
    }

    Point3Df::operator Dimension3Df() {
        return Dimension3Df(m_values[Point3Df::Axis::X], m_values[Point3Df::Axis::Y], m_values[Point3Df::Axis::Z]) ;
    }

    Point3Df::operator Point2Df() {
        return Point2Df(m_values[Point3Df::Axis::X], m_values[Point3Df::Axis::Y]) ;
    }

    Point3Df& Point3Df::operator+=(Point3Df& other) {
        m_values[Point3Df::Axis::X] += other.m_values[Point3Df::Axis::X] ;
        m_values[Point3Df::Axis::Y] += other.m_values[Point3Df::Axis::Y] ;
        m_values[Point3Df::Axis::Z] += other.m_values[Point3Df::Axis::Z] ;
        return *this ;
    }

    Point3Df& Point3Df::operator-=(Point3Df& other) {
        m_values[Point3Df::Axis::X] -= other.m_values[Point3Df::Axis::X] ;
        m_values[Point3Df::Axis::Y] -= other.m_values[Point3Df::Axis::Y] ;
        m_values[Point3Df::Axis::Z] -= other.m_values[Point3Df::Axis::Z] ;
        return *this ;
    }

    Point3Df& Point3Df::operator*=(const Scalar coeff) {
        m_values[Point3Df::Axis::X] *= coeff ;
        m_values[Point3Df::Axis::Y] *= coeff ;
        m_values[Point3Df::Axis::Z] *= coeff ;
        return *this ;
    }

    Point3Df& Point3Df::operator/=(const Scalar coeff) {
        m_values[Point3Df::Axis::X] /= coeff ;
        m_values[Point3Df::Axis::Y] /= coeff ;
        m_values[Point3Df::Axis::Z] /= coeff ;
        return *this ;
    }

    bool Point3Df::operator==(const Point3Df& other) const {
        return ((this == &other)
                    || ((m_values[Point3Df::Axis::X] == other.m_values[Point3Df::Axis::X])
                            && (m_values[Point3Df::Axis::Y] == other.m_values[Point3Df::Axis::Y])
                            && (m_values[Point3Df::Axis::Z] == other.m_values[Point3Df::Axis::Z]))) ;
    }

    bool Point3Df::operator!=(const Point3Df& other) const {
        return !(*this == other) ;
    }

    Scalar Point3Df::operator[](const int axis) const {
        return m_values[axis] ;
    }

    Scalar& Point3Df::operator[](const int axis) {
        return m_values[axis] ;
    }

    Point3Df operator-(const Point3Df& p) {
        return Point3Df(-p.m_values[Point3Df::Axis::X], -p.m_values[Point3Df::Axis::Y], -p.m_values[Point3Df::Axis::Z]) ;
    }

    Point3Df operator+(const Point3Df& a, const Point3Df& b) {
        return Point3Df(
            a.m_values[Point3Df::Axis::X] + b.m_values[Point3Df::Axis::X],
            a.m_values[Point3Df::Axis::Y] + b.m_values[Point3Df::Axis::Y],
            a.m_values[Point3Df::Axis::Z] + b.m_values[Point3Df::Axis::Z]
        ) ;
    }

    Point3Df operator-(const Point3Df& a, const Point3Df& b) {
        return Point3Df(
            a.m_values[Point3Df::Axis::X] - b.m_values[Point3Df::Axis::X],
            a.m_values[Point3Df::Axis::Y] - b.m_values[Point3Df::Axis::Y],
            a.m_values[Point3Df::Axis::Z] - b.m_values[Point3Df::Axis::Z]
        ) ;
    }

    Scalar operator*(const Point3Df& a, const Point3Df& b) {
        return a.dot(b) ;
    }

    Point3Df operator*(const Point3Df& p, Scalar coeff) {
        return Point3Df(
            p.m_values[Point3Df::Axis::X] * coeff,
            p.m_values[Point3Df::Axis::Y] * coeff,
            p.m_values[Point3Df::Axis::Z] * coeff
        ) ;
    }

    Point3Df operator/(const Point3Df& p, Scalar coeff) {
        return Point3Df(
            p.m_values[Point3Df::Axis::X] / coeff,
            p.m_values[Point3Df::Axis::Y] / coeff,
            p.m_values[Point3Df::Axis::Z] / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point3Df& p) {
        s << "Point3Df (" <<
            p.get(Point3Df::Axis::X) << "," <<
            p.get(Point3Df::Axis::Y) << "," <<
            p.get(Point3Df::Axis::Z) <<
        ")" ;
        return s ;
    }
} ;

#endif
