#include <utils/Chrono.hpp>

namespace Doom {
    Chrono::Chrono() {}

    Chrono::~Chrono() {}

    void Chrono::start() {
        m_start = std::chrono::system_clock::now() ;
        m_isStarted = true ;
    }

    void Chrono::stop() {
        m_end = std::chrono::system_clock::now() ;
        m_isStarted = false ;
    }

    bool Chrono::isStarted() const {
        return m_isStarted ;
    }
}
