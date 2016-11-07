#ifndef __LEVELPARSER_H__
#define __LEVELPARSER_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include <string>
#include <vector>

class LevelParser {
    protected:
        /** @brief The file to parse. */
        char* m_file ;

        /** @brief A temporary 2D matrix. */
        unsigned char** m_tmpMatrix ;

        /** @brief Obstacle values given in the file. */
        unsigned char m_obstacleValue ;

        /** @brief Width of the map. */
        unsigned short m_width ;

        /** @brief Height of the map. */
        unsigned short m_height ;


    public:
                                                            /** CONSTRUCTION **/
        /**
         * @brief Creation of a MapParser.
         * @param file      The file to parse.
         */
        LevelParser(const char* file) ;

        /** @brief Destruction of a MapParser. */
        virtual ~LevelParser() ;


        /**
         * @brief Set the address to the 2D matrix of the LevelMap2D.
         * @param address   Memory address of the 2D matrix used by the map.
         */
//        void setMapAddress(unsigned char*** address) {
//            m_mapAddress = address ;
//            m_tmpMatrix = *address ;
//        }

        /** @brief Get the obstacle value found in the file. */
        char getObstacleValue() {
            return m_obstacleValue ;
        }

        /** @brief Get the width of the map. */
        virtual unsigned int getWidth() {
            return m_width ;
        }

        /** @brief Get the height of the map. */
        virtual unsigned int getHeight() {
            return m_height ;
        }


                                                               /** UTILITIES **/
        /**
         * @brief Run the complete parsing task.
         * @return The matrix representing the map.
         */
        unsigned char** run() {
            parse() ;
            return m_tmpMatrix ;
        }


    protected:
        /** @brief Parser only. */
        virtual void parse() = 0 ;

        /** @brief Initialize a map. */
        virtual void initMap() {
	        m_tmpMatrix = new unsigned char*[m_width] ;
	        unsigned char* dim_2 = new unsigned char[m_width * m_height] ;
	
	        for (unsigned char i = 0 ; i < m_height ; i++)
		        m_tmpMatrix[i] = &dim_2[i * m_height] ;
        }
} ;

#endif
