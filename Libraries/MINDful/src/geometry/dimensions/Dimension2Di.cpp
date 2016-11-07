#include <geometry/dimensions/Dimension2Di.h>
#include <geometry/dimensions/Dimension3Di.h>
#include <Math.h>


namespace Mind {

    Dimension2Di::Dimension2Di() : m_width(0), m_height(0) {}

    Dimension2Di::Dimension2Di(const Dimension2Di& copied) : m_width(copied.m_width),
                                                             m_height(copied.m_height) {}

    Dimension2Di::Dimension2Di(const int& width,
                               const int& height) : m_width(width),
                                                    m_height(height) {}

    Dimension2Di::~Dimension2Di() {}



    void Dimension2Di::absolute() {
        m_width = Math::abs(m_width) ;
        m_height = Math::abs(m_height) ;
    }


                                                                                    /*** GETTERS ***/

    int Dimension2Di::getWidth() const {
        return m_width ;
    }


    int Dimension2Di::getHeight() const {
        return m_height ;
    }

                                                                                    /*** SETTERS ***/

    void Dimension2Di::setWidth(const int& width) {
        m_width = Math::abs(width) ;
    }


    void Dimension2Di::setHeight(const int& height) {
        m_height = Math::abs(height) ;
    }


    void Dimension2Di::set(const int& width, const int& height) {
        m_width = Math::abs(width) ;
        m_height = Math::abs(height) ;
    }
                                                                                    /*** OPERATORS ***/

    Dimension2Di::operator Point2Di() {
        return Point2Di(m_width, m_height) ;
    }


    Dimension2Di::operator Dimension3Di() {
        return Dimension3Di(m_width, m_height, 0) ;
    }



    Dimension2Di& Dimension2Di::operator+=(Dimension2Di& other) {
        m_width += other.m_width ;
        m_height += other.m_height ;
        return *this ;
    }


    Dimension2Di& Dimension2Di::operator-=(Dimension2Di& other) {
        m_width = (other.m_width > m_width) ? 0 : m_width - other.m_width ;
        m_height = (other.m_height > m_height) ? 0 : m_height - other.m_height ;

        return *this ;
    }


    Dimension2Di& Dimension2Di::operator*=(const int& coeff) {
        m_width *= coeff ;
        m_height *= coeff ;
        return *this ;
    }


    Dimension2Di& Dimension2Di::operator/=(const int& coeff) {
        m_width /= coeff ;
        m_height /= coeff ;
        return *this ;
    }



    Dimension2Di& Dimension2Di::operator=(const Dimension2Di& other) {
        if (this != &other) {
            m_width = other.m_width ;
            m_height = other.m_height ;
        }

        return *this ;
    }


    bool Dimension2Di::operator==(const Dimension2Di& other) const {
        return ((this == &other) ||
                    ((m_width == other.m_width) && (m_height == other.m_height))) ;
    }


    bool Dimension2Di::operator!=(const Dimension2Di& other) const {
        return !(*this == other) ;
    }


    Dimension2Di operator+(const Dimension2Di& a, const Dimension2Di& b) {
        return Dimension2Di(
                            a.getWidth() + b.getWidth(),
                            a.getHeight() + b.getHeight()
                           ) ;
    }

    Dimension2Di operator-(const Dimension2Di& a, const Dimension2Di& b) {
        return Dimension2Di(
                            a.getWidth() - b.getWidth(),
                            a.getHeight() - b.getHeight()
                           ) ;
    }

    Dimension2Di operator*(const Dimension2Di& d, const int& coeff) {
        return Dimension2Di(
                            d.getWidth() * coeff,
                            d.getHeight() * coeff
                           ) ;
    }

    Dimension2Di operator/(const Dimension2Di& d, const int& coeff) {
        return Dimension2Di(
                            d.getWidth() / coeff,
                            d.getHeight() / coeff
                           ) ;
    }

    std::ostream& operator<<(std::ostream& s, const Dimension2Di& p) {
        s << "Dimension2Di {" <<
                                 p.getWidth() << "," <<
                                 p.getHeight() <<
                           "}" ;
        return s ;
    }

} ;
