#include <geometry/points/Point2Di.h>
#include <geometry/lines/Line2Di.h>
#include <FastMath.h>
#include <Math.h>


namespace Mind {


    Point2Di::Point2Di() : m_x(0),
                           m_y(0) {}

    Point2Di::Point2Di(const Point2Di& copied) : m_x(copied.m_x),
                                                 m_y(copied.m_y) {}

    Point2Di::Point2Di(const int& x, const int& y) : m_x(x),
                                                     m_y(y) {}

    Point2Di::~Point2Di() {}


                                                             /*** UTILITIES ***/
    void Point2Di::translate(const int& x, const int& y) {
        m_x += x ;
        m_y += y ;
    }

    void Point2Di::translate(const Point2Di& offset) {
        m_x += offset.m_x ;
        m_y += offset.m_y ;
    }

    int Point2Di::dot(const Point2Di& other) const {
        return ((m_x * other.m_x) + (m_y * other.m_y)) ;
    }

    void Point2Di::normalize() {
        int max = (m_x > m_y) ? m_x : m_y ;
        m_x /= max ;
        m_y /= max ;
    }

    Point2Di Point2Di::merge(const Point2Di& a, const Point2Di& b) {
        return Point2Di(
                        (a.m_x + b.m_x) / 2,
                        (a.m_y + b.m_y) / 2
                       ) ;
    }

    int Point2Di::distanceX(const Point2Di& a, const Point2Di& b) {
        return a.m_x - b.m_x ;
    }

    int Point2Di::distanceY(const Point2Di& a, const Point2Di& b) {
        return a.m_y - b.m_y ;
    }


    Scalar Point2Di::distance(const Point2Di& a, const Point2Di& b) {
        int aX = a.getX() ;
        int aY = a.getY() ;
        int bX = b.getX() ;
        int bY = b.getY() ;

        if (aX == bX)
            return Math::abs(bY - aY) ;
        else if (aY == bY)
            return Math::abs(bX - aX) ;
        else
            return Math::hypot(Math::abs(bX - aX), Math::abs(bY - aY)) ;
    }

    Scalar Point2Di::length() {
        long int dot = (m_x * m_x) + (m_y * m_y) ;
        return FastMath::sqrt(dot) ;
    }

    Scalar Point2Di::angle(const Point2Di& b,
                           const Point2Di& c,
                           const Point2Di& d) {
        // Line between B and C
        Line2Di b_side(b, c) ;
        // Line between B and D
        Line2Di c_side(b, d) ;
        // Line between C and D
        Line2Di d_side(c, d) ;

        double angle = (b_side.lengthSquared() +
                            d_side.lengthSquared() -
                            c_side.lengthSquared()) / (2 *
                                                        b_side.length() *
                                                        d_side.length()) ;

        return Math::to_degree(acos(angle)) ;
    }


    int Point2Di::angleOrientation(const Point2Di& a,
                                   const Point2Di& b,
                                   const Point2Di& c) {
        Point2Di relativeAToB = a - b ;
        Point2Di relativeCToB = c - b ;
        return ((relativeAToB.m_x * relativeCToB.m_y) -
                        (relativeCToB.m_x * relativeAToB.m_y)) ;
    }


                                                               /*** GETTERS ***/
    int Point2Di::getX() const {
        return m_x ;
    }

    int Point2Di::getY() const {
        return m_y ;
    }


                                                               /*** SETTERS ***/

    void Point2Di::setX(const int& x) {
        m_x = x ;
    }


    void Point2Di::setY(const int& y) {
        m_y = y ;
    }


    void Point2Di::set(const int& x, const int& y) {
        m_x = x ;
        m_y = y ;
    }

    void Point2Di::set(const Point2Di& position) {
        m_x = position.m_x ;
        m_y = position.m_y ;
    }


                                                             /*** OPERATORS ***/
    Point2Di::operator Dimension2Di() {
        return Dimension2Di(m_x, m_y) ;
    }

    Point2Di::operator Point3Di() {
        return Point3Di(m_x, m_y, 0) ;
    }

    Point2Di& Point2Di::operator+=(Point2Di& other) {
        m_x += other.m_x ;
        m_y += other.m_y ;
        return *this ;
    }

    Point2Di& Point2Di::operator-=(Point2Di& other) {
        m_x -= other.m_x ;
        m_y -= other.m_y ;
        return *this ;
    }

    Point2Di& Point2Di::operator*=(const int& coeff) {
        m_x *= coeff ;
        m_y *= coeff ;
        return *this ;
    }

    Point2Di& Point2Di::operator/=(const int& coeff) {
        m_x /= coeff ;
        m_y /= coeff ;
        return *this ;
    }


    Point2Di& Point2Di::operator=(const Point2Di& other) {
        if (this != &other) {
            m_x = other.m_x ;
            m_y = other.m_y ;
        }

        return *this ;
    }


    bool Point2Di::operator==(const Point2Di& other) const {
        return ((this == &other) || ((m_x == other.m_x) && (m_y == other.m_y))) ;
    }


    bool Point2Di::operator!=(const Point2Di& other) const {
        return !(*this == other) ;
    }



                                                                /** NEGATION **/
    Point2Di operator-(const Point2Di& a) {
        return Point2Di(-a.getX(), -a.getY()) ;
    }

                                                               /** ADDITIONS **/
    Point2Di operator+(const Point2Di& a, const Point2Di& b) {
        return Point2Di(a.getX() + b.getX(), a.getY() + b.getY()) ;
    }


                                                           /** SUBSTRACTIONS **/
    Point2Di operator-(const Point2Di& a, const Point2Di& b) {
        return Point2Di(a.getX() - b.getX(), a.getY() - b.getY()) ;
    }


                                            /** PRODUCTS and MULTIPLICATIONS **/
    int operator*(const Point2Di& a, const Point2Di& b) {
        return a.dot(b) ;
    }

    Point2Di operator*(const Point2Di& p, const int& coeff) {
        return Point2Di(p.getX() * coeff, p.getY() * coeff) ;
    }


                                                               /** DIVISIONS **/
    Point2Di operator/(const Point2Di& p, const int& coeff) {
        return Point2Di(p.getX() / coeff, p.getY() / coeff) ;
    }


                                                                 /** STREAMS **/
    std::ostream& operator<<(std::ostream& s, const Point2Di& p) {
        s << "Point2Di (" << p.getX() << "," << p.getY() << ")" ;
        return s ;
    }

} ;
