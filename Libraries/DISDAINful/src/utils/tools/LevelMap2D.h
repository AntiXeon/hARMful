#ifndef __LEVELMAP2D_H__
#define __LEVELMAP2D_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "LevelParser.h"
#include <string>
#include <assert.h>

#include <iostream>
using namespace std ;

/**
 * @brief A level map is an 2D matrix filled with char values representing
 * different kind of nodes for pathfinding and AI in general. it may represent
 * wall, gaps, traps, etc.
 * @version 1.0 08/05/2013
 */
class LevelMap2D {
    protected:
        /** @brief Width of the map. */
        unsigned short m_width ;

        /** @brief Height of the map. */
        unsigned short m_height ;

        /** @brief Value considered as an obstacle (wall, gap...). */
        unsigned char m_obstacleValue ;

        /** @brief Matrix representing the map. */
        unsigned char** m_map ;

    public:
                                                            /** CONSTRUCTION **/
        /**
         * @brief Creation of a level map from scratch.
         * @param width     Width of the map.
         * @param height    Height of the map.
         * @param empty     TRUE to make a black map, FALSE to create obstacles.
         */
        LevelMap2D(unsigned short width, unsigned short height, bool empty) ;

        /** @brief Creation of a level map from a file */
        LevelMap2D(LevelParser& parser) ;

        /** @brief Destruction of a level map. */
        virtual ~LevelMap2D() ;

                                                                 /** SETTERS **/
        /**
         * @brief Define the obstacle value.
         * @param value Value considered as an obstable.
         */
        virtual void setObstacleValue(unsigned char value) {
            m_obstacleValue = value ;
        }

        /**
         * @brief Change the value of a node.
         * @param x     Position on X of the node (must be lower than width).
         * @param y     Position on Y of the node (must be lower than height).
         */
        virtual void set(unsigned short x, unsigned short y, unsigned char value) {
            m_map[x][y] = value ;
        }


                                                                 /** GETTERS **/
        /** 
         * @brief Get the node at a given position.
         * @param x     Position on X of the node (must be lower than width).
         * @param y     Position on Y of the node (must be lower than height).
         * @return Value of the node at (X, Y).
         */
        virtual unsigned char get(unsigned short x, unsigned short y) {
            assert(x < m_width) ;
            assert(y < m_height) ;
            return m_map[x][y] ;
        }

        /**
         * @brief To know if a position is an obstacle.
         */
        virtual bool isObstacle(unsigned short x, unsigned short y) {
            return (get(x, y) == m_obstacleValue) ;
        }

        /**
         * @brief Check if the coordinates are in the map.
         * @param x     Position on X.
         * @param y     Position on Y.
         * @return TRUE if both X and Y are in the matrix, FALSE else.
         */
        virtual bool inside(unsigned short x, unsigned short y) {
            return ((x < m_width) && (y < m_height)) ;
        }


        /** @brief Get the width of the map. */
        virtual unsigned short getWidth() {
            return m_width ;
        }

        /** @brief Get the height of the map. */
        virtual unsigned short getHeight() {
            return m_height ;
        }


    protected:
        /** @brief Initialize a map. */
        virtual void initMap() {
	        m_map = new unsigned char*[m_width] ;
	        unsigned char* dim_2 = new unsigned char[m_width * m_height] ;
	
	        for (unsigned char i = 0 ; i < m_height ; i++)
		        m_map[i] = &dim_2[i * m_height] ;
        }


        /** @brief Fill the map with the given value. */
        virtual void fillMap(unsigned char value) {
            for (unsigned int j = 0 ; j < m_height ; j++) {
                for (unsigned int i = 0 ; i < m_width ; i++) {
                    m_map[i][j] = value ;
                }
            }
        }
} ;

#endif
