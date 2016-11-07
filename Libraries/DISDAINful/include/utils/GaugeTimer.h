#ifndef __GAUGETIMER_H__
#define __GAUGETIMER_H__

#include "Timer.h"
#include <assert.h>

/**
 * @brief A gauge acts as a timer but the increment value may be higher than 1
 *		  and can change between each call.
 * @version 1.0 27/04/2013
 */
class GaugeTimer : public Timer {
	public:
		/**
		 * @brief Creation of the GaugeTimer.
		 * @param max	Maximal value of the gauge.
		 */
		GaugeTimer(int max) ;

		/** @brief Destruction of the GaugeTimer. */
		virtual ~GaugeTimer() ;


		/**
         * @brief Tell if the programmed time was reached. The counter is
         *        automatically reset when time is reached and the count
         *        restarts.
         * @param value		Value to modify the gauge state.
         * @return TRUE if the timer reached the end. FALSE else.
         */
        virtual inline bool isReady(int value) {
        	assert(value > -1) ;

            m_counter -= value ;
            if (m_counter < 1) {
                m_counter = m_initValue ;
                return true ;
            }
            return false ;
        }
} ;

#endif
