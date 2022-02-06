#include "ecs/system/System.hpp"
#include "BANEStrings.hpp"

using namespace Bane ;

void System::link(System* system) {
    m_linkedSystems[system -> m_name] = system ;
}

void System::unlink(const std::string& systemName) {
    m_linkedSystems.erase(systemName) ;
}

void System::unlink(const System* system) {
    m_linkedSystems.erase(system -> m_name) ;
}
