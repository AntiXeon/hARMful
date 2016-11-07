#ifndef __AMMOSTOCK_H__
#define __AMMOSTOCK_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include <unordered_map>
#include "../weapons/firearm/Firearm.h"

class AmmoStock {
    private:
        /**
         * @brief Ensemble des differentes Ammo qu'un personnage possede (cle)
         *        et la quantite possedee (valeur).
         */
        std::unordered_map<Firearm*, unsigned short> m_ammo ;

    public:
        /**
         * @brief Construction d'un stock de munitions.
         */
        AmmoStock() ;

        /** @brief Destruction d'un stock de munitions. */
        virtual ~AmmoStock() ;


        /**
         * @brief Ajouter des munitions dans l'inventaire.
         * @param item      Les munitions a ajouter.
         * @param quantity  La quantite recuperee de ces munitions.
         */
        void add(Firearm* ammo, unsigned short quantity = 1) ;

        /**
         * @brief Drop the ammo of a weapon type.
         * @param ammo  Ammo of the weapon.
         */
        void drop(Firearm* ammo) {
            m_ammo.erase(ammo) ;
        }

        /**
         * @brief Utiliser des munitions presentes dans l'inventaire.
         * @param item      Les munitions utilises.
         * @param quantity  La quantite utilisee de ces munitions.
         * @return Renvoie la quantite effectivement utilisee (si l'utilisation
         *         requiert davantage d'objet que disponible par exemple).
         */
        unsigned short use(Firearm* ammo, unsigned short quantity = 1) ;

        /**
         * @brief Tester si des munitions sont stockees dans l'inventaire.
         * @param item      Les munitions dont il faut tester la presence.
         * @return TRUE si elles sont dans l'inventaire (quantite non nulle),
         *         FALSE si elles ne sont pas dans la map ou en quantite nulle.
         */
        bool have(Firearm* a) {
            return ((m_ammo.count(a) > 0) && (m_ammo[a] > 0)) ? true : false ;
        }

        /**
         * @brief Compter le nombre d'entrees pour les munitions possedees.
         * @return Le nombre de munitions differentes dans l'inventaire.
         */
        unsigned short countAmmo() const { return m_ammo.size() ; }
        /**
         * @brief Compter le nombre possede pour un type de balles.
         * @return Le nombre possede de balles en question.
         */
        unsigned short countAmmo(Firearm* a) {
            if (m_ammo.count(a) == 1) {
                unsigned short quantity = m_ammo[a] ;
                return quantity ;
            }
            return 0 ;
        }
} ;
#endif
