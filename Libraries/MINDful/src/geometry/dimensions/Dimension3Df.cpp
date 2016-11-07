#include <geometry/dimensions/Dimension3Df.h>
#include <geometry/dimensions/Dimension2Df.h>
#include <Math.h>


namespace Mind {

    Dimension3Df::Dimension3Df() : m_width(0), m_height(0), m_depth(0) {}

    Dimension3Df::Dimension3Df(const Dimension3Df& copied) : m_width(copied.m_width),
                                                             m_height(copied.m_height),
                                                             m_depth(copied.m_depth) {}

    Dimension3Df::Dimension3Df(
                               const Scalar& width,
                               const Scalar& height,
                               const Scalar& depth) : m_width(width),
                                                      m_height(height),
                                                      m_depth(depth) {}

    Dimension3Df::~Dimension3Df() {}


    void Dimension3Df::absolute() {
        m_width = Math::abs(m_width) ;
        m_height = Math::abs(m_height) ;
        m_depth = Math::abs(m_depth) ;
    }



                                                                                    /*** GETTERS ***/
    Scalar Dimension3Df::getWidth() const {
        return m_width ;
    }

    Scalar Dimension3Df::getHeight() const {
        return m_height ;
    }

    Scalar Dimension3Df::getDepth() const {
        return m_depth ;
    }

                                                                                    /*** SETTERS ***/
    void Dimension3Df::setWidth(const Scalar& width) {
        m_width = Math::abs(width) ;
    }

    void Dimension3Df::setHeight(const Scalar& height) {
        m_height = Math::abs(height) ;
    }

    void Dimension3Df::setDepth(const Scalar& depth) {
        m_depth = Math::abs(depth) ;
    }

    void Dimension3Df::set(
                           const Scalar& width,
                           const Scalar& height,
                           const Scalar& depth
                          ) {
        m_width = Math::abs(width) ;
        m_height = Math::abs(height) ;
        m_depth = Math::abs(depth) ;
    }

                                                                                    /*** OPERATORS ***/
    Dimension3Df::operator Point3Df() {
        return Point3Df(m_width, m_height, m_depth) ;
    }

    Dimension3Df::operator Dimension2Df() {
        return Dimension2Df(m_width, m_height) ;
    }


    Dimension3Df& Dimension3Df::operator+=(Dimension3Df& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        m_depth += other.m_depth ;
        return *this ;
    }

    Dimension3Df& Dimension3Df::operator-=(Dimension3Df& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;
        m_depth = (other.m_depth > m_depth) ? 0 : m_depth - other.m_depth ;

        return *this ;
    }

    Dimension3Df& Dimension3Df::operator*=(const Scalar& coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        m_depth *= coeff ;
        return *this ;
    }

    Dimension3Df& Dimension3Df::operator/=(const Scalar& coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        m_depth /= coeff ;
        return *this ;
    }


    Dimension3Df& Dimension3Df::operator=(const Dimension3Df& other) {
        if (this != &other) {
            m_width = other.m_width ;
            m_height = other.m_height ;
            m_depth = other.m_depth ;
        }

        return *this ;
    }

    bool Dimension3Df::operator==(const Dimension3Df& other) const {
        return ((this == &other) ||
                        ((m_width == other.m_width)
                            && (m_height == other.m_height)
                            && (m_depth == other.m_depth))) ;
    }

    bool Dimension3Df::operator!=(const Dimension3Df& other) const {
        return !(*this == other) ;
    }


    Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) {
        return Dimension3Df(
                            a.getWidth() + b.getWidth(),
                            a.getHeight() + b.getHeight(),
                            a.getDepth() + b.getDepth()
                           ) ;
    }

    Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) {
        return Dimension3Df(
                            a.getWidth() - b.getWidth(),
                            a.getHeight() - b.getHeight(),
                            a.getDepth() - b.getDepth()
                           ) ;
    }

    Dimension3Df operator*(const Dimension3Df& d, const Scalar& coeff) {
        return Dimension3Df(
                            d.getWidth() * coeff,
                            d.getHeight() * coeff,
                            d.getDepth() * coeff
                           ) ;
    }

    Dimension3Df operator/(const Dimension3Df& d, const Scalar& coeff) {
        return Dimension3Df(
                            d.getWidth() / coeff,
                            d.getHeight() / coeff,
                            d.getDepth() / coeff
                           ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) {
        s << "Dimension3Df {" <<
                                 p.getWidth() << "," <<
                                 p.getHeight() << "," <<
                                 p.getDepth() <<
                           "}" ;
        return s ;
    }

} ;
