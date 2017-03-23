#include <geometry/points/Point2Df.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE or NEON are NOT available
#include <geometry/lines/Line2Df.hpp>
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;

namespace Mind {
    Point2Df::Point2Df() : m_x(0.f), m_y(0.f) {}

    Point2Df::Point2Df(const Scalar x, const Scalar y) : m_x(x), m_y(y) {}

    void Point2Df::translate(const Scalar x, const Scalar y) {
        m_x += x ;
        m_y += y ;
    }

    void Point2Df::translate(const Point2Df& offset) {
        m_x += offset.m_x ;
        m_y += offset.m_y ;
    }

    Scalar Point2Df::dot(const Point2Df& other) const {
        return (m_x * other.m_x) + (m_y * other.m_y) ;
    }

    void Point2Df::normalize() {
        Scalar lengthPoint = length() ;
        m_x /= lengthPoint ;
        m_y /= lengthPoint ;
    }

    Point2Df Point2Df::merge(const Point2Df& a, const Point2Df& b) {
        Scalar xMiddle = (a.m_x + b.m_x) / 2.f ;
        Scalar yMiddle = (a.m_y + b.m_y) / 2.f ;
        return Point2Df(xMiddle, yMiddle) ;
    }

    Scalar Point2Df::distanceX(const Point2Df& a, const Point2Df& b) {
        return std::fabs(a.m_x - b.m_x) ;
    }

    Scalar Point2Df::distanceY(const Point2Df& a, const Point2Df& b) {
        return std::fabs(a.m_y - b.m_y) ;
    }

    Scalar Point2Df::distance(const Point2Df& a, const Point2Df& b) {
        Scalar diffX, diffY ;

        diffX = a.m_x - b.m_x ;
        diffY = a.m_y - b.m_y ;

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
            c_side.lengthSquared()) /
            (2 * b_side.length() * d_side.length()) ;

        return Math::toDegrees(acos(angle)) ;
    }

    int Point2Df::angleOrientation(
        const Point2Df& a,
        const Point2Df& b,
        const Point2Df& c
    ) {
        Point2Df relativeAToB = a - b ;
        Point2Df relativeCToB = c - b ;
        return ((relativeAToB.m_x * relativeCToB.m_y) -
                        (relativeCToB.m_x * relativeAToB.m_y)) ;
    }

    Scalar Point2Df::getX() const {
        return m_x ;
    }

    Scalar Point2Df::getY() const {
        return m_y ;
    }

    Array4f& Point2Df::getCoordinates(Array4f& output) const {
        output[X] = m_x ;
        output[Y] = m_y ;
        return output ;
    }

    void Point2Df::setX(const Scalar x) {
        m_x = x ;
    }

    void Point2Df::setY(const Scalar y) {
        m_y = y ;
    }

    void Point2Df::set(const Scalar x, const Scalar y) {
        m_x = x ;
        m_y = y ;
    }

    void Point2Df::set(const Point2Df& position) {
        m_x = position.m_x ;
        m_y = position.m_y ;
    }

    Point2Df::operator Dimension2Df() {
        return Dimension2Df(m_x, m_y) ;
    }

    Point2Df::operator Point3Df() {
        return Point3Df(m_x, m_y, 0.f) ;
    }

    Point2Df& Point2Df::operator+=(Point2Df& other) {
        m_x += other.m_x ;
        m_y += other.m_y ;
        return *this ;
    }

    Point2Df& Point2Df::operator-=(Point2Df& other) {
        m_x -= other.m_x ;
        m_y -= other.m_y ;
        return *this ;
    }

    Point2Df& Point2Df::operator*=(const Scalar coeff) {
        m_x *= coeff ;
        m_y *= coeff ;
        return *this ;
    }

    Point2Df& Point2Df::operator/=(const Scalar coeff) {
        m_x /= coeff ;
        m_y /= coeff ;
        return *this ;
    }

    bool Point2Df::operator==(const Point2Df& other) const {
        return ((this == &other) || ((m_x == other.m_x) && (m_y == other.m_y))) ;
    }

    bool Point2Df::operator!=(const Point2Df& other) const {
        return !(*this == other) ;
    }

    Point2Df operator-(const Point2Df& p) {
        return Point2Df(-p.m_x, -p.m_y) ;
    }

    Point2Df operator+(const Point2Df& a, const Point2Df& b) {
        return Point2Df(a.m_x + b.m_x, a.m_y + b.m_y) ;
    }

    Point2Df operator-(const Point2Df& a, const Point2Df& b) {
        return Point2Df(a.m_x - b.m_x, a.m_y - b.m_y) ;
    }

    Scalar operator*(const Point2Df& a, const Point2Df& b) {
        return a.dot(b) ;
    }

    Point2Df operator*(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_x * coeff, p.m_y * coeff) ;
    }

    Point2Df operator/(const Point2Df& p, Scalar coeff) {
        return Point2Df(p.m_x / coeff, p.m_y / coeff) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point2Df& p) {
        s << "Point2Df (" << p.getX() << "," << p.getY() << ")" ;
        return s ;
    }
} ;

#endif
