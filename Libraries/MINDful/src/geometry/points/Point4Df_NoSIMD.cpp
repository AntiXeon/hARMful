#include <geometry/points/Point4Df.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE or NEON are NOT available
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;
const int W = 3 ;

namespace Mind {
    Point4Df::Point4Df() {
        m_values = { 0.f, 0.f, 0.f, 0.f } ;
    }

    Point4Df::Point4Df(
        const Scalar x,
        const Scalar y,
        const Scalar z,
        const Scalar w
    ) {
        m_values = { x, y, z, w } ;
    }

    void Point4Df::translate(
        const Scalar x,
        const Scalar y,
        const Scalar z,
        const Scalar w
    ) {
        m_values[Point4Df::Axis::X] += x ;
        m_values[Point4Df::Axis::Y] += y ;
        m_values[Point4Df::Axis::Z] += z ;
        m_values[Point4Df::Axis::W] += w ;
    }

    void Point4Df::translate(const Point4Df& offset) {
        m_values[Point4Df::Axis::X] += offset.m_values[Point4Df::Axis::X] ;
        m_values[Point4Df::Axis::Y] += offset.m_values[Point4Df::Axis::Y] ;
        m_values[Point4Df::Axis::Z] += offset.m_values[Point4Df::Axis::Z] ;
        m_values[Point4Df::Axis::W] += offset.m_values[Point4Df::Axis::W] ;
    }

    Scalar Point4Df::dot(const Point4Df& other) const {
        return (
            (m_values[Point4Df::Axis::X] * other.m_values[Point4Df::Axis::X]) +
            (m_values[Point4Df::Axis::Y] * other.m_values[Point4Df::Axis::Y]) +
            (m_values[Point4Df::Axis::Z] * other.m_values[Point4Df::Axis::Z]) +
            (m_values[Point4Df::Axis::W] * other.m_values[Point4Df::Axis::W])
        ) ;
    }

    Point4Df Point4Df::cross(const Point4Df& other) const {
        // Give the cross product of a Point3Df as Point4Df cross product is not
        // defined.
        return Point4Df(
            (m_values[Point4Df::Axis::Y] * other.m_values[Point4Df::Axis::Z] - m_values[Point4Df::Axis::Z] * other.m_values[Point4Df::Axis::Y]),
            (m_values[Point4Df::Axis::Z] * other.m_values[Point4Df::Axis::X] - m_values[Point4Df::Axis::X] * other.m_values[Point4Df::Axis::Z]),
            (m_values[Point4Df::Axis::X] * other.m_values[Point4Df::Axis::Y] - m_values[Point4Df::Axis::Y] * other.m_values[Point4Df::Axis::X]),
            0.f
        ) ;
    }

    void Point4Df::normalize() {
        Scalar lengthPoint = length() ;
        m_values[Point4Df::Axis::X] /= lengthPoint ;
        m_values[Point4Df::Axis::Y] /= lengthPoint ;
        m_values[Point4Df::Axis::Z] /= lengthPoint ;
        m_values[Point4Df::Axis::W] /= lengthPoint ;
    }

    Point4Df Point4Df::merge(const Point4Df& a, const Point4Df& b) {
        return Point4Df(
            (a.m_values[Point4Df::Axis::X] + b.m_values[Point4Df::Axis::X]) / 2.f,
            (a.m_values[Point4Df::Axis::Y] + b.m_values[Point4Df::Axis::Y]) / 2.f,
            (a.m_values[Point4Df::Axis::Z] + b.m_values[Point4Df::Axis::Z]) / 2.f,
            (a.m_values[Point4Df::Axis::W] + b.m_values[Point4Df::Axis::W]) / 2.f
        ) ;
    }

    Scalar Point4Df::distanceX(const Point4Df& a, const Point4Df& b) {
        return a.m_values[Point4Df::Axis::X] - b.m_values[Point4Df::Axis::X] ;
    }

    Scalar Point4Df::distanceY(const Point4Df& a, const Point4Df& b) {
        return a.m_values[Point4Df::Axis::Y] - b.m_values[Point4Df::Axis::Y] ;
    }

    Scalar Point4Df::distanceZ(const Point4Df& a, const Point4Df& b) {
        return a.m_values[Point4Df::Axis::Z] - b.m_values[Point4Df::Axis::Z] ;
    }

    Scalar Point4Df::distanceW(const Point4Df& a, const Point4Df& b) {
        return a.m_values[Point4Df::Axis::W] - b.m_values[Point4Df::Axis::W] ;
    }

    Scalar Point4Df::distance(const Point4Df& a, const Point4Df& b) {
        Scalar diffX, diffY, diffZ ;

        diffX = a.m_values[Point4Df::Axis::X] - b.m_values[Point4Df::Axis::X] ;
        diffY = a.m_values[Point4Df::Axis::Y] - b.m_values[Point4Df::Axis::Y] ;
        diffZ = a.m_values[Point4Df::Axis::Z] - b.m_values[Point4Df::Axis::Z] ;
        diffW = a.m_values[Point4Df::Axis::W] - b.m_values[Point4Df::Axis::W] ;

        #ifdef USE_APPROXIMATION
            return (Scalar) FastMath::sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) + (diffW * diffW)) ;
        #else
            return (Scalar) sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ) + (diffW * diffW)) ;
        #endif
    }

    Scalar Point4Df::length() {
        return (sqrt(this -> dot(*this))) ;
    }

    Scalar Point4Df::get(const Axis axis) const {
        return m_values[axis] ;
    }

    void Point4Df::set(const Axis axis, const Scalar value) {
        m_values[axis] = value ;
    }

    void Point4Df::set(
        const Scalar x,
        const Scalar y,
        const Scalar z,
        const Scalar w
    ) {
        m_values[Point4Df::Axis::X] = x ;
        m_values[Point4Df::Axis::Y] = y ;
        m_values[Point4Df::Axis::Z] = z ;
        m_values[Point4Df::Axis::W] = w ;
    }

    void Point4Df::set(const Point4Df& position) {
        m_values[Point4Df::Axis::X] = position.m_values[Point4Df::Axis::X] ;
        m_values[Point4Df::Axis::Y] = position.m_values[Point4Df::Axis::Y] ;
        m_values[Point4Df::Axis::Z] = position.m_values[Point4Df::Axis::Z] ;
        m_values[Point4Df::Axis::W] = position.m_values[Point4Df::Axis::W] ;
    }

    Point4Df::operator Dimension2Df() {
        return Dimension2Df(m_values[Point4Df::Axis::X], m_values[Point4Df::Axis::Y]) ;
    }

    Point4Df::operator Dimension3Df() {
        return Dimension3Df(m_values[Point4Df::Axis::X], m_values[Point4Df::Axis::Y], m_values[Point4Df::Axis::Z]) ;
    }

    Point4Df::operator Point2Df() {
        return Point2Df(m_values[Point4Df::Axis::X], m_values[Point4Df::Axis::Y]) ;
    }

    Point4Df::operator Point3Df() {
        return Point3Df(m_values[Point4Df::Axis::X], m_values[Point4Df::Axis::Y], m_values[Point4Df::Axis::Z]) ;
    }

    Point4Df& Point4Df::operator+=(Point4Df& other) {
        m_values[Point4Df::Axis::X] += other.m_values[Point4Df::Axis::X] ;
        m_values[Point4Df::Axis::Y] += other.m_values[Point4Df::Axis::Y] ;
        m_values[Point4Df::Axis::Z] += other.m_values[Point4Df::Axis::Z] ;
        m_values[Point4Df::Axis::W] += other.m_values[Point4Df::Axis::W] ;
        return *this ;
    }

    Point4Df& Point4Df::operator-=(Point4Df& other) {
        m_values[Point4Df::Axis::X] -= other.m_values[Point4Df::Axis::X] ;
        m_values[Point4Df::Axis::Y] -= other.m_values[Point4Df::Axis::Y] ;
        m_values[Point4Df::Axis::Z] -= other.m_values[Point4Df::Axis::Z] ;
        m_values[Point4Df::Axis::W] -= other.m_values[Point4Df::Axis::W] ;
        return *this ;
    }

    Point4Df& Point4Df::operator*=(const Scalar coeff) {
        m_values[Point4Df::Axis::X] *= coeff ;
        m_values[Point4Df::Axis::Y] *= coeff ;
        m_values[Point4Df::Axis::Z] *= coeff ;
        m_values[Point4Df::Axis::W] *= coeff ;
        return *this ;
    }

    Point4Df& Point4Df::operator/=(const Scalar coeff) {
        m_values[Point4Df::Axis::X] /= coeff ;
        m_values[Point4Df::Axis::Y] /= coeff ;
        m_values[Point4Df::Axis::Z] /= coeff ;
        m_values[Point4Df::Axis::W] /= coeff ;
        return *this ;
    }

    bool Point4Df::operator==(const Point4Df& other) const {
        return ((this == &other)
                    || ((m_values[Point4Df::Axis::X] == other.m_values[Point4Df::Axis::X])
                            && (m_values[Point4Df::Axis::Y] == other.m_values[Point4Df::Axis::Y])
                            && (m_values[Point4Df::Axis::Z] == other.m_values[Point4Df::Axis::Z])
                            && (m_values[Point4Df::Axis::W] == other.m_values[Point4Df::Axis::W]))) ;
    }

    bool Point4Df::operator!=(const Point4Df& other) const {
        return !(*this == other) ;
    }

    Scalar Point4Df::operator[](const int axis) const {
        return m_values[axis] ;
    }

    Scalar& Point4Df::operator[](const int axis) {
        return m_values[axis] ;
    }

    Point4Df operator-(const Point4Df& p) {
        return Point4Df(
            -p.m_values[Point4Df::Axis::X],
            -p.m_values[Point4Df::Axis::Y],
            -p.m_values[Point4Df::Axis::Z],
            -p.m_values[Point4Df::Axis::W]
        ) ;
    }

    Point4Df operator+(const Point4Df& a, const Point4Df& b) {
        return Point4Df(
            a.m_values[Point4Df::Axis::X] + b.m_values[Point4Df::Axis::X],
            a.m_values[Point4Df::Axis::Y] + b.m_values[Point4Df::Axis::Y],
            a.m_values[Point4Df::Axis::Z] + b.m_values[Point4Df::Axis::Z],
            a.m_values[Point4Df::Axis::W] + b.m_values[Point4Df::Axis::W]
        ) ;
    }

    Point4Df operator-(const Point4Df& a, const Point4Df& b) {
        return Point4Df(
            a.m_values[Point4Df::Axis::X] - b.m_values[Point4Df::Axis::X],
            a.m_values[Point4Df::Axis::Y] - b.m_values[Point4Df::Axis::Y],
            a.m_values[Point4Df::Axis::Z] - b.m_values[Point4Df::Axis::Z],
            a.m_values[Point4Df::Axis::W] - b.m_values[Point4Df::Axis::W]
        ) ;
    }

    Scalar operator*(const Point4Df& a, const Point4Df& b) {
        return a.dot(b) ;
    }

    Point4Df operator*(const Point4Df& p, Scalar coeff) {
        return Point4Df(
            p.m_values[Point4Df::Axis::X] * coeff,
            p.m_values[Point4Df::Axis::Y] * coeff,
            p.m_values[Point4Df::Axis::Z] * coeff,
            p.m_values[Point4Df::Axis::W] * coeff
        ) ;
    }

    Point4Df operator/(const Point4Df& p, Scalar coeff) {
        return Point4Df(
            p.m_values[Point4Df::Axis::X] / coeff,
            p.m_values[Point4Df::Axis::Y] / coeff,
            p.m_values[Point4Df::Axis::Z] / coeff,
            p.m_values[Point4Df::Axis::W] / coeff
        ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point4Df& p) {
        s << "Point4Df (" <<
            p.get(Point4Df::Axis::X) << "," <<
            p.get(Point4Df::Axis::Y) << "," <<
            p.get(Point4Df::Axis::Z) << "," <<
            p.get(Point4Df::Axis::W) <<
        ")" ;
        return s ;
    }
} ;

#endif
