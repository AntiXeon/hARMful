#include <geometry/points/Point3Df.hpp>

#ifdef USE_SIMD // for compilations where SSE or NEON are available
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;

namespace Mind {
    Point3Df::Point3Df() {
        m_values = SIMD::Vector4f(0.f, 0.f, 0.f, 0.f) ;
    }

    Point3Df::Point3Df(const SIMD::Vector4f& values) : m_values(values) {}

    Point3Df::Point3Df(const Scalar x, const Scalar y, const Scalar z) {
       m_values = SIMD::Vector4f(x, y, z, 0.f) ;
    }

    void Point3Df::translate(const Scalar x, const Scalar y, const Scalar z) {
        m_values += SIMD::Vector4f(x, y, z, 0.f) ;
    }

    void Point3Df::translate(const Point3Df& offset) {
        m_values += offset.m_values ;
    }

    Scalar Point3Df::dot(const Point3Df& other) const {
        return m_values.dot(other.m_values) ;
    }

    Point3Df Point3Df::cross(const Point3Df& other) const {
        return m_values.cross(other.m_values) ;
    }

    void Point3Df::normalize() {
        m_values /= length() ;
    }

    Point3Df Point3Df::merge(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f middle = (a.m_values + b.m_values) / 2.f ;
        return Point3Df(middle) ;
    }

    Scalar Point3Df::distanceX(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        float* diffValues = (float*) diff ;
        return std::fabs(diffValues[X]) ;
    }

    Scalar Point3Df::distanceY(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        float* diffValues = (float*) diff ;
        return std::fabs(diffValues[Y]) ;
    }

    Scalar Point3Df::distanceZ(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        float* diffValues = (float*) diff ;
        return std::fabs(diffValues[Z]) ;
    }

    Scalar Point3Df::distance(const Point3Df& a, const Point3Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        diff.squared() ;
        Scalar dot = diff.horizontalAdd() ;
        return FastMath::sqrt(dot) ;
    }

    Scalar Point3Df::length() {
        return FastMath::sqrt(this -> dot(*this)) ;
    }

    Scalar Point3Df::getX() const {
        return ((float*)m_values)[X] ;
    }

    Scalar Point3Df::getY() const {
        return ((float*)m_values)[Y] ;
    }

    Scalar Point3Df::getZ() const {
        return ((float*)m_values)[Z] ;
    }

    Array4f& Point3Df::getCoordinates(Array4f& output) const {
        m_values.get(output) ;
        return output ;
    }

    void Point3Df::setX(const Scalar x) {
        ((float*)m_values)[X] = x ;
    }

    void Point3Df::setY(const Scalar y) {
        ((float*)m_values)[Y] = y ;
    }

    void Point3Df::setZ(const Scalar z) {
        ((float*)m_values)[Z] = z ;
    }

    void Point3Df::set(const Scalar x, const Scalar y, const Scalar z) {
        ((float*)m_values)[X] = x ;
        ((float*)m_values)[Y] = y ;
        ((float*)m_values)[Z] = z ;
    }

    void Point3Df::set(const Point3Df& position) {
        m_values = position.m_values ;
    }

    Point3Df::operator Dimension3Df() {
        float* values = (float*) m_values ;
        return Dimension3Df(values[X], values[Y], values[Z]) ;
    }

    Point3Df::operator Point2Df() {
        float* values = (float*) m_values ;
        return Point2Df(values[X], values[Y]) ;
    }

    Point3Df& Point3Df::operator+=(Point3Df& other) {
        m_values += other.m_values ;
        return *this ;
    }

    Point3Df& Point3Df::operator-=(Point3Df& other) {
        m_values -= other.m_values ;
        return *this ;
    }

    Point3Df& Point3Df::operator*=(const Scalar coeff) {
        m_values *= coeff ;
        return *this ;
    }

    Point3Df& Point3Df::operator/=(const Scalar coeff) {
        m_values /= coeff ;
        return *this ;
    }

    bool Point3Df::operator==(const Point3Df& other) const {
        if (this != &other) {
            SIMD::Vector4i::Mask equals = (SIMD::Vector4i::Mask) (m_values == other.m_values) ;
            return ((equals.get(X) != 0) && (equals.get(Y) != 0)) ;
        }

        return true ;
    }

    bool Point3Df::operator!=(const Point3Df& other) const {
        return !(*this == other) ;
    }

    Point3Df operator-(const Point3Df& p) {
        return Point3Df(-p.m_values) ;
    }

    Point3Df operator+(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_values + b.m_values) ;
    }

    Point3Df operator-(const Point3Df& a, const Point3Df& b) {
        return Point3Df(a.m_values - b.m_values) ;
    }

    Scalar operator*(const Point3Df& a, const Point3Df& b) {
        return a.dot(b) ;
    }

    Point3Df operator*(const Point3Df& p, const Scalar coeff) {
        return Point3Df(p.m_values * coeff) ;
    }

    Point3Df operator/(const Point3Df& p, const Scalar coeff) {
        return Point3Df(p.m_values / coeff) ;
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
