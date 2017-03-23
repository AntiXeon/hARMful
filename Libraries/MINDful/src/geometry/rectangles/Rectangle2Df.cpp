#include <geometry/rectangles/Rectangle2Df.hpp>
#include <Math.hpp>
#include <algorithm>

namespace Mind {
    Rectangle2Df::Rectangle2Df() : Rectangle2Df(0.f, 0.f, 0.f, 0.f, false) {}

    Rectangle2Df::Rectangle2Df(
        const Point2Df& location,
        const Dimension2Df& size,
        const bool centered
    ) : Rectangle2Df(
            location.getX(),
            location.getY(),
            size.getWidth(),
            size.getHeight(),
            centered
        ) {}

    Rectangle2Df::Rectangle2Df(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h,
        const bool centered
    ) : m_isCentered(centered),
        m_hasChanged(true),
        m_size(w, h)
    {
        m_size = Dimension2Df(w, h) ;

        if (centered) {
            Scalar halfWidth = w / 2.f ;
            Scalar halfHeight = h / 2.f ;
            m_bottomLeftCorner = Point2Df(x - halfWidth, y - halfHeight) ;
        }
        else {
            m_bottomLeftCorner = Point2Df(x, y) ;
        }

        computeMaxPoint() ;
    }

    Rectangle2Df::Rectangle2Df(
        const Point2Df& p1,
        const Point2Df& p2
    ) : Rectangle2Df(
            p1.getX(),
            p1.getY(),
            p2.getX(),
            p2.getY()
        ) {}

    Rectangle2Df::Rectangle2Df(
        const Scalar x1,
        const Scalar y1,
        const Scalar x2,
        const Scalar y2
    ) : m_isCentered(false),
        m_hasChanged(false) {
        std::pair<Scalar, Scalar> minMax_X = std::minmax(x1, x2) ;
        std::pair<Scalar, Scalar> minMax_Y = std::minmax(y1, y2) ;

        m_bottomLeftCorner = Point2Df(minMax_X.first, minMax_Y.first) ;
        m_upRightCorner = Point2Df(minMax_X.second, minMax_Y.second) ;
        // m_upRightCorner = Point2Df(minMax_X.second, minMax_Y.first) ;
        m_size = Dimension2Df(minMax_X.second - minMax_X.first,
                                minMax_Y.second - minMax_Y.first) ;
    }

    void Rectangle2Df::translate(
        const Scalar x,
        const Scalar y
    ) {
        setAt(m_bottomLeftCorner.getX() + x, m_bottomLeftCorner.getY() + y) ;
    }

    bool Rectangle2Df::contains(
        const Scalar x,
        const Scalar y
    ) {
        computeMaxPoint() ;
        return ((x >= m_bottomLeftCorner.getX()) && (x <= m_upRightCorner.getX())
                    && (y >= m_bottomLeftCorner.getY()) && (y <= m_upRightCorner.getY())) ;
    }

    bool Rectangle2Df::contains(const Point2Df& point) {
        computeMaxPoint() ;

        Scalar x = point.getX() ;
        Scalar y = point.getY() ;
        return (
                ((x >= getBottomLeftCornerX()) && (x <= getUpRightCornerX()))
                 &&
                ((y >= getBottomLeftCornerY()) && (y <= getUpRightCornerY()))
               ) ;
    }

    bool Rectangle2Df::contains(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h
    ) {
        Scalar x2 = x + w ;
        Scalar y2 = y + h ;
        return (contains(x, y) && contains(x2, y2)) ;
    }

    bool Rectangle2Df::contains(Rectangle2Df& boundaries) {
        return contains(
            boundaries.getBottomLeftCornerX(),
            boundaries.getBottomLeftCornerY(),
            boundaries.getWidth(),
            boundaries.getHeight()
        ) ;
    }

    bool Rectangle2Df::intersects(
        const Scalar x,
        const Scalar y,
        const Scalar w,
        const Scalar h
    ) {
        if (isEmpty() || ((w == 0.f) || (h == 0.f))) {
            return false ;
        }

        Scalar xThis = getBottomLeftCornerX() ;
        Scalar yThis = getBottomLeftCornerY() ;
        Scalar x2This = getUpRightCornerX() ;
        Scalar y2This = getUpRightCornerY() ;

        return (
                ((x + w) > xThis)
                    && ((y + h) > yThis)
                    && (x < x2This)
                    && (y < y2This)
               ) ;
    }

    bool Rectangle2Df::intersects(const Line2Df& line) {
        Scalar x = std::min(line.getStartX(), line.getEndX()) ;
        Scalar y = std::min(line.getStartY(), line.getEndY()) ;
        Scalar w = std::abs(line.getEndX() - line.getStartX()) ;
        Scalar h = std::abs(line.getEndY() - line.getStartY()) ;
        return intersects(x, y, w, h) ;
    }

    bool Rectangle2Df::intersects(const Rectangle2Df& boundaries) {
        return intersects(
            ((Rectangle2Df)boundaries).getBottomLeftCornerX(),
            ((Rectangle2Df)boundaries).getBottomLeftCornerY(),
            ((Rectangle2Df)boundaries).getWidth(),
            ((Rectangle2Df)boundaries).getHeight()
        ) ;
    }

    char Rectangle2Df::position(Scalar x, Scalar y) {
        char pos = 0 ;

        if (getWidth() <= 0) {
            pos = PointOnLeft | PointOnRight ;
        }
        else if (x < getBottomLeftCornerX()) {
            pos = PointOnLeft ;
        }
        else if (x > getUpRightCornerX()) {
            pos = PointOnRight ;
        }

        if (getHeight() <= 0) {
            return pos | PointAbove | PointBelow ;
        }
        else if (y > getUpRightCornerY()) {
            return pos | PointAbove ;
        }
        else if (y < getBottomRightCornerY()) {
            return pos | PointBelow ;
        }

        return pos ;
    }

    char Rectangle2Df::position(const Point2Df& p) {
        return position(p.getX(), p.getY()) ;
    }

    Scalar Rectangle2Df::getUpLeftCornerX() {
        return m_bottomLeftCorner.getX() ;
    }

    Scalar Rectangle2Df::getUpLeftCornerY() {
        computeMaxPoint() ;
        return m_upRightCorner.getY() ;
    }

    Scalar Rectangle2Df::getUpRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.getX() ;
    }

    Scalar Rectangle2Df::getUpRightCornerY()  {
        computeMaxPoint() ;
        return m_upRightCorner.getY() ;
    }

    Scalar Rectangle2Df::getBottomLeftCornerX() const {
        return m_bottomLeftCorner.getX() ;
    }

    Scalar Rectangle2Df::getBottomLeftCornerY() const {
        return m_bottomLeftCorner.getY() ;
    }

    Scalar Rectangle2Df::getBottomRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.getX() ;
    }

    Scalar Rectangle2Df::getBottomRightCornerY() {
        return m_bottomLeftCorner.getY() ;
    }

    const Dimension2Df& Rectangle2Df::getSize() const {
        return m_size ;
    }

    Scalar Rectangle2Df::getWidth() const {
        return m_size.getWidth() ;
    }

    Scalar Rectangle2Df::getHeight() const {
        return m_size.getHeight() ;
    }

    bool Rectangle2Df::isEmpty() const {
        return ((m_size.getWidth() == 0.f) || (m_size.getHeight() == 0.f)) ;
    }

    void Rectangle2Df::computeMaxPoint() {
        if (m_hasChanged) {
            m_upRightCorner.set(
                m_bottomLeftCorner.getX() + m_size.getWidth(),
                m_bottomLeftCorner.getY() + m_size.getHeight()
            ) ;
            m_hasChanged = false ;
        }
    }

    void Rectangle2Df::setX(const Scalar x) {
        if (m_isCentered) {
            m_bottomLeftCorner.setX(x - (getWidth() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.setX(x) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setY(const Scalar y) {
        if (m_isCentered) {
            m_bottomLeftCorner.setY(y - (getHeight() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.setY(y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setAt(const Scalar x, const Scalar y) {
        if (m_isCentered) {
            m_bottomLeftCorner.setX(x - (getWidth() / 2.f)) ;
            m_bottomLeftCorner.setY(y - (getHeight() / 2.f)) ;
        }
        else {
            m_bottomLeftCorner.setX(x) ;
            m_bottomLeftCorner.setY(y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setWidth(const Scalar width) {
        if (m_isCentered) {
            Scalar currentWidth = getWidth() ;
            Scalar halfWidthDiff = (currentWidth - width) / 2.f ;
            Scalar currentBottomLeftX = getBottomLeftCornerX() ;
            m_bottomLeftCorner.setX(currentBottomLeftX + halfWidthDiff) ;
            m_size.setWidth(width) ;
        }
        else {
            m_size.setWidth(width) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Df::setHeight(const Scalar height) {
        if (m_isCentered) {
            Scalar currentHeight = getHeight() ;
            Scalar halfHeightDiff = (currentHeight - height) / 2.f ;
            Scalar currentBottomLeftY = getBottomLeftCornerY() ;
            m_bottomLeftCorner.setY(currentBottomLeftY + halfHeightDiff) ;
            m_size.setHeight(height) ;
        }
        else {
            m_size.setHeight(height) ;
        }
        m_hasChanged = true ;
    }

    Rectangle2Df& Rectangle2Df::operator=(const Rectangle2Df& other) {
        if (this != &other) {
            m_bottomLeftCorner = other.m_bottomLeftCorner ;
            m_size = other.m_size ;
            m_hasChanged = true ;
        }

        return *this ;
    }

    Rectangle2Df& Rectangle2Df::operator+=(Point2Df& other) {
        *this = (*this) + other ;
        return *this ;
    }

    Rectangle2Df& Rectangle2Df::operator+=(Rectangle2Df& other) {
        *this = (*this) + other ;
        return *this ;
    }

    bool Rectangle2Df::operator==(const Rectangle2Df& other) const {
        return ((this == &other)
                    || ((m_bottomLeftCorner == other.m_bottomLeftCorner)
                            && (m_size == other.m_size))) ;
    }

    bool Rectangle2Df::operator!=(const Rectangle2Df& other) const {
        return !(*this == other) ;
    }

    Rectangle2Df operator+(Rectangle2Df& r, Point2Df& p) {
        if (r.contains(p)) {
            return r ;
        }
        else {
            Scalar x1 = std::min(r.getBottomLeftCornerX(), p.getX()) ;
            Scalar y1 = std::min(r.getBottomLeftCornerY(), p.getY()) ;
            Scalar x2 = std::max(r.getUpRightCornerX(), p.getX()) ;
            Scalar y2 = std::max(r.getUpRightCornerY(), p.getY()) ;
            return Rectangle2Df(x1, y1, x2, y2) ;
        }
    }

    Rectangle2Df operator+(Rectangle2Df& r1, Rectangle2Df& r2) {
        if (r1.contains(r2)) {
            return r1 ;
        }
        else if (r2.contains(r1)) {
            return r2 ;
        }
        else {
            Scalar x1 = std::min(r1.getBottomLeftCornerX(), r2.getBottomLeftCornerX()) ;
            Scalar y1 = std::min(r1.getBottomLeftCornerY(), r2.getBottomLeftCornerY()) ;
            Scalar x2 = std::max(r1.getUpRightCornerX(), r2.getUpRightCornerX()) ;
            Scalar y2 = std::max(r1.getUpRightCornerY(), r2.getUpRightCornerY()) ;
            return Rectangle2Df(x1, y1, x2, y2) ;
        }
    }

    std::ostream& operator<<(std::ostream& s, const Rectangle2Df& r) {
        s << "Rectangle2Df ("
                    << ((Rectangle2Df)r).getBottomLeftCornerX()
                    << ","
                    << ((Rectangle2Df)r).getBottomLeftCornerY()
                 << " | "
                    << ((Rectangle2Df)r).getUpRightCornerX()
                    << ","
                    << ((Rectangle2Df)r).getUpRightCornerY()
                 << ")" << std::endl ;
        return s ;
    }
} ;
