#include <utils/Random.hpp>
#include <cstdlib>
#include <ctime>

namespace Doom {
    namespace Random {
        /**
         * Avoid reinitializing.
         */
        static bool IsInitialized = false ;

        void Initialize(bool force) {
            if (!IsInitialized || force) {
                srand(time(nullptr)) ;
                IsInitialized = true ;
            }
        }

        int GetInteger() {
            return rand() ;
        }

        int GetInteger(int min, int max) {
            if (min >= max) {
                return 0 ;
            }

            int diff = max - min ;
            int random = (rand() % diff) + min ;
            return random ;
        }

        float GetNormalizedFloat() {
            const float MaxRandom = RAND_MAX ;
            float random = rand() ;
            return random / MaxRandom ;
        }
    }
}
