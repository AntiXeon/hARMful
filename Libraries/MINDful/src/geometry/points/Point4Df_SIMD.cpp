#include <geometry/points/Point4Df.hpp>

#ifdef USE_SIMD // for compilations where SSE or NEON are available
#include <FastMath.hpp>
#include <Math.hpp>

const int X = 0 ;
const int Y = 1 ;
const int Z = 2 ;
const int W = 3 ;

namespace Mind {
    Point4Df::Point4Df() {
        m_values = SIMD::Vector4f(0.f, 0.f, 0.f, 0.f) ;
    }

    Point4Df::Point4Df(const SIMD::Vector4f& values) : m_values(values) {}

    Point4Df::Point4Df(
        const Scalar x,
        const Scalar y,
        const Scalar z,
        const Scalar w
    ) {
       m_values = SIMD::Vector4f(x, y, z, w) ;
    }

    void Point4Df::translate(
        const Scalar x,
        const Scalar y,
        const Scalar z,
        const Scalar w
    ) {
        m_values += SIMD::Vector4f(x, y, z, w) ;
    }

    void Point4Df::translate(const Point4Df& offset) {
        m_values += offset.m_values ;
    }

    Scalar Point4Df::dot(const Point4Df& other) const {
        return m_values.dot(other.m_values) ;
    }

    Point4Df Point4Df::cross(const Point4Df& other) const {
        return m_values.cross(other.m_values) ;
    }

    void Point4Df::normalize() {
        m_values /= length() ;
    }

    Point4Df Point4Df::merge(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f middle = (a.m_values + b.m_values) / 2.f ;
        return Point4Df(middle) ;
    }

    Point4Df Point4Df::mul(const Point4Df& p, const Point4Df& other) {
        return Point4Df(p.m_values * other.m_values) ;
    }

    Scalar Point4Df::distanceX(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[X]) ;
    }

    Scalar Point4Df::distanceY(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[Y]) ;
    }

    Scalar Point4Df::distanceZ(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[Z]) ;
    }

    Scalar Point4Df::distanceW(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        return std::fabs(diff[W]) ;
    }

    Scalar Point4Df::distance(const Point4Df& a, const Point4Df& b) {
        SIMD::Vector4f diff = a.m_values - b.m_values ;
        diff.squared() ;
        Scalar dot = diff.horizontalAdd() ;
        return FastMath::sqrt(dot) ;
    }

    Scalar Point4Df::length() {
        return FastMath::sqrt(this -> dot(*this)) ;
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
        m_values[X] = x ;
        m_values[Y] = y ;
        m_values[Z] = z ;
        m_values[W] = w ;
    }

    void Point4Df::set(const Point4Df& position) {
        m_values = position.m_values ;
    }

    std::array<float, 4> Point4Df::toArray() {
        return {m_values[0], m_values[1], m_values[2], m_values[3]} ;
    }

    Point4Df::operator Dimension2Df() {
        return Dimension2Df(m_values[X], m_values[Y]) ;
    }

    Point4Df::operator Dimension3Df() {
        return Dimension3Df(m_values[X], m_values[Y], m_values[Z]) ;
    }

    Point4Df::operator Point2Df() {
        return Point2Df(m_values[X], m_values[Y]) ;
    }

    Point4Df::operator Point3Df() {
        return Point3Df(m_values[X], m_values[Y], m_values[Z]) ;
    }

    Point4Df& Point4Df::operator+=(Point4Df& other) {
        m_values += other.m_values ;
        return *this ;
    }

    Point4Df& Point4Df::operator-=(Point4Df& other) {
        m_values -= other.m_values ;
        return *this ;
    }

    Point4Df& Point4Df::operator*=(const Scalar coeff) {
        m_values *= coeff ;
        return *this ;
    }

    Point4Df& Point4Df::operator/=(const Scalar coeff) {
        m_values /= coeff ;
        return *this ;
    }

    bool Point4Df::operator==(const Point4Df& other) const {
        if (this != &other) {
            SIMD::Vector4i::Mask equals = (SIMD::Vector4i::Mask) (m_values == other.m_values) ;
            return (
                        (equals.get(X) != 0)
                        && (equals.get(Y) != 0)
                        && (equals.get(Z) != 0)
                        && (equals.get(W) != 0)
                    ) ;
        }

        return true ;
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
        return Point4Df(-p.m_values) ;
    }

    Point4Df operator+(const Point4Df& a, const Point4Df& b) {
        return Point4Df(a.m_values + b.m_values) ;
    }

    Point4Df operator-(const Point4Df& a, const Point4Df& b) {
        return Point4Df(a.m_values - b.m_values) ;
    }

    Scalar operator*(const Point4Df& a, const Point4Df& b) {
        return a.dot(b) ;
    }

    Point4Df operator*(const Point4Df& p, const Scalar coeff) {
        return Point4Df(p.m_values * coeff) ;
    }

    Point4Df operator/(const Point4Df& p, const Scalar coeff) {
        return Point4Df(p.m_values / coeff) ;
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
