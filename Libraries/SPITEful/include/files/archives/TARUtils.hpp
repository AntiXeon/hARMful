#ifndef __SPITE__TAR_UTILS__
#define __SPITE__TAR_UTILS__

#include <utils/Platform.hpp>
#include <files/archives/TARData.hpp>
#include <string>
#include <vector>

namespace Spite {
    /**
     * TAR utils (load, save, ...).
     */
    class TARUtils final {
        public:
            /**
             * Load the content of a TAR archive in a TARData srtructure.
             */
            exported static TARData Load(const std::string& path) ;

            /**
             * Save a TAR archive from a TARData structure.
             */
            exported static void Save(
                TARData& tarData,
                const std::string& path
            ) ;
    } ;
}

#endif
