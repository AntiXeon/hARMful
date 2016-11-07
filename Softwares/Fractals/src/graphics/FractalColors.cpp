#include <Fractals/graphics/FractalColors.h>
#include <DOOMful/debug/Log.h>
#include <stddef.h>
#include <iostream>

using namespace std ;


FractalColors::FractalColors(const int& fractalIterations) {
    m_colors.resize(fractalIterations) ;
}

FractalColors::~FractalColors() {
    m_colors.clear() ;
}


void FractalColors::setColors(const std::vector<PixelColor>& keyColors) {
    // m_mutex.lock() ;
        // Not enough or too much colors...
        if ((keyColors.size() <= 1) || (keyColors.size() > m_colors.size())) {
            return ;
        }

        size_t keyColorsCount = keyColors.size() ;
        size_t colorsSlots = m_colors.size() ;
        int stepAmount = colorsSlots / (keyColorsCount - 1) ;

        // Generate the shadings between key colors.
        size_t maxKeyColorIndex = keyColorsCount - 1 ;
        for (size_t keyColorIndex = 0 ; keyColorIndex < maxKeyColorIndex ; ++keyColorIndex) {
            PixelColor startColor = keyColors[keyColorIndex] ;
            PixelColor endColor = keyColors[keyColorIndex + 1] ;

            // Red component
            float diffRed = (endColor.getRed() - startColor.getRed()) / 255.f ;
            float incrementRed = diffRed / stepAmount ;
            float accRed = startColor.getRed() ;
            // Green component
            float diffGreen = (endColor.getGreen() - startColor.getGreen()) / 255.f ;
            float incrementGreen = diffGreen / stepAmount ;
            float accGreen = startColor.getGreen() ;
            // Blue component
            float diffBlue = (endColor.getBlue() - startColor.getBlue()) / 255.f ;
            float incrementBlue = diffBlue / stepAmount ;
            float accBlue = startColor.getBlue() ;

            // Interpolation of colors
            m_colors[keyColorIndex * stepAmount] = startColor ;
            for (int step = 1 ; step < stepAmount ; ++step) {
                accRed += (incrementRed * 255.f) ;
                accGreen += (incrementGreen * 255.f) ;
                accBlue += (incrementBlue * 255.f) ;

                int colorIndex = step + (stepAmount * keyColorIndex) ;
                // cout << "Set color[" << colorIndex << "] --> (" << (int)accRed << "," << (int)accGreen << "," << (int)accBlue << ")" << endl ;
                m_colors[colorIndex] = PixelColor(accRed, accGreen, accBlue) ;
            }
        }

        m_colors.back() = keyColors.back() ;

        // for (size_t i = 0 ; i < m_colors.size() ; i++) {
        //     cout << "Color @" << i << " = " << m_colors[i].getRed() << "," << m_colors[i].getGreen() << "," << m_colors[i].getBlue() << endl ;
        // }

    // m_mutex.unlock() ;
}

PixelColor& FractalColors::getColor(const unsigned int& iteration) {
    // m_mutex.lock() ;

        PixelColor* color ;
        if (iteration < m_colors.size()) {
            color = &m_colors[iteration] ;
        }
        else {
            color = &m_colors.back() ;
        }
    // m_mutex.unlock() ;

    return *color ;
}

unsigned int FractalColors::getFractalIterations() const {
    m_mutex.lock() ;
        size_t iterations = m_colors.size() ;
    m_mutex.unlock() ;
    return iterations ;
}
