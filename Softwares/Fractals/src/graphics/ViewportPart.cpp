#include <Fractals/graphics/ViewportPart.h>
#include <DOOMful/utils/Processor.h>
#include <SDL2/SDL2_gfxPrimitives.h>


                                          	  /** CONSTRUCTION / DESTRUCTION **/
ViewportPart::ViewportPart(
		                   const int& x,
		                   const int& y,
		                   const int& width,
		                   const int& height
					   	  ) {
    m_position.setX(x) ;
    m_position.setY(y) ;
    m_dimension.setWidth(width) ;
    m_dimension.setHeight(height) ;

	m_pixels.resize(width * height) ;
}

ViewportPart::~ViewportPart() {
	m_pixels.clear() ;
}

                                                             	 /** SETTERS **/
void ViewportPart::setPixelColor(
                            const int& x,
                            const int& y,
                            const PixelColor& color
                           ) {
    // m_mutex.lock() ;
		m_pixels[x + (getWidth() * y)] = color ;
	// m_mutex.unlock() ;
}

                                                             	 /** GETTERS **/
int* ViewportPart::getPixels() const {
	return (int*) m_pixels.data() ;
}

int ViewportPart::getX() const {
    return m_position.getX() ;
}

int ViewportPart::getY() const {
    return m_position.getY() ;
}

int ViewportPart::getWidth() const {
    return m_dimension.getWidth() ;
}

int ViewportPart::getHeight() const {
    return m_dimension.getHeight() ;
}
