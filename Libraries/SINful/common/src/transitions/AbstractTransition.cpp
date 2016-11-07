#include <transitions/AbstractTransition.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractTransition::AbstractTransition(
                                           const int& last,
                                           IInterpolation* interpolation
                                          ) : m_timeLast(last),
                                              m_timeCurrent(0),
                                              m_interpolation(interpolation) {}

    AbstractTransition::~AbstractTransition() {}


                                                             /*** UTILITIES ***/
    void AbstractTransition::increaseTime(const unsigned int& increase) {
        m_timeCurrent += increase ;
    }


                                                     /*** SETTERS / GETTERS ***/
    Mind::Scalar AbstractTransition::getInterpolation() {
        return (m_interpolation -> interpolate(m_timeLast, m_timeCurrent)) ;
    }

} ;
