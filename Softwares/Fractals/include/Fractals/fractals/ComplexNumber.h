#ifndef __COMPLEX_NUMBER__
#define __COMPLEX_NUMBER__

/**
 * @brief   ComplexNumber is a complex number.
 *
 * @author  Denis CARLUS
 * @version 1.0     12/13/2015
 */
class ComplexNumber {
    private:
        /** @brief  Real part of the complex number. */
        float m_real ;

        /** @brief  Imaginary part of the complex number. */
        float m_imaginary ;


    public:
                                          	  /** CONSTRUCTION / DESTRUCTION **/
        /**
         * @brief   Creation of a ComplexNumber.
         * @param   real        Real part of the complex number.
         * @param   imaginary   Imaginary part of the complex number.
         */
        ComplexNumber(float real = 0.f, float imaginary = 0.f) ;

        /**
         * @brief   Destruction of the ComplexNumber.
         */
        virtual ~ComplexNumber() ;


                                                             	 /** GETTERS **/
        /**
         * @brief  Get the real part of the ComplexNumber.
         * @return Real part of the complex number.
         */
        float getReal() const ;

        /**
         * @brief  Get the imaginary part of the ComplexNumber.
         * @return Imaginary part of the complex number.
         */
        float getImaginary() const ;


                                                             	 /** SETTERS **/
        /**
         * @brief   Set the real part of the ComplexNumber.
         * @param   real    Real part of the complex number.
         */
        void setReal(const float& real) ;

        /**
         * @brief   Set the imaginary part of the ComplexNumber.
         * @param   real    Imaginary part of the complex number.
         */
        void setImaginary(const float& imaginary) ;
} ;

#endif
