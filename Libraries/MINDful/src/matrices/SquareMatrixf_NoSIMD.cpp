#include <matrices/SquareMatrixf.hpp>
#include <Math.hpp>

#ifdef USE_NO_SIMD

namespace Mind {
    const size_t SquareMatrixf::MaximalDataSize = 4 ;

    SquareMatrixf::SquareMatrixf(
        const size_t size,
        const Scalar value
    ) : m_size(size),
        m_defaultValue(value) {
        for (size_t col = 0 ; col < size ; ++col) {
            for (size_t row = 0 ; row < size ; ++row) {
                m_data[row][col] = value ;
            }
        }
    }

    void SquareMatrixf::identity() {
        clearWith(0) ;

        size_t dimension = size() ;
        for (size_t diag = 0 ; diag < dimension ; ++diag) {
            m_data[diag][diag] = 1.f ;
        }
    }

    Scalar SquareMatrixf::trace() const {
        size_t dimension = size() ;
        Scalar trace = 0.f ;
        for (size_t diag = 0 ; diag < dimension ; ++diag) {
            trace += m_data[diag][diag] ;
        }

        return trace ;
    }

    size_t SquareMatrixf::size() const {
        return m_size ;
    }

    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) {
        s << "SquareMatrixf: " << std::endl ;
            size_t size = p.size() ;
            for (unsigned int row = 0 ; row < size ; ++row) {
                s << "{ " ;
                for (unsigned int col = 0 ; col < size ; ++col) {
                    s << p.m_data[row][col] << " ; " ;
                }
                s << "}" << std::endl ;
            }
        s << std::endl ;
        return s ;
    }

    void SquareMatrixf::clearWith(const Scalar value) {
        for (size_t col = 0 ; col < MaximalDataSize ; ++col) {
            for (size_t row = 0 ; row < MaximalDataSize ; ++row) {
                m_data[row][col] = value ;
            }
        }
    }

    void SquareMatrixf::getData(Scalar* output) {
        size_t outputIndex = 0 ;
        for (size_t row = 0 ; row < m_size ; ++row) {
            output[outputIndex]     = m_data[row][0] ;
            output[outputIndex + 1] = m_data[row][1] ;
            output[outputIndex + 2] = m_data[row][2] ;
            output[outputIndex + 3] = m_data[row][3] ;
            outputIndex += MaximalDataSize ;
        }
    }
} ;

#endif
