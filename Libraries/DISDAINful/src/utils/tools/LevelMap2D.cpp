#include "LevelMap2D.h"

#include <iostream>
//using namespace std ;

using namespace std ;

LevelMap2D::LevelMap2D(unsigned short width, unsigned short height, bool empty) {
    m_width = width ;
    m_height = height ;
    m_obstacleValue = 0 ;

    initMap() ;

    if (empty)
        fillMap(1) ;
}

LevelMap2D::LevelMap2D(LevelParser& parser) {
    m_map = parser.run() ;
    m_obstacleValue = parser.getObstacleValue() ;
    m_width = parser.getWidth() ;
    m_height = parser.getHeight() ;
}

LevelMap2D::~LevelMap2D() {
	delete[] m_map[0] ;
	delete[] m_map ;
}
