#include "BANEStrings.hpp"

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace BANEStrings {
    namespace Errors {
        const std::string ECS_Entity_AlreadyRegistered = i18n("The Entity ID is already registered!") ;
        const std::string ECS_Component_InvalidEntity = i18n("Invalid entity used to create a new Component!") ;
    }
}
