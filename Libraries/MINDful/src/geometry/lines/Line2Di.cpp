#include <geometry/lines/Line2Di.hpp>
#include <FastMath.hpp>
#include <Math.hpp>

namespace Mind {
    Line2Di::Line2Di() : m_isChanged(false) {
        m_length = 0 ;
    }

    Line2Di::Line2Di(const Line2Di& copied) : m_start(copied.m_start),
                                              m_end(copied.m_end),
                                              m_isChanged(false) {
        m_length = Point2Di::distance(m_start, m_end) ;
    }

    Line2Di::Line2Di(
        const Point2Di& start,
        const Point2Di& end
    ) : m_start(start),
        m_end(end),
        m_isChanged(false) {
        m_length = Point2Di::distance(m_start, m_end) ;
    }

    Line2Di::~Line2Di() {}

    Scalar Line2Di::length() {
        if (m_isChanged) {
            m_length = Point2Di::distance(m_start, m_end) ;
        }
        return m_length ;
    }

    Scalar Line2Di::lengthSquared() {
        if (m_isChanged) {
            m_length = Point2Di::distance(m_start, m_end) ;
        }
        return m_length * m_length ;
    }

    bool Line2Di::isContiguousTo(const Line2Di& other) {
        return ((m_start == other.m_end) || (m_end == other.m_start)) ;
    }

    char Line2Di::CCW(const Line2Di& l, const Point2Di& p) {
        // Relative expression of S and P to the start point of S.
        Line2Di l2 = relative(l) ;
        Point2Di p2 = p - l.m_start ;

        long int ccw = (p2.getX() * l2.m_end.getY()) - (p2.getY() * l2.m_end.getX()) ;
        if (ccw == 0) {
            ccw = (p2.getX() * l2.m_end.getX()) + (p2.getY() * l2.m_end.getY()) ;
            if (ccw > 0) {
                // Make P relative to the end point of S
                p2 = p - l.m_end ;
                ccw = (p2.getX() * l.m_end.getX()) + (p2.getY() * l.m_end.getY()) ;
                if (ccw < 0) ccw = 0 ;
            }
        }

        if (ccw < 0) {
            return -1 ;
        }
        else if (ccw > 0) {
            return 1 ;
        }
        else {
            return 0 ;
        }
    }

    Line2Di Line2Di::relative(const Line2Di& l) {
        return Line2Di(Point2Di(0,0), l.m_end - l.m_start) ;
    }

    bool Line2Di::intersects(const Line2Di& line) {
        if (isContiguousTo(line))
            return false ;

        bool intersection ;
        intersection = ((CCW(*this, line.m_start) * CCW(*this, line.m_end)) < 1)
                            && ((CCW(line, m_start) * CCW(line, m_end)) < 1) ;
        return intersection ;
    }

    Scalar Line2Di::distanceTo(const Point2Di& point) {
        return FastMath::sqrt(distanceSquaredTo(point)) ;
    }

    Scalar Line2Di::distanceTo(const int& x, const int& y) {
        return distanceTo(Point2Di(x, y)) ;
    }

    Scalar Line2Di::distanceSquaredTo(const Point2Di& point) {
        Point2Di relativeLine = m_end - m_start ;
        Point2Di relativePoint = point - m_start ;

        Scalar dotProduct = relativePoint * relativeLine ;
        Scalar projLengthSquared = (dotProduct * dotProduct) / (relativeLine * relativeLine) ;
        Scalar lengthSquared = (relativePoint * relativePoint) - projLengthSquared ;

        if (lengthSquared < 0)
            return 0 ;
        return lengthSquared ;
    }

    Scalar Line2Di::distanceSquaredTo(const int& x, const int& y) {
        return distanceSquaredTo(Point2Di(x, y)) ;
    }

    const Rectangle2Di Line2Di::getBounds() const {
        return Rectangle2Di(m_start, m_end) ;
    }

    const Point2Di& Line2Di::getStartPoint() const {
        return m_start ;
    }

    const Point2Di& Line2Di::getEndPoint() const {
        return m_end ;
    }

    int Line2Di::getStartX() const {
        return m_start.getX() ;
    }

    int Line2Di::getStartY() const {
        return m_start.getY() ;
    }

    int Line2Di::getEndX() const {
        return m_end.getX() ;
    }

    int Line2Di::getEndY() const {
        return m_end.getY() ;
    }

    bool Line2Di::isEmpty() const {
        return ((m_start.getX() - m_end.getX() == 0)
                    && (m_start.getY() - m_end.getY() == 0)) ;
    }

    Line2Di& Line2Di::operator=(const Line2Di& other) {
        if (this != &other) {
            m_start = other.m_start ;
            m_end = other.m_end ;
            m_isChanged = true ;
        }

        return *this ;
    }

    bool Line2Di::operator==(const Line2Di& other) const {
        return ((this == &other)
                    || ((m_start == other.m_start) && (m_end == other.m_end))) ;
    }

    bool Line2Di::operator!=(const Line2Di& other) const {
        return !(*this == other) ;
    }

    std::ostream& operator<<(std::ostream& s, const Line2Di& l) {
        s << "Line2Di ("
                         << l.getStartPoint()
                         << " | "
                         << l.getEndPoint()
                         << ")" << std::endl ;
        return s ;
    }
} ;
