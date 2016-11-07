#include <DOOMful/utils/Processor.h>
#include <DOOMful/utils/Thread.h>
#include <Fractals/fractals/Fractal.h>

                                          	  /** CONSTRUCTION / DESTRUCTION **/
Fractal::Fractal(
                 const Mind::Dimension2Df& spaceXBounds,
                 const Mind::Dimension2Df& spaceYBounds,
                 const ComplexNumber& seed
                ) {
    m_spaceXBounds = spaceXBounds ;
    m_spaceYBounds = spaceYBounds ;
    m_seed = seed ;

    CPU_InitInfo() ;
}

Fractal::~Fractal() {}

                                                                 /** SETTERS **/
void Fractal::setBounds(
                        const Mind::Dimension2Df& spaceXBounds,
                        const Mind::Dimension2Df& spaceYBounds
                       ) {
    m_spaceXBounds = spaceXBounds ;
    m_spaceYBounds = spaceYBounds ;
}

void Fractal::setSeed(const ComplexNumber& seed) {
    m_seed = seed ;
}
