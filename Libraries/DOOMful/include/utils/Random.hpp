#ifndef __DOOM__RANDOM__
#define __DOOM__RANDOM__


namespace Doom {
    /**
     * Simple random generation. This one does not use C++11 capabilities to
     * keep things as simple as possible.
     */
    namespace Random {
        /**
         * Initialize the generation of random numbers.
         * @param force [description]
         */
        void Initialize(bool force = false) ;

        /**
         * Get an integer value from the pseudo-random value generator.
         * @return The generated value.
         */
        int GetInteger() ;

        /**
         * Get an integer value into an interval from the pseudo-random value
         * generator.
         * @param  min Minimal value of the interval.
         * @param  max Maximal value of the interval.
         * @return     The generated value. If @a min >= @a max, 0 is returned.
         */
        int GetInteger(int min, int max) ;

        /**
         * Get a float value normalized from the pseudo-random value generator.
         * @return     The generated value, the value is between 0 and 1.
         */
        float GetNormalizedFloat() ;
    }
}


#endif
