#include <geometry/dimensions/Dimension3Di.h>
#include <geometry/dimensions/Dimension2Di.h>
#include <Math.h>


namespace Mind {

    Dimension3Di::Dimension3Di() : m_width(0), m_height(0), m_depth(0) {}

    Dimension3Di::Dimension3Di(const Dimension3Di& copied) : m_width(copied.m_width),
                                                             m_height(copied.m_height),
                                                             m_depth(copied.m_depth) {}

    Dimension3Di::Dimension3Di(
                               const int& width,
                               const int& height,
                               const int& depth) : m_width(width),
                                                      m_height(height),
                                                      m_depth(depth) {}

    Dimension3Di::~Dimension3Di() {}


    void Dimension3Di::absolute() {
        m_width = Math::abs(m_width) ;
        m_height = Math::abs(m_height) ;
        m_depth = Math::abs(m_depth) ;
    }



                                                                                    /*** GETTERS ***/
    int Dimension3Di::getWidth() const {
        return m_width ;
    }

    int Dimension3Di::getHeight() const {
        return m_height ;
    }

    int Dimension3Di::getDepth() const {
        return m_depth ;
    }

                                                                                    /*** SETTERS ***/
    void Dimension3Di::setWidth(const int& width) {
        m_width = Math::abs(width) ;
    }

    void Dimension3Di::setHeight(const int& height) {
        m_height = Math::abs(height) ;
    }

    void Dimension3Di::setDepth(const int& depth) {
        m_depth = Math::abs(depth) ;
    }

    void Dimension3Di::set(
                           const int& width,
                           const int& height,
                           const int& depth
                          ) {
        m_width = Math::abs(width) ;
        m_height = Math::abs(height) ;
        m_depth = Math::abs(depth) ;
    }

                                                                                    /*** OPERATORS ***/
    Dimension3Di::operator Point3Di() {
        return Point3Di(m_width, m_height, m_depth) ;
    }

    Dimension3Di::operator Dimension2Di() {
        return Dimension2Di(m_width, m_height) ;
    }


    Dimension3Di& Dimension3Di::operator+=(Dimension3Di& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        m_depth += other.m_depth ;
        return *this ;
    }

    Dimension3Di& Dimension3Di::operator-=(Dimension3Di& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;
        m_depth = (other.m_depth > m_depth) ? 0 : m_depth - other.m_depth ;

        return *this ;
    }

    Dimension3Di& Dimension3Di::operator*=(const int& coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        m_depth *= coeff ;
        return *this ;
    }

    Dimension3Di& Dimension3Di::operator/=(const int& coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        m_depth /= coeff ;
        return *this ;
    }


    Dimension3Di& Dimension3Di::operator=(const Dimension3Di& other) {
        if (this != &other) {
            m_width = other.m_width ;
            m_height = other.m_height ;
            m_depth = other.m_depth ;
        }

        return *this ;
    }

    bool Dimension3Di::operator==(const Dimension3Di& other) const {
        return ((this == &other) ||
                        ((m_width == other.m_width)
                            && (m_height == other.m_height)
                            && (m_depth == other.m_depth))) ;
    }

    bool Dimension3Di::operator!=(const Dimension3Di& other) const {
        return !(*this == other) ;
    }


    Dimension3Di operator+(const Dimension3Di& a, const Dimension3Di& b) {
        return Dimension3Di(
                            a.getWidth() + b.getWidth(),
                            a.getHeight() + b.getHeight(),
                            a.getDepth() + b.getDepth()
                           ) ;
    }

    Dimension3Di operator-(const Dimension3Di& a, const Dimension3Di& b) {
        return Dimension3Di(
                            a.getWidth() - b.getWidth(),
                            a.getHeight() - b.getHeight(),
                            a.getDepth() - b.getDepth()
                           ) ;
    }

    Dimension3Di operator*(const Dimension3Di& d, const int& coeff) {
        return Dimension3Di(
                            d.getWidth() * coeff,
                            d.getHeight() * coeff,
                            d.getDepth() * coeff
                           ) ;
    }

    Dimension3Di operator/(const Dimension3Di& d, const int& coeff) {
        return Dimension3Di(
                            d.getWidth() / coeff,
                            d.getHeight() / coeff,
                            d.getDepth() / coeff
                           ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension3Di& p) {
        s << "Dimension3Di {" <<
                                 p.getWidth() << "," <<
                                 p.getHeight() << "," <<
                                 p.getDepth() <<
                           "}" ;
        return s ;
    }

} ;
