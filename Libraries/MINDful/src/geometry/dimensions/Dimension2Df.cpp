#include <geometry/dimensions/Dimension2Df.h>
#include <geometry/dimensions/Dimension3Df.h>
#include <Math.h>


namespace Mind {

    Dimension2Df::Dimension2Df() : m_width(0.f), m_height(0.f) {}

    Dimension2Df::Dimension2Df(const Dimension2Df& copied) : m_width(copied.m_width),
                                                             m_height(copied.m_height) {}

    Dimension2Df::Dimension2Df(const Scalar& width,
                               const Scalar& height) : m_width(width),
                                                       m_height(height) {}

    Dimension2Df::~Dimension2Df() {}



    void Dimension2Df::absolute() {
        m_width = Math::abs(m_width) ;
        m_height = Math::abs(m_height) ;
    }


                                                                                    /*** GETTERS ***/

    Scalar Dimension2Df::getWidth() const {
        return m_width ;
    }


    Scalar Dimension2Df::getHeight() const {
        return m_height ;
    }

                                                                                    /*** SETTERS ***/

    void Dimension2Df::setWidth(const Scalar& width) {
        m_width = Math::abs(width) ;
    }


    void Dimension2Df::setHeight(const Scalar& height) {
        m_height = Math::abs(height) ;
    }


    void Dimension2Df::set(const Scalar& width, const Scalar& height) {
        m_width = Math::abs(width) ;
        m_height = Math::abs(height) ;
    }
                                                                                    /*** OPERATORS ***/

    Dimension2Df::operator Point2Df() {
        return Point2Df(m_width, m_height) ;
    }


    Dimension2Df::operator Dimension3Df() {
        return Dimension3Df(m_width, m_height, 0.f) ;
    }



    Dimension2Df& Dimension2Df::operator+=(Dimension2Df& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        return *this ;
    }


    Dimension2Df& Dimension2Df::operator-=(Dimension2Df& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;

        return *this ;
    }


    Dimension2Df& Dimension2Df::operator*=(const Scalar& coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        return *this ;
    }


    Dimension2Df& Dimension2Df::operator/=(const Scalar& coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        return *this ;
    }



    Dimension2Df& Dimension2Df::operator=(const Dimension2Df& other) {
        if (this != &other) {
            m_width = other.m_width ;
            m_height = other.m_height ;
        }

        return *this ;
    }


    bool Dimension2Df::operator==(const Dimension2Df& other) const {
        return ((this == &other) ||
                    ((m_width == other.m_width) && (m_height == other.m_height))) ;
    }


    bool Dimension2Df::operator!=(const Dimension2Df& other) const {
        return !(*this == other) ;
    }


    Dimension2Df operator+(const Dimension2Df& a, const Dimension2Df& b) {
        return Dimension2Df(
                            a.getWidth() + b.getWidth(),
                            a.getHeight() + b.getHeight()
                           ) ;
    }

    Dimension2Df operator-(const Dimension2Df& a, const Dimension2Df& b) {
        return Dimension2Df(
                            a.getWidth() - b.getWidth(),
                            a.getHeight() - b.getHeight()
                           ) ;
    }

    Dimension2Df operator*(const Dimension2Df& d, const Scalar& coeff) {
        return Dimension2Df(
                            d.getWidth() * coeff,
                            d.getHeight() * coeff
                           ) ;
    }

    Dimension2Df operator/(const Dimension2Df& d, const Scalar& coeff) {
        return Dimension2Df(
                            d.getWidth() / coeff,
                            d.getHeight() / coeff
                           ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension2Df& p) {
        s << "Dimension2Df {" <<
                                 p.getWidth() << "," <<
                                 p.getHeight() <<
                           "}" ;
        return s ;
    }

} ;
