#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * @brief Timer turning on integer values.
 * @version 1.0 20/04/2013
 */
class Timer {
    protected:
        /** @brief Initialization value of the timer. */
        int m_initValue ;

        /** @brief Counter value, decreased. */
        int m_counter ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a timer. */
        Timer(int wait) ;

        /** @brief Destruction of a timer. */
        virtual ~Timer() ;


        /**
         * @brief Tell if the programmed time was reached. The counter is
         *        automatically reset when time is reached and the count
         *        restarts.
		 * @return TRUE if the timer reached the end. FALSE else.
         */
        virtual inline bool isReady() {
            m_counter-- ;
            if (m_counter < 1) {
                m_counter = m_initValue ;
                return true ;
            }
            return false ;
        }

        virtual inline void forceReady() {
            m_counter = 1 ;
        }
} ;

#endif
