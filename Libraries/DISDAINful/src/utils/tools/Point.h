#ifndef __POINT_H__
#define __POINT_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include <math.h>

/**
 * @brief A point implementation, independant of any external library.
 * @version 1.0 08/05/2013
 */
class Point {
    protected:
        /** @brief Coordinate on X axis. */
        unsigned short m_x ;

        /** @brief Coordinate on Y axis. */
        unsigned short m_y ;

    public:
                                                            /** CONSTRUCTION **/
        /** @brief Creation of a Point on (0, 0). */
        Point() {
            m_x = 0 ;
            m_y = 0 ;
        }

        /** @brief Creation of a Point with its coordinates. */
        Point(unsigned short x, unsigned short y) {
            m_x = x ;
            m_y = y ;
        }

        /** @brief Creation of a Point by copying another Point. */
        Point(const Point& p) {
            m_x = p.m_x ;
            m_y = p.m_y ;
        }

        /** @brief Destruction of a Point. */
        virtual ~Point() {}


                                                               /** UTILITIES **/
        unsigned int hash() {
            return m_x + (251 * m_y) ;
        }

        /**
         * @brief Compute the Manhattant distance between two points.
         * @param p     The second point to compute distance from the current
         *              one.
         */
        unsigned int manhattanDistance(Point* p) {
            unsigned short distanceX = absolute(m_x - (p -> m_x)) ;
            unsigned short distanceY = absolute(m_y - (p -> m_y)) ;
            return distanceX + distanceY ;
        }

        /**
         * @brief Compute the squared euclidean distance between two points.
         * @param p     The second point to compute distance from the current
         *              one.
         */
        unsigned int squaredEuclideanDistance(Point* p) {
            unsigned short distanceX = m_x - (p -> m_x) ;
            unsigned short distanceY = m_y - (p -> m_y) ;
            return (distanceX * distanceX) + (distanceY * distanceY) ;
        }

        /**
         * @brief Compute the euclidean distance between two points.
         * @param p     The second point to compute distance from the current
         *              one.
         */
        unsigned int euclideanDistance(Point* p) {
            return sqrt(squaredEuclideanDistance(p)) ;
        }

        /**
         * @brief Compute the Chebyshev distance between two points.
         * @param p     The second point to compute distance from the current
         *              one.
         */
        unsigned int chebyshevDistance(Point* p) {
            unsigned short distanceX = m_x - (p -> m_x) ;
            unsigned short distanceY = m_y - (p -> m_y) ;
            return max(distanceX, distanceY) ;
        }


                                                               /** OPERATORS **/
        /**
         * @brief Test if the Points are at the same position.
         * @param p     The Point to compare.
         * @return TRUE if X, Y and Z are equal in the two Points.
         */
        /** @brief Test if the Points are at the same position. */
        bool operator==(const Point& p) {
            return ((m_x == p.m_x) && (m_y == p.m_y)) ;
        }

        /**
         * @brief Test if the Points are not at the same position.
         * @param p     The Point to compare.
         * @return TRUE if X, Y and/or Z are different between the two Points.
         */
        bool operator!=(const Point& p) {
            return !(*this == p) ;
        }



                                                                 /** SETTERS **/
        /** @brief Get the position on X. */
        void setX(unsigned short x) {
            m_x = x ;
        }

        /** @brief Get the position on Y. */
        void setY(unsigned short y) {
            m_y = y ;
        }


                                                                 /** GETTERS **/
        /** @brief Get the position on X. */
        inline unsigned short getX() const {
            return m_x ;
        }

        /** @brief Get the position on Y. */
        inline unsigned short getY() const {
            return m_y ;
        }


    private:
        /** @brief Compute the absolute value. */
        static unsigned short absolute(int value) {
            return (value < 0) ? -value : value ;
        }

        static unsigned short max(unsigned short a, unsigned short b) {
            return (a > b) ? a : b ;
        }
} ;

#endif
