#include <matrices/SquareMatrixf.hpp>
#include <Math.hpp>

namespace Mind {
    const size_t SquareMatrixf::MaximalDataSize = SIMD::Vector4f::size() ;

    SquareMatrixf::SquareMatrixf(
        const size_t size,
        const Scalar value
    ) : m_size(size),
        m_defaultValue(value) {
        for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
            m_data[row] = SIMD::Vector4f(value) ;
        }
    }

    void SquareMatrixf::identity() {
        for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
            Scalar columns[] = { 0.f, 0.f, 0.f, 0.f } ;

            if (row < m_size) {
                columns[row] = 1.f ;
            }

            m_data[row] = SIMD::Vector4f(
                columns[0],
                columns[1],
                columns[2],
                columns[3]
            ) ;
        }
    }

    Scalar SquareMatrixf::trace() const {
        #ifdef USE_SIMD
            return SIMD::Vector4f(
                at(0,0),
                at(1,1),
                at(2,2),
                at(3,3)
            ).horizontalAdd() ;
        #else
            return at(0,0) + at(1,1) + at(2,2) + at(3,3) ;
        #endif
    }

    unsigned int SquareMatrixf::size() const {
        return m_size ;
    }

    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) {
        s << "SquareMatrixf: " << std::endl ;
            unsigned int size = p.size() ;
            for (unsigned int row = 0 ; row < size ; ++row) {
                s << "{ " ;
                float* values = (float*) p.m_data[row] ;
                for (unsigned int col = 0 ; col < size ; ++col) {
                    s << values[col] << " ; " ;
                }
                s << "}" << std::endl ;
            }
        s << std::endl ;
        return s ;
    }

    void SquareMatrixf::clearWith(const Scalar value) {
        Array4f values ;
        for (size_t col = 0 ; col < MaximalDataSize ; ++col) {
            if (col < m_size) {
                values[col] = value ;
            }
            else {
                values[col] = 0.f ;
            }
        }

        for (size_t row = 0 ; row < m_size ; ++row) {
            m_data[row].set(values) ;
        }
    }

    void SquareMatrixf::getData(Scalar* output) {
        size_t outputIndex = 0 ;
        for (size_t row = 0 ; row < m_size ; ++row) {
            float* rowValues = (float*) m_data[row] ;

            output[outputIndex]     = rowValues[0] ;
            output[outputIndex + 1] = rowValues[1] ;
            output[outputIndex + 2] = rowValues[2] ;
            output[outputIndex + 3] = rowValues[3] ;
            outputIndex += MaximalDataSize ;
        }
    }
} ;
