#include <geometry/points/Point3Df.hpp>

#ifdef USE_NO_SIMD // for compilations where SSE or NEON are NOT available
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;

namespace Mind {
    Point3Df::Point3Df() : m_x(0.f), m_y(0.f), m_z(0.f) {}

    Point3Df::Point3Df(const Point3Df& copied) : m_x(copied.m_x),
                                                 m_y(copied.m_y) {}

    Point3Df::Point3Df(
        const Scalar& x,
        const Scalar& y,
        const Scalar& z
    ) : m_x(x),
        m_y(y),
        m_z(z) {}

    Point3Df::~Point3Df() {}

    void Point3Df::translate(const Scalar& x, const Scalar& y, const Scalar& z) {
        m_x += x ;
        m_y += y ;
        m_z += z ;
    }

    void Point3Df::translate(const Point3Df& offset) {
        m_x += offset.m_x ;
        m_y += offset.m_y ;
        m_z += offset.m_z ;
    }

    Scalar Point3Df::dot(const Point3Df& other) const {
        return ((m_x * other.m_x) + (m_y * other.m_y) + (m_z * other.m_z)) ;
    }

    void Point3Df::normalize() {
        Scalar lengthPoint = length() ;
        m_x /= lengthPoint ;
        m_y /= lengthPoint ;
        m_z /= lengthPoint ;
    }

    Point3Df Point3Df::merge(const Point3Df& a, const Point3Df& b) {
        return Point3Df(
            (a.m_x + b.m_x) / 2.f,
            (a.m_y + b.m_y) / 2.f,
            (a.m_z + b.m_z) / 2.f
        ) ;
    }

    Scalar Point3Df::distanceX(const Point3Df& a, const Point3Df& b) {
        return a.m_x - b.m_x ;
    }

    Scalar Point3Df::distanceY(const Point3Df& a, const Point3Df& b) {
        return a.m_y - b.m_y ;
    }

    Scalar Point3Df::distanceZ(const Point3Df& a, const Point3Df& b) {
        return a.m_z - b.m_z ;
    }

    Scalar Point3Df::distance(const Point3Df& a, const Point3Df& b) {
        Scalar diffX, diffY, diffZ ;

        diffX = a.m_x - b.m_x ;
        diffY = a.m_y - b.m_y ;
        diffZ = a.m_z - b.m_z ;

        #ifdef USE_APPROXIMATION
            return (Scalar) FastMath::sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) ;
        #else
            return (Scalar) sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ)) ;
        #endif
    }

    Scalar Point3Df::length() {
        #ifdef USE_APPROXIMATION
            return (FastMath::sqrt(this -> dot(*this)));
        #else
            return (sqrt(this -> dot(*this)));
        #endif
    }

    Scalar Point3Df::getX() const {
        return m_x ;
    }

    Scalar Point3Df::getY() const {
        return m_y ;
    }

    Scalar Point3Df::getZ() const {
        return m_z ;
    }

    Array4f& Point3Df::getCoordinates(Array4f& output) const {
        output[X] = m_x ;
        output[Y] = m_y ;
        output[Z] = m_z ;
        return output ;
    }

    void Point3Df::setX(const Scalar& x) {
        m_x = x ;
    }

    void Point3Df::setY(const Scalar& y) {
        m_y = y ;
    }

    void Point3Df::setZ(const Scalar& z) {
        m_z = z ;
    }

    void Point3Df::set(const Scalar& x, const Scalar& y, const Scalar& z) {
        m_x = x ;
        m_y = y ;
        m_z = z ;
    }

    void Point3Df::set(const Point3Df& position) {
        m_x = position.m_x ;
        m_y = position.m_y ;
        m_z = position.m_z ;
    }

    Point3Df::operator Dimension3Df() {
        return Dimension3Df(m_x, m_y, m_z) ;
    }

    Point3Df::operator Point2Df() {
        return Point2Df(m_x, m_y) ;
    }

    Point3Df& Point3Df::operator+=(Point3Df& other) {
        m_x += other.m_x ;
        m_y += other.m_y ;
        m_z += other.m_z ;
        return *this ;
    }

    Point3Df& Point3Df::operator-=(Point3Df& other) {
        m_x -= other.m_x ;
        m_y -= other.m_y ;
        m_z -= other.m_z ;
        return *this ;
    }

    Point3Df& Point3Df::operator*=(const Scalar& coeff) {
        m_x *= coeff ;
        m_y *= coeff ;
        m_z *= coeff ;
        return *this ;
    }

    Point3Df& Point3Df::operator/=(const Scalar& coeff) {
        m_x /= coeff ;
        m_y /= coeff ;
        m_z /= coeff ;
        return *this ;
    }

    Point3Df& Point3Df::operator=(const Point3Df& other) {
        if (this != &other) {
            m_x = other.m_x ;
            m_y = other.m_y ;
            m_z = other.m_z ;
        }

        return *this ;
    }

    bool Point3Df::operator==(const Point3Df& other) const {
        return ((this == &other)
                    || ((m_x == other.m_x)
                            && (m_y == other.m_y)
                            && (m_z == other.m_z))) ;
    }

    bool Point3Df::operator!=(const Point3Df& other) const {
        return !(*this == other) ;
    }

    Point3Df operator-(const Point3Df& p) {
        return Point3Df(-p.m_x, -p.m_y, -p.m_z) ;
    }

    Point3Df operator+(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_x + b.m_x, a.m_y + b.m_y, a.m_z + b.m_z) ;
    }

    Point3Df operator-(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_x - b.m_x, a.m_y - b.m_y, a.m_z - b.m_z) ;
    }

    Scalar operator*(const Point3Df& a, const Point3Df& b) {
        return a.dot(b) ;
    }

    Point3Df operator*(const Point3Df& p, const Scalar& coeff) {
        return Point3Df(p.m_x * coeff, p.m_y * coeff, p.m_z * coeff) ;
    }

    Point3Df operator/(const Point3Df& p, const Scalar& coeff) {
        return Point3Df(p.m_x / coeff, p.m_y / coeff, p.m_z / coeff) ;
    }

    std::ostream& operator<<(std::ostream& s, const Point3Df& p) {
        s << "Point3Df (" <<
                             p.getX() << "," <<
                             p.getY() << "," <<
                             p.getZ() <<
                      ")" ;
        return s ;
    }
} ;

#endif
