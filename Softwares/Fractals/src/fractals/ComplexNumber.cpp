#include <Fractals/fractals/ComplexNumber.h>

ComplexNumber::ComplexNumber(float real, float imaginary) {
    m_real = real ;
    m_imaginary = imaginary ;
}

ComplexNumber::~ComplexNumber() {}


float ComplexNumber::getReal() const {
    return m_real ;
}

float ComplexNumber::getImaginary() const {
    return m_imaginary ;
}

void ComplexNumber::setReal(const float& real) {
    m_real = real ;
}

void ComplexNumber::setImaginary(const float& imaginary) {
    m_imaginary = imaginary ;
}
