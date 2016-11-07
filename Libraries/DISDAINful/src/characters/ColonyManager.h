#ifndef __COLONY_H__
#define __COLONY_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "../pattern/observer/ObserverInterface.h"
#include "ai/ArtificialIntelligence.h"
#include "Character.h"
#include "ColonyData.h"
#include "ColonyStrategy.h"

#include <assert.h>
#include <string>
#include <vector>

/**
 * @brief Class used to manage the data of a colony.
 * @see ColonyData
 * @version 1.0 23/10/2012  Colony class creation.
 * @version 2.0 30/03/2013  Colony is splitted into two classes to avoid a
 *                          circular dependency with the Character and AI
 *                          classes.
 */
class ColonyManager : public ObserverInterface {
    private:
        /** @brief Count the total number of colonies created. */
        static unsigned short CountColonies ;

        /** @brief List of the ColonyManager to destroy. */
        static std::vector<ColonyManager*> DestroyList ;

        /** @brief Related data of the colony. */
        ColonyData* m_data ;

        /**
         * @brief List of the characters, used to destroy all the Character
         *        objects when their are no more alive characters in the group.
         */
        std::vector<Character*> m_characters ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a ColonyManager. */
        ColonyManager(const std::string& name, ColonyStrategy* strategy) ;

        /**
         * @brief Destruction of a ColonyManager. It destroys the ColonyData and
         * all the Character objects member of the colony. */
        virtual ~ColonyManager() ;


                                                               /** UTILITIES **/
        /**
         * @brief Add a new member to the colony.
         * @param member    The member to add.
         */
        inline void addMember(Character* member) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << (m_data -> getName())
                                 << " adds member "
                                 << (member -> getName()) ;
                LogGen::print() ;
            #endif

            ArtificialIntelligence* ai = member -> getAI() ;
            assert(ai -> getColony() == 0) ;

            if (member != 0 && (m_data -> countAliveMembers() + m_data -> countKOMembers()) < 256) {
                if (ai -> getStatistics() -> isKO())
                    m_data -> addKO((unsigned long) ai) ;
                else
                    m_data -> addAlive((unsigned long) ai, ai -> getStatistics() -> getLevel()) ;

                ai -> setColony(m_data) ;
            }

            m_characters.push_back(member) ;
        }


		/**
		 * @brief Set another colony as enemy of the current one.
		 *		  The current colony is automatically an enemy of the other.
		 * @param other		The colony that is set as enemy.
		 */
		inline void setAsEnemy(ColonyManager* other) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << (m_data -> getName())
                                 << " is now enemy of "
                                 << (other -> m_data -> getName()) ;
                LogGen::print() ;
            #endif

		    m_data -> add(other -> m_data) ;

		    // Set the colony as an enemy of the other if not already done
		    if (!(other -> m_data -> hasEnemy(m_data))) {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << (m_data -> getName())
                                     << " is not yet an enemy of "
                                     << (other -> m_data -> getName()) ;
                    LogGen::print() ;
                #endif

			    other -> setAsEnemy(this) ;
		    }
		}

        /** @brief Update the level of the colony. */
        virtual inline void update(Observable* o, void*) {
            ColonyData* data = (ColonyData*) o ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << (m_data -> getName())
                                 << " is updated (level) from its manager" ;
                LogGen::print() ;
            #endif

            short level = 0 ;
            std::set<unsigned long>::iterator it ;
            std::set<unsigned long>::iterator end = data -> getAliveMembers().end() ;
            for(it = data -> getAliveMembers().begin() ; it != end ; it++)
                level += ArtificialIntelligence::convert(*it) -> getStatistics() -> getLevel() ;
            data -> setLevel(level) ;

            if (level == 0)
                setToBeDestroyed() ;
        }

        /**
         * @brief Clear the list of ColonyManager to destroy. This calls the
         *        destructor of every ColonyManager listed in the destroy list.
         *        The list is then cleared.
         */
        inline static void clearDestroyList() {
            std::vector<ColonyManager*>::iterator cm ;
            for (cm = DestroyList.begin() ; cm != DestroyList.end() ; cm++) {
                delete (*cm) ;
            }

            DestroyList.clear() ;
            assert(DestroyList.size() == 0) ;
        }

        /**
         * @brief Get the total amount of running colonies.
         * @return The amount of colonies that can fight.
         */
        inline static unsigned short countAllColonies() {
            return CountColonies ;
        }

        /** @brief Get the list of the characters in the colony. */
        inline const std::vector<Character*>& getCharacters() {
            return m_characters ;
        }

        /** @brief Get the name of the colony. */
        inline const std::string& getName() {
            return m_data -> getName() ;
        }

    private:
        /**
         * @brief The colony is set to be destroyed. It means that the
         *        destructor will be called soon.
         *        This destruction will imply the destruction of all the
         *        characters in the group (and their AI, Statistics, etc.).
         */
        inline void setToBeDestroyed() {
            assert(m_data -> isToBeDestroyed() == false) ;
            m_data -> setToDestroy() ;
            DestroyList.push_back(this) ;
        }
} ;

#endif
