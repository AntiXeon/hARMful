#ifndef __COLONYDATA_H__
#define __COLONYDATA_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "ColonyStrategy.h"
#include "../pattern/observer/Observable.h"

#include <assert.h>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Class containing only the data about colonies (groups of characters).
 *
 *        This class only allows a direct access to the collections of
 *        pointers to ArtificialIntelligences and other data on a colony. It
 *        manages the data without any relation with the Artificial Intelligence
 *        classes (it only handle pointers to ArtificialIntelligences objects to
 *        store them into collections, but it does not use methods from such
 *        classes). To avoid a direct inclusion of the ArtificialIntelligences
 *        class and so a circular dependency, we use long type data to save the
 *        address of the ArtificialIntelligences objects.
 *
 *        It contains all the functions required by the AI classes to determine
 *        the colony to fight. Indeed, the AI classes only need to read
 *        informations on the colonies to determine the best enemy one.
 *        Besides, the ColonyManager produces some informations on its related
 *        colony and it does not requires reading informations on it. In this
 *        way, both producer and reader are separated and thus no bad circular
 *        dependency is required.
 *
 *        Methods are set inline to preserve execution speed despite the
 *        separation of data and their management.
 * @see ColonyManager
 * @version 1.0 23/10/2012  Colony class creation.
 * @version 2.0 30/03/2013  Colony is splitted into two classes to avoid a
 *                          circular dependency with the Character and AI
 *                          classes.
 */
class ColonyData : public Observable {
    private:
        /** @brief List of all the ColonyData objects created in the game. */
        static std::vector<ColonyData*> ALL_COLONIES ;


        /** @brief Name of the colony. */
        std::string m_name ;

        /** @brief Strategy of the colony. */
        ColonyStrategy* m_strategy ;

        /** @brief Global level of the colony. */
        unsigned short m_level ;

        /** @brief List of the alive members of the colony. */
        std::set<unsigned long> m_membersAlive ;

        /**
         * @brief List of the KO members of the colony (thus, they can be
         * revived by their alive allies).
         */
        std::set<unsigned long> m_membersKO ;

        /**
         * @brief Total amount of enemies of the colony members.
         * Improves the efficiency of the software since it is only computed on
         * two events: new character arrival in an enemy colony or death of an
         * enemy character.
         */
        unsigned short m_enemiesAmount ;

        /** @brief List of the enemy colonies (data). */
        std::set<ColonyData*> m_enemies ;
        
        /** @brief Data on the colony to fight. */
        ColonyData* m_toFight ; // @TODO move to AI ?

        /** @brief Ratio of alive allies on alive enemies. */
        short m_situationRatio ;


        /** @brief To know if the linked ColonyManager is to be destroyed. */
        bool m_isToBeDestroyed ;

    public:
                                                            /** CONSTRUCTORS **/
        /** Creation of a ColonyData. */
        ColonyData(const std::string& name, ColonyStrategy* strategy, ObserverInterface* o) ;

        /** Destruction of a ColonyData. */
        virtual ~ColonyData() ;


                                                               /** UTILITIES **/
        /**
         * @brief Add a new member to the colony.
         * @param member    The member to add.
         * @param level     Level of the character.
         */
        inline void addAlive(unsigned long member, unsigned char level) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName() << " add " << member
                                 << ", level " << (int) level ;
                LogGen::print() ;
            #endif

            m_membersAlive.insert(member) ;
            m_level += level ;
            computeRatio() ;
        }

        /**
         * @brief Add a new member to the colony.
         * @param member    The member to add.
         * @param level     Level of the character.
         */
        inline void addKO(unsigned long member) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName() << " add KO member " << member ;
                LogGen::print() ;
            #endif

            m_membersKO.insert(member) ;
            computeRatio() ;
        }

        /**
         * @brief Add an enemy colony.
         * @param enemy     Data on the colony to add in the enemies list.
         */
        inline void add(ColonyData* enemy) {
            assert(enemy != 0) ;
            assert(enemy != this) ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName() << " add enemmy "
                                 << (enemy -> m_name) ;
                LogGen::print() ;
            #endif

            bool insert = (m_enemies.count(enemy) == 0) ;
            if (insert) {
                m_enemies.insert(enemy) ;
                m_toFight = getStrongestEnemie() ;
                m_enemiesAmount += enemy -> countAliveMembers() ;
                computeRatio() ;
            }
        }

        /**
         * @brief To know if a colony is an enemy for another one.
         * @param other     The colony to try to find in the enemies list.
         * @return TRUE if the other colony is an enemy.
         */
        inline bool hasEnemy(ColonyData* other) {
            return (m_enemies.count(other) > 0) ;
        }

        /**
         * @brief Remove an enemy colony data from the list.
         */
        inline void removeEnemieColony(ColonyData* colony) {
            if (m_enemies.count(colony) > 0) {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << getName() << " remove enemmy "
                                     << (colony -> m_name) ;
                    LogGen::print() ;
                #endif

                unsigned short max = m_enemies.size() ;
                m_enemies.erase(colony) ;

                max = max - 1 ;
                assert(m_enemies.size() == max) ;
                m_enemiesAmount -= colony -> countAliveMembers() ;
                computeRatio() ;
            }
        }


    private:
        /**
         * @brief Compute the ratio alive allies on alive enemies.
         */
         inline void computeRatio() {
            m_situationRatio = -1 ;
            if (m_enemiesAmount > 0)
                m_situationRatio = ((countAliveMembers() * 100) / m_enemiesAmount) ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName() << " computes ratio "
                                 << m_situationRatio ;
                LogGen::print() ;
            #endif
         }

        /**
         * @brief When the colony gains a member, the other colonies (enemies)
         *        should update the amount of enemy characters to fight.
         */
        inline void increaseEnemiesCharacters() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName()
                                 << " increases enemies characters..." ;
                LogGen::print() ;
            #endif

            std::set<ColonyData*>::iterator colony ;
            for (colony = m_enemies.begin() ; colony != m_enemies.end() ; colony++) {
                (*colony) -> m_enemiesAmount++ ;
                (*colony) -> computeRatio() ;
            }
        }

        /**
         * @brief When the colony loses a member, the other colonies (enemies)
         *        should update the amount of enemy characters to fight.
         */
        inline void decreaseEnemiesCharacters() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName()
                                 << " decreases enemies characters..." ;
                LogGen::print() ;
            #endif

            std::set<ColonyData*>::iterator colony ;
            for (colony = m_enemies.begin() ; colony != m_enemies.end() ; colony++) {
                (*colony) -> m_enemiesAmount-- ;
                (*colony) -> computeRatio() ;
            }
        }


    public:
                                                                 /** GETTERS **/
        /** @brief Return the list of the colonies created. */
        inline static const std::vector<ColonyData*>& getAllColonies() {
            return ColonyData::ALL_COLONIES ;
        }

        /**
         * @brief Get the name of the colony.
         * @return The name of the colony.
         */
        inline const std::string& getName() const {
            return m_name ;
        }

        /**
         * @brief Get the strategy of the colony.
         * @return The strategy of the colony.
         */
        inline ColonyStrategy* getStrategy() const {
            return m_strategy ;
        }

        /**
         * @brief Get the level of the colony.
         * @return The level of the colony.
         */
        inline unsigned short getLevel() const {
            return m_level ;
        }

        /**
         * @brief Get the list of alive members.
         * @return The list of alive members.
         */
        inline const std::set<unsigned long>& getAliveMembers() const {
            return m_membersAlive ;
        }

        /**
         * @brief Get the list of KO members.
         * @return The list of KO members.
         */
        inline const std::set<unsigned long>& getKOMembers() const {
            return m_membersKO ;
        }

        /**
         * @brief Get the count of alive members.
         * @return The count of alive members.
         */
        inline unsigned char countAliveMembers() const {
            return m_membersAlive.size() ;
        }

        /**
         * @brief Get the count of KO members.
         * @return The count of KO members.
         */
        inline unsigned char countKOMembers() const {
            return m_membersKO.size() ;
        }

        /**
         * @brief Get the list of enemy colonies.
         * @return The list of enemy colonies.
         */
        inline const std::set<ColonyData*>& getEnemies() const {
            return m_enemies ;
        }

        /**
         * @brief Get the amount of enemy colonies.
         * @return The amount of enemy colonies.
         */
        inline unsigned short countEnemyColonies() const {
            return m_enemies.size() ;
        }

        /**
         * @brief Get the amount of enemy characters.
         * @return The amount of enemy characters.
         */
        inline unsigned short countAliveEnemyCharacters() const {
            return m_enemiesAmount ;
        }

        /**
         * @brief Return the ratio of alive allies on alive enemies.
         * @return The ratio multiplied by 100 as an integer value.
         */
        inline short getRatioSituation() {
            return m_situationRatio ;
        }

        /**
         * @brief Get data on the colony to fight.
         * @return Data on the colony to fight.
         */
        inline ColonyData* getToFight() {
            if (m_toFight == 0 || m_toFight -> getLevel() == 0) {
                m_toFight = getStrongestEnemie() ;
            }

            return m_toFight ;
        }

        /**
         * @brief Get data on the strongest colony.
         * @return Data on the strongest colony.
         */
        inline ColonyData* getStrongestEnemie() {
            ColonyData* most = 0 ;

            if (m_enemies.size() > 0) {
                std::set<ColonyData*>::iterator enemy ;
                unsigned short max = 0 ;

                bool destroy ;
                unsigned short level ;
                for (enemy = m_enemies.begin() ; enemy != m_enemies.end() ; enemy++) {
                    destroy = (*enemy) -> m_isToBeDestroyed ;
                    level = ((*enemy) -> getLevel()) ;

                    if ((destroy == false) && (level > max)) {
                        most = (*enemy) ;
                        max = level ;
                    }
                }

                #ifdef DEBUG_MODE
                    if (most != 0) {
                        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                         << getName()
                                         << " gets strongest enemy "
                                         << (most -> m_name) ;
                        LogGen::print() ;
                    }
                    else {
                        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                         << getName()
                                         << " has not found an enemy colony!" ;
                        LogGen::print() ;
                    }
                #endif

            }

            return most ;
        }

        /** @brief To know if the colony will be destroyed soon. */
        inline bool isToBeDestroyed() {
            return m_isToBeDestroyed ;
        }


                                                                 /** SETTERS **/
        /**
         * @brief Set the name of the colony.
         * @param name  The new name of the colony.
         */
        inline void rename(const std::string& name) {
            assert(name.size() != 0) ;
            m_name = name ;
        }

        /**
         * @brief Set the level of the colony.
         * @param level     Computed level of the colony.
         */
        inline void setLevel(short level) {
            assert(level > -1) ;   // to prevent bad cast from signed to unsigned

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName()
                                 << " updates level "
                                 << level ;
                LogGen::print() ;
            #endif

            m_level = level ;
        }

        /**
         * @brief When a character is KO, it is translated from the "alive"
         *        members of the colony to the "KO" ones.
         * @param member    The character to translate.
         */
        inline void setAliveToKOMembers(unsigned long member) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName()
                                 << " sets alive to KO "
                                 << member ;
                LogGen::print() ;
            #endif

            m_membersKO.insert(member) ;
            m_membersAlive.erase(member) ;
            decreaseEnemiesCharacters() ;
            notifyObservers() ;
            computeRatio() ;
        }

        /**
         * @brief When a character is revived, it is translated from the "KO"
         *        members of the colony to the "alive" ones.
         * @param member    The character to translate.
         */
        inline void setKOToAliveMembers(unsigned long member) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << getName()
                                 << " sets KO to alive "
                                 << member ;
                LogGen::print() ;
            #endif

            m_membersAlive.insert(member) ;
            m_membersKO.erase(member) ;
            increaseEnemiesCharacters() ;
            notifyObservers() ;
            computeRatio() ;
        }

        /** @brief To know if the colony will be destroyed soon. */
        inline void setToDestroy() {
            assert(m_isToBeDestroyed == false) ;
            m_isToBeDestroyed = true ;
        }
} ;

#endif
