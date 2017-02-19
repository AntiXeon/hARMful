#include <geometry/rectangles/Rectangle2Di.hpp>
#include <Math.hpp>
#include <algorithm>

namespace Mind {
    Rectangle2Di::Rectangle2Di() : Rectangle2Di(0.f, 0.f, 0.f, 0.f, false) {}

    Rectangle2Di::Rectangle2Di(const Rectangle2Di& copied)
        : Rectangle2Di(
            copied.getBottomLeftCornerX(),
            copied.getBottomLeftCornerY(),
            copied.getWidth(),
            copied.getHeight(),
            copied.m_isCentered
        ) {}

    Rectangle2Di::Rectangle2Di(
        const Point2Di& location,
        const Dimension2Di& size,
        bool centered
    ) : Rectangle2Di(
            location.getX(),
            location.getY(),
            size.getWidth(),
            size.getHeight(),
            centered
    ) {}

    Rectangle2Di::Rectangle2Di(
        const int& x,
        const int& y,
        const int& w,
        const int& h,
        bool centered
    ) : m_isCentered(centered),
        m_hasChanged(true),
        m_size(w, h)
    {
        m_size = Dimension2Di(w, h) ;

        if (centered) {
            int halfWidth = w / 2 ;
            int halfHeight = h / 2 ;
            m_bottomLeftCorner = Point2Di(x - halfWidth, y - halfHeight) ;
        }
        else {
            m_bottomLeftCorner = Point2Di(x, y) ;
        }

        computeMaxPoint() ;
    }

    Rectangle2Di::Rectangle2Di(
        const Point2Di& p1,
        const Point2Di& p2
    ) : Rectangle2Di(
            p1.getX(),
            p1.getY(),
            p2.getX(),
            p2.getY()
        ) {}

    Rectangle2Di::Rectangle2Di(
                               const int& x1,
                               const int& y1,
                               const int& x2,
                               const int& y2
                              ) : m_isCentered(false),
                                  m_hasChanged(false) {
        std::pair<int, int> minMax_X = std::minmax(x1, x2) ;
        std::pair<int, int> minMax_Y = std::minmax(y1, y2) ;

        m_bottomLeftCorner = Point2Di(minMax_X.first, minMax_Y.first) ;
        // m_upRightCorner = Point2Di(minMax_X.second, minMax_Y.first) ;
        m_size = Dimension2Di(minMax_X.second - minMax_X.first,
                                minMax_Y.second - minMax_Y.first) ;
    }

    Rectangle2Di::~Rectangle2Di() {}

    void Rectangle2Di::translate(
        const int& x,
        const int& y
    ) {
        setAt(m_bottomLeftCorner.getX() + x, m_bottomLeftCorner.getY() + y) ;
    }

    bool Rectangle2Di::contains(
        const int& x,
        const int& y
    ) {
        computeMaxPoint() ;
        return ((x >= m_bottomLeftCorner.getX()) && (x <= m_upRightCorner.getX())
                    && (y >= m_bottomLeftCorner.getY()) && (y <= m_upRightCorner.getY())) ;
    }

    bool Rectangle2Di::contains(const Point2Di& point) {
        computeMaxPoint() ;

        int x = point.getX() ;
        int y = point.getY() ;
        return (
                ((x >= getBottomLeftCornerX()) && (x <= getUpRightCornerX()))
                 &&
                ((y >= getBottomLeftCornerY()) && (y <= getUpRightCornerY()))
               ) ;
    }

    bool Rectangle2Di::contains(
        const int& x,
        const int& y,
        const int& w,
        const int& h
    ) {
        int x2 = x + w ;
        int y2 = y + h ;
        return (contains(x, y) && contains(x2, y2)) ;
    }

    bool Rectangle2Di::contains(Rectangle2Di& boundaries) {
        return contains(
            boundaries.getBottomLeftCornerX(),
            boundaries.getBottomLeftCornerY(),
            boundaries.getWidth(),
            boundaries.getHeight()
        ) ;
    }

    bool Rectangle2Di::intersects(
        const int& x,
        const int& y,
        const int& w,
        const int& h
    ) {
        if (isEmpty() || ((w == 0) || (h == 0))) {
            return false ;
        }

        int xThis = getBottomLeftCornerX() ;
        int yThis = getBottomLeftCornerY() ;
        int x2This = getUpRightCornerX() ;
        int y2This = getUpRightCornerY() ;

        return (
                ((x + w) > xThis)
                    && ((y + h) > yThis)
                    && (x < x2This)
                    && (y < y2This)
               ) ;
    }

    bool Rectangle2Di::intersects(const Line2Di& line) {
        int x = std::min(line.getStartX(), line.getEndX()) ;
        int y = std::min(line.getStartY(), line.getEndY()) ;
        int w = std::abs(line.getEndX() - line.getStartX()) ;
        int h = std::abs(line.getEndY() - line.getStartY()) ;
        return intersects(x, y, w, h) ;
    }

    bool Rectangle2Di::intersects(const Rectangle2Di& boundaries) {
        return intersects(
            ((Rectangle2Di)boundaries).getBottomLeftCornerX(),
            ((Rectangle2Di)boundaries).getBottomLeftCornerY(),
            ((Rectangle2Di)boundaries).getWidth(),
            ((Rectangle2Di)boundaries).getHeight()
        ) ;
    }

    char Rectangle2Di::position(const int& x, const int& y) {
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

    char Rectangle2Di::position(const Point2Di& p) {
        return position(p.getX(), p.getY()) ;
    }

    int Rectangle2Di::getUpLeftCornerX() {
        return m_bottomLeftCorner.getX() ;
    }

    int Rectangle2Di::getUpLeftCornerY() {
        computeMaxPoint() ;
        return m_upRightCorner.getY() ;
    }

    int Rectangle2Di::getUpRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.getX() ;
    }

    int Rectangle2Di::getUpRightCornerY() {
        computeMaxPoint() ;
        return m_upRightCorner.getY() ;
    }

    int Rectangle2Di::getBottomLeftCornerX() const {
        return m_bottomLeftCorner.getX() ;
    }

    int Rectangle2Di::getBottomLeftCornerY() const {
        return m_bottomLeftCorner.getY() ;
    }

    int Rectangle2Di::getBottomRightCornerX() {
        computeMaxPoint() ;
        return m_upRightCorner.getX() ;
    }

    int Rectangle2Di::getBottomRightCornerY() {
        return m_bottomLeftCorner.getY() ;
    }

    const Dimension2Di& Rectangle2Di::getSize() const {
        return m_size ;
    }

    int Rectangle2Di::getWidth() const {
        return m_size.getWidth() ;
    }

    int Rectangle2Di::getHeight() const {
        return m_size.getHeight() ;
    }

    bool Rectangle2Di::isEmpty() const {
        return ((m_size.getWidth() == 0) || (m_size.getHeight() == 0)) ;
    }

    void Rectangle2Di::computeMaxPoint() {
        if (m_hasChanged) {
            m_upRightCorner.set(
                m_bottomLeftCorner.getX() + m_size.getWidth(),
                m_bottomLeftCorner.getY() + m_size.getHeight()
            ) ;
            m_hasChanged = false ;
        }
    }

    void Rectangle2Di::setX(const int& x) {
        if (m_isCentered) {
            m_bottomLeftCorner.setX(x - (getWidth() / 2)) ;
        }
        else {
            m_bottomLeftCorner.setX(x) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Di::setY(const int& y) {
        if (m_isCentered) {
            m_bottomLeftCorner.setY(y - (getHeight() / 2)) ;
        }
        else {
            m_bottomLeftCorner.setY(y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Di::setAt(const int& x, const int& y) {
        if (m_isCentered) {
            m_bottomLeftCorner.setX(x - (getWidth() / 2)) ;
            m_bottomLeftCorner.setY(y - (getHeight() / 2)) ;
        }
        else {
            m_bottomLeftCorner.setX(x) ;
            m_bottomLeftCorner.setY(y) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Di::setWidth(const int& width) {
        if (m_isCentered) {
            int currentWidth = getWidth() ;
            int halfWidthDiff = (currentWidth - width) / 2 ;
            int currentBottomLeftX = getBottomLeftCornerX() ;
            m_bottomLeftCorner.setX(currentBottomLeftX + halfWidthDiff) ;
            m_size.setWidth(width) ;
        }
        else {
            m_size.setWidth(width) ;
        }
        m_hasChanged = true ;
    }

    void Rectangle2Di::setHeight(const int& height) {
        if (m_isCentered) {
            int currentHeight = getHeight() ;
            int halfHeightDiff = (currentHeight - height) / 2 ;
            int currentBottomLeftY = getBottomLeftCornerY() ;
            m_bottomLeftCorner.setY(currentBottomLeftY + halfHeightDiff) ;
            m_size.setHeight(height) ;
        }
        else {
            m_size.setHeight(height) ;
        }
        m_hasChanged = true ;
    }

                                                             /*** OPERATORS ***/
    Rectangle2Di& Rectangle2Di::operator=(const Rectangle2Di& other) {
        if (this != &other) {
            m_bottomLeftCorner = other.m_bottomLeftCorner ;
            m_size = other.m_size ;
            m_hasChanged = true ;
        }

        return *this ;
    }

    Rectangle2Di& Rectangle2Di::operator+=(Point2Di& other) {
        *this = (*this) + other ;
        return *this ;
    }

    Rectangle2Di& Rectangle2Di::operator+=(Rectangle2Di& other) {
        *this = (*this) + other ;
        return *this ;
    }

    bool Rectangle2Di::operator==(const Rectangle2Di& other) const {
        return ((this == &other)
                    || ((m_bottomLeftCorner == other.m_bottomLeftCorner)
                            && (m_size == other.m_size))) ;
    }

    bool Rectangle2Di::operator!=(const Rectangle2Di& other) const {
        return !(*this == other) ;
    }

    Rectangle2Di operator+(Rectangle2Di& r, Point2Di& p) {
        if (r.contains(p)) {
            return r ;
        }
        else {
            int x1 = std::min(r.getBottomLeftCornerX(), p.getX()) ;
            int y1 = std::min(r.getBottomLeftCornerY(), p.getY()) ;
            int x2 = std::max(r.getUpRightCornerX(), p.getX()) ;
            int y2 = std::max(r.getUpRightCornerY(), p.getY()) ;
            return Rectangle2Di(x1, y1, x2, y2) ;
        }
    }

    Rectangle2Di operator+(Rectangle2Di& r1, Rectangle2Di& r2) {
        if (r1.contains(r2)) {
            return r1 ;
        }
        else if (r2.contains(r1)) {
            return r2 ;
        }
        else {
            int x1 = std::min(r1.getBottomLeftCornerX(), r2.getBottomLeftCornerX()) ;
            int y1 = std::min(r1.getBottomLeftCornerY(), r2.getBottomLeftCornerY()) ;
            int x2 = std::max(r1.getUpRightCornerX(), r2.getUpRightCornerX()) ;
            int y2 = std::max(r1.getUpRightCornerY(), r2.getUpRightCornerY()) ;
            return Rectangle2Di(x1, y1, x2, y2) ;
        }
    }

    std::ostream& operator<<(std::ostream& s, const Rectangle2Di& r) {
        s << "Rectangle2Di ("
                    << ((Rectangle2Di)r).getBottomLeftCornerX()
                    << ","
                    << ((Rectangle2Di)r).getBottomLeftCornerY()
                 << " | "
                    << ((Rectangle2Di)r).getUpRightCornerX()
                    << ","
                    << ((Rectangle2Di)r).getUpRightCornerY()
                 << ")" << std::endl ;
        return s ;
    }
} ;
