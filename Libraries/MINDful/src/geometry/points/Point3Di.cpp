#include <geometry/points/Point3Di.h>
#include <FastMath.h>
#include <math.h>


namespace Mind {

    Point3Di::Point3Di() : m_x(0),
                           m_y(0),
                           m_z(0) {}

    Point3Di::Point3Di(const Point3Di& copied) : m_x(copied.m_x),
                                                 m_y(copied.m_y),
                                                 m_z(copied.m_z) {}

    Point3Di::Point3Di(const int& x, const int& y, const int& z) : m_x(x),
                                                                   m_y(y),
                                                                   m_z(z) {}

    Point3Di::~Point3Di() {}


                                                             /*** UTILITIES ***/
    void Point3Di::translate(const int& x, const int& y, const int& z) {
        m_x += x ;
        m_y += y ;
        m_z += z ;
    }

    void Point3Di::translate(const Point3Di& offset) {
        m_x += offset.m_x ;
        m_y += offset.m_y ;
        m_z += offset.m_z ;
    }

    Scalar Point3Di::dot(const Point3Di& other) const {
        return ((m_x * other.m_x) + (m_y * other.m_y) + (m_z * other.m_z)) ;
    }

    Point3Di Point3Di::cross(const Point3Di& other) const {
        return Point3Di(
                        (m_y * other.m_z) - (m_z * other.m_y),
                        (m_z * other.m_x) - (m_x * other.m_z),
                        (m_x * other.m_y) - (m_y * other.m_x)
                       ) ;
    }

    void Point3Di::normalize() {
        int max ;
        if (m_x > m_y) {
            if (m_x > m_z) max = m_x ;
            else max = m_z ;
        }
        else {
            if (m_y > m_z) max = m_y ;
            else max = m_z ;
        }

        m_x /= max ;
        m_y /= max ;
        m_z /= max ;
    }

    Point3Di Point3Di::merge(const Point3Di& a, const Point3Di& b) {
        return Point3Di(
                        (a.m_x + b.m_x) / 2,
                        (a.m_y + b.m_y) / 2,
                        (a.m_z + b.m_z) / 2
                        ) ;
    }

    int Point3Di::distanceX(const Point3Di& a, const Point3Di& b) {
        return a.m_x - b.m_x ;
    }

    int Point3Di::distanceY(const Point3Di& a, const Point3Di& b) {
        return a.m_y - b.m_y ;
    }

    int Point3Di::distanceZ(const Point3Di& a, const Point3Di& b) {
        return a.m_z - b.m_z ;
    }

    Scalar Point3Di::distance(const Point3Di& a, const Point3Di& b) {
        int diffX, diffY, diffZ ;

        diffX = a.m_x - b.m_x ;
        diffY = a.m_y - b.m_y ;
        diffZ = a.m_z - b.m_z ;

        long int squaredDiff = (diffX * diffX) +
                                    (diffY * diffY) +
                                    (diffZ * diffZ) ;
        return FastMath::sqrt(squaredDiff) ;
    }

    Scalar Point3Di::length() {
        long int dot = (m_x * m_x) + (m_y * m_y) + (m_z * m_z) ;
        return FastMath::sqrt(dot) ;
    }


                                                               /*** GETTERS ***/
    int Point3Di::getX() const {
        return m_x ;
    }

    int Point3Di::getY() const {
        return m_y ;
    }

    int Point3Di::getZ() const {
        return m_z ;
    }


                                                               /*** SETTERS ***/
    void Point3Di::setX(const int& x) {
        m_x = x ;
    }

    void Point3Di::setY(const int& y) {
        m_y = y ;
    }

    void Point3Di::setZ(const int& z) {
        m_z = z ;
    }

    void Point3Di::set(const int& x, const int& y, const int& z) {
        m_x = x ;
        m_y = y ;
        m_z = z ;
    }

    void Point3Di::set(const Point3Di& position) {
        m_x = position.m_x ;
        m_y = position.m_y ;
        m_z = position.m_z ;
    }


                                                             /*** OPERATORS ***/
    Point3Di::operator Dimension3Di() {
        return Dimension3Di(m_x, m_y, m_z) ;
    }

    Point3Di::operator Point2Di() {
        return Point2Di(m_x, m_y) ;
    }


    Point3Di& Point3Di::operator+=(Point3Di& other) {
        m_x += other.m_x ;
        m_y += other.m_y ;
        m_z += other.m_z ;
        return *this ;
    }

    Point3Di& Point3Di::operator-=(Point3Di& other) {
        m_x -= other.m_x ;
        m_y -= other.m_y ;
        m_z -= other.m_z ;
        return *this ;
    }

    Point3Di& Point3Di::operator*=(const int& coeff) {
        m_x *= coeff ;
        m_y *= coeff ;
        m_z *= coeff ;
        return *this ;
    }

    Point3Di& Point3Di::operator/=(const int& coeff) {
        m_x /= coeff ;
        m_y /= coeff ;
        m_z /= coeff ;
        return *this ;
    }


    Point3Di& Point3Di::operator=(const Point3Di& other) {
        if (this != &other) {
            m_x = other.m_x ;
            m_y = other.m_y ;
            m_z = other.m_z ;
        }

        return *this ;
    }

    bool Point3Di::operator==(const Point3Di& other) const {
        return ((this == &other)
                    || ((m_x == other.m_x)
                            && (m_y == other.m_y)
                            && (m_z == other.m_z))) ;
    }

    bool Point3Di::operator!=(const Point3Di& other) const {
        return !(*this == other) ;
    }




                                                                /** NEGATION **/
    Point3Di operator-(const Point3Di& a) {
        return Point3Di(-a.getX(), -a.getY(), -a.getZ()) ;
    }

                                                               /** ADDITIONS **/
    Point3Di operator+(const Point3Di& a, const Point3Di& b) {
        return Point3Di(
                        a.getX() + b.getX(),
                        a.getY() + b.getY(),
                        a.getZ() + b.getZ()
                       ) ;
    }


                                                           /** SUBSTRACTIONS **/
    Point3Di operator-(const Point3Di& a, const Point3Di& b) {
        return Point3Di(
                        a.getX() - b.getX(),
                        a.getY() - b.getY(),
                        a.getZ() - b.getZ()
                       ) ;
    }


                                            /** PRODUCTS and MULTIPLICATIONS **/
    int operator*(const Point3Di& a, const Point3Di& b) {
        return a.dot(b) ;
    }

    Point3Di operator*(const Point3Di& p, const int& coeff) {
        return Point3Di(
                        p.getX() * coeff,
                        p.getY() * coeff,
                        p.getZ() * coeff
                       ) ;
    }


                                                               /** DIVISIONS **/
    Point3Di operator/(const Point3Di& p, const int& coeff) {
        return Point3Di(
                        p.getX() / coeff,
                        p.getY() / coeff,
                        p.getZ() / coeff
                       ) ;
    }


                                                                 /** STREAMS **/
    std::ostream& operator<<(std::ostream& s, const Point3Di& p) {
        s << "Point3Di (" <<
                             p.getX() << "," <<
                             p.getY() << "," <<
                             p.getZ() <<
                      ")" ;
        return s ;
    }

} ;
