#include <geometry/points/Point2Df.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE or NEON are NOT available
#include <geometry/lines/Line2Df.hpp>
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;

namespace Mind {
    Point2Df::Point2Df() {
        m_values = { 0.f, 0.f } ;
    }

    Point2Df::Point2Df(const Scalar x, const Scalar y) {
        m_values = { x, y } ;
    }

    void Point2Df::translate(const Scalar x, const Scalar y) {
        m_values[Point2Df::Axis::X] += x ;
        m_values[Point2Df::Axis::Y] += y ;
    }

    void Point2Df::translate(const Point2Df& offset) {
        m_values[Point2Df::Axis::X] += offset.m_values[Point2Df::Axis::X] ;
        m_values[Point2Df::Axis::Y] += offset.m_values[Point2Df::Axis::Y] ;
    }

    Scalar Point2Df::dot(const Point2Df& other) const {
        return (m_values[Point2Df::Axis::X] * other.m_values[Point2Df::Axis::X]) +
                (m_values[Point2Df::Axis::Y] * other.m_values[Point2Df::Axis::Y]) ;
    }

    void Point2Df::normalize() {
        Scalar lengthPoint = length() ;
        m_values[Point2Df::Axis::X] /= lengthPoint ;
        m_values[Point2Df::Axis::Y] /= lengthPoint ;
    }

    Point2Df Point2Df::merge(const Point2Df& a, const Point2Df& b) {
        Scalar xMiddle = (a.m_values[Point2Df::Axis::X] + b.m_values[Point2Df::Axis::X]) / 2.f ;
        Scalar yMiddle = (a.m_values[Point2Df::Axis::Y] + b.m_values[Point2Df::Axis::Y]) / 2.f ;
        return Point2Df(xMiddle, yMiddle) ;
    }

    Point2Df Point2Df::mul(const Point2Df& p, const Point2Df& other) {
        return Point2Df(
            p.m_values[Point2Df::Axis::X] * other.m_values[Point2Df::Axis::X],
            p.m_values[Point2Df::Axis::Y] * other.m_values[Point2Df::Axis::Y]
        ) ;
    }

    Scalar Point2Df::distanceX(const Point2Df& a, const Point2Df& b) {
        return std::fabs(a.m_values[Point2Df::Axis::X] - b.m_values[Point2Df::Axis::X]) ;
    }

    Scalar Point2Df::distanceY(const Point2Df& a, const Point2Df& b) {
        return std::fabs(a.m_values[Point2Df::Axis::Y] - b.m_values[Point2Df::Axis::Y]) ;
    }

    Scalar Point2Df::distance(const Point2Df& a, const Point2Df& b) {
        Scalar diffX, diffY ;

        diffX = a.m_values[Point2Df::Axis::X] - b.m_values[Point2Df::Axis::X] ;
        diffY = a.m_values[Point2Df::Axis::Y] - b.m_values[Point2Df::Axis::Y] ;

        #ifdef USE_APPROXIMATION
            return (Scalar) FastMath::sqrt((diffX * diffX) + (diffY * diffY)) ;
        #else
            return (Scalar) sqrt((diffX * diffX) + (diffY * diffY)) ;
        #endif
    }

    Scalar Point2Df::length() {
        #ifdef USE_APPROXIMATION
            return (FastMath::sqrt(this -> dot(*this)));
        #else
            return (sqrt(this -> dot(*this)));
        #endif
    }

    Scalar Point2Df::angle(
        const Point2Df& b,
        const Point2Df& c,
        const Point2Df& d
    ) {
        // Line between B and C
        Line2Df b_side(b, c) ;
        // Line between B and D
        Line2Df c_side(b, d) ;
        // Line between C and D
        Line2Df d_side(c, d) ;

        double angle =
        (
            b_side.lengthSquared() +
            d_side.lengthSquared() -
            c_side.lengthSquared()
        ) / (2 * b_side.length() * d_side.length()) ;

        Scalar acosAngle = static_cast<Scalar>(acos(angle));
        return Math::toDegrees(acosAngle);
    }

    int Point2Df::angleOrientation(
        const Point2Df& a,
        const Point2Df& b,
        const Point2Df& c
    ) {
        Point2Df relativeAToB = a - b ;
        Point2Df relativeCToB = c - b ;
        return static_cast<int>(
            (relativeAToB.m_values[Point2Df::Axis::X] * relativeCToB.m_values[Point2Df::Axis::Y]) -
            (relativeCToB.m_values[Point2Df::Axis::X] * relativeAToB.m_values[Point2Df::Axis::Y])
        ) ;
    }

    Scalar Point2Df::get(const Axis axis) const {
        return m_values[axis] ;
    }

    Array4f& Point2Df::getCoordinates(Array4f& output) const {
        output[X] = m_values[Point2Df::Axis::X] ;
        output[Y] = m_values[Point2Df::Axis::Y] ;
        return output ;
    }

    void Point2Df::set(const Axis axis, const Scalar x) {
        m_values[axis] = x ;
    }

    void Point2Df::set(const Scalar x, const Scalar y) {
        m_values[Point2Df::Axis::X] = x ;
        m_values[Point2Df::Axis::Y] = y ;
    }

    void Point2Df::set(const Point2Df& position) {
        m_values[Point2Df::Axis::X] = position.m_values[Point2Df::Axis::X] ;
        m_values[Point2Df::Axis::Y] = position.m_values[Point2Df::Axis::Y] ;
    }

    std::array<float, 2> Point2Df::toArray() {
        return m_values ;
    }

    Point2Df::operator Dimension2Df() {
        return Dimension2Df(m_values[Point2Df::Axis::X], m_values[Point2Df::Axis::Y]) ;
    }

    Point2Df::operator Point3Df() {
        return Point3Df(m_values[Point2Df::Axis::X], m_values[Point2Df::Axis::Y], 0.f) ;
    }

    Point2Df& Point2Df::operator+=(Point2Df& other) {
        m_values[Point2Df::Axis::X] += other.m_values[Point2Df::Axis::X] ;
        m_values[Point2Df::Axis::Y] += other.m_values[Point2Df::Axis::Y] ;
        return *this ;
    }

    Point2Df& Point2Df::operator-=(Point2Df& other) {
        m_values[Point2Df::Axis::X] -= other.m_values[Point2Df::Axis::X] ;
        m_values[Point2Df::Axis::Y] -= other.m_values[Point2Df::Axis::Y] ;
        return *this ;
    }

    Point2Df& Point2Df::operator*=(const Scalar coeff) {
        m_values[Point2Df::Axis::X] *= coeff ;
        m_values[Point2Df::Axis::Y] *= coeff ;
        return *this ;
    }

    Point2Df& Point2Df::operator/=(const Scalar coeff) {
        m_values[Point2Df::Axis::X] /= coeff ;
        m_values[Point2Df::Axis::Y] /= coeff ;
        return *this ;
    }

    bool Point2Df::operator==(const Point2Df& other) const {
        return ((this == &other) ||
                ((m_values[Point2Df::Axis::X] == other.m_values[Point2Df::Axis::X])
                    && (m_values[Point2Df::Axis::Y] == other.m_values[Point2Df::Axis::Y]))) ;
    }

    bool Point2Df::operator!=(const Point2Df& other) const {
        return !(*this == other) ;
    }

    Scalar Point2Df::operator[](const int axis) const {
        return m_values[axis] ;
    }

    Scalar& Point2Df::operator[](const int axis) {
        return m_values[axis] ;
    }

    Point2Df operator-(const Point2Df& p) {
        return Point2Df(-p.m_values[Point2Df::Axis::X], -p.m_values[Point2Df::Axis::Y]) ;
    }

    Point2Df operator+(const Point2Df& a, const Point2Df& b) {
        return Point2Df(
            a.m_values[Point2Df::Axis::X] + b.m_values[Point2Df::Axis::X],
            a.m_values[Point2Df::Axis::Y] + b.m_values[Point2Df::Axis::Y]
        ) ;
    }

    Point2Df operator-(const Point2Df& a, const Point2Df& b) {
        return Point2Df(
            a.m_values[Point2Df::Axis::X] - b.m_values[Point2Df::Axis::X],
            a.m_values[Point2Df::Axis::Y] - b.m_values[Point2Df::Axis::Y]
        ) ;
    }

    Scalar operator*(const Point2Df& a, const Point2Df& b) {
        return a.dot(b) ;
    }

    Point2Df operator*(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_values[Point2Df::Axis::X] * coeff, p.m_values[Point2Df::Axis::Y] * coeff) ;
    }

    Point2Df operator/(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_values[Point2Df::Axis::X] / coeff, p.m_values[Point2Df::Axis::Y] / coeff) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point2Df& p) {
        s << "Point2Df (" <<
            p.get(Point2Df::Axis::X) << "," <<
            p.get(Point2Df::Axis::Y)
        << ")" ;
        return s ;
    }
} ;

#endif
