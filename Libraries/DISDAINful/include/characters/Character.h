#ifndef __CHARACTER_H__
#define __CHARACTER_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "../utils/GaugeTimer.h"
#include "ai/ArtificialIntelligence.h"
#include "ai/memory/ActionMemory.h"
#include "ai/memory/MagicMemory.h"
#include "body/physique/Physique.h"

#include <set>

/**
 * @brief Generic character.
 * @see Body
 * @see Colony
 * @see Statistics
 * @version 1.0 09/05/2012  Basic version, no artificial intelligence
 * @version 1.1 17/06/2012  Artificial intelligence added
 * @version 1.2 23/10/2012  Colonies are made as an object
 * @version 1.3 29/10/2012  Statistics and Body are made as objects.
 * @version 2.0 27/03/2013  A lot of improvements are done on the software
 *                          architecture for better upgradability and
 *                          maintainability (mainly driven by the separation of
 *                          Character and AI objects).
 * @version 2.1 27/04/2013	List of all the characters generated to easily
 *							manage their actions at each frame. The action gauge
 *							appears to easily manage the velocity of each
 *							character. While this gauge is not full, the
 *							character cannot act.
 */
// @TODO manage the level up of the characters
class Character {
    public:
    	/** @brief Save all the characters generated in an array. */
		static std::set<Character*> AllCharacters ;

    protected:
    	/**
    	 * @brief Size of the action gauge filled at each round. The action
    	 * 		  gauge allows the character to act (attack, heal...).
    	 *		  The size of 7200 is based on a velocity of 120 in the
    	 *		  statistics of a character. A character having velocity of 120
    	 *		  will be able to make an action every second if the game runs
    	 *		  at 60 fps. Thus, if the character has a velocity of 240, it
    	 *		  will fill its gauge twice quicker. Conversely, a character
    	 *		  with a velocity equal to 60 will fill it twice slower.
    	 */
		static const int MAX_ACTION_GAUGE = 7200 ;


        /** @brief Name of the character. */
        std::string m_name ;

		/**
		 * @brief Gauge to know if the character can act or not.
		 * This does not affect movements.
		 */
		GaugeTimer* m_actionGauge ;

        /** @brief Artificial intelligence driving the actions of the character. */
        ArtificialIntelligence* m_ai ;

        /** @brief Action memory linked to the AI. */
        ActionMemory* m_actionmem ;

        /** @brief Physique of the character. */
        Physique* m_physique ;

        /** @brief Statistics of the character. */
        Statistics* m_statistics ;
        

    public:
        /**
	     * @brief Creation of a character.
	     */
		Character() ;

        /** @brief Destruction of the object. */
        virtual ~Character() ;


                                                                 /** ACTIONS **/
        /** @brief To run the AI and make some other extra things if needed. */
        virtual void action() = 0 ;

		/**
		 * @brief All the characters run a tick. There action jauge is filled
		 * accordingly to their speed (in the statistics). If their jauge is
		 * full, they can make an action with their AI.
		 */
		virtual void tick() {
            if (!(m_ai -> getStatistics() -> isKO())) {
			    unsigned char velocity = m_ai -> getStatistics() -> getVel() ;
			    bool ready = m_actionGauge -> isReady(velocity) ;

			    if (ready)
				    action() ;				   // The character is ready to act!
            }
		}


    protected:
                                                                 /** SETTERS **/
        /** @brief Set the name of the character. */
        inline void setName(const std::string& name) {
            assert(!name.empty()) ;
            m_name = name ;
        }

        /** @brief Set the statistics of the character. */
        virtual void setStatistics(unsigned char level) = 0 ;

        /** @brief Set the inventory of the character. */
        virtual void setInventory(unsigned char level) = 0 ;

        /** @brief Set the magic known by the character when created. */
        virtual void setMagic(unsigned char level) = 0 ;

        /**
         * @brief Compute an initial element of the statistics with an average
         * value and variance on first level of the character. For higher levels,
         * it computes additionnal points making the character stronger.
         * @param   average     Average value of the stat.
         * @param   variance    Variance applied to make a random value near the
         *                      average.
         * @param   level       Wanted level of the character.
         * @return The stat determined with average and variance.
         */
        inline unsigned int determineStat(unsigned short average,
                                          unsigned short variance) {
            int stat ;
            variance = rand() % variance ;
            char randomSign = rand() % 2 ;
            if (randomSign == 0 || (variance >= average))
                stat = average + variance ;
            else
                stat = average - variance ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Stat random = " << (int) stat
                                 << " average = " << (int) average
                                 << " variance = " << (int) variance ;
                LogGen::print() ;
            #endif

            assert(stat > 0) ;
            return stat ;
        }

        /**
         * @brief Compute an initial element of the statistics with an average
         * value and variance on first level of the character. For higher levels,
         * it computes additionnal points making the character stronger.
         * @param   average     Average value of the stat.
         * @param   variance    Variance applied to make a random value near the
         *                      average.
         * @param   level       Wanted level of the character.
         * @return The stat determined with average and variance.
         */
        inline unsigned int determineStat(unsigned short average,
                                          unsigned short variance,
                                          unsigned char level) {
            assert(level < 101) ;

            unsigned int stat ;
            variance = rand() % variance ;
            char randomSign = rand() % 2 ;
            if (randomSign == 0 || (average <= variance))
                stat = average + variance ;
            else
                stat = average - variance ;

            assert(stat > 0) ;

            return applyLevelToStat(stat, level) ;
        }

    private:
        /**
         * @brief Compute the value of a stat at a given level.
         * @param stat  Value of the stat on level 1 of the character.
         * @param level Level of the character.
         * @return Value of the stat at the wanted level.
         */
        inline unsigned int applyLevelToStat(unsigned short stat,
                                             unsigned char level) {
            return (stat + (stat * level) / 10) ;
        }


    public:
                                                                 /** GETTERS **/
        /** @brief Get the name of the character. */
        virtual const std::string& getName() const { return m_name ; }

        /** @brief Get the Artificial Intelligence object of the character. */
        ArtificialIntelligence* getAI() const { return m_ai ; }


														  /** STATIC METHODS **/
		/** @brief Count the total of characters currently available. */
		inline static unsigned int countAllCharacters() {
			return AllCharacters.size() ;
		}

		/** @brief Count the total of characters currently available. */
		inline static void tickAll() {
			std::set<Character*>::iterator character ;
			for (character = AllCharacters.begin() ; character != AllCharacters.end() ; character++) {
			    (*character) -> tick() ;
			}
		}
} ;
#endif
